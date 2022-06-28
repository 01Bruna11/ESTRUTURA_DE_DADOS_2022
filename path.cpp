#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>

struct Pos {
    int l;
    int c;
};

#define get(mat, pos) mat[pos.l][pos.c]

std::vector<Pos> get_vizinhos(Pos p) {
    std::vector<Pos> vizinhos = {
        {p.l - 1, p.c},
        {p.l + 1, p.c},
        {p.l, p.c - 1},
        {p.l, p.c + 1}
    };
    return vizinhos;
}

void refazer(std::vector<std::vector<char>>& mat, Pos inicio, Pos fim, int value) {
    Pos p = fim;
    while(p != inicio) {
        mat[p.l][p.c] = '.';
        p = get_vizinhos(p)[value];
    }
    mat[p.l][p.c] = '.';
}

bool procurar_saida(std::vector<std::vector<char>>& mat, Pos inicio, Pos fim, Pos& saida) {
    std::vector<Pos> vizinhos;
    std::vector<Pos> fila;
    std::map<Pos, int> distancia;
    std::map<Pos, Pos> anterior;
    fila.push_back(inicio);
    distancia[inicio] = 0;
    while(!fila.empty()) {
        Pos p = fila.back();
        fila.pop_back();
        vizinhos = get_vizinhos(p);
        for(int i = 0; i < (int) vizinhos.size(); i++) {
            Pos viz = vizinhos[i];
            if(get(mat, viz) == '.') {
                saida = viz;
                return true;
            }
            if(get(mat, viz) == '#') continue;
            if(distancia.find(viz) == distancia.end()) {
                distancia[viz] = distancia[p] + 1;
                anterior[viz] = p;
                fila.push_back(viz);
            }
        }
    }
    return false;
}

void remover_erros(std::vector<std::vector<char>>& mat, Pos inicio, Pos fim) {
    Pos saida;
    if(!procurar_saida(mat, inicio, fim, saida)) {
        std::cout << "Nao foi possivel encontrar a saida" << std::endl;
        return;
    }
    Pos p = saida;
    while(p != inicio) {
        mat[p.l][p.c] = 'x';
        p = anterior[p];
    }
    mat[p.l][p.c] = ' ';
}

int main() {
    int nl, nc;
    std::cin >> nl >> nc;
    std::vector<std::vector<char>> mat(nl, std::vector<char>(nc));
    for(int i = 0; i < nl; i++) {
        for(int j = 0; j < nc; j++) {
            std::cin >> mat[i][j];
        }
    }
    Pos inicio, fim;
    for(int i = 0; i < nl; i++) {
        for(int j = 0; j < nc; j++) {
            if(mat[i][j] == 'I') {
                inicio.l = i;
                inicio.c = j;
            }
            if(mat[i][j] == 'F') {
                fim.l = i;
                fim.c = j;
            }
        }
    }
    std::vector<Pos> vizinhos;
    std::vector<Pos> fila;
    std::map<Pos, int> distancia;
    std::map<Pos, Pos> anterior;
    fila.push_back(inicio);
    distancia[inicio] = 0;
    while(!fila.empty()) {
        Pos p = fila.back();
        fila.pop_back();
        vizinhos = get_vizinhos(p);
        for(int i = 0; i < (int) vizinhos.size(); i++) {
            Pos viz = vizinhos[i];
            if(get(mat, viz) == '#') continue;
            if(distancia.find(viz) == distancia.end()) {
                distancia[viz] = distancia[p] + 1;
                anterior[viz] = p;
                fila.push_back(viz);
            }
        }
    }
    remover_erros(mat, inicio, fim);
    for(int i = 0; i < nl; i++) {
        for(int j = 0; j < nc; j++) {
            std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
    
    return 0;
}



