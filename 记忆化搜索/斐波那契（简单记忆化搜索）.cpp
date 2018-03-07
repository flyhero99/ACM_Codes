//mem[n]记录递归中间结果

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 50001;

ll mem[maxn];

ll fibb(int n) {
    if(n <= 1) return (ll) n;
    if(mem[n] != 0) return mem[n];
    return mem[n] = fibb(n-1) + fibb(n-2);
}

int main() {
    int n;
    while(cin >> n) {
        cout << fibb(n) << endl;
    }
    return 0;
}