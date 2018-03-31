#include <bits/stdc++.h>
using namespace std;

const long long MAXN = 1e5 + 5;
vector <long long> adj[MAXN];
long long dp[MAXN];
bool visited[MAXN];
long long state[MAXN];

void dfs(long long curr, long long parent, long long check){
    if (visited[curr] == false){
        visited[curr] = true;
        bool isleaf = true;
        long long len = adj[curr].size();

        for (long long i=0; i<len; i++){
            if (adj[curr][i] != parent)
            {
                isleaf = false;
                dfs(adj[curr][i], curr, check);
                dp[curr] += max(0LL,dp[adj[curr][i]]);
            }
        }
        if (isleaf == true){
            if (state[curr] == check){
                dp[curr] = 1;
            }
            else {
                dp[curr] = 0;
            }
        }
        else {
            if (state[curr] == check){
                dp[curr] += 1;
            }
            else {
                dp[curr] -= 1;
            }
        }
    }
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    long long n;
    cin >> n;
    for (long long i=1; i<=n; i++){
        cin >> state[i];
    }
   
    for (long long i=1; i<n; i++){
        long long a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    for (long long i=1; i<=n; i++){
        visited[i] = false;
        dp[i] = 0;
    }
    dfs(1, -1, 0);
    long long max0 = -99999999999;
    for (int i=1; i<=n; i++){
        if (dp[i] > max0){
            max0 = dp[i];
        }
    }
    for (long long i=1; i<=n; i++){
        visited[i] = false;
        dp[i] = 0;
    }
    dfs(1, -1, 1);
    long long max1 = -99999999999;
    for (int i=1; i<=n; i++){
        if (dp[i] > max1){
            max1 = dp[i];
        }
    }
    long long ans;
    if (max0 > max1){
        ans = max0;
    }
    else {
        ans = max1;
    }
    cout << ans << "\n";
    return 0;
}