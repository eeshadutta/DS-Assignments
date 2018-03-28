#include <stdio.h>
#include <stdlib.h>
#include <vector>
using namespace std;
const int MAXN=1e5+5;
vector <int> edges[MAXN];
vector <long long> weights[MAXN];
int X[MAXN], Y[MAXN];
int COL[MAXN];
int n;
int reds=0, blacks=0;
int countb[MAXN], countr[MAXN];
long long ans;
const long long M=1e9+7;

void colors(int u, int p){
    int length = edges[u].size();
    for (int i=0; i<length; i++){
        if (edges[u][i]!=p){
            colors(edges[u][i], u);
            countb[u] += countb[edges[u][i]];
            countr[u] += countr[edges[u][i]];
        }
    }
    if (COL[u]==1){
        countb[u]++;
    }
    else{
        countr[u]++;
    }
    return;
}

void dfs(int u, int p){
    int length=edges[u].size();
    for (int i=0; i<length; i++){
        if (edges[u][i]!=p){
            dfs(edges[u][i], u);
            int remb = blacks - countb[edges[u][i]];
            int remr = reds - countr[edges[u][i]];
            ans += (remb * 1LL * countb[edges[u][i]] * weights[u][i])%M;
            ans += (remr * 1LL * countr[edges[u][i]] * weights[u][i])%M;
            ans%=M;
        }
    }
    return;
}

int main(){
    scanf ("%d", &n);
    for (int i=1; i<=n; i++){
        scanf ("%d", &COL[i]);
        if (COL[i]==1){
            blacks++;
        }
        else{
            reds++;
        }
    }
    for (int i=1; i<=(n-1); i++){
        scanf("%d %d", &X[i], &Y[i]);
        edges[X[i]].push_back(Y[i]);
        edges[Y[i]].push_back(X[i]);
        long long cost;
        scanf ("%lld", &cost);
        weights[X[i]].push_back(cost);
        weights[Y[i]].push_back(cost);
    }

    colors(1,-1);

    /*for (int i=1; i<=n; i++){
        printf("countb[%d]:%d ", i, countb[i]);
        printf("countr[%d]:%d ", i, countr[i]);
    }*/

    dfs(1,-1);

    printf("%lld\n", ans);
    return 0;

}