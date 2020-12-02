typedef double LD;
const LD eps = 1E-10;
const int maxn = 2000 + 10;

int n, m;
LD a[maxn][maxn], x[maxn];
bool free_x[maxn];

inline int sgn(LD x) { return (x > eps) - (x < -eps); }

int gauss(LD a[maxn][maxn], int n, int m) {
    memset(free_x, 1, sizeof free_x); memset(x, 0, sizeof x);
    int r = 0, c = 0;
    while (r < n && c < m) {
        int m_r = r;
        rep (i, r + 1, n-1)
            if (fabs(a[i][c]) > fabs(a[m_r][c])) m_r = i;
        if (m_r != r)
            rep (j, c, m)
                 swap(a[r][j], a[m_r][j]);
        if (!sgn(a[r][c])) {
            a[r][c] = 0;
            ++c;
            continue;
        }
        rep (i, r + 1, n-1)
            if (a[i][c]) {
                LD t = a[i][c] / a[r][c];
                rep (j, c, m + 1) a[i][j] -= a[r][j] * t;
            }
        ++r; ++c;
    }
    rep (i, r, n-1)
        if (sgn(a[i][m])) return -1;
    if (r < m) {
        per (i, r - 1, 0) {
            int f_cnt = 0, k = -1;
            rep (j, 0, m-1)
                if (sgn(a[i][j]) && free_x[j]) {
                    ++f_cnt;
                    k = j;
                }
            if(f_cnt > 0) continue;
            LD s = a[i][m];
            rep (j, 0, m-1)
                if (j != k) s -= a[i][j] * x[j];
            x[k] = s / a[i][k];
            free_x[k] = 0;
        }
        return m - r;
    }
     per(i, m - 1, 0) {
        LD s = a[i][m];
        rep (j, i + 1, m-1)
            s -= a[i][j] * x[j];
        x[i] = s / a[i][i];
    }
    return 0;
}