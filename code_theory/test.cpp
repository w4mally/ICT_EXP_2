// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-03-05.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

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

/*
関数 ten_two
intで入力された数値を2進数に変換してstringで返す関数
表示桁数はk
入力num: この値を2進数に変換する
*/
string ten_two(int k, int num){
    string ans;
    for(int i=0;i<k;i++){
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

void code_gen(vector<int> &code, vector<int> pln, vector<vector<int>> g, int k, int n){
    for(int i=0;i<n;i++){
        code.at(i) = 0;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            code.at(i) += pln.at(j)*g.at(j).at(i);
        }
        code.at(i) = code.at(i)%2;
    }
}

long long int comb(int n, int r){
    if(r == 0) return 1;
    long long int a = 1;
    long long int b = 1;
    for(int i = n-r+1;i<=n;i++){
        a = a*i;
    }
    for(int i=1;i<=r;i++){
        b = b*i;
    }
    return a/b;
}

long long int v[64][64];
void nck(int n){
    for(int i=0;i<n+1;i++){
        v[i][0] = 1;
        v[i][i] = 1;
    }
    for(int i=1;i<n+1;i++){
        for(int j=1;j<i;j++){
            v[i][j] = v[i-1][j-1] + v[i-1][j];
        }
    }
}

int two_ten(string vec){
    int num = 0;
    int len = vec.length();
    for(int i=0;i<len;i++){
        if(vec.at(len-1-i) == '1') num += pow(2, i);
    }
    return num;
}

int main(void){
    string s;
    cin >> s;
    cout << two_ten(s) << endl;
    return 0;
}