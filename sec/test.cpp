#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <bitset>
#include <algorithm>
#include <fstream>
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
    string name;
    string plain_text;
    string cipher;

    ifstream ifs("cipher_p.txt");
    if(!ifs){ 
        cout << "file not open";
    }

    getline(ifs, cipher);

    vector<int> hist(1000);
    get_char_histogram(cipher, hist);

    for(int i=32;i<128;i++){
        cout << '[' << i << ", " << hist.at(i) << ']' << endl;
    }

    ifs.close();

    return 0;
}