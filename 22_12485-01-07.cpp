// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-01-07.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
alphabet size> 6
l_1> 1
l_2> 2
l_3> 4
l_4> 8
l_5> 16
l_6> 32
[出力]
cw for l_1: 0
cw for l_2: 10
cw for l_3: 1100
cw for l_4: 11010000
cw for l_5: 1101000100000000
cw for l_6: 11010001000000010000000000000000
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//木構造を作る構造体
typedef struct node_t {
    struct node_t *up; //親を指すポインタ
    struct node_t *left; //左側の子を指すポインタ
    struct node_t *right; //右側の子を指すポインタ
    int v; //このノードに訪問したことがあるかを判定するための変数
    int leaf; //このノードが葉であるかを記録する変数
    string symbol; //このノードに対応する符号語
} *node; //この構造体のポインタをnodeで表す

int main(void){
    /*情報源アルファベットの要素数の受け取り*/
    int n = 0;
    cout << "alphabet size> ";
    cin >> n;

    vector<int> len(n); //符号語長を受け取る配列
    vector<string> cw(n); //生成した符号をいれる配列
    string buf;

    for(int i=0;i<n;i++){
        cout << "l_" << i+1 << "> ";
        cin >> len.at(i); //第i符号語の符号語長の受け取り
    }

    struct node_t pool[256] = {{0}}; //ノードの集合
    int nodes = 1; //ノード数
    node tree; //木

    /*
    なるべく左側のノードが優先されるように符号語の長さと一致する深さまで探索
    もし現在のノードの子ノードが葉でなくて、未探索ならそちらに移動(左ノード優先)
    現在のノードの子ノードが葉ではない&未探索&深さが指定された符号語の長さと一致ならそのノードを葉として符号語を記録
    子ノードが葉だった場合はそのノードを探索済みにして探索方向を切り替える
    左右のノードが探索済みだったら親に戻る
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
            if(tree->left->v != n + i){
                if(j+1 != len.at(i) && tree->left->leaf == 0){
                tree = tree->left; //左ノードに移動する
                tree->v = n + i; //左ノードを訪問済みに変更
                }
                else if(j+1 != len.at(i) && tree->left->leaf == 1){
                    tree->left->v = n + i; //左ノードを訪問済みに変更
                    j = j-1; //探索しなおし
                }
                else if(j+1 == len.at(i) && tree->left->leaf == 0){
                    tree->left->leaf = 1; //左ノードを葉とする
                    cw.at(i) = tree->left->symbol; //i番目の符号語は左ノードに対応する記号列
                    tree->left->v = n + i; //左ノードを訪問済みに変更
                }
                else if(j+1 == len.at(i) && tree->left->leaf == 1){
                    tree->left->v = n + i; //左ノードを訪問済みに変更
                    j = j-1; //探索しなおし
                }
            }
            else if(tree->right->v != n + i){
                if(j+1 != len.at(i) && tree->right->leaf == 0){
                tree = tree->right; //右ノードに移動する
                tree->v = n + i; //右ノードを訪問済みに変更
                }
                else if(j+1 != len.at(i) && tree->right->leaf == 1){
                    tree->right->v = n + i; //右ノードを訪問済みに変更
                    j = j-1; //探索しなおし
                }
                else if(j+1 == len.at(i) && tree->right->leaf == 0){
                    tree->right->leaf = 1; //右ノードを葉とする
                    cw.at(i) = tree->right->symbol; //i番目の符号語は右ノードに対応する記号列
                    tree->right->v = n + i; //右ノードを訪問済みに変更
                }
                else if(j+1 == len.at(i) && tree->right->leaf == 1){
                    tree->right->v = n + i; //右ノードを訪問済みに変更
                    j = j-1; //探索しなおし
                }
            } 
            else if(tree->left->v == n + i && tree->right->v == n + i){
                tree = tree->up; //親ノードに戻る
                j = j-2;
            }
        }
    }

    /*生成した符号語の出力*/
    for(int i=0;i<n;i++){
        cout << "cw for l_" << i+1 << ": " << cw.at(i) << endl;
    }

    return 0;
}