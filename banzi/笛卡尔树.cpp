struct CartesianTree {
    int ch[maxn][2],fa[maxn],val[maxn],index[maxn];
    void build(int a[],int n) {
        rep(i,1,n) {
            int k=i-1;
            while(val[k]>a[i]) k=fa[k];
            fa[i]=k;
            ch[i][0]=ch[k][1];
            ch[k][1]=i;
            fa[ch[k][1]]=ch[i][0];
        }
        return ch[0][1];
    }
}