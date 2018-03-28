#include <bits/stdc++.h>
using namespace std;

map <string, int> names;
set <string> fake;

int main(){
    int n;
    scanf ("%d", &n);
    for (int i=1; i<=n; i++){
        string str;
        cin>>str;
        if (names.find(str) != names.end()){
            names[str]++;
        }
        else {
            names[str] = 1;
        }
    }
    int q;
    scanf ("%d", &q);
    while(q--){
        string str;
        cin>>str;
        fake.clear();
        string temp = "";
        for (int i=0; i<6; i++){
            for (int j=0; j<6; j++){
                for (int k=0; k<6; k++){
                    temp = "";
                    int count = 0;
                    for (int s=0; s<str.size(); s++){
                        if (str[s] != '?'){
                            temp += str[s];
                            continue;
                        }
                        if (str[s]=='?'){
                            count++;
                        }
                        if (count==1){
                            if (i == 0) temp += "a";
                            else if (i == 1) temp += "b";
                            else if (i == 2) temp += "c";
                            else if (i == 3) temp += "d";
                            else if (i == 4) temp += "e";
                        }
                        else if (count==2){
                            if (j == 0) temp += "a";
                            else if (j == 1) temp += "b";
                            else if (j == 2) temp += "c";
                            else if (j == 3) temp += "d";
                            else if (j == 4) temp += "e";
                        }
                        else if (count==3){
                            if (k == 0) temp += "a";
                            else if (k == 1) temp += "b";
                            else if (k == 2) temp += "c";
                            else if (k == 3) temp += "d";
                            else if (k == 4) temp += "e";
                        }
                    }
                    fake.insert(temp);
                }
            }
        }
        set <string> :: iterator it;
        int num = 0;
        for (it = fake.begin(); it!=fake.end(); ++it){
            if (names.find(*it) != names.end()){
                num += names[*it];
            }
        }
        printf("%d\n", num);
    }
    return 0;
}
