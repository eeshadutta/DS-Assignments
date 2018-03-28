#include <stdio.h>
#include <stdlib.h>
#define MAXN 100005 

typedef struct node{
    int d, t, s;
}girl;

girl arr[MAXN];
girl heap[MAXN];
int n, d;
int heapn;

void swap(girl *x, girl *y)
{
    girl temp = *x;
    *x = *y;
    *y = temp;
    return;
}

void heapify(int i)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;
    if (left <= heapn && heap[left].s > heap[largest].s)
    {
        largest = left;
    }
    if (right <= heapn && heap[right].s > heap[largest].s)
    {
        largest = right;
    }
    swap(&heap[i], &heap[largest]);
    if (largest != i)
    {
        heapify(largest);
    }
    return;
}

/*void buildHeap()
{
    int i;
    for (i = n; i >= 1; i--)
    {
        heapify(i);
    }
    return;
}*/

void insert(girl val)
{
    int ind = heapn + 1;
    heap[ind] = val;
    heapn++;
    while (ind != 1)
    {
        if (heap[ind].s > heap[ind / 2].s)
        {
            swap(&heap[ind], &heap[ind / 2]);
        }
        ind /= 2;
    }
    return;
}

void pop()
{
    swap(&heap[1], &heap[n]);
    heapn--;
    heapify(1);
    return;
}

int cmp(void const * a, void const * b){
    girl x = *(girl *)a;
    girl y = *(girl*)b;
    return (x.d - y.d);
}

int main(){
    int t;
    scanf ("%d", &t);
    while(t--){
        scanf("%d %d", &n, &d);
        for (int i=0; i<n; i++){
            //printf("i: %d\n", i);
            scanf ("%d %d %d", &arr[i].d, &arr[i].t, &arr[i].s);
        }
        //printf("done reading\n");

        qsort(arr, n, sizeof(girl), cmp);

        int k=0;
        for (int i=1; i<=d; i++){
            while(k<n && arr[k].d==i){
                insert(arr[k]);
                k++;
            }
            heap[1].t--;
            if (heap[1].t==0){
                pop();
            }
        }
        long long ans=0;
        for (int i=1; i<=heapn; i++){
            ans += heap[i].s *1LL* heap[i].t;
        }

        printf("%lld\n", ans);
    }
    return 0;
}