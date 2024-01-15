// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-04-05.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
04-05 (b)
x=
[01001101]
[00010001]
[01110011]
[00010110]
[00001101]
[01011101]
[11001000]
[00001100]
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
関数 two_ten
string型で入力された2進数を10進数にしてintで返す関数
入力vec: この値を10進数に変換する
返り値: int型 vecを10進数にしたもの
*/
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
    /*原始多項式の次数、線形方程式の式数の入力*/
    int m = 0; // 原始多項式の次数
    int n = 0; // 線形方程式の式数
    cout << "m=";
    cin >> m;
    cout << "n=";
    cin >> n;

    int n_ = pow(2, m); // 有限体の要素数

    /*f(x)の入力*/
    vector<int> f;
    string temp;
    cout << "f(x)=";
    cin >> temp;
    for(int i=0;i<(int)temp.length();i++){
        f.push_back(temp.at(i) - '0');
    }
    cout << endl;

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

    vector<vector<string>> a(n, vector<string>(n));
    vector<string> b(n);
    /*
    Aの入力
    Aの入力は各要素を[]で囲み、各要素の間にスペースを入れない、行が切り替わったら改行という形式で受け付ける
    例
    [101][000][001]
    [101][101][100]
    [100][110][110]
    */
    for(int i=0;i<n;i++){
        string temp;
        cin >> temp;
        for(int j=0;j<n;j++){
            a.at(i).at(j) = temp.substr(1, m);
            temp.erase(0, m+2);
        }
    }

    /*
    bの入力
    bの入力は各要素を[]で囲み、1要素ごとに改行という形式で受け付ける
    例
    [010]
    [001]
    [001]
    */
    for(int i=0;i<n;i++){
        string temp;
        cin >> temp;
        b.at(i) = temp.substr(1, m);
    }

    /*
    掃き出し法を行う
    各演算は演算対象を適切に10進数に変換して添え字として、事前に計算した演算表(の配列)から呼び出すことで実現している
    */
    vector<string> tempvec(n); // 作業用配列
    int getindex = 0;
    for(int i=0;i<n;i++){
        /*もしi行i列成分が[0...0](長さmの零ベクトル)だったらそれより下の行からi列成分が非零の行を探してきて行を入れ替える*/
        if(a.at(i).at(i) == mul.at(0).at(0)){
            for(int j=i;j<n;j++){
                if(a.at(j).at(i) != mul.at(0).at(0)){
                    tempvec = a.at(i);
                    a.at(i) = a.at(j);
                    a.at(j) = tempvec;
                    swap(b.at(i), b.at(j));
                    break;
                }
            }
        }
        /*i行i列成分を[1000...](長さm,最初の要素のみ1でほか0のベクトル)にするような要素をi行全体にかける*/
        int num = two_ten(a.at(i).at(i));
        /*i行i列成分を[1000...](長さm,最初の要素のみ1でほか0のベクトル)にするような要素を探索*/
        for(int j=0;j<n_;j++){
            if(two_ten( mul.at(num).at(j) ) == pow(2,m-1)){
                getindex = j; //そのような要素の場所を記録しておく
                break; // 見つかったら探索打ち切り
            }
        }
        for(int k=0;k<n;k++){
            a.at(i).at(k) = mul.at(getindex).at(two_ten(a.at(i).at(k)));
        }
        b.at(i) = mul.at(getindex).at(two_ten(b.at(i)));

        /*i列目のi行i列成分以外の成分を全てゼロベクトルにする*/
        for(int j=0;j<n;j++){
            if(j != i && a.at(j).at(i) != mul.at(0).at(0)){
                int index_ji = two_ten(a.at(j).at(i));
                string addstr_b = mul.at(two_ten(a.at(j).at(i))).at(two_ten(b.at(i)));
                b.at(j) = add_and_sub.at(two_ten(addstr_b)).at(two_ten(b.at(j)));
                for(int k=0;k<n;k++){
                    string addstr = mul.at(index_ji).at(two_ten(a.at(i).at(k)));
                    a.at(j).at(k) = add_and_sub.at(two_ten(addstr)).at(two_ten(a.at(j).at(k)));
                }
            }
        }
    }

    /*結果の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "x=" << endl;
    for(int i=0;i<n;i++){
        cout << '[' << b.at(i) << ']' << endl;
    }
    return 0;
}