// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-05-b.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
caaaaaacaacaaacbaacbbbccabbccb
[出力]
0011111110011100111100101110010101010010011010100100101
*/

#include <iostream>
#include <string>
using namespace std;

int main(void){
    string in; //入力を受け取る変数
    string out; //符号語を入れる変数
    cout << "symbols> ";
    cin >> in; //標準入力の受け取り
    
    for(int i=0;i<in.length();i++){
        if(in.at(i) == 'a'){
            out += '1'; //もし入力のi文字目がaだったら出力文字列の末尾に1を追加
        }
        else if(in.at(i) == 'b'){
            out += "01"; //もし入力のi文字目がbだったら出力文字列の末尾に01を追加
        }
        else if(in.at(i) == 'c'){
            out += "001"; //もし入力のi文字目がcだったら出力文字列の末尾に001を追加
        }
    }

    cout << "codewords: ";
    cout << out << endl; //符号語を出力

    return 0;
}