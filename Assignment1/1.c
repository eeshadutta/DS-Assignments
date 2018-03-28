#include<stdio.h>

int main()
{
    long long n, k;
    scanf ("%lld %lld", &n, &k);
    long long arr[n], i, sum=0;
    for(i=1; i<=n; i++)
    {
        scanf ("%lld", &arr[i]);
        sum += arr[i];
    }
    if(sum < k)
        printf ("-1\n");
    else if (sum==k)
        printf ("\n");
    else {
        long long ptr=1, nMod=n, count=0, dec;
        while(k > nMod){
            count=0;
            i = 1;
            while(nMod*i <= k){
                i++;
            }
            dec = i-1;
            k -= nMod*dec;
            for (i=1; i<=n; i++){
                if (arr[i]==0){
                   count++;
                   continue;
                }
                arr[i] -= dec;
                if(arr[i] < 0){
                   k += -arr[i];
                   arr[i] = 0;
                   count++;
                }
            } 
            nMod = n-count;
        }
        for (i=1; k>0; i++){
            if (arr[i]  !=0){
                arr[i]--;
                k--;
                ptr = i+1;
            }
        }
        for (i=1; i<=n; i++){
            if (ptr > n)
                ptr = 1;
            if (arr[ptr] != 0){
                printf ("%lld ", ptr);
            }
            ptr++;
        }
        printf ("\n");
    }
    return 0;
}