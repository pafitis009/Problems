#include <bits/stdc++.h>
#define PI 3.14159265358979323846
#define MAXN 500100
using namespace std;
typedef complex<double> base;
int d[MAXN];
void compute_d(){
    for(int i=1; i<MAXN; i++){
        int j = i;
        while(j < MAXN){d[j]++;j+=i;}
    }

    //for(int i=0; i<10; i++) cout << d[i] << endl;
    //cout << endl;
    //cout << endl;cout << endl;

    double ans = 0;
    for(int i=1000; i<MAXN; i++){

        double tmp = (double)d[i]/i;
        ans = max(ans , tmp);
        //cout << fixed <<setprecision(10) << tmp << endl;
    }
    //cout << fixed << setprecision(10) << ans << endl;
}

void fft(vector<base> &a , bool invert){
    int n = a.size();
    if(n == 1) return;

    vector<base> a0(n/2) , a1(n/2);
    for(int i=0,j=0; i<n; i+=2 , j++){
        a0[j] = a[i];
        a1[j] = a[i+1];
    }
    fft(a0 , invert);
    fft(a1 , invert);

    double angle = 2*PI/n * (invert ? -1 : 1);
    base w(1) , wn = base(cos(angle) , sin(angle));

    for(int i=0; i<n/2; i++){
        a[i] = a0[i] + w*a1[i];
        a[i+(n/2)] = a0[i] - w*a1[i];
        if(invert)  a[i]/=2 , a[i+(n/2)]/=2;
        w*=wn;
    }
}

void multiply(vector<int> a , vector<int> b , vector<int> &ans){
    vector <base> fa(a.begin() , a.end()) , fb(b.begin() , b.end());
    int  n = 1;
    while(n < max(a.size() , b.size())) n <<= 1;

    n <<= 1;

    fa.resize(n) , fb.resize(n);
    fft(fa , false) , fft(fb , false);
    for(int i=0; i<n; i++) fa[i] *= fb[i];
    fft(fa , true);
    ans.resize(n);

    for(int i=0; i<n; i++) ans[i] = (int)(fa[i].real() + 0.5);
    //cout << n <<endl;
    //cout << endl;
}

int main(){
    compute_d();
    int T; cin >> T;

    vector <int> A , B; A.clear() , B.clear();A.push_back(0) , B.push_back(0);
    for(int i=1; i<=500010; i++) A.push_back(d[i]);

    B = A;
    vector<int> ans;

    multiply(A , B , ans);

    while(T--){
        int a , b; cin >> a >> b;

        /*for(int i=0; i<ans.size(); i++) cout << ans[i] << " ";
        for(int i=0; i<A.size(); i++) cout << A[i] << " ";
        for(int i=0; i<B.size(); i++) cout << B[i] << " ";*/
        int idx = a;
        for(int i=a; i<=b; i++)
            if(ans[i] > ans[idx]) idx = i;

        //for(int i=0; i<ans.size(); i++) cout << ans[i] << " ";
        //cout << endl;
        cout << idx << " " << ans[idx] << endl;
    }

    return 0;
}
