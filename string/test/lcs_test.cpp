#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

#include "../lcs.cpp"

int main() {
    string s1 = "abracadabra";
    string s2 = "cadena";
    
    int length = lcs_length(s1, s2);
    string lcs_str = lcs_reconstruct(s1, s2);
    
    cout << "String 1: " << s1 << endl;
    cout << "String 2: " << s2 << endl;
    cout << "LCS Length: " << length << endl;
    cout << "LCS String: " << lcs_str << endl;
    
    // Expected output:
    // "cadena" vs "abracadabra"
    // The subsequence could be "cada" (c-a-d-a in abracadabra)
    
    return 0;
}
