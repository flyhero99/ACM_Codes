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
#define inf 0x3f3f3f3f

const int maxn = 5e5+10;

template<class T>
void show(T a[], int len) {
    for(int i = 0; i <= len; i++)
        cout << a[i] << " ";
    cout << endl;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}

int main(){
    int T;
    while(cin >> T) {
        ll a1, a2, res=0, tmp, sum=0;
        cin >> a1;       
        if(T == 1) {
            puts("0");
            continue;
        }
        for(int i = 1; i < T; i++) {
            cin >> a1;
            sum += i*a1;
            sum %= 2;
        }
        if(sum & 1) {
            puts("1");
        }
        else {
            puts("0");
        }
    }
    return 0;
}