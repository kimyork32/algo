template <typename T>
vector<vector<T>> johnson(const digraph<T>& g) {
    int n = g.n;
    const T INF = numeric_limits<T>::max();
    
    digraph<T> ext_g(n + 1);
    for (const auto& e : g.edges) {
        ext_g.add(e.from, e.to, e.cost);
    }
    for (int i = 0; i < n; i++) {
        ext_g.add(n, i, 0);
    }
    
    vector<T> h = bellman_ford(ext_g, n);
    if (h.empty()) {
        return {};
    }
    
    digraph<T> reweighted_g(n);
    for (const auto& e : g.edges) {
        reweighted_g.add(e.from, e.to, e.cost + h[e.from] - h[e.to]);
    }
    
    vector<vector<T>> all_pairs_dist(n, vector<T>(n, INF));
    for (int u = 0; u < n; u++) {
        vector<T> dist_u = dijkstra(reweighted_g, u);
        for (int v = 0; v < n; v++) {
            if (dist_u[v] != INF) {
                all_pairs_dist[u][v] = dist_u[v] - h[u] + h[v];
            }
        }
    }
    
    return all_pairs_dist;
}
