#include <iostream>
#include <sstream>

using namespace std;

struct Vector{
    int capacity;
    int size;
    int * data;
};

Vector * vector_create(int capacity){
    Vector * vector = new Vector;
    vector->capacity = capacity;
    vector->size = 0;
    vector->data = new int[capacity];
    return vector;
}

void vector_destroy(Vector * vector){
    delete[] vector->data;
    delete vector;
}

void vector_add(Vector * vector, int value){
    if(vector->size == vector->capacity){
        vector->capacity *= 2;
        int * new_data = new int[vector->capacity];
        for(int i = 0; i < vector->size; i++){
            new_data[i] = vector->data[i];
        }
        delete[] vector->data;
        vector->data = new_data;
    }
    vector->data[vector->size] = value;
    vector->size++;
}

//retorne a string no formato 
// [ a b c ]
string vector_show(Vector * vector){
    stringstream ss;
    ss << "[ ";
    for(int i = 0; i < vector->size; i++){
        ss << vector->data[i] << " ";
    }
    ss << "]";
    return ss.str();

}


/* NAO MEXA DAQUI PRA BAIXO */
int main(){
    string line, cmd;
    int value;
    Vector * v = vector_create(0);
    while(true){
        getline(cin, line);
        cout << "$" << line << endl;
        stringstream ss(line);
        ss >> cmd;
        if(cmd == "end"){
            break;
        } else if(cmd == "init"){
            ss >> value;
            if(v != nullptr)
                vector_destroy(v);
            v = vector_create(value);
        } else if(cmd == "status"){
            cout << "size:" << v->size << " capacity:" << v->capacity << "\n";
        } else if(cmd == "add"){
            while(ss >> value)
                vector_add(v, value);
        } else if(cmd == "show"){
            cout << vector_show(v) << endl;
        } else {
            cout << "fail: comando invalido\n";
        }
    }
    vector_destroy(v);
}