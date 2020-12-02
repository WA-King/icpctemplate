// cnt[i]: 表示该节点在原串中出现的次数....记得count()
namespace pam {
	const int N=maxn<<1;
    int t[N][26], fa[N], len[N], rs[N], cnt[N], num[N];
    int sz, n, last;
	int _new(int l) {
        len[sz] = l; cnt[sz] = num[sz] = 0;
        return sz++;
	}
	void init() {
    	memset(t, 0, sz * sizeof t[0]);
	    rs[n = sz = 0] = -1;
   	 	last = _new(0);
		fa[last] = _new(-1);
	}
	int get_fa(int x) {
        while (rs[n - 1 - len[x]] != rs[n]) x = fa[x];
        return x;
	}
	void ins(int ch) {
	    rs[++n] = ch;
	    int p = get_fa(last);
		if (!t[p][ch]) {
	    	int np = _new(len[p] + 2);
	    	num[np] = num[fa[np] = t[get_fa(fa[p])][ch]] + 1;
		    t[p][ch] = np;
		}
   		++cnt[last = t[p][ch]];
		// len[last];以当前字符结尾的最长回文后缀
		// num[last]; 以当前字符结尾的回文串数量(回文后缀)
	}
	void count() {
		for(int i=sz-1;i>=2;i--) 
			cnt[fa[i]]+=cnt[i];
	}
}
