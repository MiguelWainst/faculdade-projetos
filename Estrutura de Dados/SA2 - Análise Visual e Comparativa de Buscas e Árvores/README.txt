# Relatório Técnico - Análise Comparativa de Algoritmos de Busca

## 1. Tabela de Resultados

| Tamanho (N) | Tipo dos Dados | Valor Buscado | Posição | Busca Sequencial (comp.) | Busca Binária (comp.) | Árvore (comp.) | Altura da Árvore |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **100** | Ordenados | 2 | Início | 2 | 7 | 2 | **99** |
| **100** | Ordenados | 100 | Meio | 51 | 6 | 51 | **99** |
| **100** | Ordenados | 198 | Fim | 100 | 7 | 100 | **99** |
| **100** | Ordenados | -5 | Inexistente | 100 | 6 | 2 | **99** |
| **100** | Embaralhados | 2 | Início | 2 | 7 | 11 | **10** |
| **100** | Embaralhados | 100 | Meio | 51 | 6 | 5 | **10** |
| **100** | Embaralhados | 198 | Fim | 100 | 7 | 4 | **10** |
| **100** | Embaralhados | -5 | Inexistente | 100 | 6 | 7 | **10** |
| **1000** | Ordenados | 2 | Início | 2 | 10 | 2 | **999** |
| **1000** | Ordenados | 1000 | Meio | 501 | 9 | 501 | **999** |
| **1000** | Ordenados | 1998 | Fim | 1000 | 10 | 1000 | **999** |
| **1000** | Ordenados | -5 | Inexistente | 1000 | 9 | 2 | **999** |
| **1000** | Embaralhados | 2 | Início | 2 | 10 | 9 | **18** |
| **1000** | Embaralhados | 1000 | Meio | 501 | 9 | 8 | **18** |
| **1000** | Embaralhados | 1998 | Fim | 1000 | 10 | 4 | **18** |
| **1000** | Embaralhados | -5 | Inexistente | 1000 | 9 | 11 | **18** |

---

## 2. Análise Crítica (Perguntas)

### Qual algoritmo teve menos comparações na maioria dos testes?
A Busca Binária. Ela manteve uma média estável e baixíssima de comparações em quase todos os cenários. A Busca em Árvore só conseguiu igualar essa eficiência quando os dados foram inseridos de maneira embaralhada.

### A busca em árvore foi sempre melhor que a busca sequencial? Explique.
Não. Quando inserimos os dados de forma já ordenada, a árvore sofreu uma falha estrutural e virou uma lista encadeada. Nesses casos, para achar valores no meio ou no fim, ela fez exatamente a mesma quantidade absurda de comparações que a busca sequencial.

### O que aconteceu com a árvore quando os valores foram inseridos em ordem crescente?
Ela ficou totalmente torta e "degenerou". Como cada valor inserido era maior que o anterior, todos os novos nós foram criados apenas para o lado direito. A árvore perdeu seus galhos da esquerda e virou uma linha reta vertical de altura N-1 (altura 999 para N=1000).

### Por que a altura da árvore influencia diretamente a quantidade de comparações?
Porque cada nível que o algoritmo desce para procurar um número conta como uma comparação. Se a árvore for baixa e bem espalhada (como no caso embaralhado), o caminho até a base é curto. Se ela for gigante e esticada em linha reta (caso ordenado), o algoritmo terá que percorrer todos os nós um por um.

### Por que a busca binária exige dados ordenados?
Porque ela funciona dividindo o problema ao meio. Ela testa o valor do centro; se o que você procura for menor, ela descarta toda a metade direita. Se os dados estiverem bagunçados, ela não tem como garantir que os números da direita são maiores, tornando a lógica impossível.

### Qual estrutura você escolheria para um sistema que precisa buscar dados com frequência? Justifique.
Uma Árvore Binária de Busca Auto-Balanceada (como a Árvore AVL ou Red-Black). Elas possuem mecanismos automáticos que mudam os nós de lugar caso os dados entrem ordenados, garantindo que a árvore nunca entorte e mantenha sempre a velocidade máxima de busca.

### Qual é a relação entre esta atividade e o uso de índices em bancos de dados?
Os índices dos bancos de dados organizam as chaves das tabelas em formatos de árvores de alta performance (como as Árvores B+). Isso evita que o banco precise fazer uma busca sequencial lenta lendo milhões de linhas do disco rígido toda vez que um usuário faz uma pesquisa.

### O que uma árvore balanceada resolveria neste experimento?
Ela impediria a destruição de performance que aconteceu nos testes com dados ordenados. Mesmo se inseríssemos os dados em ordem crescente, ela giraria os ponteiros internamente para manter a árvore perfeitamente distribuída e com uma altura baixíssima (reduziria a altura de 999 para cerca de 10).