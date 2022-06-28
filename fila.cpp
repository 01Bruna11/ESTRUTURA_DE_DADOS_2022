#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>
#include <bits/stdc++.h>


int main () {
   std::vector<int> fila;
   int tamanho;
   int n, m;
   int aux;
   std::cin >> tamanho;
    for (int i = 0; i < tamanho; i++) {
        std::cin >> aux;
        fila.push_back(aux);
    }
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> m;
        for(int j = 0; j < ((int)fila.size()); j++) {
            if(fila[j] == m) {
                fila.erase(fila.begin() + j);
                    break;
            }
        }
    }
    for(int i = 0; i < ((int)fila.size()); i++) {
        std::cout << "[ " << fila[i] << " ]";
    }
    return 0;
}