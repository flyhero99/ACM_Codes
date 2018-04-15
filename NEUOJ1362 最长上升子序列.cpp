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

int low[maxn], a[maxn];
int n, ans;

int binary_search(int a[], int r, int x) {
    int l = 1, mid;
    while(l <= r) {
        mid = (l+r) >> 1;
        if(a[mid] <= x)
            l = mid+1;
        else 
            r = mid-1;
    }
    return l;
}

int main() {
	while(scanf("%d", &n) != EOF) {
		for(int i = 1; i <= n; i++) {
        	scanf("%d", &a[i]); 
        	low[i] = inf;
    	}
	    low[1] = a[1]; 
	    ans = 1; 
	    for(int i = 2; i <= n; i++) {
	        if(a[i] >= low[ans])
	            low[++ans] = a[i];
	        else
	            low[binary_search(low, ans, a[i])] = a[i];
	    }
	    printf("%d\n", ans);
	}
    return 0;
}