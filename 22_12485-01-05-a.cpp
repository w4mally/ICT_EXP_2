// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-05-a.cpp
// 実行方法:コンパイルで生成したa.outを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
bababaaabaaaaaaabaabbbbbbabaaa
[出力]
101010001000000010011111101000
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
            out += '0'; //もし入力のi文字目がaだったら出力文字列の末尾に0を追加
        }
        else if(in.at(i) == 'b'){
            out += '1'; //もし入力のi文字目がbだったら出力文字列の末尾に0を追加
        }
    }

    cout << "codewords: ";
    cout << out << endl; //符号語を出力

    return 0;
}