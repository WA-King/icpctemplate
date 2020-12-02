#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define met(s) memset(s, 0, sizeof(s))
const int mod = 100000007;
const int maxn = 1000000;
const int inf = 0x3f3f3f3f;
struct edge {
	int cost, to;
	edge(int x = 0, int y = 0): to(x), cost(y) {}
};
vector<edge> g[maxn];
int dis[maxn], cnt[maxn], n, m;
bool vis[maxn];
queue<int> q;
bool spfa(int s) {
	memset(vis, false, sizeof(vis));
	memset(dis, 0x3f, sizeof(dis));
	vis[s] = true;
	dis[s] = 0;
	while (!q.empty()) q.pop();
	q.push(s);
	while (!q.empty()) {
		int now = q.front(); q.pop();
		vis[now] = false;
		for (int i = 0; i < g[now].size(); i++) {
			int to = g[now][i].to;
			if (dis[to] > dis[now] + g[now][i].cost) {
				dis[to] = dis[now] + g[now][i].cost;
				if (!vis[to]) {
					vis[to] = true;
					q.push(to);
					if (++cnt[to] > n) return false;
				}
			}
		}
	}
	return true;
}
int main()
{
	//freopen("data.txt","r",stdin);
	return 0;
}
