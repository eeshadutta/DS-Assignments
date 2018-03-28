#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
const int MAXN = 1e5 + 5;
vector<int> edges[MAXN];
vector<int> weights[MAXN];
int n;
const long long M=1e9+7;
int status[MAXN];
int zero=0;
int freq[MAXN];
int cost[MAXN];

struct node{
    int u, v, c;
};

node A[MAXN];

int cmp(void const*a, void const*b){
    node x = *(node*)a;
    node y = *(node*)b;
    return (x.c - y.c);
}

long long power(long long x, long long y, long long m){
    if (y==0){
        return 1;
    }
    if (y==1){
        return x;
    }
    long long e;
    e = power(x, y/2, m);
    e = (e*e) % m;
    if (y%2 != 0){
        e = (e*x)%m;
    }
    return e;
}

void dfs(int u, int p, int c){
    if(status[u] == 0)return;
    int length=edges[u].size();
    status[u] = 0;
    int flag=0;
    for (int i=0; i<length; i++){
        if (weights[u][i]==c){
            flag++;
        }
    }
    if (flag>=2){
        zero = 1;
        return;
    }
    for (int i=0; i<length; i++){
        
        if (edges[u][i]!=p){
            dfs(edges[u][i], u, weights[u][i]);
        }
        if (zero)break;
    }
    return;
}

int main(){
    scanf("%d", &n);
    if(n==1){
        printf("1\n");
        return 0;
    }
    for (int i=0; i<n-1; i++){
        scanf("%d %d %d", &A[i].u, &A[i].v, &A[i].c);
    }
    qsort(A, n-1, sizeof(node), cmp);
    for (int i=0; i<n-1; i++){
        edges[A[i].u].push_back(A[i].v);
        edges[A[i].v].push_back(A[i].u);
        weights[A[i].u].push_back(A[i].c);
        weights[A[i].v].push_back(A[i].c);
    }
    for(int i=1; i<=n; i++){
        status[i]=1;
        //printf("%d", status[i]);
    }

    for (int i=1; i<=n; i++){
        int cnt=0;
        int x = weights[i][0];
        int count = 1;
        for (int j=1; j<weights[i].size(); j++){
            if (weights[i][j]==x){
                count++;
                //dfs(edges[i][j], i);
                //dfs(edges[i][ind], i);
            }
            else{
                freq[cnt++] = count;
                cost[cnt-1] = x;
                x = weights[i][j];
                count=1;
            }
        }
        freq[cnt++] = count;
        cost[cnt-1] = x;
        cnt = 0;
        for(int j=0; j<weights[i].size(); j++){
            while(cost[cnt]!=weights[i][j])cnt++;
            if(freq[cnt] != 1)
            dfs(edges[i][j], i, weights[i][j]);
            if (zero)
            break;
        }
    }
    int ans = 0;
    for (int i=1; i<=n; i++){
        ans += status[i];        
    }

    if (zero == 1){
        ans=0;
    }

    //printf("%d\n", ans);

    long long req;
    req= power(ans, ans, M-1);
    req= power(ans, req, M);
    printf("%lld\n", req);   

    return 0;
}
