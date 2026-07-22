template <typename T>
vector<vector<T>> floyd_warshall(const graph<T> &g) {
    int n = g.n;
    const T INF = numeric_limits<T>::max();
    vector<vector<T>> dist(n, vector<T>(n, INF));
    
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        for (int id : g.g[i]) {
            auto &e = g.edges[id];
            int to = e.from ^ e.to ^ i;
            dist[i][to] = min(dist[i][to], e.cost);
        }
    }
    
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            if (dist[i][k] == INF) continue;
            for (int j = 0; j < n; j++) {
                if (dist[k][j] == INF) continue;
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    
    return dist;
}
