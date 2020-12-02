#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
#define pb push_back
#define fi first
#define se second
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
const int maxn=1e5+10;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;
int minpos(string a) {
    int k=0,i=0,j=1,n=a.size();
    while(k<n&&i<n&&j<n) {
        if(a[(i+k)%n]==a[(j+k)%n]) k++;
        else {
            if(a[(i+k)%n]>a[(j+k)%n]) i=i+k+1;
            else j=j+k+1;
            if(i==j) i++;
            k=0;
        }
    }
    i=min(i,j);
}
string trans(string a,int pos) {
    string ans;
    rep(i,0,a.size()-1) ans+=a[(i+pos)%a.size()];
    return ans;
}

