// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-02-01.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
alphabet size: 3
length: 4
symbol_1> a
p_1> 0.1
symbol_2> b
p_2> 0.2
symbol_3> c
p_3> 0.7
[出力]
P(aaaa): 0.0001000000
P(aaab): 0.0002000000
P(aaac): 0.0007000000
P(aaba): 0.0002000000
P(aabb): 0.0004000000
P(aabc): 0.0014000000
P(aaca): 0.0007000000
P(aacb): 0.0014000000
P(aacc): 0.0049000000
P(abaa): 0.0002000000
P(abab): 0.0004000000
P(abac): 0.0014000000
P(abba): 0.0004000000
P(abbb): 0.0008000000
P(abbc): 0.0028000000
P(abca): 0.0014000000
P(abcb): 0.0028000000
P(abcc): 0.0098000000
P(acaa): 0.0007000000
P(acab): 0.0014000000
P(acac): 0.0049000000
P(acba): 0.0014000000
P(acbb): 0.0028000000
P(acbc): 0.0098000000
P(acca): 0.0049000000
P(accb): 0.0098000000
P(accc): 0.0343000000
P(baaa): 0.0002000000
P(baab): 0.0004000000
P(baac): 0.0014000000
P(baba): 0.0004000000
P(babb): 0.0008000000
P(babc): 0.0028000000
P(baca): 0.0014000000
P(bacb): 0.0028000000
P(bacc): 0.0098000000
P(bbaa): 0.0004000000
P(bbab): 0.0008000000
P(bbac): 0.0028000000
P(bbba): 0.0008000000
P(bbbb): 0.0016000000
P(bbbc): 0.0056000000
P(bbca): 0.0028000000
P(bbcb): 0.0056000000
P(bbcc): 0.0196000000
P(bcaa): 0.0014000000
P(bcab): 0.0028000000
P(bcac): 0.0098000000
P(bcba): 0.0028000000
P(bcbb): 0.0056000000
P(bcbc): 0.0196000000
P(bcca): 0.0098000000
P(bccb): 0.0196000000
P(bccc): 0.0686000000
P(caaa): 0.0007000000
P(caab): 0.0014000000
P(caac): 0.0049000000
P(caba): 0.0014000000
P(cabb): 0.0028000000
P(cabc): 0.0098000000
P(caca): 0.0049000000
P(cacb): 0.0098000000
P(cacc): 0.0343000000
P(cbaa): 0.0014000000
P(cbab): 0.0028000000
P(cbac): 0.0098000000
P(cbba): 0.0028000000
P(cbbb): 0.0056000000
P(cbbc): 0.0196000000
P(cbca): 0.0098000000
P(cbcb): 0.0196000000
P(cbcc): 0.0686000000
P(ccaa): 0.0049000000
P(ccab): 0.0098000000
P(ccac): 0.0343000000
P(ccba): 0.0098000000
P(ccbb): 0.0196000000
P(ccbc): 0.0686000000
P(ccca): 0.0343000000
P(cccb): 0.0686000000
P(cccc): 0.2401000000
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
using namespace std;

int cnt = 0;

/*
関数 cal_p
概要：再帰的にありうる記号列パターンを全探索して、対応する確率を計算する
m: 情報源アルファベットの要素数
n: 記号列
temp: 記号列パターンを一時的に記録 
例えばm=4,n=4,symbols={a,b,c,d}としてtempが{0000}だったらaaaa {0123}だったらabcdに対応
symbols: 情報源アルファベット
p: 各情報源アルファベットの確率
sym_com: 各記号列を入れる
ans: 各記号列の確率の計算結果を入れる
*/
void cal_p(int m, int n, vector<int> &temp, vector<char> &symbols, vector<long double> &p, vector<string> &sym_com, vector<long double> &ans){
    /*もしtempのサイズがnと等しくなったらtempの中身に従って記号列を求め、確率を計算*/
    if(temp.size() == n){
        ans.at(cnt) = 1;
        for(int i=0;i<n;i++){
            sym_com.at(cnt) += symbols.at(temp.at(i));
            ans.at(cnt) = ans.at(cnt)*p.at(temp.at(i));
        }
        cnt++;
        return;
    }
    /*tempのサイズがnになるまではこの処理を行う*/
    for(int i=0;i<m;i++){
        temp.push_back(i); //tempにiをpush
        cal_p(m, n, temp, symbols, p, sym_com, ans); //tempのサイズが1大きくなったので再帰呼び出し
        temp.pop_back(); //tempをpopして次のループで別の要素をpush(これによって全探索できる)
    }
}

int main(void){
    int m = 0; // 情報源アルファベットの要素数
    int n = 0; // 記号列長
    
    cout << "alphabet size: ";
    cin >> m;
    cout << "length: ";
    cin >> n;

    int ans_len = pow(m,n); //全パターンはm^n通り

    vector<char> symbols(m); //情報源アルファベットの格納用の配列
    vector<long double> p(m); //情報源アルファベットの確率を格納する配列
    vector<string> sym_com(ans_len); //記号列のパターンを記録する配列
    vector<long double> ans(ans_len); //記号列の確率を記録する配列

    /*入力の受け取り*/
    for(int i=0;i<m;i++){
        cout << "symbol_" << i+1 << "> ";
        cin >> symbols.at(i);
        cout << "p_" << i+1 << "> ";
        cin >> p.at(i);
    }

    /*cal_pを用いて答えを計算*/
    vector<int> temp = {};
    cal_p(m, n, temp, symbols, p, sym_com, ans);

    /*計算結果を出力*/
    for(int i=0;i<ans_len;i++){
        cout << fixed;
        cout << "P(" << sym_com.at(i) << "): " <<  setprecision(10) << ans.at(i) << endl;
    }

    return 0;
}