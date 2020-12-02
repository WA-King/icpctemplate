#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define met(s) memset(s, 0, sizeof(s))
const int MOD = 100000007;
const int MAXN = 1000000;
const int inf = 0x3f3f3f3f;
char str_new[220010], str[110010];
int p[220025];
int init() {
	int len = strlen(str);
	str_new[0] = '$';
	str_new[1] = '#';
	int t = 2;
	for (int i = 0; i < len; i++) {
		str_new[t++] = str[i];
		str_new[t++] = '#';
	}
	return t;
}
int manacher() {
	memset(str_new, 0, sizeof(str_new));
	int len = init();
	int id, mx = 0, Max = 0;
	for (int i = 0; i < len; i++) {
		if (i < mx) p[i] = min(p[2 * id - i], mx - i);
		else p[i] = 1;
		while (str_new[i - p[i]] == str_new[i + p[i]]) p[i]++;
		if (mx < i + p[i]) {
			mx = i + p[i];
			id = i;
		}
		Max = max(Max, p[i] - 1);
	}
	for(int i=0;i<len;i++) p[i]--;
	return Max;
}
int main() {
	while (scanf("%s", str) != EOF) {
		int ans = manacher();
		printf("%d\n", ans );
	}
	return 0;
}
