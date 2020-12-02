struct SegmentTree {
    int cnt=0,L[maxn << 5], R[maxn << 5], data[maxn<<5];// 空间巨大,merge函数可以优化
    void pushup(int x) {
        data[x]=data[L[x]]+data[R[x]];
    }
    void ins(int &now,int l,int r,int pos) {
        if(!now) now=++cnt;
        if(l==r) {
            data[now]++;
            return ;
        }
        int mid=(l+r)>>1;
        if(pos<=mid) ins(L[now],l,mid,pos);
        else ins(R[now],mid+1,r,pos);
        pushup(now);
    }
    int merge(int u,int v,int l,int r) {// 保留u,v   构造一颗新的树
        if(!u||!v) return u|v;
        int mid=(l+r)>>1,now=++cnt;
        if(l==r) data[now]=data[u]+data[v];
        else {
            L[now]=merge(L[u],L[v],l,mid);
            R[now]=merge(R[u],R[v],mid+1,r);
            pushup(now);
        }
        return now;
    } 
    int merge(int u,int v,int l,int r) {// 将u合并到v,   v不能再被使用.节约空间
        if(!u||!v) return u|v;
        int mid=(l+r)>>1;
        if(l==r) {
            data[u]+=data[v];
        } else {
            L[u]=merge(L[u],L[v],l,mid);
            R[u]=merge(R[u],R[v],mid+1,r);
            pushup(u);
        }
        return u;
    }
    int query(int now,int l,int r,int ql,int qr) { // 区间求和
        if(ql<=l&&qr>=r) return data[now];
        int mid=(l+r)>>1,ans=0;
        if(mid>=ql) ans+=query(L[now],l,mid,ql,qr);
        if(mid<qr) ans+=query(R[now],mid+1,r,ql,qr);
        return ans;
    }
};