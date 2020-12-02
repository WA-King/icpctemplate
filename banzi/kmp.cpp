#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int inf = 0x3f3f3f3f;
const int maxn=1e5+10;
int Next[maxn];
void getNext(string a) {
	int len = a.size(), k = -1, i = 0;
	Next[0] = -1;	
	while (i < len)
	{
		while (k != -1 && a[i] != a[k]) k = Next[k];
		Next[++i] = ++k;
	}
}
int kmp(string a1,string a2) {
	int i, j = 0;
	for (i = 0; i < a1.size(); i++) {
		while (j != -1 && a1[i] != a2[j]) j = Next[j];
		j++;
		if (j == a2.size()) return i - a2.size() + 2;
	}
	return -1;
}
