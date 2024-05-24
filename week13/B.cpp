#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
#define val first
#define weight second

// Run-time error
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
    int u_voter_sum=0;
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
            int u_voter=(f[i]+c[i]+u[i])/2+1-c[i];
            u_state.push_back({i,u_voter});
            u_voter_sum += u_voter;
        }
    }
    // decide if is impossible to win
    if(n_f>=n_c+n_u) cout<<"impossible\n";
    else{
        int M=n_u, N=u_state.size();
        // 1d array ver
        vector<pair<int,int> > dp(M+1, {n_u, u_voter_sum});
        // dp[m].first=val: the curr delegtes number sum
        // dp[m].second=weight: the corresponding voter sum (that needed to be convinced)
        // for each uncertained state, check if no visiting can still satisfy the least requirement p or not
        // if yes, remove it
        for(int n=1; n<N+1; n++){
            for(int p=M; p>0; p--){
                int remain = dp[p].val - d[u_state[n-1].first];
                if(remain>=p) // it's valid to remove the state 
                    dp[p].second = min(dp[p].weight,  // doesn't remove 
                                        dp[p].weight - u_state[n-1].weight ) ;// remove
            }
        }
        // still need this many delegates vote to win 
        int m=(n_c+n_f+n_u)/2+1-n_c;
        cout<<dp[m][u_state.size()]<<"\n";
    }

    return 0;
}