#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// in.txt containts:
//  n m 
//  u v w   // m lines (edges)
//
// g++ viz.cpp -o viz
// ./viz
// neato -Tng graph.dot -o graph.png
int main() {
    ifstream inputFile("in.txt");
    if (!inputFile) {
        cerr << "error" << endl;
        return 1;
    }
    int n, m;
    if (!(inputFile >> n >> m)) {
        cerr << "error invalid format" << endl;
        return 1;
    }
    string dummy;
    getline(inputFile, dummy);
    ofstream outFile("graph.dot");
    if (!outFile) {
        cerr << "error in creating .dot" << endl;
        return 1;
    }
    outFile << "graph G {\n";
    outFile << "  node [shape=circle, style=filled, fillcolor=lightblue];\n";
    outFile << "  layout=neato; \n";
    string line;
    for (int i = 0; i < m; ++i) {
        if (getline(inputFile, line) && !line.empty()) {
            stringstream ss(line);
            int u, v;
            double weight;
            if (ss >> u >> v) {
                outFile << "  " << u << " -- " << v;
                if (ss >> weight) {
                    outFile << " [label=\"" << weight << "\"]";
                }
                outFile << ";\n";
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        outFile << "  " << i << ";\n";
    }
    outFile << "}\n";
    inputFile.close();
    outFile.close();
    cout << "successfully" << endl;
    return 0;
}
