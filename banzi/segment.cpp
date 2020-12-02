struct SegmentTree// 区间和,区间加
{
    ll data[maxn<<2],lz[maxn<<2];
    int L[maxn<<2],R[maxn<<2];
    void pushup(int k) {
        data[k]=data[k<<1]+data[k<<1|1];
    }
    void build(int l,int r,int k) {
        L[k]=l;
        R[k]=r;
        data[k]=lz[k]=0;
        if(l==r) {
            return ;
        }
        int mid=(l+r)>>1;
        build(l,mid,k<<1);
        build(mid+1,r,k<<1|1);
        pushup(k);
    }
    void lzadd(int k,ll x) {
        lz[k]+=x;
        data[k]+=(R[k]-L[k]+1)*x;
    }
    void pushdown(int k) {
        if(lz[k]==0) return ;
        lzadd(k<<1,lz[k]);
        lzadd(k<<1|1,lz[k]);
        lz[k]=0;
    }
    void change(int pos,int k,ll x) {
        if(L[k]==R[k]) {
            data[k]=x;
            return ;
        }
        pushup(k);
        int mid=(L[k]+R[k])>>1;
        if(mid>=pos) change(pos,k<<1,x);
        else change(pos,k<<1|1,x);
        pushup(k);
    }
    void add(int l,int r,int k,ll x) {
        if(L[k]>=l&&R[k]<=r) {
            lzadd(k,x);
            return ;
        }
        pushdown(k);
        int mid=(L[k]+R[k])>>1;
        if(mid>=l) add(l,r,k<<1,x);
        if(mid<r) add(l,r,k<<1|1,x);
        pushup(k);
    }
    ll query(int l,int r,int k) {
        if(L[k]>=l&&R[k]<=r) return data[k];
        pushdown(k);
        ll ans=0;
        int mid=(L[k]+R[k])>>1;
        if(mid>=l) ans=ans+query(l,r,k<<1);
        if(mid<r) ans=ans+query(l,r,k<<1|1);
        return ans;
    }
}tree;
