#include <stdio.h>

void Merge (long long arr[], long long beg, long long mid, long end, long long vel[]);
void MergeSort (long long pos[], long long beg, long long end, long long vel[]);
long long time(long long pos[], long long vel[], long long n, long long k);
int check(long long pos[], long long vel[], long long n, long long time, long long k);
long long inversions(long long arr[], long long n);
long long mergesort(long long arr[], long long beg, long long end);
long long merge(long long arr[], long long beg, long long end, long long mid);

int main(){
    long long n, k;
    scanf ("%lld %lld", &n, &k);
    long long pos[n], vel[n], i;
    for (i=0; i<n; i++){
        scanf("%lld", &pos[i]);
    }
    for (i=0; i<n; i++){
        scanf("%lld", &vel[i]);
    }
    MergeSort(pos, 0, n-1, vel);

    /*for (i=0; i<n; i++)
        printf("%lld ", pos[i]);
    printf("\n");
    for (i=0; i<n; i++)
        printf("%lld ", vel[i]);
    printf("\n");*/

    long long ans=time(pos, vel, n, k);
    if (ans>=10000000000)
        printf("-1\n");
    else
        printf("%lld\n", ans);
    return 0;
}

void Merge (long long arr[], long long beg, long long mid, long end, long long vel[]){
	long long n1=mid-beg+1;
	long long n2=end-mid;
	long long i,j,k;
	long long left[n1], right[n2];
    long long leftv[n1], rightv[n2];
	
	for (i=0; i<n1; i++){
		left[i]=arr[beg+i];
        leftv[i]=vel[beg+i];
    }
	for (j=0; j<n2; j++){
		right[j]=arr[mid+1+j];
        rightv[j]=vel[mid+1+j];
    }

	i=0;
	j=0;
	k=beg;

	while ((i<n1)&&(j<n2))
	{
		if (left[i]<right[j])
		{
			arr[k]=left[i];
            vel[k]=leftv[i];
			i++;
		}
        else if(left[i]==right[j])
        {
            if (leftv[i]<rightv[j])
            {
                arr[k]=left[i];
                vel[k]=leftv[i];
                i++;
            }
            else{
                arr[k]=right[j];
                vel[k]=rightv[j];
                j++;
            }
        }
		else
		{
			arr[k]=right[j];
            vel[k]=rightv[j];
			j++;
		}
		k++;
	}

	while (i<n1)
	{
		arr[k]=left[i];
        vel[k]=leftv[i];
		i++;
		k++;
	}
	while (j<n2)
	{
		arr[k]=right[j];
        vel[k]=rightv[j];
		j++;
		k++;
	}
    return;
}

void MergeSort (long long pos[], long long beg, long long end, long long vel[]){
	if (beg<end)
	{
		long long mid;	
		mid=beg+(end-beg)/2;
		MergeSort (pos, beg, mid, vel);
		MergeSort (pos, mid+1, end, vel);
		Merge (pos, beg, mid, end, vel);
	}
    return;
}

long long time(long long pos[], long long vel[], long long n, long long k){
    long long low = 0;
    long long high = 10000000000;
    long long mid;
    while(low < high){
        mid = low+(high-low)/2;
        int flag = check(pos, vel, n, mid, k);
        if (flag == 1){
            high = mid;
            //printf("high: %lld, mid: %lld\n",high, mid);
        }
        else{
            low = mid+1;
            //printf("low: %lld, mid: %lld\n", low, mid);
        }
    }
    return low;
}

int check(long long pos[], long long vel[], long long n, long long time, long long k){
    long long posfinal[n], i;
    for (i=0; i<n; i++){
        posfinal[i] = pos[i]+(vel[i]*time);
    }
    /*for (i=0; i<n; i++){
        printf("%lld ", posfinal[i]);
    }*/
    long long cars=inversions(posfinal, n);
    if (cars >= k)
        return 1;
    else
        return 0;
}

long long inversions(long long arr[], long long n){

    long long count = mergesort(arr, 0, n-1);
    //printf("count: %lld\n", count);
    return count; 
}

long long mergesort(long long arr[], long long beg, long long end){
    long long count=0;
    //printf("beg=%lld end=%lld\n",beg,end);
    if (beg<end){
        long long mid=beg+(end-beg)/2;
        count+= mergesort(arr, beg, mid);
        //printf("1mcount=%lld\n",count);
        count+= mergesort(arr, mid+1, end);
        //printf("2mcount=%lld\n",count);
        count+= merge(arr, beg, end, mid);
        //printf("3mcount=%lld\n",count);
    }
    return count;
}

long long merge(long long arr[], long long beg, long long end, long long mid) {
    long long n1=mid-beg+1;
	long long n2=end-mid;
	long long i,j,k;
	long long left[n1], right[n2];
    long long count=0;
	
	for (i=0; i<n1; i++){
		left[i]=arr[beg+i];
    }
	for (j=0; j<n2; j++){
		right[j]=arr[mid+1+j];
    }

	i=0;
	j=0;
	k=beg;
    //printf("n1=%lld i=%lld n2=%lld j=%lld\n",n1,i,n2,j);
    //printf("before while\n");
	while ((i<n1)&&(j<n2))
	{
       // printf("inside");
		if (left[i]<=right[j])
		{
            //printf("not there");
			arr[k]=left[i];
			i++;
		}
		else
		{
            count+= (n1-i);
            //printf("count=%lld n1=%lld i=%lld\n",count,n1,i);
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
    //printf("recount=%lld\n",count);
    return count;
}
    