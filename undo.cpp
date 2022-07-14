#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>

struct Estado{
    std::list<char> text;
    std::list<char>::iterator cursor;

    Estado(){
        cursor = text.end();
    }
    //inicia o estado com um texto inicial
    Estado(std::string text){
        for(char c : text){
            this->text.push_back(c);
        }
        cursor = this->text.end();
    }

    Estado(Estado& estado){
        for(char c : estado.text){
            this->text.push_back(c);
        }
        this->cursor = this->text.begin();
        std::advance(this->cursor, std::distance(estado.text.begin(), estado.cursor));
    }

    std::string toString(){
        std::stringstream ss;
        for(char c : text){
            ss << c;
        }
        ss << "|";           //marca o cursor 
        return ss.str();
    }
};

struct Historico{
    std::list<Estado> estados;
    std::list<Estado>::iterator it;

    Historico(std::string init_text = ""){
        estados.push_back(Estado(init_text));
        it = estados.begin();
    }

    Historico(Historico& historico){
        for(Estado estado : historico.estados){
            this->estados.push_back(estado);
        }
        this->it = this->estados.begin();
    }
    //insere um novo estado no historico
    void controlZ(){
        if(it != estados.begin()){
            it--;
        }
    }
    void controlY(){
        if(it != estados.end()){
            it++;
        }
    }
    void pushEstado() {
        auto prox = it;
        estados.erase(++prox, estados.end());
        estados.push_back(Estado(*it));
        it = --estados.end();
    }
    void insertChar(char c){
        it->text.push_back(c);
        it->cursor++;
        pushEstado();
    }
    void sendBackspace(){
        if(it->cursor != it->text.begin()){
            it->cursor--;
            it->text.erase(it->cursor);
            pushEstado();
        }
    }
    void sendDelete(){
        if(it->cursor != it->text.end()){
            it->text.erase(it->cursor);
            pushEstado();
        }
    }
    void sendRight(){
        if(it->cursor != it->text.end()){
            it->cursor++;
            pushEstado();
        }
    }
    void sendLeft(){
        if(it->cursor != it->text.begin()){
            it->cursor--;
            pushEstado();
        }
    }
    void sendUp(){
        int desl = 0;
        auto itc = it->cursor;
        //olta pro comeco da linha contando quantos elementos sao
        while(itc != it->text.begin() && *itc != '\n'){
            itc--;
            desl++;
        }
        //se nao estiver no comeco da linha, move o cursor para o comeco da linha
        if(itc != it->text.begin()){
            it->cursor = it->text.begin();
            std::advance(it->cursor, desl);
            pushEstado();
        }
    }
    void sendDown(){
        int desl = 0;
        auto itc = it->cursor;
        //volta pro comeco da linha contando quantos elementos sao
        while(((itc != it->text.end()) && *itc != '\n') || (itc == it->text.end())){
            itc++;
            desl++;
        } do {
            itc++;
            desl++;
        } while((itc != it->text.end()) && *itc != '\n');

        if(itc != it->text.end()){
            it->cursor = it->text.begin();
            std::advance(it->cursor, desl);
            pushEstado();
        }
    }

    std::string toString(){
        std::stringstream ss;
        for(Estado estado : estados){
            ss << estado.toString() << std::endl;
        }
        return ss.str();
    }
};

void controle(Historico & his, char tecla) {
    switch(tecla){
        case 'z':
            his.controlZ();
            break;
        case 'y':
            his.controlY();
            break;
        case '\b':
            his.sendBackspace();
            break;
        case '\d':
            his.sendDelete();
            break;
        case '\r':
            his.sendRight();
            break;
        case '\l':
            his.sendLeft();
            break;
        case '\u':
            his.sendUp();
            break;
        case '\d':
            his.sendDown();
            break;
        default:
            his.insertChar(tecla);
            break;
    }
}

int main () {
    Historico his;
    std::string texto;
    std::cin >> texto;
    his.pushEstado(texto);
    char tecla;
    while(std::cin >> tecla){
        controle(his, tecla);
        std::cout << his.toString() << std::endl;
    }
    return 0;
}
