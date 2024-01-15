// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-04-01.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
04-01 (b)
ADD
  | 0 1 2 3 4 5 6 
--+---------------
0 | 0 1 2 3 4 5 6 
1 | 1 2 3 4 5 6 0 
2 | 2 3 4 5 6 0 1 
3 | 3 4 5 6 0 1 2 
4 | 4 5 6 0 1 2 3 
5 | 5 6 0 1 2 3 4 
6 | 6 0 1 2 3 4 5 
MUL
  | 0 1 2 3 4 5 6 
--+---------------
0 | 0 0 0 0 0 0 0 
1 | 0 1 2 3 4 5 6 
2 | 0 2 4 6 1 3 5 
3 | 0 3 6 2 5 1 4 
4 | 0 4 1 5 2 6 3 
5 | 0 5 3 1 6 4 2 
6 | 0 6 5 4 3 2 1 
SUB
  | 0 1 2 3 4 5 6 
--+---------------
0 | 0 6 5 4 3 2 1 
1 | 1 0 6 5 4 3 2 
2 | 2 1 0 6 5 4 3 
3 | 3 2 1 0 6 5 4 
4 | 4 3 2 1 0 6 5 
5 | 5 4 3 2 1 0 6 
6 | 6 5 4 3 2 1 0 
DIV
  | 0 1 2 3 4 5 6 
--+---------------
0 | - 0 0 0 0 0 0 
1 | - 1 4 5 2 3 6 
2 | - 2 1 3 4 6 5 
3 | - 3 5 1 6 2 4 
4 | - 4 2 6 1 5 3 
5 | - 5 6 4 3 1 2 
6 | - 6 3 2 5 4 1 
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

/*
関数 print_calc_table
演算表を出力する関数
二次元配列calc : 演算結果が格納されている 演算を#で表すとして,i行j列成分にはi#jの結果が入っている
p : 有限体の要素数
calcについて、零除算など定義されない部分にはpを入れていく
*/
void print_calc_table(vector<vector<int>> &calc, int p){
    cout << "  | ";
    for(int i=0;i<p;i++){
        cout << i << " ";
    }
    cout << endl;

    cout << "--+";

    for(int i=0;i<p;i++){
        cout << "--";
    }

    cout << "-" << endl;

    for(int i=0;i<p;i++){
        cout << i << " | ";
        for(int j=0;j<p;j++){
            if(calc.at(i).at(j) == p){
                cout << "- "; // 零除算は定義されないので、ハイフンを出力
            } else {
                cout << calc.at(i).at(j) << " ";
            }
        }
        cout << endl;
    }
}

/* pとすると定義できない演算が発生する値(4など)を入力すると実行時エラーになります */
int main(void){
    /*要素数の入力*/
    int p = 0;
    cout << "p=";
    cin >> p;

    vector<vector<int>> add(p, vector<int>(p)); // 加算の結果を入れる
    vector<vector<int>> mul(p, vector<int>(p)); // 乗算の結果を入れる
    vector<vector<int>> sub(p, vector<int>(p)); // 減算の結果を入れる
    vector<vector<int>> div(p, vector<int>(p)); // 除算の結果を入れる
    map<int, int> div_value; // key: 割る数, value: 割る数に対応する逆数 

    /*1~pの逆数を求めて連想配列に入れる*/
    for(int i=1;i<p;i++){
        for(int j=0;j<p;j++){
            if((i*j)%p == 1){
                div_value[i] = j;
            }
        }
    }

    /*定義通りに計算をして結果を二次元配列に入れていく*/
    for(int i=0;i<p;i++){
        for(int j=0;j<p;j++){
            add.at(i).at(j) = (i+j)%p; // 加算

            mul.at(i).at(j) = (i*j)%p; // 乗算

            /*減算*/
            if(i-j<0){
                sub.at(i).at(j) = p-abs(i-j);
            } else {
                sub.at(i).at(j) = i-j;
            }

            /*除算*/
            if(j==0){
                div.at(i).at(j) = p; // 零除算は定義されないので、演算結果として本来ありえないpを入れておく(出力する時に中身がpならハイフンを出力するようにする)
            } else {
                div.at(i).at(j) = (i*div_value.at(j))%p;
            }
        }
    }

    /*結果の出力 予め定義した綺麗に表を出力するための関数を使う*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "ADD" << endl;
    print_calc_table(add, p);
    cout << "MUL" << endl;
    print_calc_table(mul, p);
    cout << "SUB" << endl;
    print_calc_table(sub, p);
    cout << "DIV" << endl;
    print_calc_table(div, p);

    return 0;
}