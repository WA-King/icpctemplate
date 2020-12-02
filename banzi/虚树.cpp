vi g2[maxn];
namespace faketree {
    int sta[maxn],top=0;
    void insert(int x) {
        if(top==0) {
            sta[++top]=x;
            return ;
        }
        int lca=LCA::LCA(sta[top],x);
        if(lca==sta[top]) {
            sta[++top]=x;
            return ;
        }
        while(top>1&&dep[lca]<=dep[sta[top-1]]) {
            g2[sta[top-1]].pb(sta[top]);
            top--;
        }
        if(lca!=sta[top]) {
            g2[lca].pb(sta[top]);
            sta[top]=lca;
        } 
        sta[++top]=x;
    }
    void end() {
        while(top>1) {
            g2[sta[top-1]].pb(sta[top]);
            top--;
        }
        top=0;
    }
}    