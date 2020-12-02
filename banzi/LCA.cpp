vector<int> g[maxn];
int dep[maxn], father[maxn][maxbit], lg[maxn];
namespace LCA {
    void init() {
        lg[0] = -1;
        for (int i = 1; i < maxn; i++) lg[i] = lg[i >> 1] + 1;
    }
    void dfs(int now, int fa) {
        dep[now] = dep[fa] + 1;
        father[now][0] = fa;
        for (int i = 1; i <= lg[dep[now]]; i++)
            father[now][i] = father[father[now][i - 1]][i - 1];
        for (int i = 0; i < g[now].size(); i++) {
            if (g[now][i] != fa) dfs(g[now][i], now);
        }
    }
    int LCA(int u, int v) {
        if (dep[u] < dep[v]) swap(u, v);
        while (dep[u] != dep[v])  u = father[u][lg[dep[u] - dep[v]]];
        if (u == v) return u;
        for (int i = lg[dep[u]]; i >= 0; i--) {
            if (father[u][i] != father[v][i]) {
                u = father[u][i];
                v = father[v][i];
            }
        }
        return father[u][0];
    }
}
