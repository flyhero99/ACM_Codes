#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define inf 0x3f3f3f3f

const int maxn = 400000+5;
const int maxm = 100+5;

int n, rev, qury;
deque<int> deq;
int a[maxn];
int l, r;

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

int cmp(int a, int b) {
    if(a == 1 && b == 1) return 0;
    return 1;
}

int main() {
    int t = read();
    for(int cas = 1; cas <= t; cas++) {
        n = read();
        printf("Case #%d:\n", cas);
        rev = 0; l = n; r = n-1; deq.clear();
        for(int i = 1; i <= n; i++) {
            char ss[10];
            scanf("%s", ss);
            if(ss[0] == 'P' && ss[1] == 'U') {
                int x = read();
                if(rev == 0) {
                    a[++r] = x;
                    if(x == 0) deq.push_back(r);
                }
                else {
                    a[--l] = x;
                    if(x == 0) deq.push_front(l);
                }
            }
            else if(ss[0] == 'P' && ss[1] == 'O') {
                if(rev == 0) {
                    if(a[r] == 0) deq.pop_back();
                    r--;
                }
                else {
                    if(a[l] == 0) deq.pop_front();
                    l++;
                }
            }
            else if(ss[0] == 'R') rev = !rev;
            else if(ss[0] == 'Q') {
                if(deq.empty()) { // 没有0
                    if(r < l) {
                        printf("Invalid.\n");
                        continue;
                    }
                    else {
                        int num = r-l-1;
                        printf("%d\n", num&1);
                        continue;
                    }
                }
                else {
                    if(rev == 0) { // 从左到右
                        int fnt = deq.front();
                        int num = fnt-l;
                        if(num & 1) {
                            if(fnt == r) puts("1");
                            else puts("0");
                        }
                        else {
                            if(fnt == r) puts("0");
                            else puts("1");
                        }
                    }
                    else { // 从右到左
                        int bck = deq.back();
                        int num = r-bck;
                        if(num & 1) {
                            if(bck == l) puts("1");
                            else puts("0");
                        }
                        else {
                            if(bck == l) puts("0");
                            else puts("1");
                        }
                    }
                }
            }
            // cout << "l: " << l << " r: " << r << endl;
            // for(int i = 0; i < deq.size(); i++) cout << deq[i] << ' ';
            // cout << endl;
        }
    }
    return 0;
}