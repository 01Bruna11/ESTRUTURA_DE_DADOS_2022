#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int main () {
    queue<string> time;
    int time1, time2;
    
    for(int i = 'A'; i < 'Q'; i++) {
        time.push(string(1, i));
    }
    for (int i = 0; i < 15; i++) {
        cin >> time1 >> time2;
        if (time1 > time2) {
            time.pop();
        } else {
            time.pop();
            time.pop();
        }
    }
    cout << time.front() << endl;
    return 0;

}