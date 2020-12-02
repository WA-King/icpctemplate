#include<bits/stdc++.h>

using namespace std;

const int MAX = (1 << 30) - 1;
int head[10010], edge_num = -1;
int s, t;

struct Edge
{
    int to;
    int dis;
    int next;
} edges[1000000];

void add_edge_2(int from, int to, int dis)
{
    edges[++edge_num].to = to;
    edges[edge_num].dis = dis;
    edges[edge_num].next = head[from];
    head[from] = edge_num;
}

void add_edge(int from, int to, int dis)
{
    add_edge_2(from, to, dis);
    add_edge_2(to, from, 0);
}

int d[10010];

int DFS(int u, int flow)
{
    if (u == t)
        return flow;
    int _flow = 0, __flow;
    int c_e = head[u], v;
    while (c_e != -1)
    {
        v = edges[c_e].to;
        if (d[v] == d[u] + 1 && edges[c_e].dis > 0)
        {
            __flow = DFS(v, min(flow, edges[c_e].dis));
            flow -= __flow;
            edges[c_e].dis -= __flow;
            _flow += __flow;
            edges[c_e ^ 1].dis += __flow;
            if (flow == 0)
                break;
        }
        c_e = edges[c_e].next;
    }
    if (_flow == 0)
        d[u] = -1;
    return _flow;
}

bool BFS()
{
    memset(d, -1, sizeof(d));
    queue<int> que;
    d[s] = 0;
    que.push(s);
    int _now, c_e, _new;
    while (!que.empty())
    {
        _now = que.front();
        que.pop();
        c_e = head[_now];
        while (c_e != -1)
        {
            _new = edges[c_e].to;
            if (d[_new] == -1 && edges[c_e].dis > 0)
            {
                d[_new] = d[_now] + 1;
                que.push(_new);
            }
            c_e = edges[c_e].next;
        }
    }
    if (d[t] != -1)
        return true;
    else
        return false;
}

void dinic()
{
    int max_flow = 0;
    while (BFS())
    {
        max_flow += DFS(s, MAX);
    }
    cout<<max_flow<<'\n';
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    memset(head, -1, sizeof(head));
    int n,m,k;
    cin>>n>>m>>k;
    for(int i=1;i<=n;i++)
    {
        int num,x;
        cin>>num;
        while(num--)
        {
            cin>>x;
            add_edge(1+i,1+n+x,2);
        }
    }   
    dinic();
    return 0;
}
