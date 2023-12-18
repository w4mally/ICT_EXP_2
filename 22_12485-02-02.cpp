// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-02-02.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
[入力]
alphabet size> 4
symbol_1> a
p_1> 0.1
symbol_2> b
p_2> 0.2
symbol_3> c
p_3> 0.3
symbol_4> d
p_4> 0.4
[出力]
cw for aaa: 110100111
cw for aab: 110100110
cw for aac: 11010010
cw for aad: 01001011
cw for aba: 000110111
cw for abb: 01001010
cw for abc: 1101000
cw for abd: 1010000
cw for aca: 11010101
cw for acb: 00011010
cw for acc: 0001111
cw for acd: 0001100
cw for ada: 01001001
cw for adb: 0101011
cw for adc: 101011
cw for add: 011011
cw for baa: 000110110
cw for bab: 01001000
cw for bac: 1010001
cw for bad: 0101010
cw for bba: 01000111
cw for bbb: 0101001
cw for bbc: 101010
cw for bbd: 011010
cw for bca: 1101101
cw for bcb: 111011
cw for bcc: 001001
cw for bcd: 000001
cw for bda: 0101000
cw for bdb: 011001
cw for bdc: 10111
cw for bdd: 10010
cw for caa: 11010100
cw for cab: 1101100
cw for cac: 0001110
cw for cad: 111010
cw for cba: 1101011
cw for cbb: 111001
cw for cbc: 001000
cw for cbd: 000000
cw for cca: 0100010
cw for ccb: 010000
cw for ccc: 10011
cw for ccd: 00111
cw for cda: 111000
cw for cdb: 11111
cw for cdc: 00110
cw for cdd: 00010
cw for daa: 01000110
cw for dab: 0100111
cw for dac: 101001
cw for dad: 011000
cw for dba: 0100110
cw for dbb: 010111
cw for dbc: 10110
cw for dbd: 01111
cw for dca: 110111
cw for dcb: 11110
cw for dcc: 00101
cw for dcd: 00001
cw for dda: 010110
cw for ddb: 01110
cw for ddc: 1100
cw for ddd: 1000
entropy: 5.539318
average length: 5.577000
symbols> abcdaabbccdd
encoded> 11010000100011010101000010
codewords> 110100001000110 0101000010
decoded: abcdaabbccdd
*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
using namespace std;

//木構造を作る構造体
typedef struct node_t {
    long double sum; //このノードの子ノードが持つ確率の和、子ノードを持たない場合与えられた情報源アルファベットの確率
    vector<int> child; //子ノードの添え字
    string code; //このノードに対応する符号
} node; //この構造体をnodeで表す

/*
関数 cal_p
概要：再帰的にありうる記号列パターンを全探索して、対応する確率を計算する
m: 情報源アルファベットの要素数
n: 記号列
temp: 記号列パターンを一時的に記録 
例えばm=4,n=4,symbols={a,b,c,d}としてtempが{0000}だったらaaaa {0123}だったらabcdに対応
symbols: 情報源アルファベット
p: 各情報源アルファベットの確率
sym_com: 各記号列を入れる
ans: 各記号列の確率の計算結果を入れる
*/
int cnt_ = 0;
void cal_p(int m, int n, vector<int> &temp, vector<char> &symbols, vector<long double> &p, vector<string> &sym_com, vector<long double> &ans){
    /*もしtempのサイズがnと等しくなったらtempの中身に従って記号列を求め、確率を計算*/
    if(temp.size() == n){
        ans.at(cnt_) = 1;
        for(int i=0;i<n;i++){
            sym_com.at(cnt_) += symbols.at(temp.at(i));
            ans.at(cnt_) = ans.at(cnt_)*p.at(temp.at(i));
        }
        cnt_++;
        return;
    }
    /*tempのサイズがnになるまではこの処理を行う*/
    for(int i=0;i<m;i++){
        temp.push_back(i); //tempにiをpush
        cal_p(m, n, temp, symbols, p, sym_com, ans); //tempのサイズが1大きくなったので再帰呼び出し
        temp.pop_back(); //tempをpopして次のループで別の要素をpush(これによって全探索できる)
    }
}

/*各ノードに符号を割り当てる再帰関数*/
void code_create(vector<node> &tree, int x){
    /*子ノードを持たないノードにあたるまで再帰を続ける*/
    if(tree.at(x).child.size() != 0){
        for(int i=0;i<2;i++){
            string tempcode = tree.at(x).code + (char)('1'-i); //符号の割り当て
            int index = tree.at(x).child.at(i);
            tree.at(index).code = tempcode;
            code_create(tree, index);
        }
    }
}

int main(void){
    int e = 3; //入力記号の塊のサイズ
    int n = 0; //情報源アルファベットの要素数用の変数
    long double entropy = 0; //エントロピー用の変数
    long double ave_len = 0; //平均符号語長の用の変数

    /*情報源アルファベットの要素数の受け取り*/
    cout << "alphabet size> ";
    cin >> n;

    int ans_len = pow(n,e); // 入力記号の全パターンはn^e通り

    vector<char> symbols(n); //情報源アルファベットを格納する配列
    vector<long double> p(n); //各情報源アルファベットの確率を格納する配列
    vector<string> sym_com(ans_len); //記号列のパターンを記録する配列
    vector<long double> p_com(ans_len); //記号列の確率を記録する配列

    for(int i=0;i<n;i++){
        cout << "symbol_" << i+1 << "> ";
        cin >> symbols.at(i); //情報源アルファベットの受け取り
        cout << "p_" << i+1 << "> ";
        cin >> p.at(i); //第i情報源アルファベットの確率の受け取り
    }

    /*関数cal_pを用いて各記号とそれに対応する確率を計算*/
    vector<int> temp_ = {};
    cal_p(n, e, temp_, symbols, p, sym_com, p_com);

    vector<node> tree(2*ans_len-1); //nodeの集合、すなわち木

    /*
    各情報源アルファベットに対応するノードを作る
    子ノードは存在しないので空
    このノードのcodeを最終的に出力
    */
    int cnt = 0;
    for(int i = 0;i < ans_len; i++){
        vector<int> temp = {};
        tree.at(cnt) = {p_com.at(i), temp, ""};
        cnt++;
    }

    /*
    プライオリティキューに各ノードを格納する
    本来のプライオリティキューは降順格納なので昇順格納されるように実装
    これを行うことでキューの先頭2つを取り出せば、親を持たないノードのうち最もsumが小さい2つを取り出せる
    */
    priority_queue<pair<long double, int>, vector<pair<long double, int> >, greater<pair<long double, int> > > pq;
    cnt = 0;
    for(int i = 0;i < ans_len; i++){
        pq.push(make_pair(p_com.at(i), cnt));
        cnt++;
    }

    /*
    キューの先頭2要素を取り出し、それぞれのノードのsumの和を計算
    その和をsumの値とし、取り出した2要素を子ノードに設定したあたらしいノードを木に追加していく
    */
    for(int i=ans_len;i<2*ans_len-1;i++){
        pair<long double, int> x = pq.top();
        pq.pop();
        pair<long double, int> y = pq.top();
        pq.pop();
        pair<long double, int> z = make_pair(x.first+y.first, i);
        pq.push(z);
        vector<int> temp2 = {x.second, y.second};
        tree.at(i) = {z.first, temp2, ""};
    }

    /*
    冒頭で実装した再帰関数を、上で構成した木に適応して各ノードに符号を割り当てる
    treeの先頭n個のノードが持つ符号がそれぞれの情報源アルファベットに対応する符号
    */
    code_create(tree,2*ans_len-2);

    for(int i=0;i<ans_len;i++){
        cout << "cw for " << sym_com.at(i) << ": " << tree.at(i).code << endl;
    }

    map<string, string> codewords; //key:情報源アルファベット, value:符号の連想配列
    map<string, string> decmap; //key:符号, value:情報源アルファベットの連想配列
    vector<int> len(ans_len); //各符号の符号長を格納する配列
    int maxlen = 0; //符号語の最大の長さ

    /*連想配列の作成*/
    for(int i=0;i<ans_len;i++){
        codewords[sym_com.at(i)] = tree.at(i).code;
        decmap[tree.at(i).code] = sym_com.at(i);
    }

    for(int i=0;i<ans_len;i++){
        len.at(i) = tree.at(i).code.size(); //符号長
        if(len.at(i)>maxlen) maxlen = len.at(i); //符号語の最大の長さを調べる
        entropy += -p_com.at(i)*log2(p_com.at(i)); //エントロピーの計算
        ave_len += len.at(i)*p_com.at(i); //平均符号長の計算
    }

    /*エントロピーと平均符号長の出力*/
    cout << fixed;
    cout << "entropy: " << setprecision(6) << entropy << endl;
    cout << "average length: " << setprecision(6) << ave_len << endl;

    string plaintext; //標準入力で受け取る情報源アルファベットの列
    string ans_enc; //plaintextをハフマン符号化した結果

    cout << "symbols> ";
    cin >> plaintext;

    /*符号化*/
    string p_text_copy = plaintext;
    for(int i=0;i<(int)plaintext.size()/e;i++){;
        string temp_str = p_text_copy.substr(0,3);
        ans_enc += codewords.at(temp_str);
        p_text_copy.erase(0,3);
    }

    /*符号化結果の出力*/
    cout << "encoded> " << ans_enc << endl;

    string code; //符号の入力を受け取る変数
    string ans_dec; //codeのデコード結果を受け取る変数

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
                ans_dec += decmap.at(code.substr(0,i));
                code.erase(0,i);
            }
        }
    }

    /*デコード結果の出力*/
    cout << "decoded: " << ans_dec << endl;

    return 0;
}