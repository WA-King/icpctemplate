namespace HK {
    vector<int> G[maxn];
    int uN;
    int Mx[maxn],My[maxn];
    int dx[maxn],dy[maxn];
    int dis;
    bool used[maxn];
    bool searchp() {
        queue<int> q;
        dis=inf;
        memset(dx,-1,sizeof(dx));
        memset(dy,-1,sizeof(dy));
        for(int i=0;i<uN;i++) {
            if(Mx[i]==-1) {
                q.push(i);
                dx[i]=0;
            }
        }
        while(!q.empty()) {
            int u=q.front();q.pop();
            if(dx[u]>dis) break;
            for(int v:G[u]) {
                if(dy[v]==-1) {
                    dy[v]=dx[u]+1;
                    if(My[v]==-1) dis=dy[v];
                    else {
                        dx[My[v]]=dy[v]+1;
                        q.push(My[v]);
                    }
                }
            }
        }
        return dis!=inf;
    }
    bool DFS(int u) {
        for(int v:G[u]) {
            if(!used[v]&&dy[v]==dx[u]+1) {
                used[v]=true;
                if(My[v]!=-1&&dy[v]==dis) continue;
                if(My[v]==-1||DFS(My[v])) {
                    My[v]=u;
                    Mx[u]=v;
                    return true;
                }
            }
        }
        return false;
    }
    int MaxMatch() {
        int res=0;
        memset(Mx,-1,sizeof(Mx));
        memset(My,-1,sizeof(My));
        while(searchp()) {
            memset(used,false,sizeof(used));
            for(int i=0;i<uN;i++) {
                if(Mx[i]==-1&&DFS(i)) res++;
            }
        }
        return res;
    }

}