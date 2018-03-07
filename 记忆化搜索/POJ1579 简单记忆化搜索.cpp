//记忆化搜索写法：设立边界递归终止条件，其余情况用数组记录中间结果


//#include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int maxn = 1000005;

ll mem[21][21][21];
int a, b, c;


ll w(ll a, ll b, ll c) {
    if(a <= 0 || b <= 0 || c <= 0) return 1;
    if(mem[a][b][c] != 0)
        return mem[a][b][c];
    if(a < b && b < c)
        return mem[a][b][c] = w(a, b, c-1) + w(a, b-1, c-1) - w(a, b-1, c);
    else
        return mem[a][b][c] = w(a-1, b, c) + w(a-1, b-1, c) + w(a-1, b, c-1) - w(a-1, b-1, c-1);

}

int main() {
    while(true) {
        cin >> a >> b >> c;
        if(a == -1 && b == -1 && c == -1) break;
        ll ans;
        if(a <= 0 || b <= 0 || c <= 0) ans = 1;
        else if(a > 20 || b > 20 || c > 20) ans = w(20, 20, 20);
        else ans = w(a, b, c);
        cout << "w(" << a << ", " << b << ", " << c << ") = " << ans << endl;
    }
    return 0;
}