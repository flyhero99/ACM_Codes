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

const int maxn = 5e4+10;

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

int cas;
string a, b;

int m[26];
bool vis[26];

int main() {
	cin >> cas;
	while(cas--) {
		cin >> a; cin >> b;
		mem(m, 0); mem(vis, 0);
		for(int i = 0; i < a.length(); i++) {
			int tmpa = a[i]-'a', tmpb = b[i]-'a';
			if(!vis[tmpa]) {
				m[tmpa] = tmpb;
				vis[tmpa] = true;
			}
		}
		string c;
		for(int i = 0; i < a.length(); i++) {
			int tmpa = a[i]-'a';
			c.push_back('a'+m[tmpa]);
		}
		// cout << c << endl;
		printf("%s\n", c.compare(b) == 0 ? "YES" : "NO");
	}
	return 0;
}
