#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <fstream>

template <class T>
std::vector<T> range(T _beg, T _end) {
    std::vector<T> output;
    for (char c = _beg; c < _end; c++)
        output.push_back(c);
    return output;
}

template <class T>
std::vector<T> shuffle(std::vector<T> data) {
    std::random_shuffle(data.begin(), data.end());
    return data;
}

struct Problema {
    std::vector<std::string> data;
    int size = 0;
    int dim = 0;
    std::vector<std::pair<int, int>> holes; //posicoes a preencher

    Problema(std::vector<std::string> data) {
        this->data = data;
        this->size = data.size();
        this->dim = data[0].size();
        for (int i = 0; i < size; i++)
            for (int j = 0; j < dim; j++)
                if (data[i][j] == '.')
                    holes.push_back(std::make_pair(i, j));
    }

    bool fit(int index, char value) {
        auto [pi, pj] = holes[index];

        for (int i = 0; i < size; i++)
            if (data[i][pj] == value)
                return false;   

        for (int j = 0; j < dim; j++)
            if (data[pi][j] == value)
                return false;

        int ih = pi - pi % dim;
        int jh = pj - pj % dim;
        for (int i = ih; i < ih + dim; i++)
            for (int j = jh; j < jh + dim; j++)
                if (data[i][j] == value)
                    return false;
        return true;

    }

    void put(int index, char value) {
        auto [pi, pj] = holes[index];
        data[pi][pj] = value;
    }

    bool solve(int index) {
        if (index == holes.size())
            return true;
        for (auto value : shuffle(range('1', '9')))
            if (fit(index, value)) {
                put(index, value);
                if (solve(index + 1))
                    return true;
                put(index, '.');
            }
        return false;
    }

    std::string str() {
        std::stringstream ss;
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < dim; j++)
                ss << data[i][j];
            ss << std::endl;
        }
        return ss.str();
    }

    //operator >>

};

int main() {
    auto& input = std::cin; 
    int size ();
    int dim ();
    std::vector<std::string> data (size());
    for (int i = 0; i < size(); i++)
        input >> data[i];
    Problema p(data);
    p.solve(0);
    std::cout << p.str();

    return 0;

}
