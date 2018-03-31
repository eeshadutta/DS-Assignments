#include <bits/stdc++.h>
using namespace std;

struct node{
    int val;
    int start;
    int end;
    int level;
};

const int MAXN = 1e5 + 5;
vector <node> adj[MAXN];
vector <node> levels[MAXN];
node vertices[MAXN];
bool visited[MAXN];
int x = 0;

int binSearch_start(int lev, int beg, int fin, int k){//returns the index of the element whose start value is just greater then k
    int pos=-1;
    while(beg <= fin){
        int mid = beg + (fin-beg)/2;
        if (levels[lev][mid].start <= k){
            beg = mid + 1;
        }
        else {
        	pos = mid;
            fin = mid-1;
        }
    }
    return pos;
}

int binSearch_end(int lev, int beg, int fin, int k){//returns the index of the element whose end value is just less then k
    int pos = -1;
    while (beg <= fin){
        int mid = beg + (fin-beg)/2;
        if (levels[lev][mid].end <= k){
            pos = mid; 
            beg = mid + 1;
        }
        else {

            fin = mid-1;
        }
    }
    return pos;
}

void dfs(node curr, node parent){
    if (visited[curr.val] == false){
        visited[curr.val] = true;
        curr.start = ++x;
        vertices[curr.val].start = curr.start;        
        curr.level = parent.level + 1;
        vertices[curr.val].level = curr.level;
        levels[curr.level].push_back(curr);
        int len = adj[curr.val].size();
        for (int i=0; i<len; i++){
            if (adj[curr.val][i].val != parent.val){
                dfs(adj[curr.val][i], curr);
            }
        }
        curr.end = ++x;
        vertices[curr.val].end = curr.end;
        levels[curr.level][levels[curr.level].size()-1].end = curr.end; 
    }
    return;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, q;
    cin >> n >> q;
    for (int i=1; i<n; i++){
        int a , b;
        cin >> a >> b;
        vertices[a].val = a;
        vertices[b].val = b;
        adj[a].push_back(vertices[b]);
        adj[b].push_back(vertices[a]);
    }
    for (int i=1; i<=n; i++){
        visited[i] = false;
    }
    node parent;
    parent.val = -1;
    parent.level = -1;
    dfs(vertices[1], parent);
    
    while(q--){
        int v, d;
        cin >> v >> d;
        int req_lev = vertices[v].level + d;
        if (d == 0){
            cout << "1" << endl;
            continue;
        }
        int beg = binSearch_start(req_lev, 0, levels[req_lev].size() - 1, vertices[v].start);
        int fin = binSearch_end(req_lev, 0, levels[req_lev].size() - 1, vertices[v].end);
        int ans = fin - beg + 1;
        if (beg == -1 || fin == -1){
            ans = 0;
        }
        cout << ans << endl;
    }
    return 0;
}