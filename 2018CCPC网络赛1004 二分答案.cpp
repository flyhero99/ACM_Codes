#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool check(ll a, ll d) {
    if(a == d) return false;
    return (a*a-d*d) % (2*d) == 0;
}

bool check2(ll a, ll d) {
    return a*a < 2*d + d*d;
}

int main() {
    int T; scanf("%d", &T);
    while(T--) {
        int n, a; scanf("%d %d", &n, &a);
        if(n > 2 || n == 0) puts("-1 -1");
        else if(n == 1) printf("1 %d\n", a+1);
        else {
            ll l = 1, r = 40000;
            while(l < r-1) {
                ll mid = (l+r) >> 1;
                if(check2(a, mid)) r = mid;
                else l = mid;
            }
            int ans = 0;
            for(int i = r; i > 0; i--) {
                if(check(a, i)) {
                    ans = i;
                    break;
                }
            }
            if(ans) printf("%d %d\n", (a*a-ans*ans)/2/ans, (a*a-ans*ans)/2/ans+ans);
            else puts("-1 -1");
        }
    }
    return 0;
}
