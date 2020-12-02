#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define met(s) memset(s, 0, sizeof(s))
const int mod = 100000007;
const int maxn = 100000;
const int inf = 0x3f3f3f3f;
struct node {
	int to, next;
} edge[maxn];
int head[maxn], tot;
void addedge(int u, int v) {
	edge[++tot].to = v;
	edge[tot].next = head[u];
	head[u] = tot;
}
int Stack[maxn], top; //栈
int dfn[maxn], low[maxn], belong[maxn], scc, Index, num[maxn]; //belong[i]：i属于第i个强连通分量，num[i]:第i个强联通分量的个数
bool Instack[maxn];
void tarjan(int u) {
	int v;
	low[u] = dfn[u] = ++Index;
	Stack[top++] = u;
	Instack[u] = true;
	for (int i = head[u]; i; i = edge[i].next) {
		int v = edge[i].to;
		if (!dfn[v]) {
			tarjan(v);
			if (low[u] > low[v]) low[u] = low[v];
		}
		else if (Instack[v] && low[u] > low[v]) low[u] = low[v];
	}
	if (low[u] == dfn[u]) {
		scc++;
		do {
			v = Stack[--top];
			Instack[v] = false;
			belong[v] = scc;
			num[scc]++;
		} while (v != u);
	}
}
void solve(int n) {
	memset(dfn, 0, sizeof(dfn));
	memset(Instack, false, sizeof(Instack));
	memset(num, 0, sizeof(num));
	Index = scc = top = 0;
	for (int i = 1; i <= n; i++) {
		if (!dfn[i]) tarjan(i);
	}
}
void init() {
	tot = 0;
	memset(head, 0, sizeof(head));
}