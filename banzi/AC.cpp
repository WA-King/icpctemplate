struct ACAM {
    int next[maxn][26],fail[maxn],id[maxn],root,cnt;
    int match[maxn];
    int newnode() {
        rep(i,0,25) next[cnt][i]=-1;
        id[cnt++]=0;
        return cnt-1;
    }
    void init() {
        cnt=0;
        root=newnode();
    }
    void ins(char a[],int x) {
        int len=strlen(a),now=root;
        rep(i,0,len-1) {
            if(next[now][a[i]-'a']==-1)
                next[now][a[i]-'a']=newnode();
            now=next[now][a[i]-'a'];
        }
        id[now]=x;
    }
    void build() {
        queue<int> q;
        fail[root]=root;
        rep(i,0,25) {
            if(next[root][i]==-1) {
                next[root][i]=root;
            }
            else {
                fail[next[root][i]]=root;
                match[next[root][i]]=root;
                q.push(next[root][i]);
            }
        }
        while(!q.empty()) {
            int now=q.front();
            q.pop();
            rep(i,0,25) {
                if(next[now][i]==-1) next[now][i]=next[fail[now]][i];
                else {
                    fail[next[now][i]]=next[fail[now]][i];
                    q.push(next[now][i]);
                    int tmp=fail[next[now][i]];
                    if(id[tmp]>0) match[next[now][i]]=tmp;
                    else match[next[now][i]]=match[tmp];
                }
            }
        }
    }
}AC;
