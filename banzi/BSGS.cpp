ll BSGS(ll a, ll b, ll p) { // a^x = b (mod p)
    a %= p;
    if (!a && !b) return 1;
    if (!a) return -1;
    static map<ll, ll> mp; mp.clear();
    ll m = sqrt(p + 1.5);
    ll v = 1;
    rep (i, 1, m) {
        v = v * a % p;
        mp[v * b % p] = i;
    }
    ll vv = v;
    rep (i, 1, m ) {
        auto it = mp.find(vv);
        if (it != mp.end()) return i * m - it->second;
        vv = vv * v % p;
    }
    return -1;
}