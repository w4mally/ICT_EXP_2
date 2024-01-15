// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-03-01.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
03-01 (b)
d=521
*/

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

int main(void){
    int n = 0; // ベクトルの長さ
    int d = 0; // ハミング距離
    cout << "n=";
    cin >> n;
    
    string input = ""; // 入力の一時保存
    vector<char> c_0(n); // ベクトルc_0
    vector<char> c_1(n);  // ベクトルc_1

    /*c0とc1の入力*/
    cout << "c0=";
    cin >> input;

    for(int i=0;i<n;i++){
        c_0.at(i) = input.at(i);
    }

    cout << "c1=";
    cin >> input;

    for(int i=0;i<n;i++){
        c_1.at(i) = input.at(i);
    }

    /*ベクトルの各要素を比較 違う要素があるたびにdをインクリメント*/
    for(int i=0;i<n;i++){
        if(c_0.at(i) != c_1.at(i)) d++;
    }

    /*ハミング距離の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "d=" << d << endl;

    return 0;
}