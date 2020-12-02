ll sb[maxn<<2],sr[maxn<<2];
// 计算 k!*S(n,k),k=0,1,2,...,n, 复杂度(n*log n)
void stirling_second(int n){
    int len=NTT::init(2*n+2);
	for(int i=1; i<=n; i++) sr[i]=qpow(i, n)*inv[i]%mod;
	for(int i=0; i<=n; i++){
		if(i&1) sb[i]=mod-inv[i];
		else sb[i]=inv[i];
	}
	NTT::mul(sr,sb,len);
}
// 单独计算 m!*S(n,m) 复杂度 O(m*log n)
ll calsr(ll n,ll m) {
	ll ans=0;
	rep(k,0,m) {
		ll now=C(m,k)*qpow(m-k,n)%mod;
        ans=(k&1)?(ans-now+mod)%mod:(ans+now)%mod;
	}
	return ans;
}