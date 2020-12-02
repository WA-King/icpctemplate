ll qpow(ll a,int b) {
    ll ans=1;
    while(b) {
        if(b&1) ans=ans*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ans;
}
const int G=3;
namespace NTT {
    ll wn[maxn << 2], rev[maxn << 2];
    int init(int n_) {
        int step = 0; int n = 1;
        for ( ; n < n_; n <<= 1) ++step;
        rep(i,1,n-1)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (step - 1));
        int g = qpow(G, (mod - 1) / n);
        wn[0] = 1;
        for (int i = 1; i <= n; ++i)
            wn[i] = wn[i - 1] * g % mod;
        return n;
    }
    void NTT(ll a[], int n, int f) {
        rep(i, 0, n-1)if(i < rev[i])
            std::swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += (k << 1)) {
                int t = n / (k << 1);
                rep(j, 0, k-1) {
                    ll w = f == 1 ? wn[t * j] : wn[n - t * j];
                    ll x = a[i + j];
                    ll y = a[i + j + k] * w % mod;
                    a[i + j] = (x + y) % mod;
                    a[i + j + k] = (x - y + mod) % mod;
                }
            }
        }
        if (f == -1) {
            ll ninv = qpow(n, mod-2);
            rep (i, 0, n-1) a[i] = a[i] * ninv % mod;
        }
    }
    ll tmp1[maxn<<2],tmp2[maxn<<2];
    void mul(ll a[],ll b[],int lena,int lenb) {// lena为a的项数
        int len=init(lena+lenb+2);
        rep(i,0,lena-1) tmp1[i]=a[i];
        rep(i,lena,len-1) tmp1[i]=0;
        rep(i,0,lenb-1) tmp2[i]=b[i];
        rep(i,lenb,len-1) tmp2[i]=0;
        NTT(tmp1,len,1); NTT(tmp2,len,1);
        rep(i,0,len-1) a[i]=tmp1[i]*tmp2[i]%mod;
        NTT(a,len,-1);
    }
    void mul(ll a[],ll b[],ll c[],int lena,int lenb) {
        int len=init(lena+lenb+2);
        rep(i,0,lena-1) tmp1[i]=a[i];
        rep(i,lena,len-1) tmp1[i]=0;
        rep(i,0,lenb-1) tmp2[i]=b[i];
        rep(i,lenb,len-1) tmp2[i]=0;
        NTT(tmp1,len,1); NTT(tmp2,len,1);
        rep(i,0,len-1) c[i]=tmp1[i]*tmp2[i]%mod;
        NTT(c,len,-1);
    }
    ll P[20][maxn<<2];
    void solve(ll *a,int l,int r,int dep) {//(1+a[0]*x)(1+a[1]*x)(1+a[2]*x)
        if(l==r) {
            P[dep][2*l]=1;
            P[dep][2*l+1]=a[l];
            return ;
        }
        int mid=(l+r)>>1;
        solve(a,l,mid,dep+1);
        solve(a,mid+1,r,dep+1);
        int lenl=mid-l+1,lenr=r-mid;
        mul(P[dep+1]+2*l,P[dep+1]+2*mid+2,P[dep]+l*2,lenl+1,lenr+1);
    }
    ll tmp[maxn << 2];
    void inv(ll *a,ll *b,int len) {//lena为a的项数
        if(len==1) { b[0]=qpow(a[0],mod-2); return ;}
        inv(a,b,(len+1)>>1);
        int l=init(len*2+1);
        rep(i,0,len-1) tmp[i]=a[i];
        rep(i,len,l-1) tmp[i]=0;
        NTT(tmp,l,1);
        NTT(b,l,1);
        rep(i,0,l-1) b[i]=(2-b[i]*tmp[i]%mod+mod)%mod*b[i]%mod;
        NTT(b,l,-1);
        rep(i,len,l-1) b[i]=0;
    }
    ll pa[maxn<<2],pb[maxn<<2],pb_inv[maxn<<2];
    void div(ll *a,ll *b,int lena,int lenb,ll *Q,ll *R) {//lena为a的最高次数
        rep(i,0,lena) pa[i]=a[lena-i];
        rep(i,0,lenb) pb[i]=b[lenb-i];
        rep(i,lena-lenb+1,lenb) pb[i]=0;
        inv(pb,pb_inv,lena-lenb+1);
        mul(pa,pb_inv,lena+1,lena-lenb+1);
        rep(i,0,lena-lenb) Q[i]=pa[lena-lenb-i];
        rep(i,0,lenb) pb[i]=b[i];
        mul(pb,Q,lenb+1,lena-lenb+1);
        rep(i,0,lenb-1) R[i]=(a[i]-pb[i]+mod)%mod;
    }
    ll invb[maxn<<2],D[maxn<<2],inv2=qpow(2,mod-2);
    void sqrt(ll *a,ll *b,int len) {//要保证b[0]=1,否则需要二次剩余求
        if(len==1) {b[0]=1;return ;}
        sqrt(a,b,(len+1)>>1);
        rep(i,0,len<<1) invb[i]=0;
        inv(b,invb,len);
        int l=init(2*len);
        rep(i,0,len-1) D[i]=a[i];
        rep(i,len,l-1) D[i]=0;
        NTT(D,l,1);NTT(b,l,1);NTT(invb,l,1);
        rep(i,0,l-1) b[i]=(b[i]+D[i]*invb[i]%mod)%mod*inv2%mod;
        NTT(b,l,-1);
        rep(i,len,l-1) b[i]=0;
    }
    void dao(ll *a,ll *b,int len) {
        rep(i,0,len-1) b[i-1]=i*a[i]%mod;b[len-1]=0;
    }
    void jifen(ll *a,ll *b,int len) {
        rep(i,0,len-1) b[i]=a[i-1]*qpow(i,mod-2)%mod;b[0]=0;
    }
    ll A[maxn<<2],B[maxn<<2];
    void ln(ll *a,ll *b,int len) {
        int n;for(n=1;n<=len;n<<=1);
        rep(i,0,n<<1) A[i]=B[i]=0;
        dao(a,A,n);inv(a,B,n);
        int l=init(n*2);
        NTT(A,l,1),NTT(B,l,1);
        rep(i,0,l-1) A[i]=A[i]*B[i]%mod;
        NTT(A,l,-1);jifen(A,b,n);
    }
    ll F[maxn<<2];
    void exp(ll *a,ll *b,int len) {//保证a[0]=0;
        if(len==1) { b[0]=1;return ;}
        exp(a,b,(len+1)>>1);
        ln(b,F,len);
        int l=init(2*len+1);
        rep(i,0,len-1) F[i]=(a[i]-F[i]+mod)%mod;
        rep(i,len,l-1) F[i]=b[i]=0;
        F[0]++;
        NTT(F,l,1),NTT(b,l,1);
        rep(i,0,l-1) b[i]=b[i]*F[i]%mod;
        NTT(b,l,-1);
        rep(i,len,l-1) b[i]=0;
    }
}