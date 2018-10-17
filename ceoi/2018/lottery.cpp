#include <bits/stdc++.h>
#define MAXN 10010
#define MAXQ 110
#define x first
#define y second
#define mp ma-e_pair

using namespace std;

typedef pair<int,int> pii;

int A[MAXN] , N , L , Q , ans[MAXQ][MAXN] , ch[MAXQ][MAXN] , final[MAXQ][MAXN];
pii qrs[MAXQ];


void add(int idx , int num){
    if(num <= qrs[0].x) {ch[0][idx]++;return;}
    if(num > qrs[Q-1].x) return;
    
    //cout <<"DICK" << endl;
    int low = 0 , high = Q - 1 , ret;
    
    while(low <= high){
        int mid = (low + high)/2;
        
        if(num <= qrs[mid].x){ret = mid; high = mid-1;}
        else  low = mid + 1;
    }
    
    ch[ret][idx]++;
}

int main()
{
    cin >> N >> L;
    
    for(int i=0; i<N; i++) cin >> A[i];
    
    cin >> Q;
    
    for(int i=0; i<Q; i++) {cin >> qrs[i].x; qrs[i].y = i;}
    
    sort(qrs , qrs + Q);
    
    for(int dif=1; dif<=N-L; dif++){
        int mism = 0;
        for(int i=0; i<L; i++)
            if(A[i] != A[dif + i]) mism++;
        
        //cout << mism << endl;
        add(0 , mism);
        //cout <<"DICK" << endl;
        add(dif , mism);
        
        int str = 1;
        
        while(str + dif + L <= N){
            if(A[str - 1] != A[str + dif - 1]) mism--;
            if(A[str + L - 1] != A[str + dif + L - 1]) mism++;
            
            //cout << mism << endl;
            
            add(str , mism);
            add(str + dif, mism);
            str++;
        }
        //cout << endl;
    }
    
    for(int i=0; i<Q; i++)
    for(int j=0; j<N; j++)
        ans[i][j] = ch[i][j] + ((i != 0) ? ans[i-1][j] : 0);
    
    for(int i=0; i<Q; i++)
        for(int j=0; j<N; j++)
            final[qrs[i].second][j] = ans[i][j];
        
    for(int i=0; i<Q; i++){
        for(int j=0; j<N-L+1; j++)
            cout << final[i][j] << " ";
        cout << '\n';    
    }
    
    return 0;
}
