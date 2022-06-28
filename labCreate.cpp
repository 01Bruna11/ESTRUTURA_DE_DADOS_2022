#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>

using namespace std;

struct Pos {
    int l;
    int c;
    
    Pos(int l, int c) : l(l), c(c) {}

    bool operator==(const Pos &other) const {
        return l == other.l && c == other.c;
    }
    
    bool operator!=(const Pos &other) const {
        return !(*this == other);
    }

    std::vector<Pos> get_neighbors(const std::vector<std::string> &mat) {
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
};

struct Mapa {
    std::vector<std::string> mat;
    int nl;
    int nc;
    
    Mapa(std::vector<std::string> mat) : mat(mat), nl(mat.size()), nc(mat[0].size()) {}
    
    std::vector<Pos> get_neighbors(int l, int c) {
        return mat[l][c].get_neighbors(mat);
    }
    
    bool operator==(const Mapa &other) const {
        return mat == other.mat;
    }
    
    bool operator!=(const Mapa &other) const {
        return !(*this == other);
    }
    
    void remover_erros() {
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
    
    bool procurar_caminho(int l, int c, int lf, int cf) {
        if (l == lf && c == cf)
            return true;
        std::vector<Pos> neighbors = get_neighbors(l, c);
        for (auto &neighbor : neighbors) {
            if (procurar_caminho(neighbor.l, neighbor.c, lf, cf))
                return true;
        }
        return false;
    }
};

void destroir(Mapa &mapa, int l, int c) {
    mapa.mat[l][c] = '_';
    for (auto &neighbor : mapa.get_neighbors(l, c)) {
        if (mapa.mat[neighbor.l][neighbor.c] == '#')
            destroir(mapa, neighbor.l, neighbor.c);
    }
}

template <typename T>
std::string to_string(T value) {
    std::ostringstream os;
    os << value;
    return os.str();
}

int main(int argc, char * argv[]) {
    int nl = 0, nc = 0, lfire = 0, cfire = 0;
    cin >> nl >> nc >> lfire >> cfire;
    vector<string> mat;
    for (int l = 0; l < nl; l++) {
        string line;
        cin >> line;
        mat.push_back(line);
    }
    Mapa mapa(mat);
    mapa.remover_erros();
    if (mapa.procurar_caminho(lfire, cfire, 0, 0)) {
        destroir(mapa, lfire, cfire);
        for (int l = 0; l < nl; l++) {
            for (int c = 0; c < nc; c++) {
                if (mapa.mat[l][c] == '_')
                    cout << '#';
                else
                    cout << '.';
            }
            cout << "\n";
        }
    } else {
        cout << "IMPOSSIBLE\n";
    }
    return 0;

}
