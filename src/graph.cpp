#include "graph.hpp"
#include <climits>
#include <queue>

using std::greater;
using std::make_pair;
using std::max;
using std::min;
using std::priority_queue;

int Graph::widestPath(const int &source, const int &target) {
    // Inicializa maior gargalo para menos infinito
    vector<int> widest(this->g.size(), INT_MIN);

    // Use um heap para saber qual é o vérice com o maior gargalo até então
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> heap;

    heap.push(make_pair(0, source));

    widest[source] = INT_MAX;

    while (!heap.empty()) {
        pair<int, int> temp = heap.top();
        int currentSource = temp.second;

        heap.pop();

        for (auto vertex : this->g[currentSource]) {
            int distance = max(widest[vertex.second],
                               min(widest[currentSource], vertex.first));

            if (distance > widest[vertex.second]) {
                // Atualiza gargalo
                widest[vertex.second] = distance;
                heap.push(make_pair(distance, vertex.second));
            }
        }
    }

    return widest[target];
}
