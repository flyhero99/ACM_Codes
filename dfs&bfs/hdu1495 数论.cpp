// #include<bits/stdc++.h>
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))

const int maxn = 105;
const int maxm = 105;

int n, a, b;

int gcd(int a, int b) {
    return a%b == 0 ? b : gcd(b, a%b);
}

int main() {
    while(cin >> n >> a >> b) {
        if(n == 0 && a == 0 && b == 0) return 0;
        if(a < b) swap(a, b);
        n /= gcd(a, b);
        if(n & 1) printf("NO\n");
        else printf("%d\n", n-1);
    }
}