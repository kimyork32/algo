template <typename T>
class bfs_undigraph : public undigraph<T> {
public:
    using undigraph<T>::edges;
    using undigraph<T>::g;
    using undigraph<T>::n;

    vector<int> pv;
    vector<int> pe;
    vector<int> order;
    vector<int> pos;
    vector<int> root;
    vector<int> depth;
    vector<T> dist;
    vector<int> was;
    int attempt;

    bfs_undigraph(int _n) : undigraph<T>(_n) {}

    void init() {
        pv = vector<int>(n, -1);
        pe = vector<int>(n, -1);
        order.clear();
        pos = vector<int>(n, -1);
        root = vector<int>(n, -1);
        depth = vector<int>(n, -1);
        dist = vector<T>(n);
        was = vector<int>(n, -1);
        attempt = 0;
    }

    void clear() {
        pv.clear();
        pe.clear();
        order.clear();
        pos.clear();
        root.clear();
        depth.clear();
        dist.clear();
        was.clear();
    }

private:
    void do_bfs_from(int v) {
        ++attempt;
        depth[v] = 0;
        dist[v] = T{};
        root[v] = v;
        pv[v] = pe[v] = -1;

        // Usamos un vector como cola para mayor eficiencia
        vector<int> q;
        q.push_back(v);
        was[v] = attempt;

        int head = 0;
        while (head < (int)q.size()) {
            int cur = q[head++];
            
            pos[cur] = (int) order.size();
            order.push_back(cur);

            for (int id : g[cur]) {
                auto &e = edges[id];
                int to = e.from ^ e.to ^ cur;
                
                if (was[to] == attempt) {
                    continue;
                }
                
                was[to] = attempt;
                depth[to] = depth[cur] + 1;
                dist[to] = dist[cur] + e.cost;
                pv[to] = cur;
                pe[to] = id;
                root[to] = root[cur];
                q.push_back(to);
            }
        }
    }

public:
    void bfs(int v, bool clear_order = true) {
        if (pv.empty()) {
            init();
        } else {
            if (clear_order) {
                order.clear();
            }
        }
        do_bfs_from(v);
    }

    void bfs_all() {
        init();
        for (int v = 0; v < n; v++) {
            if (depth[v] == -1) {
                do_bfs_from(v);
            }
        }
        assert((int) order.size() == n);
    }
};
