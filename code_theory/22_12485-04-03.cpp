// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-04-03.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
04-03 (b)
f+g=[11010011100110101110100011]
f-g=[11010011100110101110100011]
f*g=[01001111011010100001000100000010011001000111]
f/g= 商 [11110111] 剰余 [101010001000000111]
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

int main(void){
    int n = 0;
    int m = 0;

    /*n,mの入力*/
    cout << "n=";
    cin >> n;
    cout << "m=";
    cin >> m;

    int mul_order = n+m; // f*gの結果の次数

    /*この後、定数項まで含めてvectorに格納して扱うので次数をインクリメントしておく*/
    n++;
    m++;

    int nm_max = max(n, m); // f,gで次数が大きいほうを記録

    vector<int> f(nm_max); // 多項式f
    vector<int> g(nm_max); // 多項式g

    vector<int> add(nm_max); // f+gの結果
    vector<int> sub(nm_max); // f-gの結果
    vector<int> mul(mul_order+1); // f*gの結果
    vector<int> div(n-m+1); // f/gの商
    vector<int> rem; // f/gのあまり

    /*各配列の中身を0で初期化しておく*/
    for(int i=0;i<nm_max;i++){
        f.at(i) = 0;
        g.at(i) = 0;
    }
    for(int i=0;i<mul_order+1;i++){
        mul.at(i) = 0;
    }

    /*
    f,gをベクトルで入力 
    各数字の間にスペースを入れずに入力する
    [1010101]を入力したかったら1010101
    */
    cout << "f=";
    for(int i=0;i<n;i++){
        char c;
        cin >> c;
        f.at(i) = c - '0';
    }
    cout << "g=";
    for(int i=0;i<m;i++){
        char c;
        cin >> c;
        g.at(i) = c - '0';
    }

    cout << endl;

    /*加算、減算*/
    for(int i=0;i<nm_max;i++){
        add.at(i) = add_p(f.at(i), g.at(i), 2);
        sub.at(i) = sub_p(f.at(i), g.at(i), 2);
    }

    /*乗算*/
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(f.at(i) == 1 && g.at(j) == 1){
                mul.at(i+j) = add_p(mul.at(i+j), 1, 2);
            }
        }
    }

    /*除算*/
    vector<int> temp(n);
    int o_max = 0;
    for(int i=n-1;i>=0;i--){
        if(f.at(i) == 1){
            o_max = i;
            if(o_max < m-1){
                break;
            }
            int x = o_max - m + 1;
            div.at(x) = 1;
            for(int j=0;j<m;j++){
                if(g.at(j) == 1){
                    f.at(j+x) = sub_p(f.at(j+x), 1, 2);
                }
            }
        }
    }

    /*余りがfに入っている状態なので整形して入れなおす*/
    int flag = 0;
    for(int i=n-1;i>=0;i--){
        if(f.at(i) == 1 && flag == 0){
            flag = 1;
            rem.push_back(1);
        }
        else if(flag == 1){
            rem.push_back(f.at(i));
        }
    }
    reverse(rem.begin(), rem.end());

    /*計算結果の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "f+g=[";
    for(int i=0;i<nm_max;i++){
        cout << add.at(i);
    }
    cout << ']' << endl;

    cout << "f-g=[";
    for(int i=0;i<nm_max;i++){
        cout << sub.at(i);
    }
    cout << ']' << endl;

    cout << "f*g=[";
    for(int i=0;i<mul_order+1;i++){
        cout << mul.at(i);
    }
    cout << ']' << endl;

    cout << "f/g= 商 [";
    for(int i=0;i<n-m+1;i++){
        cout << div.at(i);
    }
    cout << "] 剰余 [";
    for(int i=0;i<(int)rem.size();i++){
        cout << rem.at(i);
    }
    cout << ']' << endl;

    return 0;
}