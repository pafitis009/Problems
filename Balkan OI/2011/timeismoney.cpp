#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pi;

struct edge{int s,e,x,y;}adj[10004];

int N , M;
typedef long long lint;
int mc1 , mc2 , mx = 1e9 , my = 1e9 , CUR1 , CUR2;

struct disj{
    int pa[204];
    void init(int n){for(int i=0; i<n; i++) pa[i] = i;}
    int findd(int x){return pa[x] = (pa[x] == x ? x : findd(pa[x]));}
    bool uni(int p , int q){
        p = findd(p) , q = findd(q);
        if(p == q) return 0;
        pa[q] = p;return 1;
    }
}disj;

bool ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 >= 1ll * dy1 * dx2;
}

bool cmp(const edge &aa , const edge &bb){
    return (1ll * aa.x * CUR1) + (1ll * aa.y * CUR2) < (1ll * bb.x * CUR1) + (1ll * bb.y * CUR2);
}

pi get_mst(int c1 , int c2 , int is){
    disj.init(N);
    CUR1 = c1 , CUR2 = c2;
    sort(adj , adj+M , cmp);

    pi tmp(0,0);
    for(int i=0; i<M; i++){
        if(disj.uni(adj[i].s , adj[i].e)){
            tmp.first += adj[i].x;
            tmp.second += adj[i].y;
            if(is) cout << adj[i].s << " " << adj[i].e << endl;
        }
    }
    if(1ll * mx * my > 1ll * tmp.first * tmp.second){
        mx = tmp.first  , my = tmp.second;
        mc1 = c1 , mc2 = c2;
    }


    return tmp;
}

void solve(pi u , pi l){
    pi n = get_mst(u.second - l.second , l.first - u.first , 0);
    if(!ccw(l,n,u)) solve(u,n) , solve(n,l);
}

int main(){
    cin >> N >> M;

    for(int i=0; i<M; i++) cin >> adj[i].s >> adj[i].e >> adj[i].x >> adj[i].y;

    pi upper = get_mst(1,0,0);
    pi lower = get_mst(0,1,0);

    solve(upper , lower);

    cout << mx << " " << my << endl;
    get_mst(mc1 , mc2 , 1);
    return 0;
}
