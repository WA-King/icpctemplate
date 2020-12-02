template<typename T>
void fwt(ll a[], int n, T f) {
    for (int d = 1; d < n; d *= 2)
        for (int i = 0, t = d * 2; i < n; i += t)
            rep (j, 0, d-1)
                f(a[i + j], a[i + j + d]);
}

void AND(ll& a, ll& b) { a =(a+b)%mod; }
void OR(ll& a, ll& b) { b =(a+b)%mod; }
void XOR (ll& a, ll& b) {
    ll x = a, y = b;
    a = (x + y) % mod;
    b = (x - y + mod) % mod;
}
void rAND(ll& a, ll& b) { a =(a-b+mod)%mod; }
void rOR(ll& a, ll& b) { b =(b-a+mod)%mod; }
void rXOR(ll& a, ll& b) {
    static ll INV2 = (mod + 1) / 2;
    ll x = a, y = b;
    a = (x + y) * INV2 % mod;
    b = (x - y + mod) * INV2 % mod;
}