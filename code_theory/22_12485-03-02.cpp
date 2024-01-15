// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-03-02.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
03-02 (b)
d_min=453
R=0.00683594
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
    int n = 0; // 符号長
    int m = 0; // 符号の要素数
    int d = 0; // 最小距離
    double r = 0; // 符号化率
    int cnt = 0; // ハミング距離を調べるカウンタ変数
    string in = ""; // 入力保持用

    /*符号長、要素数の入力*/
    cout << "n=";
    cin >> n;
    cout << "M=";
    cin >> m;

    d = n; // 最小距離はより小さいものがあるたびに更新していくので初期値は最大値であるnにしておく

    vector<vector<char>> c(m, vector<char>(n)); // 符号を保持する2次元配列
    
    /*符号の入力*/
    cout << "C=" << endl;
    for(int i=0;i<m;i++){
        cin >> in;
        for(int j=0;j<n;j++){
            c.at(i).at(j) = in.at(j);
        }
    }

    /*
    二重ループで符号の組み合わせ全パターンについてハミング距離の計算
    これまで調べたハミング距離の最小値よりも小さいハミング距離が現れたらそれをdにいれる
    */
    for(int i=0;i<m;i++){
        for(int j=i;j<m;j++){
            if(i != j){
                cnt = 0;
                for(int k=0;k<n;k++){
                    if(c.at(i).at(k) != c.at(j).at(k)) cnt++;
                }
                if(d>cnt) d = cnt;
            }
        }
    }

    r = log2(m)/n; // 符号化率の計算

    /*結果の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "d_min=" << d << endl;
    cout << "R=" << r << endl;

    return 0;
}