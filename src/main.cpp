#include "graph.hpp"
#include "input.hpp"
#include <list>
#include <vector>

using namespace std;

int numOfCities;
int numOfRoads;
int numOfQueries;

const int MAX_CITIES = 100;
Graph roads(MAX_CITIES);

list<pair<int, int>> queries;

int main() {
    // Leitura da entrada
    Input::readParameters();
    Input::readRoads();
    Input::readQueries();

    // Impressão da saída
    for (auto query : queries) {
        cout << roads.widestPath(query.first, query.second) << endl;
    }
}
