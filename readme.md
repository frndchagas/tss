# Target Set Selection (TSS)

O problema Target Set Selection (TSS) é um problema de otimização em grafos que consiste em selecionar um conjunto mínimo de nós iniciais de um grafo de tal forma que todos os nós serão eventualmente ativados, seguindo um determinado processo de propagação. 

## Exemplo

Um exemplo prático do problema TSS pode ser observado em uma rede social. Suponha que você seja um profissional de marketing tentando lançar uma nova campanha. A campanha precisa ser compartilhada pelo máximo de pessoas possíveis para ter um impacto significativo. No entanto, você só tem recursos para fazer a campanha chegar a um número limitado de pessoas inicialmente. Então, você precisa escolher cuidadosamente quem são essas pessoas iniciais. Com um entendimento adequado da rede (quem segue quem, quem tem mais seguidores, etc.), você pode usar o problema TSS para identificar os melhores candidatos para compartilhar inicialmente sua campanha, maximizando assim a disseminação da mesma.

## Exemplo de entrada

O arquivo `data.txt` contém a seguinte entrada, que representa um grafo com 5 nós e 4 arestas:

5 4
1 2
1 4
2 4
3 5


A primeira linha contém dois números, o número de nós (5) e o número de arestas (4). Cada uma das linhas seguintes contém uma aresta do grafo, representada por dois números que são os identificadores dos nós conectados por essa aresta.

## Resultado Ótimo para esta entrada

O melhor conjunto de nós iniciais para este grafo, de acordo com a formulação do problema que estamos usando (onde queremos minimizar o número de nós iniciais ativados, sujeito à condição de que todos os nós eventualmente sejam ativados), é {1,3}.

## Algoritmo usado

O problema é resolvido usando um algoritmo baseado em Programação Linear Inteira (ILP) que é implementado usando a biblioteca CPLEX da IBM. Cada nó no grafo é representado por uma variável binária x[i], onde x[i] = 1 significa que o nó i é ativado inicialmente, e x[i] = 0 significa que não é. A função objetivo é minimizar a soma de todas as variáveis x[i], e as restrições garantem que para cada nó j, ou j está no conjunto inicial, ou pelo menos um dos vizinhos de j está no conjunto inicial.
