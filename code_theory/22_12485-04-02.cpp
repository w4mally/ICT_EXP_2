// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-04-02.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
04-02 (b)
x=
5
0
4
2
5
0
5
6
1
6
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
関数 add_p
有限体F_p上での加算を行う関数
入力 : x,y,p
x+yの結果を出力する
pは要素数
*/
int add_p(int x, int y, int p){
    return (x+y)%p;
}

/*
関数 sub_p
有限体F_p上での減算を行う関数
入力 : x,y,p
x-yの結果を出力する
pは要素数
*/
int sub_p(int x, int y, int p){
    if(x-y<0){
        return p-abs(x-y);
    } else {
        return x-y;
    }
}

/*
関数 mul_p
有限体F_p上での乗算を行う関数
入力 : x,y,p
x-yの結果を出力する
pは要素数
*/
int mul_p(int x, int y, int p){
    return (x*y)%p;
}

/*
関数 add_p
有限体F_p上での除算を行う関数
入力 : x,y,p
x/yの結果を出力する
pは要素数
*/
int div_p(int x, int y, int p){
    int ans = 0;
    if(y == 0) return -1;
    for(int i=0;i<p;i++){
        if((y*i)%p == 1){
            ans = (x*i)%p;
        }
    }
    return ans;
}

int main(void){
    /*p,nの入力*/
    int p = 0;
    int n = 0;
    cout << "p=";
    cin >> p;
    cout << "n=";
    cin >> n;

    vector<vector<int>> a(n, vector<int>(n)); // 正則行列A
    vector<int> b(n); // 長さnのベクトルb

    /*
    行列の入力部分
    linear_equation_Fp.txtで書かれているように各行について要素の間にスペースを入れず入力する
    例えば、
    1 2 3
    4 5 6
    7 8 9
    のような行列を入力したいときは
    123
    456
    789
    で入力
    */
    cout << "A=" <<endl;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            char c;
            cin >> c;
            a.at(i).at(j) = c -'0';
        }
    }
    /*bの入力*/
    cout << "b=" << endl;
    for(int i=0;i<n;i++){
        cin >> b.at(i);
    }

    /*掃き出し法*/
    vector<int> tempvec(n);
    for(int i=0;i<n;i++){
        /*もしAのi行i列成分が0なら行の入れ替えを行って非零にする*/
        if(a.at(i).at(i)  == 0){
            for(int j=i+1;j<n;j++){
                if(a.at(j).at(i) != 0){
                tempvec = a.at(i);
                a.at(i) = a.at(j);
                a.at(j) = tempvec;
                swap(b.at(i), b.at(j));
                break;
                }
            }
        }
        /*i行i列成分を1にするような数字をi行目全体に掛け算する*/
        for(int j=0;j<p;j++){
            if((a.at(i).at(i)*j)%p == 1){
                for(int k=0;k<n;k++){
                    a.at(i).at(k) = mul_p(a.at(i).at(k), j, p);
                }
                b.at(i) = mul_p(b.at(i), j, p);
                break;
            }
        }
        /*i列目の各成分について,i行i列成分以外をすべて0にする*/
        for(int j=0;j<n;j++){
            /*もしj行i列成分(ただしiとjは異なる)が0でなかったら、i行目にi行i列成分がj行i列成分と等しくなるような値をかけて、j行目からi行目を引く*/
            if(a.at(j).at(i) != 0 && i != j){
                int temp = div_p(a.at(j).at(i), a.at(i).at(i), p);
                for(int k=0;k<n;k++){
                    a.at(j).at(k) = sub_p(a.at(j).at(k), mul_p(a.at(i).at(k), temp, p), p);
                }
                b.at(j) = sub_p(b.at(j), mul_p(b.at(i), temp, p), p);
            }
        }
    }

    /*結果の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "x=" << endl;
    for(int i=0;i<n;i++){
        cout << b.at(i) << endl;
    }

    return 0;
}