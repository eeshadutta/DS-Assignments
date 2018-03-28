#include <bits/stdc++.h>
#include <string.h>
using namespace std;

int MIN(int a, int b){
    if (a<b) return a;
    else return b;
}

typedef struct trie{
    trie *child[26];
    char ch;
    int freq; //no of strings which end here
    int length;
    int priority;
} trie;

trie *createNode(char c, int len, int priority){
    trie *node;
    node = (trie*)malloc(sizeof(trie));
    node->ch = c;
    node->length = len;
    node->priority = priority;
    for (int i = 0; i < 26; i++){
        node->child[i] = NULL;
    }
    node->freq = 0;
    return node;
}

void insert(trie *root, string str, int priority){
    trie *node = root;
    int ind;
    int len = str.size();
    for (int i = 0; i < len; i++){
        ind = str[i] - 'a';
        if (node->child[ind] == NULL){
            node->child[ind] = createNode(str[i], len, priority);
        }
        node = node->child[ind];
    }
    node->freq++;
    return;
}

int time(trie * root, string str){
    int len = str.size();
    int count = 1;
    int ptr = 1;
    trie *node = root;
    if (node->child[(str[0]-'a')] == NULL){
        return len;
    }
    node = node->child[(str[0]-'a')];
    for (int s=1; s<=len; s++){
        if (s==len){
            count += MIN((1+node->length-s), (s-ptr));
            return count;
        }
        int ind = str[s] - 'a';
        if (node->child[ind] == NULL){

            count += MIN((1 + node->length - s), (s - ptr)) + (len - s);
            break;
        }
        else {
            if (node->priority != node->child[ind]->priority){
                count += MIN((1+node->length-s), (s-ptr)) + 1;
                ptr = s+1;
            }
            else {
                node = node->child[ind];
                continue;
            }
        }
        node = node->child[ind];
    }
    return count;
}

int main(){
    trie *root;
    root = createNode('\0', 0, 0);
    int m, n;
    cin >> m;
    cin >> n;
    string str;
    for (int i=1; i<=m; i++){
        cin >> str;
        insert(root, str, i);
    }
    while(n--){
        cin >> str;
        int ans = time(root, str);
        printf("%d\n", ans);
    }
    return 0;
}