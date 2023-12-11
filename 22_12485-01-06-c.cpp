// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-06-c.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
1011110110111111100011011010
[出力]
bdbcddbaaccb
*/

#include <iostream>
#include <string>
using namespace std;

int main(void){
    string in; //入力を受け取る変数
    string out; //復号結果を入れる変数
    cout << "codewords> ";
    cin >> in; //標準入力の受け取り
    
    /*
    入力変数を先頭から見る
    先頭が0だったら復号結果の文字列の末尾にaを追加→入力変数の先頭を削除
    先頭が1だったら入力変数の2文字目を見る
    入力変数の先頭が1かつ入力変数の2文字目が0だったら復号結果の文字列の末尾にbを追加→入力変数の先頭から2文字を削除
    入力変数の先頭が1かつ入力変数の2文字目が1だったらさらに入力の3文字目も見る
    入力変数の先頭から2文字が11かつ3文字目が0だったら復号結果の文字列の末尾にcを追加→入力変数の先頭から3文字を削除
    入力変数の先頭から2文字が11かつ3文字目が1だったら復号結果の文字列の末尾にdを追加→入力変数の先頭から3文字を削除
    以上を入力変数が空になるまで繰り返す
    */
    while(in.empty() == 0){
        if(in.at(0) == '0'){
            out += 'a';
            in.erase(0,1);
        }
        else if(in.at(0) == '1'){
            if(in.at(1) == '0'){
                out += 'b';
                in.erase(0,2);
            }
            else if(in.at(1) == '1'){
                if(in.at(2) == '0'){
                    out += 'c';
                    in.erase(0,3);
                }
                else if(in.at(2) == '1'){
                    out += 'd';
                    in.erase(0,3);
                }
            }
        }
    }

    cout << "symbols: ";
    cout << out << endl; //復号結果を出力

    return 0;
}