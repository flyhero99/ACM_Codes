#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5;
const int mod = 1e9+7;

int gcd(int a, int b) {
    while(b != 0) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int exgcd(int a, int b, int &x, int &y) {
    if(b == 0) { x = 1; y = 0; return a; }
    int ans = exgcd(b, a%b, x, y);
    int tmp = x;
    x = y;
    y = tmp - (a/b)*y;
    return ans;
}


int main() {
    int t; scanf("%d", &t);
    while(t--) {
        int a, b; scanf("%d %d", &a, &b);
        int x, y;
        int inv = exgcd(a, b, x, y);
        if(inv != 1) cout << "Not Exist" << endl;
        else {
            // x = (x % b + b) % b;
            x %= b;
            if(x <= 0) x += b;
            cout << x << endl;
        }
    }
    return 0;
}