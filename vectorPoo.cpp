#include <iostream>
#include <sstream>
using namespace std;

//double free corruption

struct Vector{
    int capacity {0}; //esse {} é o modo de inicializar default do c++ a partir do c++11
    int size {0};
    int * data {nullptr}; //inicializar pra não conter lixo

    Vector(int capacity){
        this->capacity = capacity;
        this->size = 0;
        this->data = new int[capacity];
    }

     void operator = (const Vector& other){
        this->capacity = other.capacity;
        this->size = other.size;
        if(this->data != nullptr){
            delete[] this->data;
        }
        this->data = new int[other.capacity];
        for(int i = 0; i < other.size; i++){
            this->data[i] = other.data[i];
        }
    }

    Vector(Vector& other){
        //aqui você não precisa fazer nada, basta utilizar o operador de atribuição
        //que você já implementou
        *this = other;

    }
    ~Vector(){
        delete[] this->data;
    }
    void add(int value){
        if(this->size == this->capacity){
            this->capacity *= 2;
            int * new_data = new int[this->capacity];
            for(int i = 0; i < this->size; i++){
                new_data[i] = this->data[i];
            }
            delete[] this->data;
            this->data = new_data;
        }
    }

    string show(){
        stringstream ss;
        ss << "[ ";
        for(int i = 0; i < this->size; i++){
            ss << this->data[i] << " ";
        }
        ss << "]";
        return ss.str();
    }

    friend ostream& operator<<(ostream &os, Vector vector){
        os << "[ ";
        for(int i = 0; i < vector.size; i++)
            os << vector.data[i] << " ";
        os << "]";
        return os;
    }
};


/* NAO MEXA DAQUI PRA BAIXO */
int main(){
    string line, cmd;
    int value;
    Vector v(0);
    while(true){
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end"){
            break;
        } else if(cmd == "init"){
            ss >> value;
            v = Vector(value);
        } else if(cmd == "status"){
            cout << "size:" << v.size << " capacity:" << v.capacity << "\n";
        } else if(cmd == "add"){
            while(ss >> value)
                v.add(value);
        } else if(cmd == "show"){
            cout << v << endl;
        } else {
            cout << "fail: comando invalido\n";
        }
    }
}