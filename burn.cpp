/*Dado uma matriz que representa espaços vazios e árvores e um ponto inicial onde começa o fogo, retorne a matriz com as árvores queimadas. O fogo se não se espalha nas diagonais, apenas nas 4 direções cardeais.

A matriz está codificada assim. 1a linha: nl, nc, l, c respectivamente

    número de linhas e colunas da matriz, linha e coluna onde começa o fogo.
    Nas linhas subsequentes:
        '#' representa uma árvore
        '.' representa um espaço vazio
        'o' representa uma árvore queimada

Saída esperada:

    Imprima a matriz após a queimada acontecer.

Testes

>>>>>>>> 01
2 3 1 1
#.#
.##
========
#.o
.oo
<<<<<<<<

>>>>>>>> 02
5 5 0 0
#..#.
#...#
###..
..#.#
..###
========
o..#.
o...#
ooo..
..o.o
..ooo
<<<<<<<<

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>

void show_matrix(std::vector<std::vector<char>> mat){
    for(int i = 0; i < mat.size(); i++){
        for(int j = 0; j < mat[i].size(); j++){
            std::cout << mat[i][j];
        }
        std::cout << std::endl;
    }
}

void tocar_fogo(std::vector<std::vector<char>> &mat, int l, int c){
    if(l < 0 || l >= mat.size() || c < 0 || c >= mat[l].size()){
        return;
    }
    if(mat[l][c] != '#'){
        return;
    }
    mat[l][c] = 'o';
    tocar_fogo(mat, l - 1, c - 1);
    tocar_fogo(mat, l - 1, c);
    tocar_fogo(mat, l - 1, c + 1);
    tocar_fogo(mat, l, c - 1);
    tocar_fogo(mat, l, c + 1);
    tocar_fogo(mat, l + 1, c - 1);
    tocar_fogo(mat, l + 1, c);
    tocar_fogo(mat, l + 1, c + 1);
}

int main () {
    int nl, nc, l, c;
    std::cin >> nl >> nc >> l >> c;
    std::vector<std::vector<char>> mat(nl, std::vector<char>(nc));
    for(int i = 0; i < nl; i++){
        for(int j = 0; j < nc; j++){
            std::cin >> mat[i][j];
        }
    }
    tocar_fogo(mat, l, c);
    show_matrix(mat);
    return 0;
}
