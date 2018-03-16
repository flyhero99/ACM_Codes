#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define ll long long
#define pb push_back
#define mp make_pair
#define pii pair<int, int>
#define mem(a, b) memset(a, b, sizeof(a))

const int maxn = 200010;

int dp[maxn];
int num[7];
int sum;

void Complete_Pack(int value) {
    for(int i = value;i <= sum;i++) dp[i] = max(dp[i], dp[i-value]+value);
}

void ZeroOne_Pack(int value) {
    for(int i = sum;i >= value;i--) dp[i] = max(dp[i], dp[i-value]+value);
}

void Multi_Pack(int value, int number) {
    if(value*number >= sum) Complete_Pack(value);
    else {
        int k = 1;
        while(k < number) {
            ZeroOne_Pack(k*value);
            number -= k;
            k <<= 1;
        }
        ZeroOne_Pack(number*value);
    }
}

int main() {
    for(int cas = 1;;cas++) {
        sum = 0;
        for(int i = 1;i <= 6;i++) {
            scanf("%d", &num[i]);
            sum += i*num[i];
        }
        if(sum == 0) break;
        mem(dp, 0);
        printf("Collection #%d:\n", cas);
        if(sum & 1) printf("Can't be divided.\n\n");
        else {
            sum /= 2;
            for(int i = 1;i <= 6;i++) Multi_Pack(i, num[i]);
            if(dp[sum] == sum) printf("Can be divided.\n\n");
            else printf("Can't be divided.\n\n");
        }
    }
    return 0;
}