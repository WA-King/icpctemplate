const int maxn=405;
const int mod=1e9+7;
const int inf=2e9;
ll w[maxn][maxn];
ll lx[maxn],ly[maxn];
int linker[maxn];//linker[i]:右边第i个点的匹配对象
ll slack[maxn];
int n;
bool visy[maxn];
int pre[maxn];
void bfs(int k) {
    int x,y=0,yy=0,delta;
    memset(pre,0,sizeof(pre));
    for(int i=1;i<=n;i++) slack[i]=inf;
    linker[y]=k;
    while(1) {
        x=linker[y];delta=inf;visy[y]=true;
        for(int i=1;i<=n;i++) {
            if(!visy[i]) {
                if(slack[i]>lx[x]+ly[i]-w[x][i]) {
                    slack[i]=lx[x]+ly[i]-w[x][i];
                    pre[i]=y;
                }
                if(slack[i]<delta) delta=slack[i],yy=i;
            }
        }
        for(int i=0;i<=n;i++) {
            if(visy[i])lx[linker[i]]-=delta,ly[i]+=delta;
            else slack[i]-=delta;
        }
        y=yy;
        if(linker[y]==-1) break;
    }
    while(y) linker[y]=linker[pre[y]],y=pre[y];
}
ll km() {
    memset(lx,0,sizeof(lx));
    memset(ly,0,sizeof(ly));
    memset(linker,-1,sizeof(linker));
    for(int i=1;i<=n;i++) {
        memset(visy,false,sizeof(visy));
        bfs(i);
    }
    ll ans=0;
    for(int i=1;i<=n;i++) ans+=w[linker[i]][i];
    return ans;
}
