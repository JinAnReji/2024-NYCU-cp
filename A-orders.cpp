#include<bits/stdc++.h>
using namespace std;

int main(){
    int n; cin>>n;
    vector<pair<int,int> > c(n); // item cost
    for(int i=0; i<n; i++) {
        c[i].first=i;
        cin>>c[i].second;
    }
    int m; cin>>m;
    vector<int> s(m); // total cost of an order
    int max_order=0;
    for(auto& ele: s) {
        cin>>ele;
        max_order = max(max_order, ele);
    }
    
    // determin 3 cases:
    // 1. unique order? print the index out
    // 2. impossible order?
    // 3. more than one ways to give such sum?
    
    struct
    {
        bool operator()(pair<int,int> a, pair<int,int> b) const { return a.second < b.second; }
    } customLess;
    
    // reorder the prices of each item into acscending order
    sort(c.begin(), c.end(), customLess);
    vector<int> dp(max_order+1,-1);  // record the index of item if the sum can be achieved  
    // use the cheapest item to initialize
    for( int j=1; j<=max_order ; j++){
        if(j>=c[0].second && j%c[0].second==0)
            dp[j] = c[0].first; // record the item index
        else{
            dp[j]=0;
        } 
    }
     // compute the answer for each order
    for(int o=0; o<m; o++){
         // go through items from low cost to higher cost
        for(int i=1; i<n; i++){
            // go from small order to the larger order
            for(int j=1; j<=s[o]; j++){
                int diff = j-c[i].second;
                if(diff<0 || dp[j]==-2) continue; // skip if the sum is not enough to order the curr item i
                if (diff%c[i].second==0){ // find an explicit sol for dp[j]
                    if(dp[j]) dp[j]=-2; // dp[j] already have a sol, mark -2: Ambiguous
                    else dp[j]=c[i].first;// dp[j] have no sol yet, store the item index
                }
                else{ // check the table for sol (may fail to find one)
                    if(dp[diff] && dp[j]) dp[j]=-2; // if dp[diff] has a sol and dp[j] also already has a sol: Ambiguous
                    else if (dp[diff]>=1) dp[j]=c[i].first; // if dp[diff] has a non-ambiguous sol and dp[j] has no sol yet: record the curr item index
                }
            }
        }  
        
        // output the answer
        if(dp[s[o]]==-2) cout<<"Ambiguous\n";
        else if(dp[s[o]]==0) cout<<"Impossible\n";
        else{
            list<int> ans;
            for(int i=s[o]; i>0; ){
                assert(dp[i]>=1);
                ans.push_front(dp[i]);
                i -= dp[i];
            }
            for(auto& ele: ans) cout<<ele<<" ";
            cout<<"\n";
        }
    }
    return 0;
}
