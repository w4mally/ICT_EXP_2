// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-05-02.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

void get_char_histogram(string input, vector<int> &char_hist){
    /*asciiコードは32~127(96個)*/
    int i, j, t;
    int len;

    /*文字列の長さ取得*/
    len = input.length();

    /*ヒストグラムの初期化*/
    for(i=32;i<128;i++){
        char_hist.at(i) = 0;
    }

    for(i=0;i<len;i++){
        char_hist.at(input.at(i))++;
    }
}

int main(void){
    string input_text;
    vector<int> char_hist(1000);

    /*入力ファイルオープン*/
    ifstream ifs("cipher.txt");
    if(!ifs){
        cout << "file not open";
        exit(0);
    }
    ofstream ofs("char_histgram.txt");
    if(!ofs){
        cout << "er";
        exit(0);
    }

    /*ファイルの読み込み・表示*/
    cout << "\n\n";
    cout << "*****************************************************" << endl;
    cout << "********       Text file is displayed.     **********" << endl;
    cout << "*****************************************************" << endl;
    cout << "\n\n";

    while(getline(ifs, input_text)){
        cout << input_text;
    }

    /*テキストのヒストグラムを求める*/
    get_char_histogram(input_text, char_hist);

    /*ヒストグラムの表示・書き込み*/
    cout << "\n\n";
    cout << "*****************************************************" << endl;
    cout << "**********    Histogram is displayed.   ***********" << endl;
    cout << "*****************************************************" << endl;
    cout << "\n\n";
    
    for(int i=32;i<128;i++){
        cout << '[' << (char)i << ", " << char_hist.at(i) << ']' << endl;
        ofs << i << ", " << char_hist.at(i) << endl;
    }

    ifs.close();
    ofs.close();
}