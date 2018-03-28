#include <stdio.h>

void Merge (long long arr[], int beg, int mid, int end)
{
	int n1=mid-beg+1;
	int n2=end-mid;
	int i,j,k;
	long long left[n1], right[n2];
	
	for (i=0; i<n1; i++)
		left[i]=arr[beg+i];
	for (j=0; j<n2; j++)
		right[j]=arr[mid+1+j];

	i=0;
	j=0;
	k=beg;
	while ((i<n1)&&(j<n2))
	{
		if (left[i]<right[j])
		{
			arr[k]=left[i];
			i++;
		}
		else
		{
			arr[k]=right[j];
			j++;
		}
		k++;
	}

	while (i<n1)
	{
		arr[k]=left[i];
		i++;
		k++;
	}
	while (j<n2)
	{
		arr[k]=right[j];
		j++;
		k++;
	}
    return;
}

void MergeSort (long long arr[], int beg, int end)
{
	if (beg<end)
	{
		int mid;	
		mid=beg+(end-beg)/2;
		MergeSort (arr, beg, mid);
		MergeSort (arr, mid+1, end);
		Merge (arr, beg, mid, end);
	}
    return;
}

int check(long long arr[], int n, int k, long long timeassumed){
    int left=0, right=0, count=1;
    long long sum=0;
    while(right != n){
        sum = (arr[right]-arr[left]+1)*arr[right];
        if (sum > timeassumed){
            left = right;
            count++;
            sum = 0;
        }
        else 
            right++;
    }
    if (count <= k)
        return 1;
    else
        return 0;
}

long long time(long long arr[], int n, int k){
    long long low = arr[n-1];
    long long high = (arr[n-1]-arr[0]+1)*arr[n-1];
    while(low < high){
        long long mid = low+(high-low)/2;
        int flag = check(arr, n, k, mid);
        if (flag == 1){
            high = mid;
        }
        else{
            low = mid+1;
        }
    }
    return low;
}

int main()
{
	int n, k, i;
	scanf ("%d %d", &n, &k);
    long long arr[n];
	for (i=0; i<n; i++)
		scanf ("%lld", &arr[i]);

	MergeSort (arr, 0, n-1);
    long long ans=time(arr, n, k);
    printf("%lld\n", ans);
	return 0;
}
