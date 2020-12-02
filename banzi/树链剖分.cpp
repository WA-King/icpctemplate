int dep[maxn],son[maxn],siz[maxn],tp[maxn],fa[maxn];// tp链顶
int id[maxn],rk[maxn],cnt=0;// id dfs序, rk 反dfs序
vector<int> g[maxn];
void dfs1(int now,int f,int d) {
    dep[now]=d,fa[now]=f,siz[now]=1;
    for(int x:g[now]) {
        if(x==f) continue;
        dfs1(x,now,d+1);
        siz[now]+=siz[x];
        if(siz[x]>siz[son[now]]) son[now]=x;
    }
}
void dfs2(int now,int t) {
    tp[now]=t,id[now]=++cnt,rk[cnt]=now;
    if(!son[now]) return ;
    dfs2(son[now],t);
    for(int x: g[now]) {
        if(x==fa[now]||x==son[now]) continue;
        dfs2(x,x);
    }
}