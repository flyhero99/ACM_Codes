#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define MOD 1000000007

#define INF 0x3f3f3f3f
using namespace std;

int point,road;
int u,v,w,st,ed;

struct qnode{
    int v , c ;
    qnode(int tempv = 0 , int tempc = 0) : v(tempv),c(tempc){ }
    bool operator < (const qnode &r) const{
        return c > r.c ;
    }
};

struct Edge{
    int start , cost ;
    Edge(int tempstart = 0 , int tempcost = 0 ) : start(tempstart),cost(tempcost){}

};
vector <Edge> E[250] ;
bool vis[250];
int dist[250];

void dij(int start) {
    memset(vis,0,sizeof(vis));
    for(int i = 0 ; i < point ; i ++ ) dist[i] = INF ;
    priority_queue <qnode> infi ;
    while(! infi.empty() )  infi.pop(); // reset
    dist[start] = 0;

    infi.push(qnode(start , 0));
    qnode tmp ;
    while( ! infi.empty() ){
        tmp = infi.top() ;
        infi.pop();
        int u =tmp.v ;
        if(vis[u]) continue ;
        vis[u] = true ;
        for(int i = 0 ; i < E[u].size() ; i ++ ){
            int v = E[u][i].start ;
            int cost = E[u][i].cost ;
            if(! vis[v] ){
                dist[v] = min(dist[v],dist[u] + cost);
                infi.push(qnode(v,dist[v]));
            }
        }
    }
}

void addedge(int u,int v,int w){
  E[u].push_back(Edge(v,w));
  E[v].push_back(Edge(u,w));
}

int main(){

 while(cin >> point >> road ){
    for(int i = 0; i <= point; ++ i) E[i].clear();
    for(int i = 0; i < road ; ++ i){
        scanf("%d %d %d",&u,&v,&w);
        addedge(u,v,w);
    }
    scanf("%d%d",&st,&ed);
    dij(st);
    if(dist[ed] == INF) puts("-1");
    else printf("%d\n",dist[ed]);
 }
 return 0;
}
