#include <iostream>
#include <ctime>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstdlib>
using namespace std;
int t,s=20,cnt;
long long fac[1001];
long long ksc(long long x,long long y,long long mod){
	long long res=0;
	while(y) {
		if(y&1)
		res=(res+x)%mod;
		x=(x<<1)%mod;
		y>>=1;
	}
	return res;
}
long long ksm(long long x,long long y,long long mod) {
	long long res=1;
	while(y) {
		if(y&1)
		res=ksc(res,x,mod);
		x=ksc(x,x,mod);
		y>>=1;
	}
	return res;
}
int miller_rabin(long long n) {
	if(n==2)
	return 1;
	if(n<2||!(n%2))
	return 0;
	long long u,pre,x;
	int k=0;
	u=n-1;
	while(!(u&1)) {
		++k;
		u>>=1;
	}
	for(int i=1;i<=s;++i) {
		x=rand()%(n-2)+2;
		x=ksm(x,u,n);
		pre=x;
		for(int j=1;j<=k;++j) {
			x=ksc(x,x,n);
			if(x==1&&pre!=1&&pre!=n-1)
			return 0;
			pre=x;
		}
		if(x!=1)
		return 0;
	}
	return 1;
}
long long gcd(long long a,long long b){//注意与一般的gcd不一样
    if (a==0) return 1;//pollard_rho的需要
    if (a<0) return gcd(-a,b);//可能有负数
    while (b){
        long long t=a%b; a=b; b=t;
    }
    return a;
}
long long pollard_rho(long long n,long long c) {//找因子

	long long i=1,k=2;//用来判断是否形成了环
	long long xx=rand()%n,y=xx;
	while(1) {
		i++;
		xx=(ksc(xx,xx,n)+c)%n;
		long long d=gcd(y-xx,n);
		if(1<d&&d<n)//找到一个因数
		return d;
		if(y==xx)//出现循环，那么这次寻找失败
		return n;
		if(i==k){//相当于每次找连续k这么多次取模有没有得到相同余数
			y=xx;
			k<<=1;
		} 
	} 
}
void find(long long n) {//通过找因数来找质因子
	if(miller_rabin(n)) {
		fac[++cnt]=n;//记录质因子
		return;
	}
	long long p=n;
	while(p>=n)
	p=pollard_rho(p,rand()%(n-1)+1);//如果转了一圈还是p，则继续while循环
	//p是当前找到的一个因数（不一定是质因数），再分别找p和n/p的质因数
	find(p);
	find(n/p);
}
int main()
{
	srand(time(0)+19260817);
	scanf("%d",&t);
	while(t--)
	{
		long long x;
		scanf("%lld",&x);
		if(miller_rabin(x))
		{
			printf("Prime\n");
			continue;
		}
		cnt=0;	
		find(x); 
		sort(fac+1,fac+cnt+1);
        for(int i=1;i<=cnt;i++) cout<<fac[i]<<'\n';
	}
	return 0;
}

