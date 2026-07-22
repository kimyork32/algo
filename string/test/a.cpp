#include <bits/stdc++.h>
#include <cassert>
using namespace std;

template <typename T>
vector<int> kmp_table(int n, const T &s) {
    vector<int> p(n, 0);
    int k = 0;
    for (int i = 1; i < n; i++) {
        while (k > 0 && !(s[i] == s[k])) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

template <typename T>
vector<int> kmp_table(const T &s) {
    return kmp_table((int) s.size(), s);
}

template <typename T>
vector<int> kmp_search(int n, const T &s, int m, const T &w, const vector<int> &p) {
    assert(n >= 1 && (int) p.size() == n);
    vector<int> res;
    int k = 0;
    for (int i = 0; i < m; i++) {
        while (k > 0 && (k == n || !(w[i] == s[k]))) {
            k = p[k - 1];
        }
        if (w[i] == s[k]) {
            k++;
        }
        if (k == n) {
            res.push_back(i - n + 1);
        }
    }
    return res;
}

template <typename T>
vector<int> kmp_search(const T &s, const T &w, const vector<int> &p) {
    return kmp_search((int) s.size(), s, (int) w.size(), w, p);
}

bool check(int n, int l, int k, const string& s, const string& mid) {
    vector<int> p = kmp_table(mid);
    int ml = 0;
    int count = 0;
    int cl = 0;
    for (int i = 0; i < n; i++) {
        while (ml > 0 && (ml == (int)mid.size() || s[i] != mid[ml])) {
            ml = p[ml - 1];
        }
        if (s[i] == mid[ml]) {
            ml++;
        }
        cl++;
        if (ml == (int)mid.size() && cl >= l) {
            count++;
            cl = 0;
            ml = 0;
        }
    }
    return count >= k;
}

void solve() {
    int n, l, k;
    cin >> n >> l >> k;
    string s;
    cin >> s;
    if (1LL * k * l > n) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";

    string ans = "";
    int ml = n - (k - 1) * l; 
    for (int i = 0; i < ml; i++) {
        char best = 'a' - 1;
        for (char c = 'z'; c >= 'a'; c--) {
            string p = ans + c;
            if (check(n, l, k, s, p)) {
                best = c;
                break;
            }
        }
        if (best < 'a') break;
        ans += best;
    }
    cout << ans << "\n";
}

int main() {
    int tt; cin >> tt;
    while (tt--) {
        solve();
    }
    return 0;
}
