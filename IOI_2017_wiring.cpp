#include <bits/stdc++.h>
#define MAXN 200100
#define INF 1e18

using namespace std;

typedef long long int lint;
typedef pair<lint,int> pi;

vector <pi> all;
vector < vector<lint> > dp;

int blues , reds , G[MAXN];
lint par[MAXN];

lint ass(int a , int b , int c){
    if(a >= b || c < b) return 0ll;
    lint n = max(b-a , c-b+1);
    lint ret = 0;

    //for(int i=a; i<b; i++) ret += (all[b-1].first - all[i].first);
    //for(int i=b; i<=c; i++) ret+= (all[i].first - all[b].first);


    ret = ret + (b-a)*all[b-1].first;
    ret = ret - (c-b+1)*all[b].first;
    ret -= par[b-1]; ret += par[c];
    if(a) ret += par[a-1];
    if(b) ret -= par[b-1];

    ret = ret + (n * (all[b].first - all[b-1].first));

    return ret;
}

lint solve(){
    dp.assign(MAXN , vector<lint>());
    int idx = 1 , cnt = 0;
    
    for(int i=0; i<all.size(); i++){
        if(i == 0) par[i] = all[i].first;
        else par[i] = par[i-1] + all[i].first;
    }
    
    while(idx < blues + reds){
        if(all[idx].second != all[idx-1].second)
            G[cnt++] = idx - prev;
        idx++;
    }
    
    G[cnt++] = idx - prev;

    for(int i=0; i<cnt; i++)
        dp[i].assign(G[i] + 2, INF);

    idx = 1 , cnt = 0;
    dp[0][G[0]] = 0;
    while(idx < blues + reds){
        if(all[idx].second != all[idx-1].second){
            for(int i=G[cnt]-1; i>=0; i--)
                dp[cnt][i] = min(dp[cnt][i] , dp[cnt][i+1] + abs(all[idx].first - all[idx-i-1].first));

            for(int i=0; i<=min(G[cnt],G[cnt+1]); i++)
                dp[cnt+1][G[cnt+1]-i] = min(dp[cnt+1][G[cnt+1]-i] , dp[cnt][i] + ass(idx - i , idx , idx+i-1));

            for(int i=G[cnt+1]-1; i>=0; i--)
                dp[cnt+1][i] = min(dp[cnt+1][i] ,dp[cnt+1][i+1] + abs(all[idx-1].first - all[idx+G[cnt+1]-i-1].first));
            
            cnt++;
        }
        idx++;
    }

    return dp[cnt][0];
}

long long min_total_length(vector <int> r , vector<int> b){
    blues = b.size();
    reds = r.size();
    all.clear();
    
    for(int i=0; i<blues; i++) all.push_back({b[i] , 1});
    for(int i=0; i<reds; i++) all.push_back({r[i] , -1});

    sort(all.begin() , all.end());
    
    long long ret = solve();

    return ret;
}


