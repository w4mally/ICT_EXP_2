// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-02-05.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
symbols> LZ77_and_LZ78_are_the_two_lossless_data_compression_algorithms_published_in_papers_by_Abraham_Lempel_and_Jacob_Ziv_in_1977_and_1978._They_are_also_known_as_LZ1_and_LZ2_respectively._These_two_algorithms_form_the_basis_for_many_variations_including_LZW,_LZSS,_LZMA_and_others._Besides_their_academic_influence,_these_algorithms_formed_the_basis_of_several_ubiquitous_compression_schemes,_including_GIF_and_the_DEFLATE_algorithm_used_in_PNG_and_ZIP.
codewords length> 10
node: 0
symbol: L
node: 0
symbol: Z
node: 0
symbol: 7
node: 3
symbol: _
node: 0
symbol: a
node: 0
symbol: n
node: 0
symbol: d
node: 0
symbol: _
node: 1
symbol: Z
node: 3
symbol: 8
[出力]
encoded: (0, L) (0, Z) (0, 7) (3, _) (0, a) (0, n) (0, d) (0, _) (1, Z) (3, 8) (8, a) (0, r) (0, e) (8, t) (0, h) (13, _) (0, t) (0, w) (0, o) (8, l) (19, s) (0, s) (0, l) (13, s) (22, _) (7, a) (17, a) (8, c) (19, m) (0, p) (12, e) (22, s) (0, i) (19, n) (11, l) (0, g) (19, r) (33, t) (15, m) (25, p) (0, u) (0, b) (23, i) (22, h) (13, d) (8, i) (6, _) (30, a) (30, e) (12, s) (8, b) (0, y) (8, A) (42, r) (5, h) (5, m) (8, L) (13, m) (49, l) (11, n) (7, _) (0, J) (5, c) (19, b) (8, Z) (33, v) (46, n) (8, 1) (0, 9) (3, 7) (60, d) (68, 9) (10, .) (8, T) (15, e) (52, _) (5, r) (16, a) (23, s) (19, _) (0, k) (6, o) (18, n) (11, s) (57, Z) (0, 1) (71, _) (9, 2) (8, r) (24, p) (13, c) (17, i) (0, v) (13, l) (52, .) (74, h) (24, e) (14, w) (80, a) (23, g) (37, i) (17, h) (0, m) (25, f) (37, m) (14, h) (16, b) (5, s) (33, s) (8, f) (37, _) (103, a) (6, y) (8, v) (77, i) (5, t) (33, o) (6, s) (67, c) (23, u) (7, i) (6, g) (85, W) (0, ,) (85, S) (0, S) (124, _) (9, M) (0, A) (87, o) (102, e) (50, .) (8, B) (24, i) (7, e) (25, t) (75, i) (12, _) (63, a) (135, m) (33, c) (67, f) (120, e) (6, c) (13, ,) (106, e) (22, e) (35, g) (101, t) (39, s) (110, o) (12, m) (45, _) (131, _) (42, a) (22, i) (25, o) (0, f) (8, s) (13, v) (13, r) (5, l) (8, u) (42, i) (0, q) (41, i) (17, o) (41, s) (28, o) (103, p) (31, s) (156, o) (47, s) (0, c) (75, m) (24, ,) (119, l) (41, d) (33, n) (36, _) (0, G) (0, I) (0, F) (87, t) (75, _) (0, D) (0, E) (183, L) (129, T) (187, _) (162, g) (149, h) (103, _) (168, e) (61, i) (47, P) (0, N) (181, _) (5, n) (61, Z) (182, P) (0, .)
decoded: LZ77_and_LZ78
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
    string s = "";
    int cnt = 1; //ノードの番号を記録 ノードを作るたびにインクリメント
    int flag = 0; //枝をたどっている途中で符号化する記号列の終端に達したかどうかを判定する
    cout << "symbols> ";
    cin >> s;
    
    vector<int> midcode_num; //中間符号語の番号を格納する配列
    vector<char> midcode_sym; //中間符号語の文字を格納する配列
    /*
    ノードを表す連想配列 
    key:対応文字列
    value:何番目に生成されたか、対応文字列の末尾から1文字取り除いた文字列が対応するノードの番号、対応文字列の末尾
    */
    map<string, tuple<int, int, char>> node;

    /*
    辞書作成、中間符号語の生成
    符号化する記号列について、符号化した部分は削除
    記号列が空になるまで続ける
    */
    while(s.empty() == 0){
        for(int i=1;i<=(int)s.size();i++){
            /*もし先頭からi文字切り取った文字列が辞書になかったら*/
            if(node.count(s.substr(0,i)) == 0){
                string temp = s.substr(0,i); //sの先頭i字を切り取り
                /*
                切り取ったのが2文字以上なら切り取った文字をkeyとして保存
                中間符号語としては
                (keyの末尾から1文字取り除いた文字列のノードの参照番号, keyの末尾)
                にあたるものを保存している
                */
                if(i>1){
                    node[s.substr(0,i)] = make_tuple(cnt, get<0>(node.at(s.substr(0,i-1))), temp.back());
                    midcode_num.push_back(get<0>(node.at(s.substr(0,i-1)))); //中間符号語出力用に参照番号を配列に保存
                    midcode_sym.push_back(temp.back()); //中間符号語出力用に切り取った文字列の末尾を配列に保存
                    cnt++;
                }
                /*
                切り取ったのが1文字でも同様にそれをkeyとして保存するが
                中間符号語としては
                (0, key)
                にあたるものを保存している
                (つまり新規に出現した文字)
                */
                else if(i==1){
                    node[s.substr(0,1)] = make_tuple(cnt, 0, temp.back());
                    midcode_num.push_back(0); //中間符号語出力用に0を参照番号として配列に保存
                    midcode_sym.push_back(temp.back()); //中間符号語出力用に切り取った1文字を配列に保存
                    cnt++;
                }
            s.erase(0,i); //中間符号語を生成した部分を削除
            break;
            }
            /*
            もし枝をたどっている途中に符号化する記号列の末尾に到達したらここの処理が行われる
            その時点の参照番号のみを保存
            flagを1にする
            */
            else if(node.count(s.substr(0,i)) == 1 && i == (int)s.size()){
                midcode_num.push_back(get<0>(node.at(s.substr(0,i))));
                flag = 1;
                cnt++;
                s.erase(0,i);
                break;
            }
        }
    }

    /*中間符号語の出力*/
    cout << "encoded: ";
    /*枝をたどっている途中に記号列の末尾に到達することがなかった場合*/
    if(flag == 0){
        for(int i=0;i<cnt-1;i++){
        cout << "(" << midcode_num.at(i) << ", " << midcode_sym.at(i) << ") ";
        }
        cout << endl;
    } 
    /*枝をたどっている途中に記号列の末尾に到達することがあった場合*/
    else if(flag == 1){
        for(int i=0;i<cnt-1;i++){
        if(i<cnt-2) cout << "(" << midcode_num.at(i) << ", " << midcode_sym.at(i) << ") ";
        else if(i == cnt-2) cout << "(" << midcode_num.at(i) << ") ";
        }
        cout << endl;
    }

    /*＊＊＊復号部分＊＊＊*/
    int cw_len = 0; 
    string dec = ""; //復号結果はここに入れる
    cout << "codewords length> ";
    cin >> cw_len;

    vector<int> node_num(cw_len); //中間符号語の第1要素を格納する配列
    vector<char> node_char(cw_len); //中間符号語の第2要素を格納する配列
    map<int, pair<int, char>> node_; //中間符号語を連想配列で保存 key:参照番号 value:第1要素,第2要素

    /*中間符号語の受け取り*/
    for(int i=0;i<cw_len;i++){
        cout << "node: ";
        cin >> node_num.at(i);
        cout << "symbol: ";
        cin >> node_char.at(i);
        node_[i+1] = make_pair(node_num.at(i), node_char.at(i));
    }

    /*
    復号を行う
    もし中間符号語の第1要素が0なら、その1文字を復号結果の末尾に追加
    そうでない場合
    1.現在見ている中間符号語の第2要素をtempの先頭に追加
    2.現在見ている中間符号語の第1要素が指しているノードに移動
    1.と2.をを第1要素が0になるまで繰り返す
    3.出来上がったtempを復号結果末尾に追加
    */
    string temp = "";
    int temp_num = 0;
    for(int i=0;i<cw_len;i++){
        if(node_num.at(i) == 0){
            dec += node_char.at(i);
        }
        else if(node_num.at(i) != 0){
            temp = "";
            temp_num = i+1;
            while(true){
                temp = node_.at(temp_num).second + temp; //1.
                if(node_.at(temp_num).first == 0) break; //第1要素が0だったら終了
                temp_num = node_.at(temp_num).first; //2.
            }
            dec += temp; //3.
        }
    }

    /*復号結果の出力*/
    cout << "decoded: " << dec << endl;
    
    return 0;
}