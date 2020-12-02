struct Graph {
    int h[maxn],to[maxn],nex[maxn],c[maxn],cnt=0;
    void init(int n) {
        cnt=0;
        for(int i=0;i<=n;i++) h[maxn]=0;
    }
    void addedge(int u,int v,int cost=0) {
        to[++cnt]=v;
        nex[cnt]=head[u];
        c[cnt]=cost;
        head[u]=cnt;
    }
    void addedge2(int u,int v,int cost=0) {
        addedge(u,v,cost); addedge(v,u,cost);
    }
};
