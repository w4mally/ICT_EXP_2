// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-02-06.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
using namespace std;

/*
実行結果
[入力]
alphabet size: 2
length: 5
symbol_1> a
p_1> 0.2
symbol_2> b
p_2> 0.8
cp_11> 0.2
cp_12> 0.8
cp_21> 0.5
cp_22> 0.5
[出力]
P(aaaaa): 0.0003200000
P(aaaab): 0.0012800000
P(aaaba): 0.0032000000
P(aaabb): 0.0032000000
P(aabaa): 0.0032000000
P(aabab): 0.0128000000
P(aabba): 0.0080000000
P(aabbb): 0.0080000000
P(abaaa): 0.0032000000
P(abaab): 0.0128000000
P(ababa): 0.0320000000
P(ababb): 0.0320000000
P(abbaa): 0.0080000000
P(abbab): 0.0320000000
P(abbba): 0.0200000000
P(abbbb): 0.0200000000
P(baaaa): 0.0032000000
P(baaab): 0.0128000000
P(baaba): 0.0320000000
P(baabb): 0.0320000000
P(babaa): 0.0320000000
P(babab): 0.1280000000
P(babba): 0.0800000000
P(babbb): 0.0800000000
P(bbaaa): 0.0080000000
P(bbaab): 0.0320000000
P(bbaba): 0.0800000000
P(bbabb): 0.0800000000
P(bbbaa): 0.0200000000
P(bbbab): 0.0800000000
P(bbbba): 0.0500000000
P(bbbbb): 0.0500000000
*/


int cnt = 0;
int prev_int = 0; //cal_p_markovにおいて1つ前の記号が何であったのかを記録しておく変数
/*
関数 cal_p_markov
概要：再帰的にありうる記号列パターンを全探索して、対応する確率を計算する
m: 情報源アルファベットの要素数
n: 記号列
temp: 記号列パターンを一時的に記録 
例えばm=4,n=4,symbols={a,b,c,d}としてtempが{0000}だったらaaaa {0123}だったらabcdに対応
symbols: 情報源アルファベット
p: 各情報源アルファベットの確率
sym_com: 各記号列を入れる
ans: 各記号列の確率の計算結果を入れる
con_p: 記号生成の条件付確率を決める i行j列成分には第iシンボルが生起した後に第jシンボルが生起する確率が記録されている
*/
void cal_p_markov(int m, int n, vector<int> &temp, vector<char> &symbols, vector<long double> &p, vector<string> &sym_com, vector<long double> &ans, vector<vector<long double>> &con_p){
    /*もしtempのサイズがnと等しくなったらtempの中身に従って記号列を求め、確率を計算*/
    if(temp.size() == n){
        ans.at(cnt) = 1;
        for(int i=0;i<n;i++){
            /*1文字目はpから確率を求めて計算*/
            if(i == 0){
                sym_com.at(cnt) += symbols.at(temp.at(i)); // 記号列を記録
                ans.at(cnt) = ans.at(cnt)*p.at(temp.at(i)); // 1文字目が生成される確率の計算
                prev_int = temp.at(i); // 1文字目が何であったのかを覚えておく
            /*1文字目以降は条件付確率を用いて計算する*/
            } else {
                sym_com.at(cnt) += symbols.at(temp.at(i)); // 記号列を記録
                ans.at(cnt) = ans.at(cnt)*con_p.at(prev_int).at(temp.at(i)); // i文字目が生成される確率の計算
                prev_int = temp.at(i); // 1文字目が何であったのかを覚えておく
            }
        }
        cnt++;
        return;
    }
    /*tempのサイズがnになるまではこの処理を行う*/
    for(int i=0;i<m;i++){
        temp.push_back(i); //tempにiをpush
        cal_p_markov(m, n, temp, symbols, p, sym_com, ans, con_p); //tempのサイズが1大きくなったので再帰呼び出し
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
    vector<vector<long double>> con_p(m, vector<long double>(m)); //条件付確率を格納する二次元配列
    vector<string> sym_com(ans_len); //記号列のパターンを記録する配列
    vector<long double> ans(ans_len); //記号列の確率を記録する配列

    /*入力の受け取り*/
    for(int i=0;i<m;i++){
        cout << "symbol_" << i+1 << "> ";
        cin >> symbols.at(i);
        cout << "p_" << i+1 << "> ";
        cin >> p.at(i);
    }

    for(int i=0;i<m;i++){
        for(int j=0;j<m;j++){
            cout << "cp_" << i+1 << j+1 << "> ";
            cin >> con_p.at(i).at(j);
        }
    }
    /*cal_p_markovを用いて出力を計算*/
    vector<int> temp = {};
    cal_p_markov(m, n, temp, symbols, p, sym_com, ans, con_p);

    /*計算結果を出力*/
    for(int i=0;i<ans_len;i++){
        cout << fixed;
        cout << "P(" << sym_com.at(i) << "): " <<  setprecision(10) << ans.at(i) << endl;
    }

}