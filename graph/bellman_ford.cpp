template <typename T>
// vector<T> bellman_ford(const graph<T>& g, vector<T>& pe, int start) { // pv: parent edge [-1..-1]
vector<T> bellman_ford(const graph<T> &g, int start) {
    assert(0 <= start && start < g.n);
    const T INF = numeric_limits<T>::max();
    vector<T> dist(g.n, INF);
    dist[start] = 0;
    
    bool any = true;
    for (int step = 0; step < g.n && any; step++) {
        any = false;
        for (int i = 0; i < g.n; i++) {
            if (dist[i] == INF) {
                continue;
            }
            for (int id : g.g[i]) {
                auto &e = g.edges[id];
                int to = e.from ^ e.to ^ i;
                if (dist[i] + e.cost < dist[to]) {
                    dist[to] = dist[i] + e.cost;
                    any = true;
                }
            }
        }
        // If we can still relax edges on the V-th iteration, 
        // there is a negative weight cycle reachable from start.
        if (step == g.n - 1 && any) {
            return vector<T>(); // signal negative cycle
        }
    }
    
    return dist;
    // returns numeric_limits<T>::max() if there's no path
    // returns empty vector if a negative cycle is reachable from start
}
