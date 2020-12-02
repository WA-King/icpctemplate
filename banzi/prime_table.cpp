int prime[maxn],p[maxn];
void init(int up) {
    rep(i,1,up) p[i]=i;
    rep(i,2,up) {
        if(p[i]==i) prime[++prime[0]]=i;
        for(int j=1;j<=prime[0]&&i<=up/prime[j];j++) {
            p[i*prime[j]]=prime[j];
            if(i%prime[j]==0) break;
        }
    }
}
vector<pii> smallfc(int x) {
    vector<pii> ans;
    while(x!=1) {
        pii now;
        now.fi=p[x];
        while(x%now.fi==0) {
            now.se++;
            x/=now.fi;
        }
        ans.pb(now);
    }
    reverse(ans.begin(),ans.end());
    return ans;
}
vector<pair<ll,int>> bigfc(ll x) {
    vector<pair<ll,int>> ans;
    rep(i,1,prime[0]) {
        if(prime[i]>x/prime[i]) break;
        if(x%prime[i]!=0) continue;
        int cnt=0;
        while(x%prime[i]==0) {
            cnt++;
            x/=prime[i];
        }
        ans.pb({prime[i],cnt});
    }
    return ans;
}