namespace LTree{
    int cnt=0;
    struct node {
        int l,r,val,d,fa;
    }t[maxn];
    int newnode(int x){
        t[++cnt].val=x;
        t[cnt].l=t[cnt].r=t[cnt].d=t[cnt].fa=0;
    }
    int merge(int a,int b) {
        if(!a||!b) return a|b;
        if(t[a].val>t[b].val) swap(a,b);
        t[b].fa=a;
        t[a].r=merge(t[a].r,b);
        if(t[t[a].r].d>t[t[a].l].d) swap(t[a].r,t[a].l):
        t[a].d=t[t[a].r].d+1;
        return a;
    }
    int pushup(int x) {
        if(!x) return ;
        if(t[x].d!=t[t[x].r].d+1) {
            t[x].d=t[t[x].r].d+1;
            pushup(t[x].fa);
        }
    }
}