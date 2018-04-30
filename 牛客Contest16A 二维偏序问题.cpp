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
#define lb lower_bound
#define ub upper_bound
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define ull unsigned long long
#define inf 0x3f3f3f3f
#define il inline
#define lowbit(x) x&-x

const int maxn = 300000+5;
const double eps = 1e-6;
const double pi = 3.141592653589793238462643385;
const int mod = 1e9;

template <class T>
void show(T a[], int len) {
    for(int i = 1; i <= len; i ++) cout << a[i] << " "; cout << endl;
}

inline int read() {
    int x = 0, f = 1; char ch = getchar();
    while(ch<'0' || ch>'9') {if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0' && ch<='9') {x=x*10+ch-'0'; ch=getchar();}
    return x*f;
}

struct node {
    int l, r, ii;
}arr[maxn];

int a[maxn];
int b[maxn];

bool cmp(node a, node b) {
    if(a.l == b.l)
        return a.r < b.r;
    else
        return a.l < b.l;
}

// 按先l后r排序，记录i~n之间最大的r，对于每个arr[i].r, 若arr[i].r > a[i+1]则满足条件，ans++。

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        scanf("%d %d", &arr[i].l, &arr[i].r);
        // if(arr[i].l > arr[i].r) {
        //     arr[i].l = arr[i].r = 0;
        // }
        arr[i].ii = i+1;
    }
    sort(arr, arr+n, cmp);
    // for(int i = 0; i < n; i++) cout << arr[i].l << ' ' << arr[i].r << ' ' << arr[i].ii << endl;
    memset(a, 0, sizeof(a));
    for(int i = n-1; i >= 0;i--) {
        a[i] = max(arr[i].r, a[i+1]);
        // if(arr[i].r > a[i+1]) { // 新的最大值出现
        //     a[i] = arr[i].r; // 更新最大值
        //     b[i] = arr[i].ii; // 记录位置
        // }
        // else {
        //     a[i] = a[i+1]; // i～n最小值=i+1～n最小值
        //     b[i] = b[i+1]; // 最小值位置不变
        // }
    }
    // for(int i = 0; i <= n; i++) cout << a[i] << ' '; cout << endl;
    // for(int i = 0; i <= n; i++) cout << b[i] << ' '; cout << endl;
    int ans = 0;
    for(int i = 0; i < n-1; i++) {
        if(arr[i].r < a[i+1]) { // 找到大于i+1～n之间最大的r
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}