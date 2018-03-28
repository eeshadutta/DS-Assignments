#include <bits/stdc++.h>
using namespace std;

queue<int> qu;
vector<int> adj[2000005];
bool visited[2000005];
int depth[2000005];
int n, k;

int BintoDec(string str, int len){
    int dec = 0;
    int base = 1;
    for (int i=len-1; i>=0; i--){
        dec = dec + ((str[i]-'0') * base);
        base = base * 2;
    }
    return dec;
}

void bfs()
{
    while (!qu.empty())
    {
        int parent = qu.front();
        qu.pop();
        for (int i = 0; i < k; i++)
        {
            int temp = parent ^ (1<<i);
            if (visited[temp] == false)
            {
                qu.push(temp);
                visited[temp] = true;
                depth[temp] = depth[parent] + 1;
            }
        }
    }
    return;
}

int main()
{
    cin >> n >> k;
    string str;
    for (int i = 0; i < 2000005; i++){
        visited[i] = false;
        depth[i] = 0;
    }
    for (int i=1; i<=n; i++){
        cin >> str;
        int dec = BintoDec(str, k);
        if (visited[dec] == false){
            qu.push(dec);
            visited[dec] = true;
        }
    }
    bfs();
    int max = 0;
    for (int i=0; i<2000005; i++){
        if (depth[i] > max){
            max = depth[i];
        }
    }
    int ans;
    ans = k-max;
    cout << ans;
    cout << "\n";
    return 0;
}