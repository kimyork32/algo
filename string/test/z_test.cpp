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

int main() {
    string s = "abacaba";
    vector<int> z = z_function(s);
    
    cout << "Z-array for '" << s << "':" << endl;
    for (int x : z) {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}
