// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-04-04-a.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
このプログラムは入力された次数mと原始多項式で定義される有限体の加減乗除を計算し、演算表を出力する
問題04-04(b)の解答は別途22_12485-04-04-b.cppを実行して得る
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
関数 poly_mul
多項式の掛け算を行う
多項式の情報は文字列でベクトルとして受け取る
(例)1+X+X^2 → "111", X^2 → "001"
掛け算した結果を文字列として返す
[入力]
n: 多項式fの次数
m: 多項式gの次数
f: 多項式(文字列)
g: 多項式(文字列)
[出力]
f*gを文字列で返す
*/
string poly_mul(int n, int m, string f, string g){
    vector<int> mul(n+m+1);
    for(int i=0;i<n+m+1;i++){
        mul.at(i) = 0;
    }
    string result;
    for(int i=0;i<n+1;i++){
        for(int j=0;j<m+1;j++){
            if(f.at(i) == '1' && g.at(j) == '1'){
                mul.at(i+j) = add_p(mul.at(i+j), 1, 2);
            }
        }
    }

    for(int i=0;i<n+m+1;i++){
        if(mul.at(i) == 0){
            result.push_back('0');
        }
        else if(mul.at(i) == 1){
            result.push_back('1');
        }
    }

    return result;
}

/*
関数 poly_rem
多項式の割り算f/gを行って余りを保存する
[入力]
n: 多項式fの次数+1
m: 多項式gの次数+1
f: 多項式f(係数をvectorでもつ)
g: 多項式g(係数をvectorでもつ)
[出力]
無し
この関数を実行するとfの中身が割り算のあまりになっている
*/
void poly_rem(int n, int m, vector<int> &f, vector<int> &g){
    vector<int> temp(n);
    int o_max = 0;
    for(int i=n-1;i>=0;i--){
        if(f.at(i) == 1){
            o_max = i;
            if(o_max < m-1){
                break;
            }
            int x = o_max - m + 1;
            for(int j=0;j<m;j++){
                if(g.at(j) == 1){
                    f.at(j+x) = sub_p(f.at(j+x), 1, 2);
                }
            }
        }
    }
}

/*
関数 print_vector_table
演算表を出力する関数
[入力]
m: 原始多項式の次数
calc: 演算結果が格納されている2次元配列
[出力]
返り値無し
問題の例にあるように演算表を出力する
未定義の演算(零除算)についてはcalcに演算結果の代わりにハイフン列が格納されていることが想定されている
*/
void print_vector_table(int m, vector<vector<string>> &calc){
    int n = pow(2, m);
    for(int i=0;i<m;i++){
        cout << " ";
    }
    cout << '|';
    for(int i=0;i<n;i++){
        string temp = ten_two(m, i);
        reverse(temp.begin(), temp.end());
        cout << " [" << temp << "] ";
    }
    cout << endl;

    for(int i=0;i<m+3;i++){
        cout << '-';
    }
    cout << '+';
    for(int i=0;i<n;i++){
        cout << "--";
        for(int i=0;i<m;i++){
            cout << '-';
        }
        cout << "--";
    }
    cout << endl;

    for(int i=0;i<n;i++){
        cout << '[';
        string temp = ten_two(m, i);
        reverse(temp.begin(), temp.end());
        cout << temp << "] |";

        for(int j=0;j<n;j++){
            if(calc.at(i).at(j).at(0) == '-'){
                cout << ' ' << calc.at(i).at(j) << ' ';
            } else {
            cout << " [" << calc.at(i).at(j) << "] ";
            }
        }
        cout << endl;
    }
}

int main(void){
    /*mの入力*/
    int m = 0;
    cout << "m=";
    cin >> m;

    int n = pow(2, m); // 要素数

    string one  = "1";
    for(int i=1;i<m;i++){
        one.push_back('0');
    }

    /*f(x)の入力*/
    vector<int> f;
    string temp;
    cout << "f(x)=";
    cin >> temp;
    for(int i=0;i<(int)temp.length();i++){
        f.push_back(temp.at(i) - '0');
    }

    /*
    それぞれの配列について、演算記号を@とするとi行j列目には
    iをn桁の2進数にしてそれを反転したものをs1
    jをn桁の2進数にしてそれを反転したものをs2
    として
    s1@s2が格納されている
    例
    m=8のとき
    mulの1行2列目には
    [10000000]*[01000000]
    の結果が格納されている
    */
    vector<vector<string>> add_and_sub(n, vector<string>(n)); // 加算と減算の演算結果を格納する2次元配列
    vector<vector<string>> mul(n, vector<string>(n)); // 乗算の結果を格納する2次元配列
    vector<vector<string>> div(n, vector<string>(n)); // 除算の結果を格納する2次元配列

    /*
    加算、減算
    F_2上の演算はx+y=x-yが成立するのでこの部分で加算の演算表と減算表はどちらも求められている
    */
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            string temp1 = ten_two(m, i);
            string temp2 = ten_two(m, j);
            reverse(temp1.begin(), temp1.end());
            reverse(temp2.begin(), temp2.end());
            for(int k=0;k<m;k++){
                if(temp1.at(k) == '0' && temp2.at(k) == '0'){
                    add_and_sub.at(i).at(j).push_back('0');
                }
                else if(temp1.at(k) == '1' && temp2.at(k) == '1'){
                    add_and_sub.at(i).at(j).push_back('0');
                } else {
                    add_and_sub.at(i).at(j).push_back('1');
                } 
            }
        }
    }

    /*乗算*/
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            string temp1 = ten_two(m, i);
            string temp2 = ten_two(m, j);
            reverse(temp1.begin(), temp1.end());
            reverse(temp2.begin(), temp2.end());
            string mul_res = poly_mul(m-1, m-1, temp1, temp2);
            vector<int> temp;
            for(int k=0;k<(int)mul_res.length();k++){
                temp.push_back(mul_res.at(k) - '0');
            }
            poly_rem(mul_res.length(), m+1, temp, f);

            for(int k=0;k<m;k++){
                if(temp.at(k) == 0) mul.at(i).at(j).push_back('0');
                else if(temp.at(k) == 1) mul.at(i).at(j).push_back('1');
            }
        }
    }

    /*除算*/
    int memo = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m+2;j++){
            div.at(i).at(0).push_back('-');
        }
    }
    for(int i=1;i<n;i++){
        for(int j=0;j<n;j++){
            if(mul.at(j).at(i) == one){
                memo = j;
                break;
            }
        }
        for(int j=0;j<n;j++){
            div.at(j).at(i) = mul.at(memo).at(j);
        }
    }

    /*演算表の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "ADD";
    print_vector_table(m, add_and_sub);
    cout << endl;
    cout << "MUL";
    print_vector_table(m, mul);
    cout << endl;
    cout << "SUB";
    print_vector_table(m, add_and_sub);
    cout << endl;
    cout << "DIV";
    print_vector_table(m, div);
    cout << endl;

    return 0;
}