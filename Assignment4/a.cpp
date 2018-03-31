#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 5;
const long long M = 1e9 + 7;

struct node{
    long long x11, x12, x21, x22;
};

node arr[MAXN];
node segTree[4 * MAXN];
int n;

node build(int start, int end, int index){
    if (start == end){
        segTree[index].x11 = arr[start].x11;
        segTree[index].x12 = arr[start].x12;
        segTree[index].x21 = arr[start].x21;
        segTree[index].x22 = arr[start].x22;
        return segTree[index];
    }
    int mid = start + (end - start)/2;
    node left = build(start, mid, 2*index);
    node right = build(mid+1, end, 2*index+1);
    segTree[index].x11 = ((left.x11 * right.x11)%M + (left.x12 * right.x21)%M)%M;
    segTree[index].x12 = ((left.x11 * right.x12)%M + (left.x12 * right.x22)%M)%M;
    segTree[index].x21 = ((left.x21 * right.x11)%M + (left.x22 * right.x21)%M)%M;
    segTree[index].x22 = ((left.x21 * right.x12)%M + (left.x22 * right.x22)%M)%M;
    return segTree[index];
}

node query(int left, int right, int start, int end, int index){
    if ((left <= start) && (right >= end)){
        return segTree[index];
    }
    else if ((left > end) || (right < start)){
        node temp;
        temp.x11 = 1;
        temp.x12 = 0;
        temp.x21 = 0;
        temp.x22 = 1;
        return temp;
    }
    else {
        int mid = start + (end - start)/2;
        node L = query(left, right, start, mid, 2*index);
        node R = query(left, right, mid+1, end, 2*index+1);
        node temp;
        temp.x11 = ((L.x11 * R.x11)%M + (L.x12 * R.x21)%M)%M;
        temp.x12 = ((L.x11 * R.x12)%M + (L.x12 * R.x22)%M)%M;
        temp.x21 = ((L.x21 * R.x11)%M + (L.x22 * R.x21)%M)%M;
        temp.x22 = ((L.x21 * R.x12)%M + (L.x22 * R.x22)%M)%M;
        return temp;
    }
}

void update(int start, int end, int ind, int seg_ind){
    if (start == end){
        if (start == ind){
            segTree[seg_ind].x11 = arr[ind].x11;
            segTree[seg_ind].x12 = arr[ind].x12;
            segTree[seg_ind].x21 = arr[ind].x21;
            segTree[seg_ind].x22 = arr[ind].x22;
            return;            
        }
    }
    if ((ind < start) || (ind > end))
    return;
    if (start != end){
        int mid = start + (end - start)/2;
        update(start, mid, ind, 2*seg_ind);
        update(mid+1, end, ind, 2*seg_ind + 1);
    }
    segTree[seg_ind].x11 = ((segTree[2*seg_ind].x11 * segTree[2*seg_ind+1].x11)%M + (segTree[2*seg_ind].x12 * segTree[2*seg_ind+1].x21)%M)%M;
    segTree[seg_ind].x12 = ((segTree[2*seg_ind].x11 * segTree[2*seg_ind+1].x12)%M + (segTree[2*seg_ind].x12 * segTree[2*seg_ind+1].x22)%M)%M;
    segTree[seg_ind].x21 = ((segTree[2*seg_ind].x21 * segTree[2*seg_ind+1].x11)%M + (segTree[2*seg_ind].x22 * segTree[2*seg_ind+1].x21)%M)%M;
    segTree[seg_ind].x22 = ((segTree[2*seg_ind].x21 * segTree[2*seg_ind+1].x12)%M + (segTree[2*seg_ind].x22 * segTree[2*seg_ind+1].x22)%M)%M;
    return;
}

int main(){
    cin >> n;
    for (int i=1; i<=n; i++){
        cin >> arr[i].x11 >> arr[i].x12 >> arr[i].x21 >> arr[i].x22;
    }
    node temp = build(1, n, 1);
    int q;
    cin >> q;
    while(q--){
        int flag;
        cin >> flag;
        if (flag == 1){
            int left, right;
            cin >> left >> right;
            node temp = query(left, right, 1, n, 1);
            printf ("%lld %lld %lld %lld\n", temp.x11, temp.x12, temp.x21, temp.x22);
        }
        else if (flag == 2){
            int ind;
            node temp;
            cin >> ind >> temp.x11 >> temp.x12 >> temp.x21 >> temp.x22;
            arr[ind].x11 = temp.x11;
            arr[ind].x12 = temp.x12;
            arr[ind].x21 = temp.x21;
            arr[ind].x22 = temp.x22;
            update(1, n, ind, 1);
        }
    }
    return 0;
}