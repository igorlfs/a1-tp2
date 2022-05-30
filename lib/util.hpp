#pragma once

#include <list>
#include <vector>

using std::list;
using std::pair;
using std::vector;

using graph = vector<list<pair<int, int>>>;

class Util {
  public:
    /// @brief cálcula o caminho de source a target em g com o maior gargalo
    /// @param g, grafo a ser caminhado
    /// @param source, vértice de início
    /// @param target, vértice de destino
    /// @return maior gargalo
    static int widestPath(const graph &g, const int &source, const int &target);
};
