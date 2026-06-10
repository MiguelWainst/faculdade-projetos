/*
=============================================================================
  BATALHA NAVAL - v2.0
  Desenvolvido com base no jogo original
  Arquivo unico em C
=============================================================================

  REGRAS ORIGINAIS IMPLEMENTADAS:
  - Navios de diferentes tamanhos (Porta-Avioes=4, Cruzador=3, Destroyer=2)
  - Um navio so afunda quando TODOS os seus segmentos sao atingidos
  - Apos um acerto o jogador ganha outro turno (tiro extra)
  - Apos um erro o turno passa para o adversario (no modo 2 jogadores)
  - No modo 1 jogador: o computador tambem atira com IA basica
  - Modo 2 jogadores: turnos alternados em sistema "passe e jogue"
  - Bonus de vida: com 1 vida restante, 3 acertos consecutivos = +1 vida

  NAVIOS:
  - 1x Porta-Avioes  (tamanho 4) = P
  - 2x Cruzador      (tamanho 3) = C
  - 3x Destroyer     (tamanho 2) = D

  DIFICULDADES (afetam vidas do jogador, vidas da IA no single player,
                e numero de navios da IA):
  - Facil:   5 vidas, IA com 3 vidas
  - Medio:   3 vidas, IA com 2 vidas
  - Dificil: 2 vidas, IA com 1 vida
  - Guerra:  1 vida,  IA com 1 vida (IA com mira assistida)
=============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* =========================================================================
   CONSTANTES E DEFINES
   ========================================================================= */

#define LINHAS      10
#define COLUNAS     10

/* Celulas do mapa */
#define VAZIO       ' '
#define NAVIO       'N'   /* invisivel para o adversario */
#define ACERTO      '*'
#define ERRO        'o'
#define AFUNDADO    'X'

/* Tipos de navio */
#define QTD_TIPOS   3
#define QTD_NAVIOS  6   /* 1 + 2 + 3 */

/* Cores ANSI */
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"
#define BG_BLUE     "\033[44m"
#define BG_CYAN     "\033[46m"
#define BG_RED      "\033[41m"
#define BG_GREEN    "\033[42m"
#define BG_DARK     "\033[100m"
#define BLINK       "\033[5m"

/* =========================================================================
   ESTRUTURAS
   ========================================================================= */

typedef struct {
    int lin[4];         /* linhas dos segmentos */
    int col[4];         /* colunas dos segmentos */
    int tamanho;        /* 2, 3 ou 4 */
    int acertos;        /* quantos segmentos ja foram atingidos */
    int afundado;       /* 1 = afundado */
    char nome[20];      /* nome do navio */
    char simbolo;       /* P, C ou D */
} Navio;

typedef struct {
    char mapa[LINHAS][COLUNAS];         /* mapa real (com navios) */
    char mapa_visivel[LINHAS][COLUNAS]; /* mapa que o adversario ve */
    Navio navios[QTD_NAVIOS];
    int  qtd_navios;
    int  navios_afundados;
    int  vidas;
    int  vidas_max;
    int  acertos_consecutivos; /* para bonus de vida */
    int  total_acertos;
    int  total_erros;
    char nome[30];
} Jogador;

typedef struct {
    int dificuldade;    /* 1=Facil 2=Medio 3=Dificil 4=Guerra */
    int modo;           /* 1=Single 2=Dois Jogadores */
    int vidas_j1;
    int vidas_j2;       /* vidas iniciais para cada modo */
} Config;

/* =========================================================================
   PROTOTIPAGEM
   ========================================================================= */

/* Utilitarios */
void  limpar_tela();
void  pausar();
void  nova_seed();
int   rand_range(int min, int max);

/* Interface */
void  tela_titulo();
void  tela_vitoria(Jogador *vencedor, Jogador *perdedor);
void  tela_game_over(Jogador *perdedor);
void  exibir_mapa_duplo(Jogador *ataque, Jogador *defesa, int mostrar_navios_defesa);
void  exibir_mapa_simples(Jogador *j, int esconder_navios);
void  exibir_status(Jogador *j1, Jogador *j2);
void  barra_vidas(int vidas, int max);
void  mensagem_acerto(Navio *n, int afundou);
void  mensagem_erro();
void  mensagem_bonus_vida();

/* Configuracao */
Config menu_principal();
int    menu_dificuldade();
int    menu_modo();

/* Logica do jogo */
void   inicializar_jogador(Jogador *j, char *nome, int vidas);
void   inicializar_mapas(Jogador *j);
int    posicionar_navio_valido(Jogador *j, int idx, int lin, int col, int dir, int tam);
void   posicionar_navios_manual(Jogador *j);
void   posicionar_navios_auto(Jogador *j);
int    processar_tiro(Jogador *atirador, Jogador *alvo, int lin, int col);
void   marcar_afundado(Jogador *alvo, Navio *n);
int    verificar_vitoria(Jogador *j);
void   turno_jogador(Jogador *atirador, Jogador *alvo);
void   turno_ia(Jogador *ia, Jogador *alvo, int dificuldade);

/* Conversao */
int   col_para_idx(char c);
char  idx_para_col(int i);
int   validar_coordenada(char *str, int *lin, int *col);

/* IA */
int  ia_escolher_tiro(Jogador *ia, Jogador *alvo, int *lin, int *col, int dificuldade);

/* =========================================================================
   DADOS DOS NAVIOS
   ========================================================================= */

typedef struct { int tam; char nome[20]; char simbolo; } TipoNavio;

TipoNavio TIPOS_NAVIOS[QTD_TIPOS] = {
    {4, "Porta-Avioes", 'P'},
    {3, "Cruzador",     'C'},
    {2, "Destroyer",    'D'}
};

int QTDS_NAVIOS[QTD_TIPOS] = {1, 2, 3}; /* 1 Porta-Avioes, 2 Cruzadores, 3 Destroyers */

/* =========================================================================
   UTILITARIOS
   ========================================================================= */

void limpar_tela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("\n" CYAN "  [ Pressione ENTER para continuar... ]" RESET);
    while(getchar() != '\n');
}

void nova_seed() {
    srand((unsigned)time(NULL));
}

int rand_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

/* =========================================================================
   INTERFACE VISUAL
   ========================================================================= */

void tela_titulo() {
    limpar_tela();
    printf(CYAN BOLD);
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                              ║\n");
    printf("  ║    ██████╗  █████╗ ████████╗ █████╗ ██╗     ██╗  ██╗█████╗ ║\n");
    printf("  ║    ██╔══██╗██╔══██╗╚══██╔══╝██╔══██╗██║     ██║  ██║██╔══██╗║\n");
    printf("  ║    ██████╔╝███████║   ██║   ███████║██║     ███████║███████║║\n");
    printf("  ║    ██╔══██╗██╔══██║   ██║   ██╔══██║██║     ██╔══██║██╔══██║║\n");
    printf("  ║    ██████╔╝██║  ██║   ██║   ██║  ██║███████╗██║  ██║██║  ██║║\n");
    printf("  ║    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═╝  ╚═╝║\n");
    printf("  ║                                                              ║\n");
    printf(BLUE "  ║       " YELLOW "███╗   ██╗ █████╗ ██╗   ██╗ █████╗ ██╗     " BLUE "           ║\n");
    printf("  ║       " YELLOW "████╗  ██║██╔══██╗██║   ██║██╔══██╗██║" BLUE "              ║\n");
    printf("  ║       " YELLOW "██╔██╗ ██║███████║██║   ██║███████║██║" BLUE "              ║\n");
    printf("  ║       " YELLOW "██║╚██╗██║██╔══██║╚██╗ ██╔╝██╔══██║██║" BLUE "              ║\n");
    printf("  ║       " YELLOW "██║ ╚████║██║  ██║ ╚████╔╝ ██║  ██║███████╗" BLUE "         ║\n");
    printf("  ║       " YELLOW "╚═╝  ╚═══╝╚═╝  ╚═╝  ╚═══╝  ╚═╝  ╚═╝╚══════╝" BLUE "        ║\n");
    printf(CYAN "  ║                                                              ║\n");
    printf("  ║            " RESET WHITE "~ Afunde a frota inimiga! ~" CYAN "                     ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n");
}

void barra_vidas(int vidas, int max) {
    printf("[");
    for(int i = 0; i < max; i++) {
        if(i < vidas)
            printf(RED "♥" RESET);
        else
            printf(BG_DARK " " RESET);
    }
    printf("] %d/%d", vidas, max);
}

void exibir_status(Jogador *j1, Jogador *j2) {
    printf(CYAN "  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║ " BOLD YELLOW "%-20s" RESET CYAN "                  " BOLD YELLOW "%-20s" RESET CYAN "    ║\n",
           j1->nome, j2->nome);
    printf("  ║ " RESET "Vidas: ");
    barra_vidas(j1->vidas, j1->vidas_max);
    printf(CYAN "                 " RESET "Vidas: ");
    barra_vidas(j2->vidas, j2->vidas_max);
    printf(CYAN " ║\n");
    printf("  ║ " RESET "Acertos: " GREEN "%-4d" RESET " Erros: " RED "%-4d" RESET CYAN "          " RESET "Acertos: " GREEN "%-4d" RESET " Erros: " RED "%-4d" RESET CYAN "  ║\n",
           j1->total_acertos, j1->total_erros,
           j2->total_acertos, j2->total_erros);
    printf("  ╚══════════════════════════════════════════════════════════════╝\n" RESET);
}

void exibir_mapa_simples(Jogador *j, int esconder_navios) {
    printf(CYAN BOLD "       A   B   C   D   E   F   G   H   I   J\n" RESET);
    printf(CYAN "     ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐\n" RESET);

    for(int i = 0; i < LINHAS; i++) {
        printf(CYAN "  %2d │" RESET, i+1);
        for(int j2 = 0; j2 < COLUNAS; j2++) {
            char c = esconder_navios ?
                     j->mapa_visivel[i][j2] :
                     j->mapa[i][j2];

            /* Substituir NAVIO invisivel pelo mapa_visivel se escondendo */
            if(esconder_navios && j->mapa_visivel[i][j2] == VAZIO)
                c = VAZIO;
            else if(!esconder_navios && j->mapa[i][j2] == NAVIO)
                c = 'n'; /* mostra navio */

            switch(c) {
                case ACERTO:
                    printf(RED BOLD " * " RESET);
                    break;
                case AFUNDADO:
                    printf(BG_RED BOLD " X " RESET);
                    break;
                case ERRO:
                    printf(BLUE " o " RESET);
                    break;
                case 'n':
                    printf(GREEN " ■ " RESET);
                    break;
                case NAVIO:
                    /* no mapa visivel nao aparece */
                    printf(BG_BLUE "   " RESET);
                    break;
                default:
                    printf(BG_BLUE "   " RESET);
                    break;
            }
            printf(CYAN "│" RESET);
        }
        if(i < LINHAS - 1)
            printf("\n" CYAN "     ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n" RESET);
    }
    printf("\n" CYAN "     └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘\n" RESET);
}

void exibir_mapa_duplo(Jogador *ataque, Jogador *defesa, int mostrar_navios_defesa) {
    printf(BOLD YELLOW "  ╔═══════════════════════════════╗     ╔═══════════════════════════════╗\n");
    printf("  ║    SEU MAPA                   ║     ║    INIMIGO                    ║\n");
    printf("  ╚═══════════════════════════════╝     ╚═══════════════════════════════╝\n" RESET);

    /* Cabecalho colunas */
    printf(CYAN BOLD "       A   B   C   D   E   F   G   H   I   J" RESET);
    printf("           ");
    printf(CYAN BOLD "A   B   C   D   E   F   G   H   I   J\n" RESET);

    printf(CYAN "     ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐" RESET);
    printf("           ");
    printf(CYAN "┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐\n" RESET);

    for(int i = 0; i < LINHAS; i++) {
        /* Mapa do jogador (mostra seus navios) */
        printf(CYAN "  %2d │" RESET, i+1);
        for(int j2 = 0; j2 < COLUNAS; j2++) {
            char c = ataque->mapa[i][j2];
            switch(c) {
                case ACERTO:   printf(RED BOLD " * " RESET);    break;
                case AFUNDADO: printf(BG_RED BOLD " X " RESET); break;
                case ERRO:     printf(BLUE " o " RESET);        break;
                case NAVIO:    printf(GREEN " ■ " RESET);       break;
                default:       printf(BG_BLUE "   " RESET);     break;
            }
            printf(CYAN "│" RESET);
        }

        printf("      ");

        /* Mapa do inimigo (mostra apenas tiros) */
        printf(CYAN "  %2d │" RESET, i+1);
        for(int j2 = 0; j2 < COLUNAS; j2++) {
            char c;
            if(mostrar_navios_defesa)
                c = defesa->mapa[i][j2];
            else
                c = defesa->mapa_visivel[i][j2];

            switch(c) {
                case ACERTO:   printf(RED BOLD " * " RESET);    break;
                case AFUNDADO: printf(BG_RED BOLD " X " RESET); break;
                case ERRO:     printf(BLUE " o " RESET);        break;
                case NAVIO:    printf(GREEN " ■ " RESET);       break;
                default:       printf(BG_BLUE "   " RESET);     break;
            }
            printf(CYAN "│" RESET);
        }
        printf("\n");

        if(i < LINHAS - 1) {
            printf(CYAN "     ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤" RESET);
            printf("           ");
            printf(CYAN "├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤\n" RESET);
        }
    }
    printf(CYAN "     └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘" RESET);
    printf("           ");
    printf(CYAN "└───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘\n" RESET);
}

void mensagem_acerto(Navio *n, int afundou) {
    if(afundou) {
        printf(BG_RED BOLD "\n  ╔══════════════════════════════════════╗" RESET "\n");
        printf(BG_RED BOLD "  ║  💥  NAVIO AFUNDADO: %-14s  ║" RESET "\n", n->nome);
        printf(BG_RED BOLD "  ╚══════════════════════════════════════╝" RESET "\n");
        printf(GREEN BOLD "  ► Voce ganha um tiro extra!\n" RESET);
    } else {
        printf(YELLOW BOLD "\n  ┌─────────────────────────────┐\n");
        printf("  │  💥  ACERTO! Tiro extra!    │\n");
        printf("  └─────────────────────────────┘\n" RESET);
    }
}

void mensagem_erro() {
    printf(BLUE "\n  ┌────────────────────────────┐\n");
    printf("  │  〇  AGUA! Vez do inimigo.  │\n");
    printf("  └────────────────────────────┘\n" RESET);
}

void mensagem_bonus_vida() {
    printf(GREEN BLINK BOLD "\n  ╔══════════════════════════════════════════╗\n");
    printf("  ║  ♥  BONUS! 3 ACERTOS SEGUIDOS = +1 VIDA ♥  ║\n");
    printf("  ╚══════════════════════════════════════════╝\n" RESET);
}

void tela_vitoria(Jogador *vencedor, Jogador *perdedor) {
    limpar_tela();
    printf(YELLOW BOLD);
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                              ║\n");
    printf("  ║    ██╗   ██╗██╗████████╗ ██████╗ ██████╗ ██╗ █████╗         ║\n");
    printf("  ║    ██║   ██║██║╚══██╔══╝██╔═══██╗██╔══██╗██║██╔══██╗        ║\n");
    printf("  ║    ██║   ██║██║   ██║   ██║   ██║██████╔╝██║███████║        ║\n");
    printf("  ║    ╚██╗ ██╔╝██║   ██║   ██║   ██║██╔══██╗██║██╔══██║        ║\n");
    printf("  ║     ╚████╔╝ ██║   ██║   ╚██████╔╝██║  ██║██║██║  ██║        ║\n");
    printf("  ║      ╚═══╝  ╚═╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝  ╚═╝        ║\n");
    printf("  ║                                                              ║\n");
    printf("  ╚══════════════════════════════════════════════════════════════╝\n");
    printf(RESET GREEN BOLD "\n  ► Vencedor: %s\n" RESET, vencedor->nome);
    printf(RED "  ► Derrotado: %s\n" RESET, perdedor->nome);
    printf(WHITE "\n  Estatisticas de %s:\n", vencedor->nome);
    printf("  Acertos: " GREEN "%d" RESET " | Erros: " RED "%d" RESET "\n\n",
           vencedor->total_acertos, vencedor->total_erros);

    /* Mostra o mapa do perdedor revelado */
    printf(CYAN BOLD "  Frota inimiga revelada:\n" RESET);
    exibir_mapa_simples(perdedor, 0);
}

void tela_game_over(Jogador *perdedor) {
    limpar_tela();
    printf(RED BOLD);
    printf("\n");
    printf("  ╔══════════════════════════════════════════════════════════╗\n");
    printf("  ║                                                          ║\n");
    printf("  ║   ██████╗  █████╗ ███╗   ███╗███████╗                   ║\n");
    printf("  ║  ██╔════╝ ██╔══██╗████╗ ████║██╔════╝                   ║\n");
    printf("  ║  ██║  ███╗███████║██╔████╔██║█████╗                     ║\n");
    printf("  ║  ██║   ██║██╔══██║██║╚██╔╝██║██╔══╝                     ║\n");
    printf("  ║  ╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗                   ║\n");
    printf("  ║   ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝                   ║\n");
    printf("  ║                                                          ║\n");
    printf("  ║   ██████╗ ██╗   ██╗███████╗██████╗ ██╗                  ║\n");
    printf("  ║  ██╔═══██╗██║   ██║██╔════╝██╔══██╗██║                  ║\n");
    printf("  ║  ██║   ██║██║   ██║█████╗  ██████╔╝██║                  ║\n");
    printf("  ║  ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗╚═╝                  ║\n");
    printf("  ║  ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║██╗                  ║\n");
    printf("  ║   ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝╚═╝                  ║\n");
    printf("  ╚══════════════════════════════════════════════════════════╝\n");
    printf(RESET "\n" RED "  %s foi eliminado!\n" RESET, perdedor->nome);
}

/* =========================================================================
   MENUS
   ========================================================================= */

int menu_dificuldade() {
    int op;
    printf(CYAN BOLD "\n  ╔═══════════════════════════════════════╗\n");
    printf("  ║        ESCOLHA A DIFICULDADE          ║\n");
    printf("  ╠═══════════════════════════════════════╣\n");
    printf("  ║  " GREEN "(1) FACIL   " RESET CYAN "- 5 vidas | IA: facil   ║\n");
    printf("  ║  " YELLOW "(2) MEDIO   " RESET CYAN "- 3 vidas | IA: media   ║\n");
    printf("  ║  " RED "(3) DIFICIL " RESET CYAN "- 2 vidas | IA: esperta ║\n");
    printf("  ║  " RED BLINK "(4) GUERRA  " RESET CYAN "- 1 vida  | IA: hunter  ║\n");
    printf("  ╚═══════════════════════════════════════╝\n" RESET);
    printf("  >> ");
    scanf("%d", &op);
    while(getchar() != '\n');
    if(op < 1 || op > 4) op = 2;
    return op;
}

int menu_modo() {
    int op;
    printf(CYAN BOLD "\n  ╔═══════════════════════════════════════╗\n");
    printf("  ║            MODO DE JOGO               ║\n");
    printf("  ╠═══════════════════════════════════════╣\n");
    printf("  ║  " GREEN "(1) SINGLE PLAYER" RESET CYAN " - vs Computador   ║\n");
    printf("  ║  " YELLOW "(2) 2 JOGADORES  " RESET CYAN " - vs Amigo        ║\n");
    printf("  ╚═══════════════════════════════════════╝\n" RESET);
    printf("  >> ");
    scanf("%d", &op);
    while(getchar() != '\n');
    if(op < 1 || op > 2) op = 1;
    return op;
}

Config menu_principal() {
    Config cfg;
    tela_titulo();
    cfg.modo        = menu_modo();
    cfg.dificuldade = menu_dificuldade();

    /* Vidas baseadas na dificuldade */
    switch(cfg.dificuldade) {
        case 1: cfg.vidas_j1 = 5; cfg.vidas_j2 = 3; break;
        case 2: cfg.vidas_j1 = 3; cfg.vidas_j2 = 2; break;
        case 3: cfg.vidas_j1 = 2; cfg.vidas_j2 = 1; break;
        case 4: cfg.vidas_j1 = 1; cfg.vidas_j2 = 1; break;
        default: cfg.vidas_j1 = 3; cfg.vidas_j2 = 2;
    }
    return cfg;
}

/* =========================================================================
   INICIALIZACAO
   ========================================================================= */

void inicializar_mapas(Jogador *j) {
    for(int i = 0; i < LINHAS; i++)
        for(int k = 0; k < COLUNAS; k++) {
            j->mapa[i][k]         = VAZIO;
            j->mapa_visivel[i][k] = VAZIO;
        }
}

void inicializar_jogador(Jogador *j, char *nome, int vidas) {
    strncpy(j->nome, nome, 29);
    j->vidas              = vidas;
    j->vidas_max          = vidas;
    j->qtd_navios         = 0;
    j->navios_afundados   = 0;
    j->acertos_consecutivos = 0;
    j->total_acertos      = 0;
    j->total_erros        = 0;
    inicializar_mapas(j);
}

/* =========================================================================
   POSICIONAMENTO DE NAVIOS
   ========================================================================= */

int posicionar_navio_valido(Jogador *j, int idx, int lin, int col, int dir, int tam) {
    /* dir: 0=horizontal, 1=vertical */
    /* Verifica limites */
    if(dir == 0 && col + tam > COLUNAS) return 0;
    if(dir == 1 && lin + tam > LINHAS)  return 0;

    /* Verifica colisao e zona de exclusao (1 casa de distancia) */
    for(int s = 0; s < tam; s++) {
        int l = lin + (dir == 1 ? s : 0);
        int c = col + (dir == 0 ? s : 0);

        /* Zona de exclusao de 1 casa ao redor */
        for(int dl = -1; dl <= 1; dl++)
            for(int dc = -1; dc <= 1; dc++) {
                int nl = l + dl, nc = c + dc;
                if(nl >= 0 && nl < LINHAS && nc >= 0 && nc < COLUNAS)
                    if(j->mapa[nl][nc] == NAVIO) return 0;
            }
    }

    /* Posiciona */
    for(int s = 0; s < tam; s++) {
        j->navios[idx].lin[s] = lin + (dir == 1 ? s : 0);
        j->navios[idx].col[s] = col + (dir == 0 ? s : 0);
        j->mapa[j->navios[idx].lin[s]][j->navios[idx].col[s]] = NAVIO;
    }
    j->navios[idx].tamanho  = tam;
    j->navios[idx].acertos  = 0;
    j->navios[idx].afundado = 0;
    return 1;
}

void posicionar_navios_auto(Jogador *j) {
    int idx = 0;
    for(int t = 0; t < QTD_TIPOS; t++) {
        for(int q = 0; q < QTDS_NAVIOS[t]; q++) {
            int colocado = 0;
            j->navios[idx].tamanho = TIPOS_NAVIOS[t].tam;
            strncpy(j->navios[idx].nome, TIPOS_NAVIOS[t].nome, 19);
            j->navios[idx].simbolo = TIPOS_NAVIOS[t].simbolo;

            while(!colocado) {
                int lin = rand_range(0, LINHAS - 1);
                int col = rand_range(0, COLUNAS - 1);
                int dir = rand_range(0, 1);
                colocado = posicionar_navio_valido(j, idx, lin, col, dir, TIPOS_NAVIOS[t].tam);
            }
            idx++;
        }
    }
    j->qtd_navios = idx;
}

void exibir_legenda_posicionamento() {
    printf(CYAN BOLD "\n  LEGENDA DOS NAVIOS:\n" RESET);
    printf(GREEN "  ■ " RESET "= Seu navio posicionado\n");
    printf(CYAN "  ╔══════════════════════════════════════════════════╗\n");
    printf("  ║  Navio           │ Tam │ Qtd │ Simbolo          ║\n");
    printf("  ╠══════════════════════════════════════════════════╣\n");
    printf("  ║  Porta-Avioes    │  4  │  1  │   P              ║\n");
    printf("  ║  Cruzador        │  3  │  2  │   C              ║\n");
    printf("  ║  Destroyer       │  2  │  3  │   D              ║\n");
    printf("  ╚══════════════════════════════════════════════════╝\n" RESET);
    printf("  Formato de entrada: " YELLOW "COLUNA LINHA DIRECAO\n" RESET);
    printf("  Ex: " GREEN "A 3 H" RESET " (coluna A, linha 3, Horizontal)\n");
    printf("  Ex: " GREEN "B 5 V" RESET " (coluna B, linha 5, Vertical)\n\n");
}

void posicionar_navios_manual(Jogador *j) {
    int idx = 0;

    printf(CYAN BOLD "\n  ══════════════════════════════════════════\n");
    printf("    POSICIONANDO NAVIOS: %s\n", j->nome);
    printf("  ══════════════════════════════════════════\n" RESET);

    exibir_legenda_posicionamento();

    for(int t = 0; t < QTD_TIPOS; t++) {
        for(int q = 0; q < QTDS_NAVIOS[t]; q++) {
            j->navios[idx].tamanho = TIPOS_NAVIOS[t].tam;
            strncpy(j->navios[idx].nome, TIPOS_NAVIOS[t].nome, 19);
            j->navios[idx].simbolo = TIPOS_NAVIOS[t].simbolo;

            int colocado = 0;
            while(!colocado) {
                limpar_tela();
                printf(CYAN BOLD "  Posicionando navios de: " YELLOW "%s\n\n" RESET, j->nome);
                exibir_legenda_posicionamento();
                printf(CYAN BOLD "  Mapa atual:\n" RESET);
                exibir_mapa_simples(j, 0);

                printf(YELLOW BOLD "\n  >> Posicione: %s (tamanho %d) [%d/%d]\n" RESET,
                       TIPOS_NAVIOS[t].nome, TIPOS_NAVIOS[t].tam,
                       q+1, QTDS_NAVIOS[t]);
                printf("  Coluna (A-J), Linha (1-10), Direcao (H/V): ");

                char col_c, dir_c;
                int  lin_i;
                if(scanf(" %c %d %c", &col_c, &lin_i, &dir_c) != 3) {
                    while(getchar() != '\n');
                    printf(RED "  Entrada invalida!\n" RESET);
                    continue;
                }
                while(getchar() != '\n');

                int col_i = col_para_idx(col_c);
                int dir_i = (dir_c == 'h' || dir_c == 'H') ? 0 : 1;
                int lin_m = lin_i - 1;

                if(col_i < 0 || lin_m < 0 || lin_m >= LINHAS) {
                    printf(RED "  Coordenada invalida! Tente novamente.\n" RESET);
                    pausar();
                    continue;
                }

                if(!posicionar_navio_valido(j, idx, lin_m, col_i, dir_i, TIPOS_NAVIOS[t].tam)) {
                    printf(RED "  Posicao invalida! Fora dos limites ou colisao com outro navio.\n" RESET);
                    pausar();
                } else {
                    colocado = 1;
                    printf(GREEN "  Navio posicionado com sucesso!\n" RESET);
                }
            }
            idx++;
        }
    }
    j->qtd_navios = idx;

    limpar_tela();
    printf(CYAN BOLD "  Mapa final de %s:\n" RESET, j->nome);
    exibir_mapa_simples(j, 0);
    printf(GREEN BOLD "\n  Todos os navios posicionados!\n" RESET);
    pausar();
}

/* =========================================================================
   LOGICA DO JOGO
   ========================================================================= */

int col_para_idx(char c) {
    if(c >= 'a' && c <= 'j') return c - 'a';
    if(c >= 'A' && c <= 'J') return c - 'A';
    return -1;
}

char idx_para_col(int i) {
    return 'A' + i;
}

void marcar_afundado(Jogador *alvo, Navio *n) {
    for(int s = 0; s < n->tamanho; s++)
        alvo->mapa[n->lin[s]][n->col[s]] = AFUNDADO;
    /* Atualiza mapa visivel */
    for(int s = 0; s < n->tamanho; s++)
        alvo->mapa_visivel[n->lin[s]][n->col[s]] = AFUNDADO;
    alvo->navios_afundados++;
}

/*
  Retorna:
   0 = erro (agua)
   1 = acerto (navio atingido mas nao afundou)
   2 = navio afundado
*/
int processar_tiro(Jogador *atirador, Jogador *alvo, int lin, int col) {
    /* Ja atirado aqui? */
    if(alvo->mapa_visivel[lin][col] == ACERTO  ||
       alvo->mapa_visivel[lin][col] == AFUNDADO ||
       alvo->mapa_visivel[lin][col] == ERRO) {
        printf(YELLOW "  Voce ja atirou aqui! Tente outra coordenada.\n" RESET);
        return -1; /* tiro invalido, nao conta */
    }

    if(alvo->mapa[lin][col] == NAVIO) {
        /* Acerto! Marca nos dois mapas */
        alvo->mapa[lin][col]         = ACERTO;
        alvo->mapa_visivel[lin][col] = ACERTO;
        atirador->total_acertos++;
        atirador->acertos_consecutivos++;

        /* Verifica se afundou o navio */
        for(int n = 0; n < alvo->qtd_navios; n++) {
            if(alvo->navios[n].afundado) continue;
            for(int s = 0; s < alvo->navios[n].tamanho; s++) {
                if(alvo->navios[n].lin[s] == lin && alvo->navios[n].col[s] == col) {
                    alvo->navios[n].acertos++;
                    if(alvo->navios[n].acertos == alvo->navios[n].tamanho) {
                        alvo->navios[n].afundado = 1;
                        marcar_afundado(alvo, &alvo->navios[n]);
                        return 2; /* afundou */
                    }
                    return 1; /* acertou mas nao afundou */
                }
            }
        }
        return 1;
    } else {
        /* Erro */
        alvo->mapa[lin][col]         = ERRO;
        alvo->mapa_visivel[lin][col] = ERRO;
        atirador->total_erros++;
        atirador->acertos_consecutivos = 0;
        atirador->vidas--;
        return 0;
    }
}

int verificar_vitoria(Jogador *j) {
    return (j->navios_afundados >= j->qtd_navios);
}

/* =========================================================================
   IA
   ========================================================================= */

/* Estado da IA para modo "cacar" */
static int ia_modo_caca    = 0;    /* 0=busca, 1=caca */
static int ia_alvo_lin     = -1;
static int ia_alvo_col     = -1;
static int ia_dir          = -1;   /* 0=horiz, 1=vert */
static int ia_dir_step     = 1;
static int ia_tentativas   = 0;

void ia_resetar_caca() {
    ia_modo_caca  = 0;
    ia_alvo_lin   = -1;
    ia_alvo_col   = -1;
    ia_dir        = -1;
    ia_dir_step   = 1;
    ia_tentativas = 0;
}

int ia_escolher_tiro(Jogador *ia __attribute__((unused)), Jogador *alvo, int *lin, int *col, int dificuldade) {
    int tentativas = 0;

    /* Dificuldade 4 (Guerra): IA inteligente com modo caca */
    if(dificuldade == 4 || dificuldade == 3) {

        /* Modo caca: ja acertou um navio, tenta afundar */
        if(ia_modo_caca && ia_alvo_lin >= 0) {
            /* Tenta direcoes em torno do alvo */
            int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};
            int d_start = (ia_dir >= 0) ? ia_dir * 2 : 0;

            for(int d = 0; d < 4; d++) {
                int nd = (d_start + d) % 4;
                int nl = ia_alvo_lin + dirs[nd][0] * ia_dir_step;
                int nc = ia_alvo_col + dirs[nd][1] * ia_dir_step;

                if(nl >= 0 && nl < LINHAS && nc >= 0 && nc < COLUNAS &&
                   alvo->mapa_visivel[nl][nc] == VAZIO) {
                    *lin = nl;
                    *col = nc;
                    ia_dir = nd / 2;
                    return 1;
                }
            }
            /* Sem opcao no modo caca, volta para busca */
            ia_resetar_caca();
        }

        /* Modo busca: xadrez (atira em casas alternadas para maior eficiencia) */
        int max_try = 200;
        do {
            *lin = rand_range(0, LINHAS - 1);
            *col = rand_range(0, COLUNAS - 1);
            tentativas++;
            if(tentativas > max_try) break;
        } while(alvo->mapa_visivel[*lin][*col] != VAZIO ||
                (dificuldade == 4 && ((*lin + *col) % 2 != 0)));
        return 1;
    }

    /* Dificuldades 1 e 2: aleatorio */
    int max_try = 200;
    do {
        *lin = rand_range(0, LINHAS - 1);
        *col = rand_range(0, COLUNAS - 1);
        tentativas++;
        if(tentativas > max_try) break;
    } while(alvo->mapa_visivel[*lin][*col] != VAZIO);
    return 1;
}

/* =========================================================================
   TURNOS
   ========================================================================= */

void turno_jogador(Jogador *atirador, Jogador *alvo) {
    int disparando = 1;

    while(disparando) {
        limpar_tela();
        printf(YELLOW BOLD "\n  ══ VEZ DE: %s ══\n\n" RESET, atirador->nome);
        exibir_status(atirador, alvo);
        printf("\n");
        exibir_mapa_duplo(atirador, alvo, 0);

        /* Exibe status de navios inimigos */
        printf(CYAN "\n  Navios inimigos: ");
        for(int n = 0; n < alvo->qtd_navios; n++) {
            if(alvo->navios[n].afundado)
                printf(RED "%-12s(X) " RESET, alvo->navios[n].nome);
            else
                printf(GREEN "%-12s(%d/%d) " RESET, alvo->navios[n].nome,
                       alvo->navios[n].acertos, alvo->navios[n].tamanho);
        }
        printf("\n");

        /* Coleta coordenada */
        int lin = -1, col = -1;
        int valido = 0;
        while(!valido) {
            printf(WHITE "\n  Digite a coordenada (ex: B5 ou b5): " RESET);
            char entrada[10];
            if(scanf("%9s", entrada) != 1) { while(getchar()!='\n'); continue; }
            while(getchar() != '\n');

            if(strlen(entrada) < 2) { printf(RED "  Entrada invalida!\n" RESET); continue; }

            col = col_para_idx(entrada[0]);
            lin = atoi(entrada + 1) - 1;

            if(col < 0 || lin < 0 || lin >= LINHAS) {
                printf(RED "  Coordenada invalida! Use A-J e 1-10.\n" RESET);
                continue;
            }
            valido = 1;
        }

        int resultado = processar_tiro(atirador, alvo, lin, col);
        if(resultado == -1) continue; /* tiro invalido, tenta de novo */

        if(resultado == 0) {
            mensagem_erro();
            /* Perde vida ja foi decrementado em processar_tiro */
            if(atirador->vidas <= 0) {
                pausar();
                return;
            }
            pausar();
            disparando = 0; /* fim do turno */
        } else {
            /* Acerto */
            Navio *nav_atingido = NULL;
            for(int n = 0; n < alvo->qtd_navios; n++) {
                if(alvo->navios[n].afundado &&
                   alvo->mapa[alvo->navios[n].lin[0]][alvo->navios[n].col[0]] == AFUNDADO) {
                    /* Pega o ultimo afundado */
                    if(resultado == 2) nav_atingido = &alvo->navios[n];
                }
            }
            /* Encontra navio atingido mais recente */
            for(int n = 0; n < alvo->qtd_navios; n++) {
                if(resultado == 2 && alvo->navios[n].afundado &&
                   (alvo->navios[n].lin[0] == lin || alvo->navios[n].col[0] == col)) {
                }
            }

            if(resultado == 2) {
                /* Acha qual navio afundou */
                for(int n = 0; n < alvo->qtd_navios; n++) {
                    if(alvo->navios[n].afundado && alvo->navios[n].acertos == alvo->navios[n].tamanho) {
                        for(int s = 0; s < alvo->navios[n].tamanho; s++) {
                            if(alvo->navios[n].lin[s] == lin && alvo->navios[n].col[s] == col) {
                                nav_atingido = &alvo->navios[n];
                                break;
                            }
                        }
                    }
                    if(nav_atingido) break;
                }
                if(!nav_atingido) {
                    for(int n = 0; n < alvo->qtd_navios; n++) {
                        if(alvo->navios[n].afundado) {
                            nav_atingido = &alvo->navios[n];
                        }
                    }
                }
                mensagem_acerto(nav_atingido, 1);
            } else {
                mensagem_acerto(NULL, 0);
            }

            /* Bonus de vida: 1 vida + 3 acertos consecutivos */
            if(atirador->vidas == 1 && atirador->acertos_consecutivos >= 3) {
                atirador->vidas++;
                if(atirador->vidas > atirador->vidas_max)
                    atirador->vidas = atirador->vidas_max + 1; /* pode ultrapassar max */
                atirador->acertos_consecutivos = 0;
                mensagem_bonus_vida();
            }

            /* Verifica vitoria */
            if(verificar_vitoria(alvo)) {
                pausar();
                return;
            }

            printf(YELLOW "  Voce ganhou um tiro extra!\n" RESET);
            pausar();
            /* Continua atirando */
        }
    }
}

void turno_ia(Jogador *ia, Jogador *alvo, int dificuldade) {
    int disparando = 1;

    while(disparando) {
        int lin, col;
        ia_escolher_tiro(ia, alvo, &lin, &col, dificuldade);

        printf(CYAN BOLD "\n  [IA] %s atira em %c%d\n" RESET,
               ia->nome, idx_para_col(col), lin + 1);

        int resultado = processar_tiro(ia, alvo, lin, col);
        if(resultado == -1) continue;

        if(resultado == 0) {
            printf(BLUE "  [IA] Errou! Agua.\n" RESET);
            ia_resetar_caca();
            pausar();
            disparando = 0;
        } else if(resultado == 1) {
            printf(YELLOW "  [IA] ACERTOU seu navio! Atira de novo...\n" RESET);
            /* Ativa modo caca */
            if(!ia_modo_caca) {
                ia_modo_caca = 1;
                ia_alvo_lin  = lin;
                ia_alvo_col  = col;
            }
            ia_dir_step++;

            /* Verifica game over */
            if(alvo->vidas <= 0) { pausar(); return; }
            pausar();
            /* Continua atirando */
        } else {
            printf(RED "  [IA] Afundou seu %s!\n" RESET,
                   /* procura navio afundado */
                   alvo->navios[alvo->navios_afundados - 1].nome);
            ia_resetar_caca();
            /* Bonus de vida IA */
            if(ia->vidas == 1 && ia->acertos_consecutivos >= 3) {
                ia->vidas++;
                ia->acertos_consecutivos = 0;
            }
            if(alvo->vidas <= 0 || verificar_vitoria(alvo)) { pausar(); return; }
            pausar();
        }
    }
}

/* =========================================================================
   MAIN GAME LOOP
   ========================================================================= */

void jogo_single_player(Config *cfg) {
    Jogador j1, ia;
    char nome[30];

    limpar_tela();
    printf(YELLOW BOLD "\n  Digite seu nome: " RESET);
    scanf("%29s", nome);
    while(getchar() != '\n');

    inicializar_jogador(&j1, nome, cfg->vidas_j1);
    inicializar_jogador(&ia, "COMPUTADOR", cfg->vidas_j2);

    /* Posicionamento */
    limpar_tela();
    printf(CYAN BOLD "\n  Como deseja posicionar seus navios?\n" RESET);
    printf(GREEN "  (1) Manualmente\n" RESET);
    printf(YELLOW "  (2) Automaticamente\n" RESET);
    printf("  >> ");
    int op;
    scanf("%d", &op);
    while(getchar() != '\n');

    if(op == 1)
        posicionar_navios_manual(&j1);
    else
        posicionar_navios_auto(&j1);

    posicionar_navios_auto(&ia);

    /* Loop do jogo */
    int rodando = 1;
    while(rodando) {
        /* Turno do jogador */
        turno_jogador(&j1, &ia);

        if(verificar_vitoria(&ia)) {
            tela_vitoria(&j1, &ia);
            rodando = 0;
            break;
        }
        if(j1.vidas <= 0) {
            tela_game_over(&j1);
            /* Mostra mapa da IA */
            printf(CYAN "\n  Frota inimiga era:\n" RESET);
            exibir_mapa_simples(&ia, 0);
            rodando = 0;
            break;
        }

        /* Turno da IA */
        limpar_tela();
        printf(RED BOLD "\n  ══ VEZ DO COMPUTADOR ══\n\n" RESET);
        exibir_status(&ia, &j1);
        printf("\n");
        exibir_mapa_simples(&j1, 0);
        turno_ia(&ia, &j1, cfg->dificuldade);

        if(verificar_vitoria(&j1)) {
            /* Improvavel: todos navios da IA afundados antes */
            tela_vitoria(&ia, &j1);
            rodando = 0;
            break;
        }
        if(j1.vidas <= 0) {
            tela_game_over(&j1);
            printf(CYAN "\n  Frota inimiga era:\n" RESET);
            exibir_mapa_simples(&ia, 0);
            rodando = 0;
            break;
        }
    }

    pausar();
}

void jogo_dois_jogadores(Config *cfg) {
    Jogador j1, j2;
    char nome1[30], nome2[30];

    limpar_tela();
    printf(YELLOW BOLD "\n  Nome do Jogador 1: " RESET);
    scanf("%29s", nome1);
    while(getchar() != '\n');
    printf(YELLOW BOLD "  Nome do Jogador 2: " RESET);
    scanf("%29s", nome2);
    while(getchar() != '\n');

    inicializar_jogador(&j1, nome1, cfg->vidas_j1);
    inicializar_jogador(&j2, nome2, cfg->vidas_j1);

    /* Posicionamento J1 */
    limpar_tela();
    printf(CYAN BOLD "\n  %s: Como deseja posicionar seus navios?\n" RESET, j1.nome);
    printf(GREEN "  (1) Manualmente\n" RESET);
    printf(YELLOW "  (2) Automaticamente\n" RESET);
    printf("  >> ");
    int op;
    scanf("%d", &op);
    while(getchar() != '\n');
    if(op == 1) posicionar_navios_manual(&j1);
    else        posicionar_navios_auto(&j1);

    /* Transicao */
    limpar_tela();
    printf(YELLOW BOLD "\n  Passe o computador para %s!\n" RESET, j2.nome);
    printf(CYAN "  (O mapa de %s nao sera revelado)\n" RESET, j1.nome);
    pausar();

    /* Posicionamento J2 */
    limpar_tela();
    printf(CYAN BOLD "\n  %s: Como deseja posicionar seus navios?\n" RESET, j2.nome);
    printf(GREEN "  (1) Manualmente\n" RESET);
    printf(YELLOW "  (2) Automaticamente\n" RESET);
    printf("  >> ");
    scanf("%d", &op);
    while(getchar() != '\n');
    if(op == 1) posicionar_navios_manual(&j2);
    else        posicionar_navios_auto(&j2);

    /* Transicao */
    limpar_tela();
    printf(YELLOW BOLD "\n  Passem o computador para %s para comecar!\n" RESET, j1.nome);
    pausar();

    /* Loop do jogo */
    int vez = 1; /* 1 = j1, 2 = j2 */
    int rodando = 1;

    while(rodando) {
        if(vez == 1) {
            turno_jogador(&j1, &j2);

            if(verificar_vitoria(&j2)) {
                tela_vitoria(&j1, &j2);
                rodando = 0;
                break;
            }
            if(j1.vidas <= 0) {
                tela_game_over(&j1);
                rodando = 0;
                break;
            }
            if(j2.vidas <= 0) {
                tela_vitoria(&j1, &j2);
                rodando = 0;
                break;
            }

            /* Transicao de turno */
            limpar_tela();
            printf(YELLOW BOLD "\n  Passe o computador para %s!\n" RESET, j2.nome);
            pausar();
            vez = 2;
        } else {
            turno_jogador(&j2, &j1);

            if(verificar_vitoria(&j1)) {
                tela_vitoria(&j2, &j1);
                rodando = 0;
                break;
            }
            if(j2.vidas <= 0) {
                tela_game_over(&j2);
                rodando = 0;
                break;
            }
            if(j1.vidas <= 0) {
                tela_vitoria(&j2, &j1);
                rodando = 0;
                break;
            }

            /* Transicao de turno */
            limpar_tela();
            printf(YELLOW BOLD "\n  Passe o computador para %s!\n" RESET, j1.nome);
            pausar();
            vez = 1;
        }
    }

    pausar();
}

/* =========================================================================
   MAIN
   ========================================================================= */

int main() {
    nova_seed();

    int jogar_novamente = 1;
    while(jogar_novamente) {
        Config cfg = menu_principal();

        if(cfg.modo == 1)
            jogo_single_player(&cfg);
        else
            jogo_dois_jogadores(&cfg);

        limpar_tela();
        printf(CYAN BOLD "\n  Deseja jogar novamente?\n" RESET);
        printf(GREEN "  (1) Sim\n" RESET);
        printf(RED   "  (2) Nao\n" RESET);
        printf("  >> ");
        int op;
        scanf("%d", &op);
        while(getchar() != '\n');
        jogar_novamente = (op == 1);
    }

    limpar_tela();
    printf(CYAN BOLD "\n  Obrigado por jogar Batalha Naval!\n\n" RESET);
    return 0;
}