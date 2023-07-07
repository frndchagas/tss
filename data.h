#ifndef DATA_H
#define DATA_H

#include <vector>

class Data {
public:
    int num_nodes; // número de nós
    int num_edges; // número de arestas
    std::vector<std::pair<int, int>> edges; // lista de arestas

    Data(const char* filename); // construtor que carrega os dados a partir de um arquivo

    void LoadData(const char* filename); // função para carregar os dados
    void printData(); // função para imprimir os dados
};

#endif
