 #include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

int main () {
    int n;
    std::cin >> n;
    std::vector<int> vet(n);
    for (int i = 0; i < n; i++) {
        std::cin >> vet[i];
    }
    std::vector<int> rvet(n);
    std::reverse_copy(vet.begin(), vet.end(), rvet.begin());
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += vet[i];
    }
    int mult = 1;
    for (int i = 0; i < n; i++) {
        mult *= vet[i];
    }
    int min = vet[0];
    for (int i = 1; i < n; i++) {
        if (vet[i] < min) {
            min = vet[i];
        }
    }
    std::stringstream ss;
    for (int i = 0; i < n; i++) {
        ss << vet[i] << " ";
    }
    std::cout << ss.str() << '\n';
    std::stringstream ss2;
    for (int i = 0; i < n; i++) {
        ss2 << rvet[i] << " ";
    }

    std::ostream &os = std::cout;
    os << ss2.str() << '\n';
    os << sum << '\n';
    os << mult << '\n';
    os << min << '\n';
    std::vector<int> inv(n);
    std::reverse_copy(vet.begin(), vet.end(), inv.begin());
    for (int i = 0; i < n; i++) {
        os << inv[i] << " ";
    }
    os << '\n';
    return 0;
}
