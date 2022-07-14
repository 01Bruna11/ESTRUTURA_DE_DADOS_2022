#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

/*********************************************************
 *                  MAP - MANIPULAÇÃO                    *
 *********************************************************/

std::vector<int> sozinhos(const std::vector<int>& v) {
    std::vector<int> novo;
    
    for (int i = 0; i < v.size(); i++) {
		for (int j = 0; j < v.size(); j++) {
		   if(v[i] != v[j]) {
		       novo.push_back(v[i]);
		   return novo;
		   }
		}
	}
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    os << "[ ";
    for (auto i : v)
        os << i << " ";
    os << "]";
    return os;
}

int mais_ocorrencias(const std::vector<int>& v) {
    std::vector<int> novo;
    int cont = 0;
    
    for(int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if(v[i] == v[j]) {
                cont++;
            }
        }
    }
    return cont;
}

//MAIS_RECORRENTES ---> Quais os níveis de stress mais recorrentes. (abs)

std::vector<int> mais_recorrentes(const std::vector<int>& v) {
    std::vector<int> novo;
    int cont = 0;
    
    for(int i = 0; i < v.size(); i++) {
        for (int j = i + 1; j < v.size(); j++) {
            if(v[i] == v[j]) {
                novo.push_back(v[i]);
            return novo;
            }
        }
    }


/*********************************************************
 *                     PROXIMIDADE                       *
 *********************************************************/

int briga(const std::vector<int>& v) {
    std::vector<int> novo;
    int cont = 0;
    int i = 0;
    
    for(i = 0; i < v.size(); i++) {
        if(v[i-1] > 30 && v[i] > 50 && v[i+1] > 30) {
            cont++;
        }
    }
    return cont;
}

int apaziguado(const std::vector<int>& v) {
    std::vector<int> novo;
    int pos = 0;
    
    for(int i = 0; i < v.size(); i++) {
        if(v[i] > 80 && v[i+1] < 10 || v[i] > 80 && v[i-1] < 10) {
            pos = i;
        }
    }
    return pos;


/*********************************************************
 *                     SEQUÊNCIAS                        *
 *********************************************************/

int quantos_times(const std::vector<int>& v) {
    std::vector<int> novo;
    int cont = 0;
    
    for(int i = 0; i < v.size(); i++) {
        if(v[i] > 0 && v.size()-1 > 0 || v[i] < 0 && v.size()-1 < 0) {
           cont++;
        }
    }
    return cont;
}

//MAIOR_TIME ---> Qual o maior time que apareceu na fila?

char maior_time(const std::vector<int>& v) {
    std::vector<int> novo;
    int contM = 0, contH = 0;
    
    for(int i = 0; i < v.size(); i++) {
        if(v[i] > 0 && v.size()-1 > 0) {
           contM++;
        }
        if(v[i] < 0 && v.size()-1 < 0) {
            contH++;
        }
    }
    
    if(contM > contH) {
        std::cout << "Time Mulheres";
    } else {
        std::cout << "Time Homens";
    }
}

//SOZINHOS ---> Quantas pessoas não estavam em um time?

int sozinhos2(const std::vector<int>& v) {
    std::vector<int> novo;
    int cont = 0;
    
    for(int i = 0; i < v.size(); i++) {
        if(v[i] > 0 && v[i-1] > 0 || v[i] < 0 && v[i-1] < 0) {
           cont++;
        }
    }
    return cont;
    
}

/*********************************************************
 *                        GRUPOS                         *
 *********************************************************/

int casais(const std::vector<int>& v) {
    std::vector<int> novo;
    int x = 0, cont = 0;
    
    for(int i = 0; i < v.size(); i++) {
        for(int j = i + 1; j < v.size(); j++) {    
            if((v[i] > 0 == v[j] < 0) || (v[j] > 0 && v[i] < 0)) {
                cont++;   
            }
       }
    } 
        
    return cont/2;
    
}

int trios(const std::vector<int>& v) {
    std::vector<int> novo;
    int x = 0, cont = 0;
    
    for(int i = 0; i < v.size(); i++) {
        if(v[i] == v[i+1] && v[i] == v[i-1]) {
            cont++;   
       }
    } 
        
    return cont;
    
}

/*********************************************************
 *                      ALTERAÇÃO                        *
 *********************************************************/

//REMOVE ---> Dado a pessoa X, como fica a fila após remover X?

std::vector<int> remove(std::vector<int>& v) {
    std::vector<int> novo;
    int x = 0;
    std::cin >> x;
    
    for(int i = 0; i < v.size(); i++) {
        v.erase(v.begin() + 2);
    return v;
    }
}

//INSERT --->  Como fica a fila se eu inserir a pessoa X na posição Y.

std::vector<int> inserir(std::vector<int>& v) {
    
    for(int i = 0; i < v.size(); i++) {
        v.insert(v.begin() + 3, v[i+4]);
    return v;
    }
    
}

std::vector<int> dance(std::vector<int>& v) {
    
    for(int i = 0; i < v.size(); i++) {
        for(int j = i+1; j < v.size(); j++) {
            if(v[i] == v[j]) {
                v.erase(v.begin() + i, v.begin() + j+1);
            return v;
            }
        }
    } 
    
}

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    for(int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

int main () 
{

/*********************************************************
 *                  MAP - MANIPULAÇÃO                    *
 *********************************************************/

std::vector<int> v = {4, 1, 3, -1, -3, -3}; // Tá voltando valor da posição 0
    for(int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        
    std::cout << "\n";
    
    std::cout << sozinhos(v) << "\n";

    std::cout << "\n";
    
    std::vector<int> v = {1, -5, 4, 5, -1, -5, -5}; // Tá voltando valor da posição 0
    for(int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        std::cout << "\n";
        std::cout << sozinhos2(v) << "\n";
        std::cout << "\n";

/*********************************************************
 *                     PROXIMIDADE                       *
 *********************************************************/
std::vector<int> v = {1, -5, 4, 5, -1, -5, -5} 
for (int i = 0; i < v.size(); i++)
    std::cout << v[i] << " ";
    std::cout << "\n";
    std::cout << proximidade(v) << "\n";
    std::cout << "\n";

/*********************************************************
 *                     SEQUÊNCIAS                        *
 *********************************************************/

std::vector<int> v = {5, 7, -6, -3}; // Tá voltando valor da posição 0
    for(int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        std::cout << "\n";
        std::cout << sequencia(v) << "\n";
        std::cout << "\n";

/*********************************************************
 *                        GRUPOS                         *
 *********************************************************/

std::vector<int> v = {2, -2, 3, -3}; // Tá voltando valor da posição 0
    for (int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        std::cout << "\n";
        std::cout << casais(v) << "\n";
        std::cout << "\n";
        std::cout << trios(v) << "\n";
        std::cout << "\n";

/*********************************************************
 *                      ALTERAÇÃO                        *
 *********************************************************/

//REMOVE ---> Dado a pessoa X, como fica a fila após remover X?

 std::vector<int> v = {1, 2, 3, 4, 5}; // Tá voltando valor da posição 0
    for(int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        
    std::cout << "\n";
    
    std::cout << remove(v) << "\n";
    
    std::cout << "\n";

//INSERT --->  Como fica a fila se eu inserir a pessoa X na posição Y.

 std::vector<int> v = {1, 2, 3, 4, 5}; // Tá voltando valor da posição 0
    for(int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        
    std::cout << "\n";
    
    std::cout << inserir(v) << "\n";
    
    std::cout << "\n";

 std::vector<int> v = {6, 1, 1, 3, 4, 5}; // Tá voltando valor da posição 0
    for(int i = 0; i < v.size(); i++)
        std::cout << v[i] << " ";
        
    std::cout << "\n";
    
    std::cout << dance(v) << "\n";
    
    std::cout << "\n";

return 0;

}