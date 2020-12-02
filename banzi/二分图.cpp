#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int book[505][505], k, m, n;
int cx[505], cy[505], vis[505];
void init() {
	memset(cx, -1, sizeof(cx));
	memset(cy, -1, sizeof(cy));
	memset(vis, 0, sizeof(vis));
	memset(book, 0, sizeof(book));
}
int line(int x) {
	int i;
	for (i = 1; i <= n; i++) {
		if (book[x][i] && !vis[i]) {
			vis[i] = 1;
			if (cy[i] == -1 || line(cy[i])) {
				cx[x] = i;
				cy[i] = x;
				return 1;
			}
		}
	}
	return 0;
}
int maxmatch() {
	int sum = 0, i;
	for (i = 1; i <= m; i++) {
		if (cx[i] == -1) {
			memset(vis, 0, sizeof(vis));
			sum += line(i);
		}
	}
	return sum;
}
