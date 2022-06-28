#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <cmath>

char WALL = '#';

struct Position {
    int l;
    int c;
    
    Position(int l, int c) : l(l), c(c) {}
    
    bool operator==(const Position &other) const {
        return l == other.l && c == other.c;
    }
    
    bool operator!=(const Position &other) const {
        return !(*this == other);
    }
    
    std::vector<Position> get_neighbors(const std::vector<std::string> &mat) {
        std::vector<Position> neighbors;
        int nl = mat.size();
        int nc = mat[0].size();
        if (l > 0 && mat[l - 1][c] != WALL)
            neighbors.push_back(Position(l - 1, c));
        if (l < nl - 1 && mat[l + 1][c] != WALL)
            neighbors.push_back(Position(l + 1, c));
        if (c > 0 && mat[l][c - 1] != WALL)
            neighbors.push_back(Position(l, c - 1));
        if (c < nc - 1 && mat[l][c + 1] != WALL)
            neighbors.push_back(Position(l, c + 1));
        return neighbors;
    }
};

struct Mapa {
    std::vector<std::string> mat;
    int nl;
    int nc;
    
    Mapa(std::vector<std::string> mat) : mat(mat), nl(mat.size()), nc(mat[0].size()) {}
    
    std::vector<Position> get_neighbors(int l, int c) {
        return mat[l][c].get_neighbors(mat);
    }
    
    bool operator==(const Mapa &other) const {
        return mat == other.mat;
    }
    
    bool operator!=(const Mapa &other) const {
        return !(*this == other);
    }
    
    void remove_errors() {
        for (int l = 0; l < nl; l++) {
            for (int c = 0; c < nc; c++) {
                if (mat[l][c] == WALL) {
                    std::vector<Position> neighbors = get_neighbors(l, c);
                    for (auto neighbor : neighbors) {
                        if (mat[neighbor.l][neighbor.c] == 'o') {
                            mat[l][c] = '.';
                            break;
                        }
                    }
                }
            }
        }
    }
};

auto exists = [](const std::vector<std::string> &mat, int l, int c) {
    return l >= 0 && l < mat.size() && c >= 0 && c < mat[0].size();
};

void destroir_mapa(Mapa &mapa) {
    for (int l = 0; l < mapa.nl; l++) {
        for (int c = 0; c < mapa.nc; c++) {
            if (mapa.mat[l][c] == 'o')
                mapa.mat[l][c] = '.';
        }
    }
}

int main(int argc, char * argv[]) {
    std::vector<std::string> mat;
    int nl, nc, lfire, cfire;
    std::cin >> nl >> nc >> lfire >> cfire;
    for (int l = 0; l < nl; l++) {
        std::string line;
        std::cin >> line;
        mat.push_back(line);
    }
    Mapa mapa(mat);
    mapa.remove_errors();
    std::vector<Position> neighbors = mapa.get_neighbors(lfire, cfire);
    for (auto neighbor : neighbors) {
        if (mapa.mat[neighbor.l][neighbor.c] == '.') {
            mapa.mat[neighbor.l][neighbor.c] = 'o';
            destroir_mapa(mapa);
            std::cout << neighbor.l << " " << neighbor.c << "\n";
            return 0;
        }
    }
    std::cout << "NONE\n";
    return 0;
}