# Relatório de Aprofundamento - Tutoria 7: Árvores Binárias

Miguel Wainstein
Implementação prática de Árvores Binárias de Busca (ABB) em linguagem C pura, explorando algoritmos 
de contagem de nós, busca de valores extremos (mínimo e máximo), remoção de nós em cenários variados 
e análise comparativa de eficiência estrutural frente à busca sequencial linear.

## Exercícios Concluídos
- [x] Exercício 1 — Cadastro de Alunos com Árvore Binária de Busca
- [x] Exercício 2 — Contando Elementos da Árvore
- [x] Exercício 3 — Menor e Maior Valor da Árvore
- [x] Exercício 4 — Removendo um Valor da Árvore
- [x] Exercício 5 — Comparando Busca Sequencial e Busca em Árvore

## Como Compilar e Executar os Exercícios
A partir do diretório raiz do projeto, execute os seguintes comandos no terminal:

```bash
# Exercício 1
gcc exercicio-01/main.c -o ex1.exe && ./ex1.exe

# Exercício 2
gcc exercicio-02/main.c -o ex2.exe && ./ex2.exe

# Exercício 3
gcc exercicio-03/main.c -o ex3.exe && ./ex3.exe

# Exercício 4
gcc exercicio-04/main.c -o ex4.exe && ./ex4.exe

# Exercício 5
gcc exercicio-05/main.c -o ex5.exe && ./ex5.exe

Respostas Teóricas e Análise CríticaDesafio Extra (Exercício 3) — 
Por que as buscas por menor e maior valor não precisam percorrer a árvore inteira?Devido à propriedade fundamental da Árvore Binária de Busca (ABB). Por definição de projeto, qualquer nó à esquerda de uma raiz contém um valor obrigatoriamente menor que ela, e qualquer nó à direita contém um valor obrigatoriamente maior. Portanto, o menor valor do sistema estará, sem exceções, no nó folha mais à esquerda possível, e o maior valor no nó mais à direita. O algoritmo só precisa seguir uma linha reta descendente, ignorando o restante da árvore ($O(\log n)$ no melhor caso).Perguntas Analíticas (Exercício 5)
1. Qual busca fez menos comparações?A Busca na Árvore Binária de Busca realizou consideravelmente menos comparações para localizar elementos situados nas porções finais do vetor (ex: 5 comparações contra 18 da busca sequencial).
2. A árvore sempre será melhor? Justifique.Não. A eficiência da árvore depende exclusivamente de quão bem distribuídos (balanceados) estão seus nós. Se a árvore estiver desorganizada e com formatos lineares, ela perderá sua performance lógica de busca.
3. O que pode acontecer se os valores forem inseridos já ordenados?Ocorre um problema crítico chamado Degeneração da Árvore. Se inserirmos dados já ordenados (como 10, 20, 30...), os elementos serão inseridos sequencialmente um abaixo do outro na subárvore direita. A árvore perde sua característica de bifurcação e se transforma estruturalmente em uma lista encadeada simples ($O(n)$), invalidando a vantagem de velocidade.
4. Como uma árvore balanceada ajudaria nesse caso?Estruturas de árvores auto-balanceadas (como as árvores AVL ou Red-Black) possuem algoritmos internos de rotação. Sempre que um nó é inserido e causa um desequilíbrio na altura de um dos lados, a árvore move os ponteiros e rearranja seus nós automaticamente. Isso garante que a altura seja mantida sempre o mais próxima possível de $\log_2 n$, impedindo a perda de performance mesmo se os dados entrarem em ordem estável.