#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>
#include <optional>
#include <numeric>
#include <functional>
#include <sstream>

const char EMPTY = '.';

//metodo generico para formatar um container como texto
template <class T>
std::string fmt(T data) {
    std::ostringstream ss;
    ss << "[";
    for (auto it = data.begin(); it != data.end(); ++it)
        ss << (it != data.begin() ? ", " : "") << *it;
    ss << "]";
    return ss.str();
}

//gera um vector generico de [beg, end[
template <class T>
std::vector<T> range(T _beg, T _end) {
    std::vector<T> output;
    for (char c = _beg; c < _end; c++)
        output.push_back(c);
    return output;
}

//embaralha e retorna um vetor generico
template <class T>
std::vector<T> shuffle(std::vector<T> data) {
    std::random_shuffle(data.begin(), data.end());
    return data;
}

//!ADD

struct Problema {
    std::string data;
    int lim;
    std::vector<int> holes; //posicoes a preencher

    Problema(std::string data, int lim) { 
        this->data = data;
        this->lim = lim;
        for (int i = 0; i < (int) data.size(); i++)
            if (data[i] == EMPTY)
                this->holes.push_back(i);
    }

    //se posso colocar esse valor em data[index]
    bool fit(int index, char value) {
        if (index < 0 || index >= (int) data.size())
            return false;
        if (data[index] != EMPTY)
            return false;
        if (value == '0' && index % 2 == 0)
            return false;
        if (value == '1' && index % 2 == 1)
            return false;
        return true;
    }

    //tenta resolver o problema recursivamente retornando na primeira solução encontrada
    bool solve(int hindex) {
        if (hindex == (int) holes.size())
            return true;
        int index = holes[hindex];
        for (char value : range('0', '3'))
            if (fit(index, value)) {
                data[index] = value;
                if (solve(hindex + 1))
                    return true;
                data[index] = EMPTY;
            }
        return false;
    }

    //tenta resoler o problema recursivamente contando quantas soluções existem
    int count_solutions(int hindex) {
        if (hindex == (int) holes.size())
            return 1;
        int index = holes[hindex];
        int count = 0;
        for (char value : range('0', '3'))
            if (fit(index, value)) {
                data[index] = value;
                count += count_solutions(hindex + 1);
                data[index] = EMPTY;
            }
        return count;
    }

    //verifica se remover essa posição, gera uma única solução
    bool can_remove(int index) {
        if (index < 0 || index >= (int) data.size())
            return false;
        if (data[index] == EMPTY)
            return false;
        return true;
    }

    //pega a lista de todas as posições e embaralha
    //para cada posição, se removê-la gera um problema com única solução
    //então remova
    void fill_holes() {
        std::vector<int> list = range(0, (int) data.size());
        shuffle(list);
        for (int index : list)
            if (can_remove(index)) {
                data[index] = EMPTY;
                if (count_solutions(0) == 1)
                    holes.erase(std::remove(holes.begin(), holes.end(), index), holes.end());
                data[index] = '1';
                if (count_solutions(0) == 1)
                    holes.erase(std::remove(holes.begin(), holes.end(), index), holes.end());
                data[index] = '2';
                if (count_solutions(0) == 1)
                    holes.erase(std::remove(holes.begin(), holes.end(), index), holes.end());
                data[index] = '3';
                if (count_solutions(0) == 1)
                    holes.erase(std::remove(holes.begin(), holes.end(), index), holes.end());
                data[index] = '0';
                if (count_solutions(0) == 1)
                    holes.erase(std::remove(holes.begin(), holes.end(), index), holes.end());
            }
        }
};
 

int main (int argc, char * argv[]) {
    srand(time(0));
    int size { 5 }, lim { 3 };
    if (argc < 3) {
        puts("Passe size e lim como argumentos");
        return 1;
    }
    std::istringstream(argv[1]) >> size;
    std::istringstream(argv[2]) >> lim;
    std::cout << size << ' ' << lim << '\n';

    Problema prob(std::string(size, EMPTY), lim);
    prob.solve(0);
    std::cout << prob.data << "\n";
    prob.fill_holes();
    std::cout << prob.data << '\n';

    return 0;

}