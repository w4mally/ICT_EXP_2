// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-02-04.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
alphabet size> 4
symbol_1> a
p_1> 0.6
symbol_2> b
p_2> 0.2
symbol_3> c
p_3> 0.1
symbol_4> d
p_4> 0.1
symbols> aadaadaabcccbdbcbacc
codewords> 00101011001100110011             
length> 30
[出力]
range: [0.3360268712840387789154636, 0.3360268712840835686895668)
encoded: 0101011000000101110110110110011010111110000000
decode: aaabdaaaaacaaaaaabababcbbbbadd
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
using namespace std;

int main(void){
    /*＊＊＊符号化部分＊＊＊*/
    int n = 0; //情報源アルファベットの要素数用の変数

    /*情報源アルファベットの要素数の受け取り*/
    cout << "alphabet size> ";
    cin >> n;

    vector<char> symbols(n); //情報源アルファベットを格納する配列
    vector<long double> p(n); //各情報源アルファベットの確率を格納する配列
    vector<pair<long double, long double>> p_section(n); //各情報源アルファベットに対応する区間
    map<char, pair<long double, long double>> sym_to_sec; //key=情報源アルファベット,value=区間の連想配列

    long double temp_p = 0;
    for(int i=0;i<n;i++){
        cout << "symbol_" << i+1 << "> ";
        cin >> symbols.at(i); //情報源アルファベットの受け取り
        cout << "p_" << i+1 << "> ";
        cin >> p.at(i); //第i情報源アルファベットの確率の受け取り
        p_section.at(i) = make_pair(temp_p, temp_p+p.at(i));
        temp_p += p.at(i);

        sym_to_sec[symbols.at(i)] = p_section.at(i); //連想配列作成
    }

    /*符号化する記号列の受け取り*/
    string s;
    cout << "symbols> ";
    cin >> s;

    pair<long double, long double> ans = make_pair(0,1); //符号化に使う区間を記録
    long double ans_len = 1; //区間幅

    /*記号列を先頭から1文字ずつ見ていって1文字ごとに区間を更新*/
    for(int i=0;i<(int)s.size();i++){
        ans.second = ans.first + sym_to_sec.at(s.at(i)).second*ans_len;
        ans.first += sym_to_sec.at(s.at(i)).first*ans_len;
        ans_len = ans.second - ans.first;
    }

    /*計算した区間の上限と下限を出力*/
    cout << fixed;
    cout << "range: [" <<  setprecision(25) << ans.first << ", " << ans.second << ")" << endl;

    double rep_value = (ans.first+ans.second)/2; //代表値
    int code_len = ceil(-log2(ans_len)) + 1; //符号長

    string enc = ""; //符号化の結果はここに記録

    /*符号長分だけ代表値の小数点以下を2進数に変換した値を調べる、各桁の値が分かるたびにcodeの末尾に追記*/
    for(int i=0;i<code_len;i++){
        rep_value = rep_value*2;
        if(rep_value >= 1){
            enc += "1";
            rep_value -= 1;
        }
        else if(rep_value < 1){
            enc += "0";
        }
    }

    /*符号化結果を出力*/
    cout << "encoded: " << enc << endl;

    /*＊＊＊復号部分＊＊＊*/
    string code = "";
    string dec; //復号結果
    int dec_len = 0;
    cout << "codewords> ";
    cin >> code;
    cout << "length> ";
    cin >> dec_len;

    rep_value = 0; //代表値用の変数,また使うので初期化

    /*codeから2進数→10進数に変換して代表値を復元*/
    for(int i=0;i<(int)code.size();i++){
        if(code.at(i) == '1'){
            long double x = 1/(pow(2,i+1));
            rep_value += x;
        }
    }

    int temp_sub = 0;
    for(int i=0;i<dec_len;i++){
        /*代表値がどの区間に入っているかを全探索*/
        for(int j=0;j<n;j++){
            if(p_section.at(j).first <= rep_value && rep_value < p_section.at(j).second){
                dec += symbols.at(j);
                temp_sub = j;
            }
        }
        /*代表値の更新*/
        rep_value = (rep_value - p_section.at(temp_sub).first)/(p_section.at(temp_sub).second - p_section.at(temp_sub).first);
    }

    /*復号結果の出力*/
    cout << "decode: " << dec << endl;

    return 0;
}