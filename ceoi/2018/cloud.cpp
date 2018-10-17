#include <bits/stdc++.h>
#define MAXC 100010
#define MAXN 4018
using namespace std;


using lint = long long;
using pi = pair<int,int>;



struct ord{
    int c,f,v;  
    
    bool operator<(const ord &o){
        return pi(o.f , o.c) < pi(f,c);
    }
}arr[MAXN];

int N , M;
lint last[MAXC] , cur[MAXC];

int main(){
    cin >> N;
    
    for(int i=0; i<N; i++) {
        cin >> arr[i].c >> arr[i].f >> arr[i].v;
        arr[i].v *= -1;
    }
    
    cin >> M;
    
    for(int i=N; i<N+M; i++) {
        cin >> arr[i].c >> arr[i].f >> arr[i].v;
        arr[i].c *= -1;
    }
    
    
    sort(arr , arr + M + N);
    
    for(int i=0; i<MAXC; i++) last[i] = -1e18;
    last[0] = 0;
    
    
    for(int i=0; i<N+M; i++){

        for(int j=0; j<MAXC; j++){
            cur[j] = last[j];
            if(j - arr[i].c >= 0 && j - arr[i].c < MAXC) 
                cur[j] = max(cur[j] , last[j - arr[i].c] + arr[i].v);
        }
        memcpy(last , cur , sizeof(last));
    }
    
    cout << *max_element(last , last + MAXC);
    
    return 0;
}
