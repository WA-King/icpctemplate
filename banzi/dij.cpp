vector<pair<ll,ll>> g[maxn];
ll dis[maxn];
void dij(int s) {
    memset(dis,0x3f,sizeof(dis));
    dis[s]=0;
    priority_queue<pair<ll,ll>> q;
    q.push({0,s});
    while(!q.empty()) {
        pair<ll,ll> now=q.top();q.pop();
        now.fi=-now.fi;
        for(auto x:g[now.se]) {
            if(dis[x.fi]>dis[now.se]+x.se) {
                dis[x.fi]=dis[now.se]+x.se;
                q.push({-dis[x.fi],x.fi});
            }
        }
    }
}