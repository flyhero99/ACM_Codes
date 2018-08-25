#include<stdio.h>
#include<string.h>
#include<algorithm>
int max(int a,int b){return a>b?a:b;}
struct Node{int x,y,v;}node[100005];
long long arr[1<<18],M,ans;
int sortedy[100005];
void update(int y,int val){y++;
    for(arr[y+=M]=max(arr[y],val),y/=2;y;y/=2)
        arr[y]=max(arr[y*2],arr[y*2+1]);
}
int query(int l,int r){l++,r++;
    for(ans=-1,l+=M-1,r+=M+1;l^r^1;l/=2,r/=2){
        if(~l&1)ans=max(ans,arr[l^1]);
        if( r&1)ans=max(ans,arr[r^1]);
    }return ans;
}
int main(){
    int t;scanf("%d",&t);
    while(t--){
        int n;scanf("%d",&n);
        memset(arr,0,sizeof arr);
        M=1;while(M-2<n)M*=2;
        for(int i=1;i<=n;i++)
            scanf("%d%d%d",&node[i].x,&node[i].y,&node[i].v);
        for(int i=1;i<=n;i++)
            sortedy[i]=node[i].y;
        std::sort(sortedy,sortedy+n+1);
        int sortlen=std::unique(sortedy,sortedy+n+1)-sortedy;
        std::sort(node+1,node+1+n,[](Node a,Node b){
            return a.x==b.x?a.y>b.y:a.x<b.x;
        });
        long long ans=0;
        for(int i=1;i<=n;i++){
            int pos=std::lower_bound(sortedy,sortedy+n+1,node[i].y)-sortedy;
            long long qret=query(0,pos-1)+node[i].v;
            ans=max(ans,qret);
            update(pos,qret);
        }printf("%lld\n",ans);
    }
    return 0;
}