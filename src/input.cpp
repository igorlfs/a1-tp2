#include "input.hpp"
#include "msgassert.hpp"
#include <algorithm>
#include <list>
#include <vector>

using std::list;
using std::min;
using std::pair;
using std::vector;

extern short numOfCities;
extern short numOfRoads;
extern short numOfQueries;

extern vector<list<pair<int, int>>> roads;

extern list<pair<int, int>> queries;

void Input::readParameters(istream &_istream) {
    _istream >> numOfCities >> numOfRoads >> numOfQueries;

    const int MAX_CITIES = 100;
    assert(numOfCities > 1,
           "Número de cidades " << numOfCities << " é menor do que o esperado");
    assert(numOfCities <= MAX_CITIES,
           "Número de cidades " << numOfCities << " é maior do que o esperado");

    const int MAX_ROADS_CEILING = 1000;
    short maxRoads = min(numOfCities * (numOfCities - 1), MAX_ROADS_CEILING);
    assert(numOfRoads > 0,
           "Número de rodovias " << numOfRoads << " é negativo");
    assert(numOfRoads <= maxRoads,
           "Número de rodovias " << numOfRoads << " é maior do que o esperado");

    const int MAX_QUERIES = 1000;
    assert(numOfQueries > 0,
           "Número de consultas " << numOfQueries << " não é positivo");
    assert(numOfQueries <= MAX_QUERIES, "Número de consultas "
                                            << numOfQueries
                                            << " é maior do que o esperado");
}

void Input::readRoads(istream &_istream) {
    for (int i = 0; i < numOfRoads; ++i) {
        int start;
        int end;
        int weight;

        _istream >> start >> end >> weight;

        assert(start > 0, "Vértice de partida " << start << " não positivo");
        assert(start <= numOfCities, "Vértice de partida "
                                         << start
                                         << " maior que o número de cidades "
                                         << numOfCities);
        assert(end > 0, "Vértice de chegada " << end << " não positiva");
        assert(end <= numOfCities,
               "Vértice de chegada " << end << " maior que o número de cidades "
                                     << numOfCities);

        assert(start != end,
               "Vértice de partida e vértice de chegada coincidem");

        const int MAX_WEIGHT = 1e6;
        assert(weight > 0, "Peso " << weight << " não positivo");
        assert(weight <= MAX_WEIGHT,
               "Peso " << weight << " maior que o máximo " << MAX_WEIGHT);

        roads[start].emplace_back(weight, end);
    }
}

void Input::readQueries(istream &_istream) {
    for (int i = 0; i < numOfQueries; ++i) {
        int start;
        int end;

        _istream >> start >> end;

        assert(start != end,
               "Vértice de partida e vértice de chegada coincidem");

        queries.emplace_back(start, end);
    }
}
