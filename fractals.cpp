#include <iostream>
#include <vector>
#include <algorithm>

struct Posicao {
    int x;
    int y;
};

#define get(matriz, Posicao) matriz[Posicao.x][Posicao.y]

std::vector<Posicao> get_posicoes_vizinhas(Posicao posicao, int linhas, int colunas) {
    std::vector<Posicao> posicoes_vizinhas;
    if (posicao.x > 0) {
        posicoes_vizinhas.push_back({posicao.x - 1, posicao.y});
    }
    if (posicao.x < linhas - 1) {
        posicoes_vizinhas.push_back({posicao.x + 1, posicao.y});
    }
    if (posicao.y > 0) {
        posicoes_vizinhas.push_back({posicao.x, posicao.y - 1});
    }
    if (posicao.y < colunas - 1) {
        posicoes_vizinhas.push_back({posicao.x, posicao.y + 1});
    }
    return posicoes_vizinhas;
}

bool procurar_saida(std::vector<std::vector<char>> matriz, Posicao inicio, Posicao fim) {
    std::vector<Posicao> posicoes_vizinhas;
    std::vector<Posicao> posicoes_visitadas;
    posicoes_vizinhas.push_back(inicio);
    while (!posicoes_vizinhas.empty()) {
        Posicao posicao = posicoes_vizinhas.back();
        posicoes_vizinhas.pop_back();
        if (get(matriz, posicao) == 'F') {
            return true;
        }
        if (std::find(posicoes_visitadas.begin(), posicoes_visitadas.end(), posicao) == posicoes_visitadas.end()) {
            posicoes_visitadas.push_back(posicao);
            std::vector<Posicao> vizinhos = get_posicoes_vizinhas(posicao, matriz.size(), matriz[0].size());
            for (Posicao vizinho : vizinhos) {
                if (get(matriz, vizinho) == '_') {
                    posicoes_vizinhas.push_back(vizinho);
                }
            }
        }
    }
    return false;
}

void remover_erros(std::vector<std::vector<char>>& matriz) {
    for (int i = 0; i < matriz.size(); i++) {
        for (int j = 0; j < matriz[0].size(); j++) {
            if (matriz[i][j] == '#') {
                matriz[i][j] = '_';
            }
        }
    }
}

int main () {
    int linhas = 0;
    int colunas = 0;
    std::cin >> linhas >> colunas;
    std::vector<std::string> matriz(linhas);
    getchar();
    Posicao inicio, fim;
    for (int i = 0; i < linhas; i++) {
        std::getline(std::cin, matriz[i]);
    }
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j] == 'I') {
                inicio = {i, j};
                matriz[i][j] = ' ';
            }
            if (matriz[i][j] == 'F') {
                fim = {i, j};
                matriz[i][j] = ' ';
            }
        }
    }
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            std::cout << matriz[i][j];
        }
        std::cout << std::endl;
    }

    return 0;

}