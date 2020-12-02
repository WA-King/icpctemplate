namespace LCT{
    const int N=maxn;
    int ch[N][2],rev[N],fa[N],stk[N];
	bool son(int x) {return ch[fa[x]][1] == x;}
	bool isroot(int x) {return ch[fa[x]][1]!=x && ch[fa[x]][0]!=x; }
	void reverse(int x) {swap(ch[x][1],ch[x][0]); rev[x] ^= 1;}
	void pushup(int x) {
        .......
    }
	void pushdown(int x) {if(rev[x])reverse(ch[x][0]) , reverse(ch[x][1]) , rev[x] ^= 1;}
	void rot(int x) {
		 int y = fa[x] , z = fa[y] , c = son(x);
		if(!isroot(y))ch[z][son(y)] = x; fa[x] = z;
		ch[y][c] = ch[x][!c]; fa[ch[y][c]] = y;
		ch[x][!c] = y; fa[y] = x; pushup(y);
	}
	void splay(int x) {
		 int top = 0; stk[++top] = x;
		for( int i = x; !isroot(i) ; i = fa[i])stk[++top] = fa[i];
		while(top)pushdown(stk[top--]);
		for( int y = fa[x]; !isroot(x) ; rot(x) , y = fa[x])
			if(!isroot(y))son(x) ^ son(y) ? rot(x) : rot(y);
		pushup(x); return;
	}
	void access(int x) { for( int y = 0; x; y = x,x = fa[x])splay(x),ch[x][1] = y,pushup(x); }
    void makeroot(int x) {access(x); splay(x); reverse(x);}
    int findroot(int x) {access(x); splay(x); while(ch[x][0])x=ch[x][0]; return x;}
    void split(int x,int y) {makeroot(x); access(y); splay(y);}
    void link(int x,int y) {if((!x)||(!y))return; makeroot(x); fa[x] = y;  }
    void cut(int x,int y) {if((!x)||(!y))return; split(x,y); ch[y][0] = fa[x] = 0; pushup(y);}
    bool adj(int x,int y) {
        split(x,y);
        return ch[y][0]==x&&ch[x][0]==0&&ch[x][1]==0;
    }
}
/*  维护子树大小(不是splay的大小)
void pushup(int x) {
    sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+sz2[x]+1;
}
void access(int x) { 
    for( int y = 0; x; y = x,x = fa[x]) {
        splay(x);
        sz2[x]+=sz[ch[x][1]]-sz[y];
        ch[x][1] = y,pushup(x); 
    }
}
void link(int x,int y) {
    split(x,y);
    fa[x]=y;sz2[y]+=sz[x];
    pushup(y);
}
*/