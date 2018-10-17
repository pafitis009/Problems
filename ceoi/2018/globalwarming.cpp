#include <bits/stdc++.h>
#define MAXN 201000

using namespace std;
int M1[MAXN] , P1[MAXN] , M2[MAXN] , P2[MAXN] , gt[MAXN] , x , get[MAXN]
, arr[MAXN] , N;
int main() {
    cin >> N >> x;
    //cout << "YES" << endl;
    for(int i=0; i<N; i++) {
        cin >> arr[i];
        //cout << arr[i];
        
    }
    
    //cout << "YES" << endl;
    
    //M1[0] = 0;
    int L = 0;
    for(int i=0; i<N-1; i++){
        int lo = 1 , hi = L;
        
        while(lo <= hi){
            int mid = ceil((hi + lo)/2);
            if(arr[M1[mid]] < arr[i]) lo = mid + 1;
            else hi = mid - 1;   
        }
        
        //cout << lo << endl;
        
        int newL = lo;
        P1[i] = M1[newL - 1];
        M1[newL] = i;
        
        L = max(L , newL);
        
        int ret = 0; lo = 0 , hi = L;
        
        while(lo <= hi){
            int mid = (lo + hi)/2;
            
            if(arr[M1[mid]] <= arr[i + 1] + x - 1){ret = mid , lo = mid + 1;}
            else hi = mid - 1;
        }
        
        gt[i] = ret;
        //cout << ret << " " << M1[ret] << endl;
    }
    
    //cout << endl;
    for(int i=0; i<N; i++) arr[i] *= -1;
    reverse(arr , arr + N);
    
    L = 0;
    int ans = 1;
    for(int i=0; i<N-1; i++){
        int hi = L , lo = 1;
        //cout << "YES " << L << endl;
        while(lo <= hi){
            int mid = ceil((hi+lo)/2);
            
            if(arr[M2[mid]] < arr[i]) lo = mid + 1;
            else hi = mid - 1;
        }
        
        int newL = lo;
        P2[i] = M2[newL-1];
        M2[newL] = i;
        //cout << "YES" << endl;
        L = max(L , newL);
        
        //cout << i << " " << newL << "  " <<  gt[N - i - 2] << endl;
        
        ans = max(ans , newL + gt[N - i - 2]);
    }
    
    cout << ans << endl;
    
    return 0;
}
