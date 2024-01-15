// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-04-06-encode.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
04-06 (b)
[10101101][01111001][11101111][00000100]
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

int two_ten(string vec){
    int num = 0;
    int len = vec.length();
    for(int i=0;i<len;i++){
        if(vec.at(len-1-i) == '1') num += pow(2, i);
    }
    return num;
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

int main(void){
    /*原始多項式f(x)の入力*/
    vector<int> f;
    string temp;
    cin >> temp;
    for(int i=0;i<(int)temp.length();i++){
        f.push_back(temp.at(i) - '0');
    }

    int m = temp.length() - 1; // f(x)の次数
    int n_ = pow(2, m); // 有限体の要素数

    string one = "1";
    string x = "0";
    for(int i=0;i<m-1;i++){
        one.push_back('0');
        x.push_back('0');
    }
    x.at(1) = '1';

    /*まず先に、演算表を前計算しておく*/
    /*
    それぞれの配列について、演算記号を@とするとi行j列目には
    iをn桁の2進数にしたものをs1
    jをn桁の2進数にしたものをs2
    として
    s1@s2が格納されている
    例
    m=8のとき
    mulの1行2列目には
    [00000001]*[00000010]
    の結果が格納されている
    */
    vector<vector<string>> add_and_sub(n_, vector<string>(n_)); // 加算と減算の演算結果を格納する2次元配列
    vector<vector<string>> mul(n_, vector<string>(n_)); // 乗算の結果を格納する2次元配列
    /*
    加算、減算
    F_2上の演算はx+y=x-yが成立するのでこの部分で加算の演算表と減算表はどちらも求められている
    */
    for(int i=0;i<n_;i++){
        for(int j=0;j<n_;j++){
            string temp1 = ten_two(m, i);
            string temp2 = ten_two(m, j);
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
    for(int i=0;i<n_;i++){
        for(int j=0;j<n_;j++){
            string temp1 = ten_two(m, i);
            string temp2 = ten_two(m, j);
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

    int n = 0;
    int dim = 0;
    cout << "n=";
    cin >> n;
    cout << "k=";
    cin >> dim;
    cout << endl;

    vector<vector<string>> g(dim, vector<string>(n)); // 生成行列
    vector<string> alpha(n); // (1, alpha, alpha^2, ... , alpha^254)
    alpha.at(0) = one;
    alpha.at(1) = x;
    for(int i=2;i<n;i++){
        alpha.at(i) = mul.at(two_ten(x)).at(two_ten(alpha.at(i-1)));
    }
    
    /*gの生成*/
    for(int i=0;i<dim;i++){
        for(int j=0;j<n;j++){
            if(i == 0){
                g.at(i).at(j) = alpha.at(0); // 1行目は全て1で埋める
            } 
            else if(i == 1){
                g.at(i).at(j) = alpha.at(j); // 2行目は1, alpha, alpha^2, ... , alpha^254で埋める
            } 
            else if(i >= 2){
                g.at(i).at(j) = mul.at(two_ten(g.at(i-1).at(j))).at(two_ten(alpha.at(j))); // 3行目以降はi列成分が1つ上の成分にalpha^{i-1}をかけたものになる
            } 
        }
    }

    /*符号化する情報の受け取り*/
    string p;
    vector<string> u(dim); // 情報ベクトル
    vector<string> c(n); // 符号化結果
    cin >> p;
    for(int i=0;i<dim;i++){
        u.at(i) = p.substr(1, m);
        p.erase(0, m+2);
    }

    /*情報ベクトルに生成行列をかける*/
    for(int i=0;i<n;i++){
        for(int j=0;j<dim;j++){
            string addstr = mul.at(two_ten(u.at(j))).at(two_ten(g.at(j).at(i)));
            c.at(i) = add_and_sub.at(two_ten(c.at(i))).at(two_ten(addstr));
        }
    }

    /*符号化結果の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "c=" << endl;
    for(int i=0;i<n;i++){
        cout << '[' << c.at(i) << ']';
    }
    cout << endl;

    return 0;
}