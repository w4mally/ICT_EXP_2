// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-12.cpp
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
codewords> 0011011100011001100110010011100010001010011011101001101110100101001100111100110011101110001100100111001110
[出力]
symbols: abaaadbddcabcabcdcaaccaacbadbb
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
using namespace std;

int main(void){
    int n = 0; //情報源アルファベットの要素数
    int maxlen = 0; //符号語長の最大値
    string code; //符号語列
    string ans_sym; //復号結果

    /*情報源アルファベットの要素数の受け取り*/
    cout << "alphabet size> ";
    cin >> n;

    vector<char> symbols(n); //情報源アルファベットを格納する配列
    vector<string> codewords(n); //符号語を格納する配列
    map<string, char> decmap; //key:符号語,value:アルファベットの連想配列

    /*情報源アルファベットとそれに対応する符号語の受け取り、連想配列の作成、maxlenの調査*/
    for(int i=0;i<n;i++){
        cout << "symbol_" << i << "> ";
        cin >> symbols.at(i);
        cout << "codeword_" << i << "> ";
        cin >> codewords.at(i);
        if(codewords.at(i).size() > maxlen) maxlen = codewords.at(i).size();
        decmap[codewords.at(i)] = symbols.at(i);
    }

    cout << "codewords> ";
    cin >> code;

    /*
    i=1~maxlenとして
    codeについて、先頭i文字を見る
    もし先頭i文字がdecmapのkeyとして存在するならそれに対応するvalueをデコード結果の末尾に追加してcodeから先頭i文字を消去
    これをcodeが空になるまで続ける
    */
    while(code.empty() == 0){
        for(int i=1;i<=maxlen;i++){
            if(decmap.count(code.substr(0,i))){
                ans_sym += decmap.at(code.substr(0,i));
                code.erase(0,i);
            }
        }
    }

    /*デコード結果の出力*/
    cout << "symbols: " << ans_sym << endl;

    return 0;
}