#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cmath>
using namespace std;

bool isPrime(int n) {
    if(n == 1) return false;
    if(n == 2 || n == 3) return true;
    for(int i = 2; i*i <= n; i++) 
        if(n % i == 0) return false;
    return true;
}

int n;
vector<int> vec;

void solve() {
    if(n == 1) {
        for(int i = 2; i <= 10; i++) {
            if(isPrime(i)) vec.push_back(i);
        }
    }
    else {
        for(int i = pow(10, n/2 - 1); i < pow(10, n/2); i++) {
            int huiw;
            if(n & 1) { // 长度为奇数
                for(int mid = 0; mid <= 9; mid++) {
                    // cout << i << endl;
                    string tmp = to_string(i);
                    // cout << tmp << endl;
                    int l = 0, r = (int)tmp.length()-1;
                    while(l < r) { // 构造回文串
                        swap(tmp[l], tmp[r]);
                        l++, r--;
                    }
                    // cout << to_string(i)+to_string(mid)+tmp << endl;
                    huiw = stoi(to_string(i)+to_string(mid)+tmp);
                    if(isPrime(huiw)) vec.push_back(huiw);
                }
            }
            else {
                string tmp = to_string(i);
                int l = 0, r = (int)tmp.length()-1;
                while(l < r) {
                    swap(tmp[l], tmp[r]);
                    l++, r--;
                }
                huiw = stoi(to_string(i)+tmp);
                if(isPrime(huiw)) vec.push_back(huiw);
            }
        }
    }
}

int main() {
    while(cin >> n) {
        vec.clear();
        solve();
        printf("%d\n", vec.size());
        sort(vec.begin(), vec.end());
        if(vec.size() == 0) cout << endl;
        for(int i = 0; i < vec.size(); i++) {
            printf("%d%c", vec[i], i==(vec.size()-1) ? '\n' : ' ');
        }
    }
}