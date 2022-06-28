/*

Dado um vetor de inteiros A, imprima um triângulo de números 
tal que na base do triângulo estejam todos os elementos do vetor original, 
e tal que, a cada i-ésimo nível acima da base, o número de elementos seja 
um a menos que no nível inferior e cada elemento do i-ésimo nível seja a 
soma de dois elementos consecutivos do nível inferior.

    Entrada
        Os elementos da base
    Saída
        O triângulo

Testes


>>>>>>>> 01
1 2 3
========
[ 8 ]
[ 3 5 ]
[ 1 2 3 ]
<<<<<<<<

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

struct Triangle {
    std::vector<int> base;
    std::vector<int> result;

    Triangle(std::vector<int> base) : base(base) {
        this->base = base;
        this->result = base;
    }

    void solve() {
        for (int i = 1; i < base.size(); i++) {
            for (int j = 0; j < base.size() - i; j++) {
                result[j] = base[j] + base[j + 1];
            }
            std::copy(result.begin(), result.end(), base.begin());
        }
    }
};

void print_triangle(std::vector<int> base) {
    Triangle triangle(base);
    triangle.solve();
    for (int i = 0; i < base.size(); i++) {
        std::cout << base[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> base;
    std::string line;
    while (std::getline(std::cin, line)) {
        std::stringstream ss(line);
        int value;
        while (ss >> value) {
            base.push_back(value);
        }
    }
    print_triangle(base);
    return 0;
}




