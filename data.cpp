#include "data.h"
#include <fstream>
#include <iostream>

Data::Data(const char* filename) {
    LoadData(filename);
}

void Data::LoadData(const char* filename) {
    std::ifstream file(filename);
    
    // Assumindo que o arquivo começa com o número de nós e arestas
    file >> num_nodes >> num_edges;

    // Carregar todas as arestas
    for (int i = 0; i < num_edges; ++i) {
        int start, end;
        file >> start >> end;
        edges.push_back(std::make_pair(start, end));
    }

    file.close();
}

void Data::printData() {
    std::cout << "Número de nós: " << num_nodes << std::endl;
    std::cout << "Número de arestas: " << num_edges << std::endl;
    std::cout << "Arestas: " << std::endl;
    for (auto &edge : edges) {
        std::cout << edge.first << " " << edge.second << std::endl;
    }
}
