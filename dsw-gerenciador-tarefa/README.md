# 📋 Gerenciador de Tarefas

Interface web para gerenciamento de tarefas, desenvolvida como atividade prática do componente curricular de **Desenvolvimento de Sistemas Web**.

O projeto implementa a estrutura visual de um sistema de tarefas com tela de login, formulário de cadastro de atividades e uma grade responsiva para exibição das tarefas cadastradas.

---

## ✨ Recursos implementados

- **Tela de login** — formulário de acesso com campos de usuário e senha.
- **Cadastro de tarefas** — formulário para criar novas atividades, com campo de título e seletor de prioridade (Baixa, Média, Alta).
- **Listagem de tarefas** — grade responsiva exibindo as tarefas cadastradas, com checkbox de conclusão e selo colorido indicando a prioridade de cada item.
- **Layout responsivo** — adapta-se a telas de celular, tablet e desktop (grid de 1, 2 ou 3 colunas conforme o tamanho da tela).

---

## 🛠️ Tecnologias utilizadas

| Tecnologia | Finalidade |
|---|---|
| **HTML5** | Estrutura semântica da página |
| **Tailwind CSS v4** (via CDN) | Estilização e responsividade |

---

## 🚀 Como testar localmente

Não é necessário instalar nada — o projeto usa apenas um arquivo HTML com o Tailwind carregado via CDN.

1. Baixe (ou clone) este repositório:
   ```bash
   git clone <url-do-seu-repositorio>
   ```
2. Entre na pasta do projeto:
   ```bash
   cd <nome-da-pasta>
   ```
3. Abra o arquivo `index.html` diretamente no navegador (basta dar dois cliques nele), ou use a extensão **Live Server** do VS Code para recarregamento automático.

> 💡 É necessário estar conectado à internet, pois o Tailwind CSS é carregado por CDN.

---

## 📁 Estrutura do projeto

```
.
├── index.html   # Página principal (login, cadastro e lista de tarefas)
└── README.md    # Documentação do projeto
```

---

## 📚 Contexto acadêmico

Projeto desenvolvido para a disciplina **Desenvolvimento de Sistemas Web** — 2026, como parte da atividade de implantação de interface e organização do ambiente de desenvolvimento no GitHub Codespaces.

**Professor:** Alexandre Bendlin