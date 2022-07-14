#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>

/* refaça o problema da queimada usando recurssão.

verifique a primeira posição e queime-o
inicie a pilha com esse elemento
enquanto a pilha não estiver vazia faça
    pegue topo da pilha

    faça uma lista com todos os vizinhos de topo que podem ser queimados
    se lista eh vazia
        desempilhe
    senão
        escolha um dos vizinhos
        queime
        empilhe

Exemplo:

>>>>>>>> 01
2 3 1 1
#.#
.##
========
#.o
.oo
<<<<<<<<

*/
typedef struct Pos{
    int x;
    int y;
}Pos;

std::vector<Pos> vizinhos(Pos pos) {
    std::vector<Pos> vizinhos;
    vizinhos.push_back({pos.x-1, pos.y});
    vizinhos.push_back({pos.x+1, pos.y});
    vizinhos.push_back({pos.x, pos.y-1});
    vizinhos.push_back({pos.x, pos.y+1});
    return vizinhos;
}

bool ehVizinho(Pos pos1, std::vector<Pos> vizinhos) {
    for (auto vizinho : vizinhos) {
        if (ehVizinho(pos1, vizinho)) {
            return true;
        }
    }
    return false;
}

bool tocar_fogos(std::vector<std::string> &mapa, size_t lin, sie_t col) {
    std::vector<Pos> fogos;
    for (size_t i = 0; i < lin; i++) {
        for (size_t j = 0; j < col; j++) {
            if (mapa[i][j] == '#') {
                fogos.push_back({i, j});
            }
        }
    }
    for (auto fogo : fogos) {
        std::vector<Pos> vizinhos = vizinhos(fogo);
        for (auto vizinho : vizinhos) {
            if (mapa[vizinho.x][vizinho.y] == '.') {
                mapa[vizinho.x][vizinho.y] = 'o';
                return true;
            }
        }
    }
    return false;
}

int main () {
    std::vector<std::string> mapa;
    size_t lin, col;
    std::cin >> lin >> col;
    for (size_t i = 0; i < lin; i++) {
        std::string linha;
        std::cin >> linha;
        mapa.push_back(linha);
    }
    while (tocar_fogos(mapa, lin, col)) {
    }
    for (auto linha : mapa) {
        std::cout << linha << std::endl;
    }
    return 0;
}