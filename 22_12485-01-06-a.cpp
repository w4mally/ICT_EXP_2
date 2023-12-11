// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-06-a.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
111111010001001111111111101001
[出力]
bbbbbbabaaabaabbbbbbbbbbbabaab
*/

#include <iostream>
#include <string>
using namespace std;

int main(void){
    string in; //入力を受け取る変数
    string out; //復号結果を入れる変数
    cout << "codewords> ";
    cin >> in; //標準入力の受け取り
    
    for(int i=0;i<in.length();i++){
        if(in.at(i) == '0'){
            out += 'a'; //もし入力のi文字目が0だったら出力文字列の末尾にaを追加
        }
        else if(in.at(i) == '1'){
            out += 'b'; //もし入力のi文字目が1だったら出力文字列の末尾にbを追加
        }
    }

    cout << "symbols: ";
    cout << out << endl; //復号結果を出力

    return 0;
}