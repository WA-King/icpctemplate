// 有向图具有欧拉回路的条件:
// 1.所有点出度等于入度
// 2.基图连通
vector<pair<int,bool>> g[maxn];
vector<int>ans;// need reverse
void dfs(int now) {
    for(auto &x:g[now]) {
        if(x.se) continue;
        x.se=true;
        dfs(x.fi);
    }
    ans.pb(now);
}