#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

const int maxn = 5e5+5;
tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> t;
int cas, n, m, tmp, k;
char cmd[10];

int main() {
    cin >> cas;
    while(cas--) {
        t.clear();
        cin >> n >> m;
        int cnt = n;
        for(int i = 0; i < n; i++) {
            cin >> tmp;
            t.insert(tmp);
        }
        while(m--) {
            scanf("%s %d", cmd, &k);
            // for(int i = 0; i < 5; i++) printf("%d\n", *t.find_by_order(i));
            if(strcmp(cmd, "query") == 0) {
                int ans = *t.find_by_order(cnt-k);
                cout << ans << endl;
            }
            else if(strcmp(cmd, "insert") == 0) {
                t.insert(k);
                cnt++;
            }
            else if(strcmp(cmd, "delete") == 0) {
                t.erase(k);
                cnt--;
            }
        }
    }
    return 0;
}