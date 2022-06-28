#define PROF
#include <iostream>
#include <vector>

void rotacao(std::vector<int>& v, int r) {
    #ifdef PROF
    r = r % v.size();
    std::vector<int> aux;
    for (int i = v.size() - r; i < (int)v.size(); i++)
        aux.push_back(v[i]);
    for(int i = (int) v.size() - r - 1; i >= 0; i--)
        v[i + r] = v[i];
    for (int i = 0; i < (int) aux.size(); i++)
        v[i] = aux[i];
    #else
    #endif
}

void show(std::vector<int> &v) {
    std::cout << "[ ";
    for(int value : v)
        std::cout << value << " ";
    std::cout << "]\n";
}

int main() {
    int size, r;
    std::cin >> size >> r;
    std::vector<int> v(size);
    for(int i = 0; i < size; i++)
        std::cin >> v[i];
    rotacao(v, r);
    show(v);
}
    