/*
* @Author: WA_King
* @Date:   2019-08-07 10:08:24
* @Last Modified by:   lcw
* @Last Modified time: 2019-08-07 10:30:12
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define met(s) memset(s, 0, sizeof(s))
const int mod = 100000007;
const int maxn = 310;
const int inf = 0x3f3f3f3f;
int nx, ny; //两边的点的数目
int g[maxn][maxn], linker[maxn];//linker[i]:右边第i个点的匹配对象
int lx[maxn], ly[maxn], slack[maxn];
bool visx[maxn], visy[maxn]; //x,y是否被访问
bool dfs(int x) {
	visx[x] = true;
	for (int y = 0; y < ny; y++) {
		if (visy[y]) continue;
		int tmp = lx[x] + ly[y] - g[x][y];
		if (tmp == 0) {
			visy[y] = true;
			if (linker[y] == -1 || dfs(linker[y])) {
				linker[y] = x;
				return true;
			}
		}
		else if (slack[y] > tmp) slack[y] = tmp;
	}
	return false;
}
int km() {
	memset(linker, -1, sizeof(linker));
	memset(ly, 0, sizeof(ly));
	for (int i = 0; i < nx; i++) {
		lx[i] = -inf;
		for (int j = 0; j < ny; j++) {
			if (g[i][j] > lx[i]) lx[i] = g[i][j];
		}
	}
	for (int x = 0; x < nx; x++) {
		for (int i = 0; i < ny; i++) slack[i] = inf;
		while (1) {
			memset(visx, false, sizeof(visx));
			memset(visy, false, sizeof(visy));
			if (dfs(x)) break;
			int d = inf;
			for (int i = 0; i < ny; i++) {
				if (!visy[i] && d > slack[i]) d = slack[i];
			}
			for (int i = 0; i < nx; i++) {
				if (visx[i]) lx[i] -= d;
			}
			for (int i = 0; i < ny; i++) {
				if (visy[i]) ly[i] += d;
				else slack[i] -= d;
			}
		}
	}
	int res = 0;
	for (int i = 0; i < ny; i++) {
		if (linker[i] != -1) res += g[linker[i]][i];
	}
	return res;
}
