// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-07.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

//木構造を作る構造体
typedef struct node_t{
    struct node_t *up; //親を指すポインタ
    struct node_t *left; //左側の子を指すポインタ
    struct node_t *right; //右側の子を指すポインタ
    int v; //このノードに訪問したことがあるかを判定するための変数
    int leaf; //このノードが葉であるかを記録する変数
    string symbol; //このノードに対応する符号語
} *node; //この構造体のポインタをnodeで表す

int main(void){
    int n = 0; //情報源アルファベットの要素数用の変数
    double e = 0; //エントロピー用の変数
    double ave_len = 0; //平均符号語長の用の変数
    /*情報源アルファベットの要素数の受け取り*/
    cout << "alphabet size> ";
    cin >> n;

    vector<double> p(n); //情報源アルファベットの確率を受け取る配列
    vector<int> len(n); //確率から求めた各符号長を格納する配列
    vector<string> cw(n); //生成した符号をいれる配列

    for(int i=0;i<n;i++){
        cout << "p_" << i+1 << '>';
        cin >> p.at(i); //第i情報源アルファベットの確率の受け取り
    }

    for(int i=0;i<n;i++){
        len.at(i) = (int)ceil(-log2(p.at(i))); //情報源アルファベットの確率から符号長を求める
        e += -p.at(i)*log2(p.at(i)); 
        ave_len += len.at(i)*p.at(i); //平均符号長の計算
    }

    struct node_t pool[256] = {{0}}; //ノードの集合
    int nodes = 1; //ノード数
    node tree; //木

    /*
    なるべく左側のノードが優先されるように符号語の長さと一致する深さまで探索
    もし現在のノードの子ノードが葉でなくて、未探索ならそちらに移動(左ノード優先)
    現在のノードの子ノードが葉ではない&未探索&深さが指定された符号語の長さと一致ならそのノードを葉として符号語を記録
    左右のノードが探索済みだったら根に戻る
    以上を各符号語に対して行い、符号を構成する
    */
    for(int i=0;i<n;i++){
        tree = pool; //根に戻る
        for(int j=0;j<len.at(i);j++){
            /*もし現在のノードに子がいないなら子ノードを作成*/
            if(tree->left == 0){
                tree->left = pool + nodes;
                nodes++;
                tree->left->up = tree;
                tree->left->symbol = tree->symbol + '0';
                tree->right = pool + nodes;
                nodes++;
                tree->right->up = tree;
                tree->right->symbol = tree->symbol + '1';
            }
            if(tree->left->v != n + i && tree->left->leaf == 0){
                if(j+1 != len.at(i)){
                tree->left->v = n + i; //左ノードを訪問済みに変更
                tree = tree->left; //左ノードに移動する
                }
                else if(j+1 == len.at(i)){
                    tree->left->leaf = 1; //左ノードを葉とする
                    cw.at(i) = tree->left->symbol; //i番目の符号語は左ノードに対応する記号列
                }
            }
            else if(tree->right->leaf == 0 && tree->right->v != n + i){
                if(j+1 != len.at(i)){
                tree->right->v = n + i; //右ノードを訪問済みに変更
                tree = tree->right; //右ノードに移動
                }
                else if(j+1 == len.at(i)){
                    tree->right->leaf = 1; //右ノードを葉とする
                    tree->leaf = 1; //子ノードがどちらも葉になったら今後の探索においてそのノードを探索しなくてよいので、現在のノードも(便宜的に)葉に変更
                    cw.at(i) = tree->right->symbol; //i番目の符号語は右ノードに対応する記号列
                }
            } else {
                tree = pool; //もし左右どちらのノードも探索済みだったら根に戻って探索を再開する
            }
        }
    }

    /*生成した符号語の出力*/
    for(int i=0;i<n;i++){
        cout << "cw for p_" << i+1 << ": " << cw.at(i) << endl;
    }

    /*エントロピーと平均符号長の出力*/
    cout << fixed;
    cout << "entropy: " << setprecision(6) << e << endl;
    cout << "average length: " << setprecision(6) << ave_len << endl; 
    return 0;
}