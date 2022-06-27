#include <vector>
#include <list>
#include <iostream>
#include <sstream>

using namespace std;

struct Client {
    string name {""};
    int docs {0};
    int patience { 0 };

    Client(string name, int docs, int patience) {
        this->name = name;
        this->docs = docs;
        this->patience = patience;
    }

    string str() {
        stringstream ss;
        ss << "Cliente: " << this->name << " Documentos: " << this->docs << " Patience: " << this->patience;
        return ss.str();
    }
};

std::string fmt(auto data, string open = "[", string close = "]", string sep = ", ") {
    std::ostringstream ss;
    ss << open;
    for (auto it = data.begin(); it != data.end(); ++it)
        ss << (it != data.begin() ? sep : "") << *it;
    ss << close;
    return ss.str();
}

struct Bank {
    vector<Client*> tellers;    //caixas
    list<Client*> queue_in;     //fila de entrada
    list<Client*> queue_out;    //fila de saida
    int docs_gain {0};          //documentos processados
    int docs_lost {0};          //documentos perdidos
    int tics {0};               //quantidade de tempo que passou

    void tic() {
        tics++;
        empty_queue_out();
        for (int i = 0; i < (int) tellers.size(); i++)
            process_teller(i);
        decrease_patience();
    }

    Bank(int teller_size) {
        for (int i = 0; i < teller_size; i++)
            tellers.push_back(nullptr);
    }

    ~Bank() {
        for (int i = 0; i < (int) tellers.size(); i++)
            if (tellers[i] != nullptr)
                delete tellers[i];
    }

    void arrive(std::string name, int docs, int patience) {
        Client * client = new Client(name, docs, patience);
        queue_in.push_back(client);
    }

    bool empty() {
        return queue_in.empty() && queue_out.empty();
    }

    void empty_queue_out() {
        for (auto it = queue_out.begin(); it != queue_out.end(); it++) {
            docs_lost += (*it)->docs;
            delete *it;
        }
        queue_out.clear();
    }

    void process_teller(int index) {
        if (tellers[index] != nullptr) {
            if (tellers[index]->docs > 0) {
                docs_gain++;
                tellers[index]->docs--;
            } else {
                queue_out.push_back(tellers[index]);
                tellers[index] = nullptr;
            }
        } else {
            if (!queue_in.empty()) {
                tellers[index] = queue_in.front();
                queue_in.pop_front();
            }
        }
    }

    void decrease_patience() {
        for (auto it = queue_in.begin(); it != queue_in.end(); it++) {
            if ((*it)->patience > 0) {
                (*it)->patience--;
            } else {
                queue_out.push_back(*it);
                docs_lost += (*it)->docs;
            }
        }
        queue_in.remove_if([](Client* c) { return c->patience == 0; });
    }

    void finish() {
        while (!empty())
            tic();
    }

    std::string str() {
        std::stringstream ss;
        for (auto client : tellers)
            ss << "[" << (client == nullptr ? "" : client->str()) << "]";
        ss << "\nin  :" << fmt(queue_in, "{", "}", " ");
        ss << "\nout :" << fmt(queue_out,  "{", "}", " ");
        ss << "\ngain:" << docs_gain << " lost:" << docs_lost;
        return ss.str();
    }

};

int main() {
    Bank banco(3);

    while(true) {
        string line, cmd;
        getline(cin, line);
        cout << "$" << line << "\n";
        stringstream ss(line);
        ss >> cmd;
        if (cmd == "end") {
            break;
        }else if (cmd == "show") {
            std::cout << banco.str() << "\n";
        } else if (cmd == "in") {
            string name { };
            int docs { }, patience { };
            ss >> name >> docs >> patience;
            banco.arrive(name, docs, patience);
        } else if (cmd == "init") {
            int size { };
            ss >> size;
            banco = Bank(size);
        } else if (cmd == "tic") {
            banco.tic();
        } else if (cmd == "finish") {
            banco.finish();
        } else {
            cout << "fail: command not found\n";
        }
    }
}