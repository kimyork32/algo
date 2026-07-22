#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

template <typename T>
vector<int> z_function(int n, const T &s) {
    vector<int> z(n, n);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = (i > r ? 0 : min(r - i + 1, z[i - l]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}

template <typename T>
vector<int> z_function(const T &s) {
    return z_function((int) s.size(), s);
}

template <typename T>
vector<int> duval_prefixes(int n, const T &s) {
    vector<int> z = z_function(n, s);
    vector<int> ans(n, 0);
    int i = 0, pos = 0;
    while (i < n) {
        int j = i, k = i;
        while (j < n) {
            j++;
            if (j > pos) {
                if (z[k] <= pos - k && s[z[k]] < s[k + z[k]]) {
                    int shift = (pos - i) / (j - k) * (j - k);
                    ans[pos] = ans[pos - shift] + shift;
                } else {
                    ans[pos] = i;
                }
                pos++;
            }
            if (s[k] < s[j]) k = i; else
            if (!(s[j] < s[k])) k++;
            else break;
        }
        while (i <= k) {
            i += j - k;
        }
    }
    return ans;
    // returns 0-indexed positions of the least cyclic shifts of all prefixes
}

template <typename T>
vector<int> duval_prefixes(const T &s) {
    return duval_prefixes((int) s.size(), s);
}

int main() {
    string s = "amandamanda";
    vector<int> ans = duval_prefixes(s);
    cout << "String: " << s << endl;
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << "Prefix length " << i + 1 << " least cyclic shift at index: " << ans[i] << endl;
    }
    return 0;
}
