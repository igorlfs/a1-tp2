#pragma once

#include <iostream>

using std::istream;

class Input {
  public:
    /// @brief Lê e garante que os parâmetros (número de cidades, número de
    /// rodovias e número de consultas) estão corretos
    /// @param _istream, arquivo de entrada
    static void readParameters(istream &_istream = std::cin);

    /// @brief Lê rodovias
    /// @param _istream, arquivo de entrada
    static void readRoads(istream &_istream = std::cin);

    /// @brief Lê consultas
    /// @param _istream, arquivo de entrada
    static void readQueries(istream &_istream = std::cin);
};
