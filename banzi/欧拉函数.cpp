//phi[1]=1,  1与1是互质的
int phi[maxn];
void euler(int n) {
    memset(phi,0,sizeof(phi));
    phi[1]=1;
    for(int i=2;i<=n;i++) {
        if(!phi[i]) {
            for(int j=i;j<=n;j++) {
                if(!phi[j]) phi[j]=j;
                phi[j]=phi[j]/i*(i-1);
            }
        }
    }
}