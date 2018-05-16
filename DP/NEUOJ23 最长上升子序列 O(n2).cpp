#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 5000+5;

int t;

string s1, s2;
int dp[maxn][maxn];

int main() {
    scanf("%d", &t);
    while(t--) {
        cin >> s1 >> s2;
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < s1.length(); i++) {
            for(int j = 0; j < s2.length(); j++) {
                if(s1[i] == s2[j]) dp[i+1][j+1] = dp[i][j]+1;
                else dp[i+1][j+1] = max(dp[i+1][j], dp[i][j+1]);
            }
        }
        cout << dp[s1.length()][s2.length()] << endl;
    }
    return 0;
}