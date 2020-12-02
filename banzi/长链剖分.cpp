int dep[maxn],height[maxn],son[maxn];
vector<int> g[maxn];
void dfs1(int now,int fa) {
    height[now]=dep[now]=dep[fa]+1;
    for(int x:g[now]) {
        if(x==fa) continue;
        dfs1(x,now);
        if(height[x]>height[now]) {
            height[now]=height[x];
            son[now]=x;
        }
    }
}
// 求每个节点子树中,距离为k的节点数量,找到一个k,使节点数最多
int tmp[maxn],*dp[maxn],*p,ans[maxn];
void dfs2(int now,int fa) {
    dp[now][0]=1;
    if(son[now]) {
        dp[son[now]]=dp[now]+1;
        dfs2(son[now],now);
        ans[now]=ans[son[now]]+1;
    }
    for(int x:g[now]) {
        int len=height[x]-dep[x]+1;
        if(x==fa||x==son[now]) continue;
        dp[x]=p;
        p+=len;
        dfs2(x,now);
        for(int j=0;j<len;j++) {
            dp[now][j+1]+=dp[x][j];
            if(dp[now][j+1]>dp[now][ans[now]]||(dp[now][j+1]==dp[now][ans[now]]&&ans[now]>j+1)) {
                ans[now]=j+1;
            }
        }
    }
    if(dp[now][ans[now]]==1) ans[now]=0;
}
int main()
{
    ios::sync_with_stdio(false);cin.tie(0);
    int n;
    cin>>n;
    rep(i,1,n-1) {
        int u,v;
        cin>>u>>v;
        g[u].pb(v);
        g[v].pb(u);
    }
    dfs1(1,0);
    p=tmp;
    dp[1]=p;
    p+=height[1];
    dfs2(1,0);
    rep(i,1,n) cout<<ans[i]<<'\n';
    return 0;
}