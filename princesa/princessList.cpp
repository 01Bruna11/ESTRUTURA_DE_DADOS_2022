#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

void show_vet(std::vector<int> vet, int sword) {
    for (size_t i = 0; i < vet.size(); i++)
        std::cout << i << (i == sword? "> " : "  ");
    std::cout << std::endl;
}
int main() {
    int size {}, sword {};
    std::cin >> size >> sword;
    std::vector<int> vet(size);
    for (int i = 0; i < size; i++)
        vet[i] = i + 1;
    sword -= 1;
    int qtd = vet.size() - 1;
    while(qtd--) {
        show_vet(vet, sword);
        sword = (sword + 1) % vet.size();
        vet.erase(vet.begin() + sword);
        sword = sword % vet.size();
    }
    show_vet(vet, sword);
    return 0;
}