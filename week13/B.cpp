#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

int main(){
    int s; cin>>s;
    vector<int> d(s),c(s),f(s),u(s);
    for(int i=0; i<s; i++){
        cin>>d[i]>>c[i]>>f[i]>>u[i];
    }

    // n_u: #delegates of uncertained states
    // n_c: #delegates that must vote for c
    // n_f: #delegates that must vote for f
    vector<pair<int,int> > u_state; // (i,#voters to convince)
    int n_u=0, n_c=0, n_f=0; 
    for(int i=0; i<s; i++){
        if(f[i]>=c[i]+u[i]) {
            n_f+=d[i];
        }
        else if(c[i]>f[i]+u[i]) {
            n_c+=d[i];
        }
        else{
            n_u+=d[i];
            u_state.push_back({i,(f[i]+c[i]+u[i])/2+1-c[i]});
        }
    }
    // decide if is impossible to win
    if(n_f>=n_c+n_u) cout<<"impossible\n";
    else{
        
    }

    return 0;
}
