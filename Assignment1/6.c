#include <stdio.h>
#include <stdlib.h>

typedef struct stack{
    int data;
    int min;
    struct stack *next;
}stack;

stack * push(stack * head, int val){
    stack *temp=(stack*)malloc(sizeof(stack));
    temp->data=val;
    temp->next=head;
    if (head==NULL){
        temp->min=val;
    }
    else {
        if (val<head->min){
            temp->min=val;
        }
        else {
            temp->min=head->min;
        }
    }
    return temp;
}

stack * pop(stack * head){
    stack *temp=head;
    head=head->next;
    free (temp);
    return head;
}

int main(){
    int n, i, val;
    scanf("%d", &n);
    stack *head1=NULL;
    stack *head2=NULL;
    for (i=1; i<=n; i++){
        scanf("%d", &val);
        head1=push(head1, val);
    }
    int moves=0;
    while(head1!=NULL || head2!=NULL){
        if (head2==NULL){
            if (head1->min != head1->data){
                head2=push(head2, head1->data);
                head1=pop(head1);
                moves++;
            }
            else{
                head1=pop(head1);
            }   
        }
        else if(head1==NULL){
            if (head2->min != head2->data){
                head1=push(head1, head2->data);
                head2=pop(head2);
                moves++;
            }
            else{
                head2=pop(head2);
            }
        }
        else {
            if (head1->min < head2->min){
                if (head1->min != head1->data){
                    head2=push(head2, head1->data);
                    head1=pop(head1);
                    moves++;
                }
                else{
                    head1=pop(head1);
                }
            }
            else {
                if (head2->min != head2->data){
                    head1=push(head1, head2->data);
                    head2=pop(head2);
                    moves++;
                }
                else{
                head2=pop(head2);
                }
            }
        }
    }
    printf("%d\n", moves);
    return 0;
}