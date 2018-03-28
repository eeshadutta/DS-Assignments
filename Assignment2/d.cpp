#include<iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
int q, p;
const long long M=1e9+7;
const int MAXN=1e6+5;
long long P[MAXN];

typedef struct node
{
    long long val;
    struct node *left;
    struct node *right;
    int height;
    int freq;
    long long hash;
    int nodes;
} avl;

avl *root = NULL;

long long MAX(long long a, long long b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int height(avl *node)
{
    if (node == NULL){
        return -1;
    }
    else{
        return node->height;
    }
}

void updateHeight(avl *node)
{
    if (node == NULL){
        return;
    }
    else{
        node->height = 1 + MAX(height(node->left), height(node->right));

        node->nodes=node->freq;
        if (node->left!=NULL){
            node->nodes += node->left->nodes;
        }
        if (node->right!=NULL){
            node->nodes += node->right->nodes;
        }
        int rank = node->nodes;
        if (node->right!=NULL){
            rank -= node->right->nodes;
        }

        node->hash = (((node->val * P[rank]) % M ) * node->freq) % M;
        if (node->left!=NULL){
            node->hash = (node->hash + node->left->hash) % M;
        }
        if (node->right!=NULL){
            node->hash = (node->hash + (P[rank] * node->right->hash)%M)%M;
        }
    }
}

avl *rightRotate(avl *ptr)
{
    avl *z = ptr;
    avl *y = ptr->left;
    avl *t = y->right;
    y->right = z;
    z->left = t;
    updateHeight(z);
    updateHeight(y);
    return y;
}

avl *leftRotate(avl *ptr)
{
    avl *z = ptr;
    avl *y = ptr->right;
    avl *t = y->left;
    y->left = z;
    z->right = t;
    updateHeight(z);
    updateHeight(y);
    return y;
}

avl *insert(avl *ptr, long long val)
{
    if (ptr == NULL)
    {
        avl *temp = (avl *)malloc(sizeof(avl));
        temp->val = val;
        temp->left = NULL;
        temp->right = NULL;
        temp->height = 0;
        temp->freq = 1;
        temp->nodes = 1;
        updateHeight(temp);
        return temp;
    }
    if (ptr->val == val)
    {
        ptr->freq++;
        updateHeight(ptr);
        return ptr;
    }
    if (val < ptr->val)
    {
        ptr->left = insert(ptr->left, val);
        updateHeight(ptr);
    }
    else
    {
        ptr->right = insert(ptr->right, val);
        updateHeight(ptr);
    }
    updateHeight(ptr);
    int hd = height(ptr->left) - height(ptr->right);
    if (val<ptr->val && val < ptr->left->val)
    {
        //ll case
        return rightRotate(ptr);
    }
    else if (val<ptr->val && val > ptr->left->val)
    {
        //lr case
        avl *newroot = leftRotate(ptr->left);
        ptr->left = newroot;
        return rightRotate(ptr);
    }
    else if (val>ptr->val && val > ptr->right->val)
    {
        //rr case
        return leftRotate(ptr);
    }
    else if (val>ptr->val && val < ptr->right->val)
    {
        //rl case
        avl *newroot = rightRotate(ptr->right);
        ptr->right = newroot;
        return leftRotate(ptr);
    }
    return ptr;
}

avl *balance(avl *ptr)
{
    if (ptr->left == NULL || ptr->right == NULL)
        return ptr;
    int hd = height(ptr->left) - height(ptr->right);
    if (hd > 1)
    {
        int h2d = height(ptr->left->left) - height(ptr->left->right);
        if (height(ptr->left->left) >= height(ptr->left->right))
        {
            //left left
            return rightRotate(ptr);
        }
        else if (height(ptr->left->left) < height(ptr->left->right))
        {
            //left right
            avl *newroot = leftRotate(ptr->left);
            ptr->left = newroot;
            return rightRotate(ptr);
        }
    }
    else if (hd < -1)
    {
        if (height(ptr->right->left) > height(ptr->right->right))
        {
            //right left
            avl *newroot = rightRotate(ptr->right);
            ptr->right = newroot;
            return leftRotate(ptr);
        }
        else if (height(ptr->right->left) <= height(ptr->right->right))
        {
            //right right
            return leftRotate(ptr);
        }
    }
    return ptr;
}

avl *del(avl *ptr, long long val)
{
    if (ptr == NULL)
    {
        return ptr;
    }
    if (val < ptr->val)
    {
        ptr->left = del(ptr->left, val);
        updateHeight(ptr);
        return balance(ptr);
        return ptr;
    }
    if (val > ptr->val)
    {
        ptr->right = del(ptr->right, val);
        updateHeight(ptr);
        return balance(ptr);
        return ptr;
    }
    if (val == ptr->val)
    {
        if (ptr->freq > 1)
        {
            ptr->freq--;

            updateHeight(ptr);
            return balance(ptr);
            return ptr;
        }
        else
        {
            if (ptr->right != NULL &&
                ptr->left != NULL)
            {
                avl *temp = ptr->right;
                while (temp->left != NULL)
                    temp = temp->left;
                ptr->val = temp->val;
                ptr->freq = temp->freq;
                temp->freq = 1;
                ptr->right = del(ptr->right, temp->val);
                updateHeight(ptr);
                return balance(ptr);
                return ptr;
            }
            if (ptr->right != NULL)
            {
                avl *temp = ptr->right;
                return temp;
            }
            else
            {
                avl *temp = ptr->left;
                return temp;
            }
        }
    }
    if (ptr->val < val)
        ptr->right = del(ptr->right, val);
    else
        ptr->left = del(ptr->left, val);
    updateHeight(ptr);
    return balance(ptr);
}

/*void preorder(avl *root)
{
    if (root != NULL)
    {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
    return;
}*/

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin>>q>>p;
    P[0]=1;
    for (int i=1; i<MAXN; i++){
        P[i]=(P[i-1]*p)%M;
    }
    while (q--)
    {
        char c;
        long long x;
        cin>>c;
        if (c=='A' || c=='D'){
            cin>>x;
        }
        if (c=='A'){
            root = insert(root, x);
        }
        else if (c=='D'){
            root = del(root, x);
        }
        else if (c=='H'){
            if (root==NULL){
                cout<<0<<endl;
            }
            else{
                cout<<root->hash<<endl;
            }
        } 
    }
    return 0;
}