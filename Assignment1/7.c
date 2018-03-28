#include <stdio.h>
#include <stdlib.h>
#include <string.h>
const long m=1000000007;

typedef struct stack{
    long long data;
    struct stack* next;
}stack;

long long power(long long x, long long y){
    long long p=1;
    while(y>0){
        if (y%2==1){
            p=(p*x)%m;
        }
        x=(x*x)%m;
        y/=2;
    }
    return p;
}

stack * push(stack * head, int val){
    stack *temp=(stack *)malloc(sizeof(stack));
    temp->data=val;
    temp->next=head;
    return temp;
}

stack *pop(stack * head){
    stack * temp=head;
    head=head->next;
    free(temp);
    return head;
}

int main(){
    int t, i, length;
    stack *head=NULL;
    scanf("%d", &t);
    while (t--){
        char s[200005];
        scanf ("%s", s);
        length=strlen(s);
        //printf("length: %d\n", length);
        for (i=0; i<length; i++){
            //printf("s[i]: %s\n", s[i]);
            if (s[i]-48<=9 && s[i]-48>=0){
                head=push(head, s[i]-48);
                //printf("head data: %lld\n", head->data);
            }
            
            else {
                long long b=head->data;
                head=pop(head);
                long long a=head->data;
                head=pop(head);
                //printf("a: %lld b: %lld oper: %c\n", a, b, s[i]);
                if (s[i]=='+'){
                    long long ans=((a%m) + (b%m))%m;
                    head=push(head, ans);
                    //printf("head data: %lld\n", head->data);
                    //printf("oper: %s, ans: %lld", s[i], ans);
                }
                else if (s[i]=='-'){
                    long long ans=((a%m) - (b%m) + m)%m;
                    head=push(head, ans);
                    //printf("head data: %lld\n", head->data);
                    //printf("oper: %s, ans: %lld", s[i], ans);
                }
                else if (s[i]=='*'){
                    long long ans=((a%m) * (b%m))%m;
                    head=push(head, ans);
                    //printf("head data: %lld\n", head->data);
                    //printf("oper: %s, ans: %lld", s[i], ans);
                }
                else if (s[i]=='/'){
                    long long ans=(a%m) * power(b, m-2) % m;
                    head=push(head, ans);
                    //printf("head data: %lld\n", head->data);
                    //printf("oper: %s, ans: %lld", s[i], ans);
                }
            }
        }
        long long ans=head->data;
        printf ("%lld\n", ans);
    }
    return 0;
}