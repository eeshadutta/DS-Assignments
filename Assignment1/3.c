#include <stdio.h>
#include <stdlib.h>
int swaps=0;

int BinarySearch(long long arr[],int small[],int n, long long value)
{
   int beg = 0;
   int end = n-1;
   int mid;
   while (beg < end)
   {
       mid = beg + ((end - beg) / 2);
       if (arr[small[mid]] > value)
           end = mid;
       else if (arr[small[mid]] < value)
           beg = mid + 1;
       else
           return mid;
   }
   return beg;
}
  
int lis(long long arr[], int n)
{
    int small[n];
    int parent[n];
    int length = 0;
    int i;
    for(i=0 ; i<n ;i++)
    {
        if(i == 0)
        {
            small[length] = i;
            parent[i] = -1;
        }
        else if(arr[i] <= arr[small[length]])
        {
            int pos = BinarySearch(arr,small,length+1,arr[i]);
            small[pos] = i;
            if(pos != 0)
            {
                parent[i] = small[pos-1];
            }
        }
        else
        {
            length++;
            small[length] = i;
            parent[i] = small[length-1];
        }
    }
    return (length+1);
}

void Merge (long long int arr[], int beg, int mid, int end)
{
    int n=end-beg+1, l;
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
		int mid, i;
        int n=end-beg+1;
        long long temp[n];	
		mid=beg+(end-beg)/2;
		MergeSort (arr, beg, mid);
		MergeSort (arr, mid+1, end);
        for (i=beg; i<=end; i++)
            temp[i-beg]=arr[i];
        swaps += (n-lis(temp,n));
		Merge (arr, beg, mid, end);
	}
    return;
}

int main()
{
	int n, i;
	scanf ("%d", &n);
    long long arr[n];
	for (i=0; i<n; i++)
		scanf ("%lld", &arr[i]);

	MergeSort (arr, 0, n-1);

    printf("%d\n", swaps);
	return 0;
}
