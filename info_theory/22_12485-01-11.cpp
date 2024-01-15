// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-11.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
alphabet size> 4
symbol_0> a
codeword_0> 0011
symbol_1> b
codeword_1> 01110
symbol_2> c
codeword_2> 1
symbol_3> d
codeword_3> 0010
symbols> abcabadcbddbadacbbaabbaccbacdd
[出力]
codewords: 001101110100110111000110010101110001000100111000110010001110111001110001100110111001110001111011100011100100010
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
using namespace std;

int main(void){
    int n = 0; //情報源アルファベットの要素数を受け取る変数
    string in; //入力記号列用の変数
    string out; //出力符号用の変数
    cout << "alphabet size> " ; 
    cin >> n;
    
    vector<char> symbols(n); //情報源アルファベットを格納する配列
    vector<string> codes(n); //情報源アルファベットに対応する符号を格納する配列
    map<char, string> enc; //情報源アルファベットの各記号をkey,その記号に対応する符号をvalueとする連想配列

    //情報源アルファベットおよびそれに対応する符号語の受け取り+mapへの登録
    for(int i=0;i<n;i++){
        cout << "symbol_" << i << "> ";
        cin >> symbols.at(i);
        cout << "codeword_" << i << "> ";
        cin >> codes.at(i);

        enc[symbols.at(i)] = codes.at(i);
    }

    cout << "symbols> ";
    cin >> in;

    //入力の先頭から1文字ずつそれをkeyとしてmapから文字列を取り出して、出力に足していく
    for(int i=0;i<in.length();i++){
        out += enc.at(in.at(i));
    }

    //結果の出力
    cout << "codewords: " << out << endl;

    return 0;
}