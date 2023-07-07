#include "data.h"
#include <ilcplex/ilocplex.h>

int main() {
    // Lê os dados do arquivo "data.txt"
    Data data("data.txt");

    // Imprime os dados carregados para verificação
    data.printData();

    // Cria o ambiente CPLEX
    IloEnv env;

    try {
        // Cria as variáveis do modelo. Cada nó no grafo é representado por uma variável binária x[i],
        // onde x[i] = 1 significa que o nó i é ativado inicialmente, e x[i] = 0 significa que não é.
        // Como a numeração dos nós começa a partir do 1, criamos um vetor com 'num_nodes+1' elementos
        // e ignoramos o primeiro elemento.
        IloBoolVarArray x(env, data.num_nodes+1);

        // Cria o modelo de programação linear
        IloModel model(env);

        // Função objetivo: Minimizar o número de nós iniciais.
        // Isso é feito somando todas as variáveis x[i], pois cada x[i] = 1 representa um nó inicial.
        IloExpr obj(env);
        for (int i = 1; i <= data.num_nodes; ++i) {
            obj += x[i];
        }
        model.add(IloMinimize(env, obj));
        obj.end();

        // Restrições: Para cada nó j, ou j está no conjunto inicial (ou seja, x[j] = 1),
        // ou pelo menos um dos vizinhos de j está no conjunto inicial.
        // Isso é verificado criando uma soma de todos os x[i] para os nós i que são vizinhos de j,
        // e então restringindo que x[j] deve ser maior ou igual a 1 menos essa soma.
        // Assim, se nenhum vizinho de j estiver no conjunto inicial (ou seja, a soma é 0), então x[j] deve ser 1.
        for (int j = 1; j <= data.num_nodes; ++j) {
            IloExpr sum(env);
            for (auto &edge : data.edges) {
                if (edge.second == j) {
                    sum += x[edge.first];
                }
            }
            model.add(x[j] >= 1 - sum);
            sum.end();
        }

        // Cria o objeto CPLEX a partir do modelo
        IloCplex cplex(model);
        
        // Resolve o modelo
        cplex.solve();

        // Gera o modelo em LP
        cplex.exportModel("model.lp");

        // Imprimir a solução
        // Para cada nó i, imprime se o nó i é ativado inicialmente (ou seja, x[i] = 1)
        for (int i = 1; i <= data.num_nodes; ++i) {
            std::cout << "Nó " << i << ": " << cplex.getValue(x[i]) << std::endl;
        }
    }
    // Caso ocorra um erro durante a resolução, imprime detalhes sobre o erro
    catch (IloException& e) {
        std::cerr << "Exception caught: " << e << std::endl;
    }
    // Caso ocorra algum outro erro não esperado, imprime uma mensagem de erro genérica
    catch (...) {
        std::cerr << "Unknown exception caught" << std::endl;
    }

    // Finaliza o ambiente CPLEX
    env.end();

    return 0;
}
