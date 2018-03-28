#include <vector>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
const int MAXN=1e3+5;
int X[MAXN], Y[MAXN], R[MAXN];
vector <int> edges[MAXN];
bool visited[MAXN];
int cycle[MAXN];
int flag=0;

void dfscc(int node, int parent){
    if (visited[node]!=true){
        visited[node] = true;
        int length = edges[node].size();
        int i;
        for (i=0; i<length; i++){
            if (edges[node][i]!=parent)
                dfscc(edges[node][i], node);
        }
    }
    return;
}

void dfsno(int node, int parent, int count){
    if (cycle[node]==-1){
        if (count%2 == 0){
            cycle[node]=0;
        }
        else {
            cycle[node]=1;
        }
        count++;
        int length = edges[node].size();
        for (int i=0; i<length; i++){
            if (edges[node][i]!=parent)
                dfsno(edges[node][i], node, count);
        }
    }
    else if ((cycle[node]==0 && count%2==1) || (cycle[node==1 && count%2==0])){
        flag=1;
    }
    return;
}

int gcd(int a, int b){
    if (a==0 || b==0){
        return 0;
    }
    if (a==b){
        return a;
    }
    if (a>b){
        return gcd(a-b, b);
    }
    if (b>a){
        return gcd(a, b-a);
    }
}

int main(){
    int n;
    scanf ("%d", &n);
    int i, j;
    
    for (i=1; i<=n; i++){
        scanf ("%d %d %d", &X[i], &Y[i], &R[i]);
    }
    
    for (i=1; i<=n; i++){
        for (j=1; j<=n; j++){
            if (((X[j] - X[i]) * (X[j] - X[i])) + ((Y[j] - Y[i]) * (Y[j] - Y[i])) == ((R[j] + R[i]) * (R[j] + R[i]))){
                edges[i].push_back(j);
                edges[j].push_back(i);
            }
        }
    }

    for (i=1; i<=n; i++){
        visited[i]=false;
    }

    for (i=1; i<=n; i++){
        cycle[i]=-1;
    }
    //printf("calculating\n");
    dfsno(1, -1, 0);
    //printf("1\n");
    if (flag == 1){
        printf("The input gear cannot move.\n");
        return 0;
    }

    dfscc(1, -1);
    //printf("2\n");
    if (visited[n]==false){
        printf("The input gear is not connected to the output gear.\n");
        return 0;
    }

    dfsno(1, -1, 0);
    //printf("3\n");
    int div = gcd(R[1], R[n]);
    //printf("gcd %d\n", div);
    R[1]/=div;
    R[n]/=div;
    if (cycle[1]==cycle[n]){
        printf("%d:%d\n", R[1], R[n]);
    }
    else {
        printf("-%d:%d\n", R[1], R[n]);
    }
    return 0;
}
