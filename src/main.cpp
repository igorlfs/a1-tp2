#include "input.hpp"
#include "util.hpp"
#include <list>
#include <vector>

using namespace std;

using graph = vector<list<pair<int, int>>>;

int numOfCities;
int numOfRoads;
int numOfQueries;

const int MAX_CITIES = 100;
graph roads(MAX_CITIES);

list<pair<int, int>> queries;

int main() {
    // Leitura da entrada
    Input::readParameters();
    Input::readRoads();
    Input::readQueries();

    // Impressão da saída
    for (auto q : queries) {
        cout << Util::widestPath(roads, q.first, q.second) << endl;
    }
}
