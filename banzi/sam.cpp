namespace sam {
    const int M = maxn << 1;
    int t[M][26], len[M] = {-1}, fa[M], sz = 2, last = 1;
    ll endpos[M];
    void init() { memset(t, 0, (sz + 10) * sizeof t[0]); sz = 2; last = 1; }
    void ins(int ch) {
        int p = last, np = last = sz++;endpos[np]=1;
        len[np] = len[p] + 1;
        for (; p && !t[p][ch]; p = fa[p]) t[p][ch] = np;
        if (!p) { fa[np] = 1; return; }
        int q = t[p][ch];
        if (len[p] + 1 == len[q]) fa[np] = q;
        else {
            int nq = sz++; len[nq] = len[p] + 1;
            memcpy(t[nq], t[q], sizeof t[0]);
            fa[nq] = fa[q];
            fa[np] = fa[q] = nq;
            for (; t[p][ch] == q; p = fa[p]) t[p][ch] = nq;
        }
    }
    //拓扑排序
    int c[M] = {1}, a[M];
    void rsort() {
        rep (i, 1, sz-1) c[i] = 0;
        rep (i, 1, sz-1) c[len[i]]++;
        rep (i, 1, sz-1) c[i] += c[i - 1];
        rep (i, 1, sz-1) a[--c[len[i]]] = i;
    }
    //计算endpos大小
    void calendpos() {
        rsort();
        per(i,sz-1,2) {
            endpos[fa[a[i]]]+=endpos[a[i]];
        }
    }
}