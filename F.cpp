#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int from;
    int to;
    int absorption; // 两个仓库的吸光能力乘积
};

bool compareEdges(const Edge& a, const Edge& b) {
    return a.absorption > b.absorption;
}

int main() {
    int n;
    cin >> n;

    vector<int> absorption(n + 1);
    vector<Edge> edges;

    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        edges.push_back({ a, b });
    }
    for (int i = 1; i <= n; i++) {
        cin >> absorption[i];
    }
    for (int i = 0; i < n - 1; i++) {
        edges[i].absorption = absorption[edges[i].from] * absorption[edges[i].to];
    }
    // 按照吸光能力乘积降序排序
    sort(edges.begin(), edges.end(), compareEdges);

    vector<bool> used(n + 1, false);
    int maxAbsorption = 0;

    for (const auto& edge : edges) {
        if (!used[edge.from] && !used[edge.to]) {
            maxAbsorption += edge.absorption;
            used[edge.from] = true;
            used[edge.to] = true;
            //cout << edge.from << edge.to << "  ";
        }
    }

    cout << maxAbsorption << endl;
}