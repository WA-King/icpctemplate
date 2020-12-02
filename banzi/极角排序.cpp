const double eps=1e-9;
int sign(long double a) { return a<-eps?-1:a>eps; }
int cmp(long double a,long double b) { return sign(a-b); }
struct P {
    long double x,y;
    P() {}
    P(long double _x,long double _y) : x(_x),y(_y) {}
    P operator+(P p) { return {x+p.x,y+p.y}; }
    P operator-(P p) { return {x-p.x,y-p.y}; }
    P operator*(long double d) { return {x*d,y*d}; }
    P operator/(long double d) { return {x/d,y/d}; }
    bool operator==(P o) const {
        return cmp(x,o.x)==0&&cmp(y,o.y)==0;
    }
    long double len() {return sqrt(x*x+y*y);}
    long double dot(P p) { return x*p.x+y*p.y; }
    long double det(P p) { return x*p.y-y*p.x; }
    int quad() { return sign(y)==1||(sign(y)==0&&sign(x)>=0); }
};
bool cmp_angle(P a,P b) {
    int qa=a.quad(),qb=b.quad();
    if(qa==qb) {
        return a.det(b)>0;
    }
    else return qa<qb;
}