int n,m;
// match[i], i所对应的匹配点
int match[maxn],pre[maxn],vis[maxn],fa[maxn],tim[maxn],idx,ans;
vi g[maxn];
queue<int>Q;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
int lca(int x,int y) {
	for (++idx;;swap(x,y))
		if (x) {
			x=find(x);
			if (tim[x]==idx) return x;
			else tim[x]=idx,x=pre[match[x]];
		}
}
void blossom(int x,int y,int p) {
	while (find(x)!=p) {
		pre[x]=y;y=match[x];
		if (vis[y]==2) vis[y]=1,Q.push(y);
		if (find(x)==x) fa[x]=p;
		if (find(y)==y) fa[y]=p;
		x=pre[y];
	}
}
int Aug(int S) {
	for (int i=1;i<=n;++i)
		vis[i]=pre[i]=0,fa[i]=i;
	while (!Q.empty()) Q.pop();
	Q.push(S);vis[S]=1;
	while (!Q.empty()) {
		int u=Q.front();Q.pop();
        for(int v:g[u]) {
			if (find(u)==find(v)||vis[v]==2) continue;
			if (!vis[v]) {
				vis[v]=2;pre[v]=u;
				if (!match[v]) {
					for (int x=v,lst;x;x=lst)
						lst=match[pre[x]],match[x]=pre[x],match[pre[x]]=x;
					return 1;
				}
				vis[match[v]]=1,Q.push(match[v]);
			}
			else {
				int gg=lca(u,v);
				blossom(u,v,gg);blossom(v,u,gg);
			}
		}
	}
	return 0;
}
int MaxMatch() {
    int ans=0;
    rep(i,1,n) {
        if(!match[i]) ans+=Aug(i);
    }
    return ans;
}