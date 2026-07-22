#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include "../z.cpp"

int main() {
    string text = "el gato y otro gato";
    string pattern = "gato";
    
    // El "truco" de la Súper Cadena
    string s = pattern + "#" + text;
    
    vector<int> z = z_function(s);
    
    cout << "Buscando el patron: '" << pattern << "'\n";
    cout << "Dentro del texto: '" << text << "'\n";
    cout << "Super Cadena creada: '" << s << "'\n\n";
    
    // Recorremos solo la parte del texto en el arreglo Z.
    // El texto empieza despues del patron y el simbolo '#'.
    int start_of_text = pattern.size() + 1;
    
    bool found = false;
    for (int i = start_of_text; i < (int)s.size(); i++) {
        // Si Z[i] es igual al tamano del patron, es un match exacto!
        if (z[i] == (int)pattern.size()) {
            // Para obtener el indice original en el texto, restamos el desfase
            cout << "-> ¡Coincidencia encontrada en el indice original del texto: " 
                 << i - start_of_text << "!" << endl;
            found = true;
        }
    }
    
    if (!found) {
        cout << "No se encontraron coincidencias." << endl;
    }
    
    return 0;
}
