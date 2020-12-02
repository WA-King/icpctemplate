ll jc[maxn],inv[maxn];
void cinit(int n) {
	jc[0]=inv[0]=1;
	rep(i,1,n) jc[i]=jc[i-1]*i%mod;
	inv[n]=qpow(jc[n],mod-2);
	per(i,n-1,1) inv[i]=inv[i+1]*(i+1)%mod;
}
ll C(int n,int m,int p=mod) { return m>n?0:jc[n]*inv[m]%p*inv[n-m]%p; }
ll lucas(ll n,ll m,ll p=mod){ return m==0?1:lucas(n/p,m/p,p)*C(n%p,m%p,p)%p; }