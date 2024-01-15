#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <bitset>
#include <algorithm>
using namespace std;

char ascii_to_char(string s){
    int ascii = 0;
    for(int i=7;i>=0;i--){
        if(s.at(i) == '1') ascii += pow(2,7-i);
    }
    char ans = ascii;
    return ans;
}

int two_ten(string s){
    int ans = 0;
    int size = s.size();
    for(int i=size-1;i>=0;i--){
        if(s.at(i) == '1') ans += pow(2,size-1-i);
    }
    return ans;
}

string ten_two(int cnt, int num){
    string ans;
    for(int i=0;i<ceil(log2(cnt));i++){
        if(num%2 == 0){
            ans += '0';
        }
        else if(num%2 == 1){
            ans += '1';
        }
        num = num/2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(void){
    int a;
    int b;
    cin >> a >> b;
    string s = ten_two(a, b);

    cout << s << endl;
    
    return 0;
}