#include "graph.hpp"
#include <climits>
#include <queue>

using std::less;
using std::make_pair;
using std::max;
using std::min;
using std::priority_queue;

int Graph::widestPath(const int &source, const int &target) {
    // Inicializa maior gargalo para menos infinito
    vector<int> widest(this->g.size(), INT_MIN);

    // Use um heap para saber qual é o vérice com o maior gargalo até então
    priority_queue<pair<int, int>, vector<pair<int, int>>, less<>> heap;

    // Insira a fonte no heap
    heap.push(make_pair(0, source));

    widest[source] = INT_MAX;

    while (!heap.empty()) {
        int currentSource = heap.top().second;

        heap.pop();

        for (auto vertex : this->g[currentSource]) {
            int bottleneck = max(widest[vertex.second],
                                 min(widest[currentSource], vertex.first));

            if (bottleneck > widest[vertex.second]) {
                // Atualiza o gargalo
                widest[vertex.second] = bottleneck;

                // Coloque o vértice no heap
                heap.push(make_pair(bottleneck, vertex.second));
            }
        }
    }

    return widest[target];
}
