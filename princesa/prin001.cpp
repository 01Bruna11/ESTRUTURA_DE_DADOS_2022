#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <list>
#include <map>
#include <queue>
#include <stack>

using namespace std;

const int dead = 0;

int mover(int pos, int size, int dir) {
    if (dir == 1)
        return (pos + 1) % size;
    else
        return (pos + size - 1) % size;
}

//achar o proximo elemento vivo a partir de incio + 1
//dir é 1 ou -1
int achar_vivo(vector<int>& v, int pos, int dir) {
    do {
        pos = mover(pos, v.size(), dir);
    } while (v[pos] == dead);
    return pos;
}

void mostrar(int vet[], int size, int aux) {
    cout << "[";
    for(int i = 0; i < size; i++) {
        if(vet[i] != dead) {
            cout << (" ");
            if((i == aux) && (vet[i] < 0))
                cout << ("<");
            cout << (vet[i]);
            if((i == aux) && (vet[i] > 0))
                cout << (">");
        }
    }
    cout << ("]") << endl;
}

int main () {
    int size {};
    int esc {};
    int fase {};
    cin >> size;
    cin >> esc;
    cin >> fase;
    int vet[size];
    for(int i = 0; i < size; i++) {
        vet[i] = (i + 1) * fase;
        fase *= -1;
    }
    esc = esc - 1;
    mostrar(vet, size, esc);
    int qtd = size - 1;
    while(qtd--) {
        int dir = size - 1;
        while(qtd--) {
            int dir = vet[esc] > 0 ? 1 : -1;
            int vai_morrer = achar_vivo(v, esc, dir);
            vet[vai_morrer] = dead;
            esc = achar_vivo(v, size, vai_morrer, dir);
            mostrar(vet, size, esc);
        }
    }
    return 0;
}