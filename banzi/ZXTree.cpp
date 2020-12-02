struct ZXTree {
    int cnt=0, T[maxn], L[maxn << 4], R[maxn << 4], sum[maxn << 4];
    void init() { cnt=0; }
    int build(int l, int r) {
        int rt = ++cnt;
        sum[rt] = 0;
        if (l < r) {
            int mid = (l + r) >> 1;
            L[rt] = build(l, mid);
            R[rt] = build(mid + 1, r);
        }
        return rt;
    }
    int update(int pre, int l, int r, int x) {
        int rt = ++cnt;
        L[rt] = L[pre];
        R[rt] = R[pre];
        sum[rt] = sum[pre] + 1;
        if (l < r)
        {
            int mid = (l + r) >> 1;
            if (x <= mid)
                L[rt] = update(L[pre], l, mid, x);
            else
                R[rt] = update(R[pre], mid + 1, r, x);
        }
        return rt;
    }
    int query_kth(int u, int v, int l, int r, int k) {//第k小
        if (l >= r)
            return l;
        int x = sum[L[v]] - sum[L[u]], mid = (l + r) >> 1;
        if (x >= k)
            return query(L[u], L[v], l, mid, k);
        else
            return query(R[u], R[v], mid + 1, r, k - x);
    }
    int query_cnt(int u,int v,int l,int r,int x) {//小于k的数目
        if(r<=x) return sum[v]-sum[u];
        int ans=0,mid=(l+r)>>1;
        ans+=query_cnt(L[u],L[v],l,mid,x);
        if(x>mid) ans+=query_cnt(R[u],R[v],mid+1,r,x);
        return ans;
    }
};
