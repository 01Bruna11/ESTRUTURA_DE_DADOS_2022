#include <iostream>
#include <list>
#include <sstream>

struct State{
    std::list<char> text;
    std::list<char>::iterator cursor;

    State(){
        cursor = text.end();
    }

    State(std::string init){
        for(int i = 0; i < (int) init.size(); i++){
            text.push_back(init[i]);
        }
        cursor = text.end();
    }

    State(const State& other){
        text = other.text;
        cursor = other.cursor;
    }

    State& operator = (const State& other){
        text = other.text;
        cursor = other.cursor;
        return *this;
    }

    std::string str(){
        std::stringstream ss;
        for(auto it = text.begin(); it != text.end(); ++it){
            ss << *it;
        }
        return ss.str();
    }

    void insert(char c){
        text.insert(cursor, c);
        cursor++;
    }

    void erase(){
        if(cursor != text.begin()){
            cursor--;
            text.erase(cursor);
        }
    }

    std::string getText() {
        std::stringstream ss;
        for(auto it = text.begin(); it != text.end(); it++){
            if(it == cursor)
                ss << "|";
            ss << *it;
        }    
        if(cursor == text.end())
            ss << "|";
        return ss.str();
    }

};

struct Ambient{
    std::list<State> states;
    std::list<State>::iterator ite;

    Ambient(std::string init_text = ""){
        states.push_back(State(init_text));
        ite = states.begin();
    }

    void controlZ(){
        if(states.size() > 1){
            states.pop_back();
            ite = states.end();
            ite--;
        }
    }

    void controlY(){
        if(states.size() > 1){
            states.pop_back();
            ite = states.end();
            ite--;
        }
    }

    void insertChar(char c){
        auto prox = ite;
        states.erase(++prox, states.end());
        states.push_back(*ite);
        ite = --states.end();

        ite->text.insert(ite->cursor, c);
    }

    void eraseChar(){
        auto prox = ite;
        states.erase(++prox, states.end());
        states.push_back(*ite);
        ite = --states.end();

        ite->erase();
    }

    void moveCursor(char c){
        auto prox = ite;
        states.erase(++prox, states.end());
        states.push_back(*ite);
        ite = --states.end();

        if(c == '>'){
            if(ite->cursor != ite->text.end()){
                ite->cursor++;
            }
        }
        else if(c == '<'){
            if(ite->cursor != ite->text.begin()){
                ite->cursor--;
            }
        }
    }

    std::string getText(){
        return ite->getText();
    }

    void processKey(Ambient& amb, char tecla){
        if(tecla == 'z'){
            amb.controlZ();
        }
        else if(tecla == 'y'){
            amb.controlY();
        }
        else if(tecla == 'r'){
            amb.insertChar('\n');
        }
        else if(tecla == 'b'){
            amb.eraseChar();
        }
        else if(tecla == 'd'){
            amb.eraseChar();
        }
        else if(tecla == '>'){
            amb.moveCursor('>');
        }
        else if(tecla == '<'){
            amb.moveCursor('<');
        }
        else{
            amb.insertChar(tecla);
        }
    }
        
};

int main() {
    Ambient amb;
    std::string line;
    while(std::getline(std::cin, line)){
        for(int i = 0; i < (int) line.size(); i++){
            amb.processKey(amb, line[i]);
        }
        std::cout << amb.getText() << std::endl;
    }
    return 0;
}

