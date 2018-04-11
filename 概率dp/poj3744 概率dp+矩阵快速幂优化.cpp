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
#define mem(g, h) memset(g, h, sizeof(g))

const int maxn = 1e8+5;

int n;
int x[12];
double p, ans;

struct mat {
    double a[2][2];
};

mat init() {
    mat res;
    memset(res.a, 0, sizeof(res.a));
    for(int i = 0;i < 2;i++) {
        res.a[i][i] = 1;
    }
    return res;
}

mat mul(mat aa, mat bb) {
    mat ans;
    for(int i = 0;i < 2;i++) {
        for(int j = 0;j < 2;j++) {
            ans.a[i][j] = 0;
            for(int k = 0;k < 2;k++) {
                ans.a[i][j] += aa.a[i][k]*bb.a[k][j];
            }
        }
    }
    return ans;
}

mat qpow(mat aa, ll bb) {
    mat res = init();
    while(bb) {
        if(bb & 1) {
            res = mul(res, aa);
        }
        aa = mul(aa, aa);
        bb >>= 1;
    }
    return res;
}

int main() {
    while(scanf("%d %lf", &n, &p) != EOF) {
        for(int i = 1; i <= n; i++) scanf("%d", &x[i]);
        sort(x+1, x+n+1);
        if(x[1] == 1) {
            printf("%.7f\n", 0);
            continue;
        }
        mat coef, res;
        ans = 1.0;
        coef.a[0][0] = p, coef.a[0][1] = 1.0-p, coef.a[1][0] = 1.0, coef.a[1][1] = 0.0;
        for(int i = 1; i <= n; i++) {
            if(x[i] == x[i-1]) continue;
            if(x[i] == x[i-1]+1) {
                ans = 0.0;
                break;
            }
            res = qpow(coef, x[i]-x[i-1]-1);
            ans *= (1-res.a[0][0]);
        }
        printf("%.7f\n", ans);
    }
    return 0;
}