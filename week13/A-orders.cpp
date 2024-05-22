// #include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;

vector<int> dp;

int main(){
    int n; cin>>n;
    vector<int> menu(n); // item price
    for(auto& ele: menu) cin>>ele;

    int m; cin>>m;
    vector<int> s(m); // total cost of an order
    int max_order=0;
    for(auto& ele: s) {
        cin>>ele;
        max_order = max(max_order, ele);
    }
    
    dp.assign(max_order+1,0);
    // go through every item
    for(int q=0; q<n; q++){
        int x = menu[q];
        if(dp[x]==0){
            dp[x]=q+1;
            // go through every possible sum, to fill up the dp table correctly
            for(int j=0; j<max_order+1-x; j++){
                if(dp[j]==0) continue; // skip the prices that can't be given
                if(dp[j]==-1){ 
                    dp[j+x] = -1; // if dp[j] has multi sol, then dp[j+x] also has multi sol
                    continue;
                }
                // following are case that dp[j] has unique sol
                if(dp[j+x]!=0){ // if dp[j+x] has at least a sol, then we have found another sol for dp[j+x]
                    dp[j+x]=-1;
                    continue;
                }
                // following are case that dp[j+x] has no sol yet
                dp[j+x]=q+1;
            }
        }
        else{
            dp[x]=-1;
            for(int j=1; j<max_order+1-x; j++){
                if(dp[j]!=0) dp[j+x] = -1;
            }
        }
    }
    // now just print out the answer
    for(int i=0; i<m; i++){
        int order=s[i];
        if(dp[order]==0) cout<<"Impossible";
        else if(dp[order]==-1) cout<<"Ambiguous";
        else{
            vector<int> ans;
            for(int p=order; p>0; ){
                ans.push_back(dp[p]);
                p -= menu[dp[p]-1];
            }
            sort(ans.begin(), ans.end());
            for(auto& ele: ans) cout<<ele<<" ";
        }
        cout<<"\n";
    }
    return 0;
}
