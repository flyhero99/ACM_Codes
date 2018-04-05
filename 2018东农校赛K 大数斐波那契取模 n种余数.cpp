// #include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<stack>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 1e6+5;

typedef unsigned long long ull;
int modnum[maxn];
int Mod;
ull a, b;

int powermod(ull a, ull b, int c) {
    ull ans = 1;
    a %= c;
    while(b) {
        if(b & 1)
           ans = ans * a % c;
        a = a * a % c;
        b >>= 1;
    }
    return ans;
}

int main() {
    int t; scanf("%d", &t);
    while(t--) {
        scanf("%llu %llu %d", &a, &b, &Mod);
        if(Mod == 1 || a == 0) {
            printf("0\n");
            continue;
        }
        modnum[0] = modnum[1] = 1;
        int p = 1;
        for(int i = 2; ; i++) {
            modnum[i] = (modnum[i-1]+modnum[i-2]) % Mod;
            if(modnum[i]==1 && modnum[i-1]==1) {
                p = i-1;
                break;
            }
        }
        printf("%d\n", modnum[powermod(a, b, p)-1]);
    }
    return 0;
}