#pragma once

#include <list>
#include <vector>

using std::list;
using std::pair;
using std::vector;

using graph = vector<list<pair<int, int>>>;

class Graph {
  public:
    /// Construtores

    /// @brief construtor padrão
    Graph() = default;
    /// @brief constrói grafo e define um tamanho
    /// @param size, tamanho a ser definido
    Graph(const int &size) { this->g.resize(size); }

    /// Getters

    /// @brief retorna o grafo
    /// @return grafo
    graph getGraph() { return this->g; }

    /// Setters

    /// @brief altera o valor do grafo
    /// @param h, novo valor do grafo
    void setGraph(const graph &h) { this->g = h; }

    /// Operações

    /// @brief redimensiona o grafo
    /// @param size, o novo tamanho do grafo
    void resize(const int &size) { this->g.resize(size); }

    /// @brief adicona uma nova aresta
    /// @param start, vértice de saída
    /// @param end, vértice de entrada
    /// @param weight, peso da aresta
    void addEdge(const int &start, const int &end, const int &weight) {
        this->g.at(start).emplace_back(weight, end);
    }

    /// @brief calcula o caminho com o maior gargalo
    /// @param source, vértice de início
    /// @param target, vértice de destino
    /// @return maior gargalo
    int widestPath(const int &source, const int &target);

  private:
    graph g;
};
