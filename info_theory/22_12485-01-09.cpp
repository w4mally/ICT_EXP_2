// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-09.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
alphabet size> 27
symbol_1> a
p_1> 0.1571
symbol_2> b
p_2> 0.1524
symbol_3> c
p_3> 0.1386
symbol_4> d
p_4> 0.127
symbol_5> e
p_5> 0.1040
symbol_6> f
p_6> 0.0912
symbol_7> g
p_7> 0.0657
symbol_8> h
p_8> 0.0564
symbol_9> i
p_9> 0.0345
symbol_10> j
p_10> 0.0301
symbol_11> k
p_11> 0.0148
symbol_12> l
p_12> 0.0138
symbol_13> m
p_13> 0.0054
symbol_14> n
p_14> 0.005
symbol_15> o
p_15> 0.0018
symbol_16> p
p_16> 0.0012
symbol_17> q
p_17> 0.0005
symbol_18> r
p_18> 0.0002
symbol_19> s
p_19> 0.0001
symbol_20> t
p_20> 0.00008
symbol_21> u
p_21> 0.00007
symbol_22> v
p_22> 0.00003
symbol_23> w
p_23> 0.00001
symbol_24> x
p_24> 0.000004
symbol_25> y
p_25> 0.000003
symbol_26> z
p_26> 0.000002
symbol_27> _
p_27> 0.000001
symbols> symbols_are_symbols
codewords> 110100010100001101000101001110011101001001110100011110101110100010100001101000101001110001000110100010101101110100010100111000111010001010000110100010100111001110100100111010001111010111010001010000
[出力]
cw for a: 000
cw for b: 001
cw for c: 010
cw for d: 100
cw for e: 101
cw for f: 111
cw for g: 0110
cw for h: 1100
cw for i: 01110
cw for j: 01111
cw for k: 11011
cw for l: 110101
cw for m: 1101001
cw for n: 11010000
cw for o: 110100011
cw for p: 1101000100
cw for q: 11010001011
cw for r: 110100010101
cw for s: 11010001010000
cw for t: 11010001010001
cw for u: 11010001010010
cw for v: 110100010100110
cw for w: 1101000101001111
cw for x: 11010001010011101
cw for y: 110100010100111001
cw for z: 1101000101001110000
cw for _: 1101000101001110001
entropy: 3.367071
average length: 3.397289
encoded: 110100010100001101000101001110011101001001110100011110101110100010100001101000101001110001000110100010101101110100010100111000111010001010000110100010100111001110100100111010001111010111010001010000
decoded: symbols_are_symbols
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
    int n = 0; //情報源アルファベットの要素数用の変数
    long double e = 0; //エントロピー用の変数
    long double ave_len = 0; //平均符号語長の用の変数

    /*情報源アルファベットの要素数の受け取り*/
    cout << "alphabet size> ";
    cin >> n;

    vector<char> symbols(n); //情報源アルファベットを格納する配列
    vector<long double> p(n); //各情報源アルファベットの確率を格納する配列
    map<char, long double> in; //情報源アルファベットとそれに対応する確率を格納する連想配列 key:アルファベット, value:確率

    for(int i=0;i<n;i++){
        cout << "symbol_" << i+1 << "> ";
        cin >> symbols.at(i); //情報源アルファベットの受け取り
        cout << "p_" << i+1 << "> ";
        cin >> p.at(i); //第i情報源アルファベットの確率の受け取り

        in[symbols.at(i)] = p.at(i); //連想配列への格納
    }

    vector<node> tree(2*n-1); //nodeの集合、すなわち木

    /*
    各情報源アルファベットに対応するノードを作る
    子ノードは存在しないので空
    このノードのcodeを最終的に出力
    */
    int cnt = 0;
    for(int i = 0;i < n; i++){
        vector<int> temp = {};
        tree.at(cnt) = {p.at(i), temp, ""};
        cnt++;
    }

    /*
    プライオリティキューに各ノードを格納する
    本来のプライオリティキューは降順格納なので昇順格納されるように実装
    これを行うことでキューの先頭2つを取り出せば、親を持たないノードのうち最もsumが小さい2つを取り出せる
    */
    priority_queue<pair<long double, int>, vector<pair<long double, int> >, greater<pair<long double, int> > > pq;
    cnt = 0;
    for(int i = 0;i < n; i++){
        pq.push(make_pair(p.at(i), cnt));
        cnt++;
    }

    /*
    キューの先頭2要素を取り出し、それぞれのノードのsumの和を計算
    その和をsumの値とし、取り出した2要素を子ノードに設定したあたらしいノードを木に追加していく
    */
    for(int i=n;i<2*n-1;i++){
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
    code_create(tree,2*n-2);

    for(int i=0;i<n;i++){
        cout << "cw for " << symbols.at(i) << ": " << tree.at(i).code << endl;
    }

    map<char, string> codewords; //key:情報源アルファベット, value:符号の連想配列
    map<string, char> decmap; //key:符号, value:情報源アルファベットの連想配列
    vector<int> len(n); //各符号の符号長を格納する配列
    int maxlen = 0; //符号語の最大の長さ

    for(int i=0;i<n;i++){
        codewords[symbols.at(i)] = tree.at(i).code;
        decmap[tree.at(i).code] = symbols.at(i);
    }

    for(int i=0;i<n;i++){
        len.at(i) = tree.at(i).code.size(); //符号長
        if(len.at(i)>maxlen) maxlen = len.at(i); //符号語の最大の長さを調べる
        e += -p.at(i)*log2(p.at(i)); //エントロピーの計算
        ave_len += len.at(i)*p.at(i); //平均符号長の計算
    }

    /*エントロピーと平均符号長の出力*/
    cout << fixed;
    cout << "entropy: " << setprecision(6) << e << endl;
    cout << "average length: " << setprecision(6) << ave_len << endl;

    string plaintext; //標準入力で受け取る情報源アルファベットの列
    string ans_enc; //plaintextをハフマン符号化した結果

    cout << "symbols> ";
    cin >> plaintext;

    /*符号化*/
    for(int i=0;i<(int)plaintext.size();i++){
        ans_enc += codewords.at(plaintext.at(i));
    }

    /*符号化結果の出力*/
    cout << "encoded: " << ans_enc << endl;

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