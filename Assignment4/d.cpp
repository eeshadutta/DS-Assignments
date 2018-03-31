#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
int n;
vector <long long> arr;
vector <long long> segTree[4*MAXN];

void build(int start, int end, int ind){
    if (start == end){
        segTree[ind].push_back(arr[start]);
        return;
    }
    int mid = start + (end-start)/2;
    build(start, mid, 2*ind);
    build(mid+1, end, 2*ind+1);

    int n1 = segTree[2*ind].size();
    int n2 = segTree[2*ind + 1].size();
    int i=0, j=0;
    while((i<n1) && (j<n2)){
        if (segTree[2*ind][i] < segTree[2*ind+1][j]){
            segTree[ind].push_back(segTree[2*ind][i]);
            i++;
        }
        else {
            segTree[ind].push_back(segTree[2*ind+1][j]);
            j++;
        }
    }
    while(i<n1){
        segTree[ind].push_back(segTree[2*ind][i]);
        i++;
    }
    while(j<n2){
        segTree[ind].push_back(segTree[2*ind+1][j]);
        j++;
    }
    return;
}

int query(int left, int right, int start, int end, int index, long long k){
    if ((left <= start) && (right >= end)){
        int len = segTree[index].size();
        return upper_bound(segTree[index].begin(), segTree[index].end(), k) - segTree[index].begin();
    }
    else if ((left > end) || (right < start)){
        return 0;
    } 
    else {
        int mid = start + (end - start)/2;
        return (query(left, right, start, mid, 2*index, k) + query(left, right, mid+1, end, 2*index+1, k));
    }   
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    arr.push_back(0);
    for (int i=1; i<=n; i++){
        int val;
        cin >> val;
        arr.push_back(val);
    }
    build(1, n, 1);

    int q;
    cin >> q;
    while(q--){
        int left, right;
        long long k;
        cin >> left >> right >> k;
        int ans;
        ans = query(left, right, 1, n, 1, k);
        cout << ans << "\n";
    }
    return 0;
}