#include "stdio.h"
#include "stdlib.h"
#define MOD 1000000007
typedef struct node
{
	struct node * next;
	struct node * prev;
	long long val;
}node;
/*Start of Template for Dequeue*/
node * push_front(node * head, long long value)
{
	//Returns the new head after adding element at front
	node * tmp=(node *)malloc(sizeof(node));
	if(head!=NULL)
	head->prev=tmp;
	tmp->prev=NULL;
	tmp->val=value;
	tmp->next=head;
	head=tmp;
	return head;
} 

node * push_end(node * tail, long long value)
{
	//Returns the new tail after adding element at end
	node * tmp=(node *)malloc(sizeof(node));
	if(tail!=NULL)
	tail->next=tmp;
	tmp->next=NULL;
	tmp->prev=tail;
	tmp->val=value;
	tail=tmp;
	return tail;
}

node * pop_front(node * head)
{
	//Returns the new head after removing element from front
	if(head==NULL)
		return head;
	node * tmp=head->next;
	if(tmp!=NULL)
	tmp->prev=NULL;
	free(head);
	return tmp;
}

node * pop_end(node * tail)
{
	//Returns the new tail after removing element from end
	if(tail==NULL)
		return tail;
	node * tmp=tail->prev;
	if(tmp!=NULL)
	tmp->next=NULL;
	free(tail);
	return tmp;
}

long long front(node * head)
{
	//Returns the front most element
	if(head==NULL)return -1;
	return head->val;
}

long long end(node * tail)
{
	//Returns the last element
	if(tail==NULL)return -1;
	return tail->val;
}
/*End of template for Dequeue*/

/*Template for Mod Iverse*/
long long modExp(long long a, long long b, long long p)
{
	if(b==0){
		return 1;
	}
	if(b==1)return a;
	long long ttt=modExp(a,b/2,p);
	ttt=(ttt*ttt)%p;
	if((b%2)==0)return ttt;
	return (ttt*a)%p;
}
long long modInv(long long aaa, long long bbb)
{
	return modExp(aaa,bbb-2,bbb);
}
/*End of Template for Mod Inverse*/

int N,K,i;
long long A[1000005];
long long min()
{
	node * HEAD=NULL; node * TAIL=NULL;
	TAIL=push_end(TAIL,0);
	if(HEAD==NULL)
	HEAD=TAIL;
	for(i=1; i<K; i++)
	{
		int idx=end(TAIL);
		while((idx!=-1) && (A[idx]>=A[i]))
		{
			TAIL=pop_end(TAIL);
			idx=end(TAIL);
		}
		if(TAIL==NULL)
			HEAD=NULL;
		TAIL=push_end(TAIL,i);
		if(HEAD==NULL)
			HEAD=TAIL;
	}
	long long prod_min=A[front(HEAD)];
	
	for(i=K; i<N; i++)
	{
		if((front(HEAD) < (i-K+1)) && (front(HEAD)!=-1))
		{
			if(HEAD==NULL)
				TAIL=NULL;
			HEAD=pop_front(HEAD);
		}	
		int idx=end(TAIL);
		int cnt=0;
		while((idx!=-1) && (A[idx]>=A[i]))
		{
			TAIL=pop_end(TAIL);
			idx=end(TAIL);
			cnt++;
		}
		if(TAIL==NULL)
			HEAD=NULL;
		if(HEAD!=NULL){
			prod_min=(prod_min*A[front(HEAD)])%MOD;
			TAIL=push_end(TAIL,i);
			if(HEAD==NULL)
			HEAD=TAIL;	
		}
		else
		{
			TAIL=push_end(TAIL,i);
			if(HEAD==NULL)
			HEAD=TAIL;
			prod_min=(prod_min*A[front(HEAD)])%MOD;	
		}
	}
	return prod_min;
}
long long max()
{
	node * HEAD=NULL; node * TAIL=NULL;
	TAIL=push_end(TAIL,0);
	if(HEAD==NULL)
	HEAD=TAIL;
	for(i=1; i<K; i++)
	{
		int idx=end(TAIL);
		while((idx!=-1) && (A[idx]<=A[i]))
		{
			TAIL=pop_end(TAIL);
			idx=end(TAIL);
		}
		if(TAIL==NULL)
			HEAD=NULL;
		TAIL=push_end(TAIL,i);
		if(HEAD==NULL)
			HEAD=TAIL;
	}
	long long prod_max=A[front(HEAD)];
	for(i=K; i<N; i++)
	{
		if((front(HEAD) < (i-K+1)) && (front(HEAD)!=-1))
		{
			HEAD=pop_front(HEAD);
			if(HEAD==NULL)
				TAIL=NULL;
		}
		int idx=end(TAIL);
		while((idx!=-1) && (A[idx]<=A[i]))
		{
			TAIL=pop_end(TAIL);
			idx=end(TAIL);
		}
		if(TAIL==NULL)
			HEAD=NULL;
		if(HEAD!=NULL){
			prod_max=(prod_max*A[front(HEAD)])%MOD;
			TAIL=push_end(TAIL,i);
			if(HEAD==NULL)
			HEAD=TAIL;	
		}
		else
		{
			TAIL=push_end(TAIL,i);
			if(HEAD==NULL)
			HEAD=TAIL;
			prod_max=(prod_max*A[front(HEAD)])%MOD;	
		}
		
	}
	return prod_max;
}
int main()
{
	scanf("%d %d", &N, &K);
	for(i=0; i<N; i++)
		scanf("%lld", &A[i]);
	long long ans=(max()*modInv(min(),MOD))%MOD;
	printf("%lld\n", ans);
	return 0;
}