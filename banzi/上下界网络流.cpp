struct E {
    int to, cp,id;
    E(int to, int cp,int id): to(to), cp(cp),id(id) {}
};

struct Dinic {
    static const int M = 1E5 * 5;
    int m, s, t;
    vector<E> edges;
    vector<int> G[M];
    int d[M];
    int cur[M];
    void change(int _s,int _t) {
        s=_s,t=_t;
    }
    void init(int n, int s, int t) {
        this->s = s; this->t = t;
        for (int i = 0; i <= n; i++) G[i].clear();
        edges.clear(); m = 0;
    }
    void addedge(int u, int v, int cap,int id) {
        edges.emplace_back(v, cap,id);
        edges.emplace_back(u, 0,0);
        G[u].push_back(m++);
        G[v].push_back(m++);
    }
    bool BFS() {
        memset(d, 0, sizeof d);
        queue<int> Q;
        Q.push(s); d[s] = 1;
        while (!Q.empty()) {
            int x = Q.front(); Q.pop();
            for (int& i: G[x]) {
                E &e = edges[i];
                if (!d[e.to] && e.cp > 0) {
                    d[e.to] = d[x] + 1;
                    Q.push(e.to);
                }
            }
        }
        return d[t];
    }
    int DFS(int u, int cp) {
        if (u == t || !cp) return cp;
        int tmp = cp, f;
        for (int& i = cur[u]; i < G[u].size(); i++) {
            E& e = edges[G[u][i]];
            if (d[u] + 1 == d[e.to]) {
                f = DFS(e.to, min(cp, e.cp));
                e.cp -= f;
                edges[G[u][i] ^ 1].cp += f;
                cp -= f;
                if (!cp) break;
            }
        }
        return tmp - cp;
    }
    int go() {
        int flow = 0;
        while (BFS()) {
            memset(cur, 0, sizeof cur);
            flow += DFS(s, inf);
        }
        return flow;
    }
} DC;
int flow[maxn];
// 有源汇最大流
int main()
{
    ios::sync_with_stdio(false);cin.tie(nullptr);
    int n,m,s,t;
    cin>>n>>m>>s>>t;
    DC.init(n+3,n+1,n+2);
    DC.addedge(t,s,inf,0);
    rep(i,1,m) {
        int u,v,down,up;
        cin>>u>>v>>down>>up;
        DC.addedge(u,v,up-down,i);
        flow[u]-=down;
        flow[v]+=down;
    }
    rep(i,1,n) {
        if(flow[i]>0) DC.addedge(n+1,i,flow[i],0);
        if(flow[i]<0) DC.addedge(i,n+2,-flow[i],0);
    }

    DC.go();
    bool f=true;
    for(int x:DC.G[n+1]) {
        if(DC.edges[x].cp>0) {
            f=false;
            break;
        }
    }
    if(f) {
        int ans=0;
        for(int x:DC.G[t]) {
            if(DC.edges[x].id==0&&DC.edges[x].to!=s) {
                ans+=DC.edges[x].cp;
            }
        }
        rep(i,1,n+2) {
            for(int x:DC.G[i]) {
                if(DC.edges[x].id==0) {
                    DC.edges[x].cp=0;
                }
            }
        }
        DC.change(s,t);
        ans+=DC.go();
        cout<<ans<<'\n';
    }
    else cout<<"please go home to sleep"<<'\n';
    return 0;
}
