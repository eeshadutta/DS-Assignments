#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int com[MAXN];
bool dep[MAXN];
int visited[MAXN];
vector <int> g[MAXN];
vector <int> gr[MAXN];
int indegree[MAXN];
priority_queue <int, vector <int>, greater <int> > qu;
vector <int> lexi_order;
bool flag_cycle = false;

void dfs_cycle(int node){
    dep[node] = true;
    visited[node] = 0;
    int len = gr[node].size();
    for (int i=0; i<len; i++){
        if (visited[gr[node][i]] == -1){
            dfs_cycle(gr[node][i]);
        }
        else if (visited[gr[node][i]] == 0){
            flag_cycle = true;
            return;
        }
    }
    visited[node] = 1;
}

void topoSort(int n){
    for (int i=1; i<=n; i++){
        indegree[i] = 0;
    }
    for (int i=1; i<=n; i++){
        int len = g[i].size();
        for (int j=0; j<len; j++){
            indegree[g[i][j]]++;
        }
    }
    for (int i=1; i<=n; i++){
        if (indegree[i] == 0){
            qu.push(i);
        }
    }
    while (!qu.empty()){
        int curr = qu.top();
        qu.pop();
        lexi_order.push_back(curr);
        int len = g[curr].size();
        for (int i=0; i<len; i++){
            indegree[g[curr][i]]--;
            if (indegree[g[curr][i]] == 0){
                qu.push(g[curr][i]);
            }
        }
    }
    int len = lexi_order.size();
    for (int i=0; i<len; i++){
        if (dep[lexi_order[i]] == true)
            cout << lexi_order[i] << " ";
    }
    cout << "\n";
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, k;
    cin >> n >> m >> k;
    for (int i=1; i<=m; i++){
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        gr[v].push_back(u);
    }
    for (int i=0; i<k; i++){
        cin >> com[i];
    }
    for (int i=1; i<=n; i++){
        dep[i] = false;
    }
    for (int j=1; j<=n; j++){
        visited[j] = -1;
    }
    for (int i=0; i<k; i++){
        if(visited[com[i]]==-1)
        dfs_cycle(com[i]);
        if (flag_cycle == true){
            cout << "GO HOME RAJAS" << "\n";
            return 0;
        }
    }
    int count = 0;
    for (int i=1; i<=n; i++){
        if (dep[i] == true){
            count++;
        }
    }
    cout << count << "\n";
    topoSort(n);
    return 0;
}