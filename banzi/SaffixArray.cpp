struct SuffixArray
{
    int sa[maxn], rank[maxn], ws[maxn], wv[maxn], wa[maxn], wb[maxn], height[maxn], st[maxbit][maxn], N;
    bool cmp(int *r, int a, int b, int l){return r[a]==r[b] and r[a+l]==r[b+l];}
    void build(int *r, int n, int m)
    {
        N=n;
        n++;
        int i, j, k=0, p, *x=wa, *y=wb, *t;
        for(i=0;i<m;i++)ws[i]=0;
        for(i=0;i<n;i++)ws[x[i]=r[i]]++;
        for(i=1;i<m;i++)ws[i]+=ws[i-1];
        for(i=n-1;i>=0;i--)sa[--ws[x[i]]]=i;
        for(p=j=1;p<n;j<<=1,m=p)
        {
            for(p=0,i=n-j;i<n;i++)y[p++]=i;
            for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
            for(i=0;i<n;i++)wv[i]=x[y[i]];
            for(i=0;i<m;i++)ws[i]=0;
            for(i=0;i<n;i++)ws[wv[i]]++;
            for(i=1;i<m;i++)ws[i]+=ws[i-1];
            for(i=n-1;i>=0;i--)sa[--ws[wv[i]]]=y[i];
            for(t=x,x=y,y=t,p=1,i=1,x[sa[0]]=0;i<n;i++)
                x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
        }
        
        for(i=0;i<n;i++)rank[sa[i]]=i;
        
        for(i=0;i<n-1;height[rank[i++]]=k)
            for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
    }
    void build_st()     //st表
    {
        int i, k;
        for(i=1;i<=N;i++)st[0][i]=height[i];
        for(k=1;k<=maxbit;k++)
            for(i=1;i+(1<<k)-1<=N;i++)
                st[k][i]=min(st[k-1][i],st[k-1][i+(1<<k)-1]);
    }
    int lcp(int x, int y)   //最长公共前缀
    {
        int l=rank[x], r=rank[y];
        if(l>r)swap(l,r);
        if(l==r)return N-sa[l];
        int t=log2(r-l);
        return min(st[t][l+1],st[t][r-(1<<t)+1]);
    }
}SA;
