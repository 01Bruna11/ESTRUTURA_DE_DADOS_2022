#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cmath>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

const int N = 101;

char a[N][N];
int qx[N*N], qy[N*N];
int d[N][N];

int main () {
    int n, startL, startC, goalL, goalC;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> a[i][j];
        }
    }
    std::cin >> startL >> startC >> goalL >> goalC;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = -1;
        }
    }
    d[startL][startC] = 0;
    qx[0] = startL;
    qy[0] = startC;
    int qt = 1;
    while (qt > 0) {
        int x = qx[qt-1];
        int y = qy[qt-1];
        qt--;
        if (x == goalL && y == goalC) {
            break;
        }
        if (x > 0 && a[x-1][y] == '.' && d[x-1][y] == -1) {
            d[x-1][y] = d[x][y] + 1;
            qx[qt] = x-1;
            qy[qt] = y;
            qt++;
        }
        if (x < n-1 && a[x+1][y] == '.' && d[x+1][y] == -1) {
            d[x+1][y] = d[x][y] + 1;
            qx[qt] = x+1;
            qy[qt] = y;
            qt++;
        }
        if (y > 0 && a[x][y-1] == '.' && d[x][y-1] == -1) {
            d[x][y-1] = d[x][y] + 1;
            qx[qt] = x;
            qy[qt] = y-1;
            qt++;
        }
        if (y < n-1 && a[x][y+1] == '.' && d[x][y+1] == -1) {
            d[x][y+1] = d[x][y] + 1;
            qx[qt] = x;
            qy[qt] = y+1;
            qt++;
        }
    }
    std::cout << d[goalL][goalC] << std::endl;
    return 0;
}