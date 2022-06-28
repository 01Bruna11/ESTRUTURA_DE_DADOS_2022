#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

struct Pos {
    int l, c;
    Pos(int l, int c) : l(l), c(c) {}
};

std::vector<Pos> get_neighbors(const std::vector<std::string> &mat, int l, int c) {
    std::vector<Pos> neighbors;
    int nl = mat.size();
    int nc = mat[0].size();
    if (l > 0 && mat[l - 1][c] != '#')
        neighbors.push_back(Pos(l - 1, c));
    if (l < nl - 1 && mat[l + 1][c] != '#')
        neighbors.push_back(Pos(l + 1, c));
    if (c > 0 && mat[l][c - 1] != '#')
        neighbors.push_back(Pos(l, c - 1));
    if (c < nc - 1 && mat[l][c + 1] != '#')
        neighbors.push_back(Pos(l, c + 1));
    return neighbors;
}

bool procurar_caminho(const std::vector<std::string> &mat, int l, int c, int nl, int nc, int lf, int cf) {
    if (l == lf && c == cf)
        return true;
    std::vector<Pos> neighbors = get_neighbors(mat, l, c);
    for (auto &neighbor : neighbors) {
        if (procurar_caminho(mat, neighbor.l, neighbor.c, nl, nc, lf, cf))
            return true;
    }
    return false;
}

void remover_erros(std::vector<std::string> &mat) {
    int nl = mat.size();
    int nc = mat[0].size();
    for (int l = 0; l < nl; l++) {
        for (int c = 0; c < nc; c++) {
            if (mat[l][c] == '#') {
                if (l > 0 && mat[l - 1][c] == '#')
                    mat[l - 1][c] = '_';
                if (l < nl - 1 && mat[l + 1][c] == '#')
                    mat[l + 1][c] = '_';
                if (c > 0 && mat[l][c - 1] == '#')
                    mat[l][c - 1] = '_';
                if (c < nc - 1 && mat[l][c + 1] == '#')
                    mat[l][c + 1] = '_';
            }
        }
    }
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &mat) {
    for (auto &line : mat)
        os << line << "\n";
    return os;
}

int main() {
    int nl, nc;
    std::cin >> nl >> nc;
    std::vector<std::string> mat(nl);
    for (int i = 0; i < nl; i++) {
        std::cin >> mat[i];
    }
    remover_erros(mat);
    int lf, cf;
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            if (mat[i][j] == 'F') {
                lf = i;
                cf = j;
            }
        }
    }

    std::cout << mat << std::endl;
    std::cout << procurar_caminho(mat, 0, 0, nl, nc, lf, cf) << std::endl;
    return 0;
}

