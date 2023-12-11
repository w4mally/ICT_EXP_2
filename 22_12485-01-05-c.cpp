// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-05-c.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
abcabadcbddbadacbbaabbaccbacdd
[出力]
010110010011111010111111100111011010100010100110110100110111111
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
            out += "10"; //もし入力のi文字目がbだったら出力文字列の末尾に10を追加
        }
        else if(in.at(i) == 'c'){
            out += "110"; //もし入力のi文字目がcだったら出力文字列の末尾に110を追加
        }
        else if(in.at(i) == 'd'){
            out += "111"; //もし入力のi文字目がdだったら出力文字列の末尾に111を追加
        }
    }

    cout << "codewords: ";
    cout << out << endl; //符号語を出力

    return 0;
}