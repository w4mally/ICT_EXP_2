// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-02-10.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]

[出力]

*/

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <bitset>
#include <algorithm>
using namespace std;

/*
関数 ascii_to_char
入力s: アスキーコードを表す "01100001"など
sを10進数に変換してそのアスキーコードに対応する1文字を返す
*/
char ascii_to_char(string s){
    int ascii = 0;
    for(int i=7;i>=0;i--){
        if(s.at(i) == '1') ascii += pow(2,7-i);
    }
    char ans = ascii;
    return ans;
}

/*
関数 two_ten
入力s:　2進数を表す文字列
sが表す数値を10進数に変換してint型で返す
*/
int two_ten(string s){
    int ans = 0;
    int size = s.size();
    for(int i=size-1;i>=0;i--){
        if(s.at(i) == '1') ans += pow(2,size-1-i);
    }
    return ans;
}

string ten_two(int cnt, int num){
    string ans;
    for(int i=0;i<ceil(log2(cnt));i++){
        if(num%2 == 0){
            ans += '0';
        }
        else if(num%2 == 1){
            ans += '1';
        }
        num = num/2;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

int main(void){
    /*＊＊＊符号化部分＊＊＊*/
    string s = "";
    string enc = "";
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

    int enc_cnt = 1;
    /*枝をたどっている途中に記号列の末尾に到達することがなかった場合*/
    if(flag == 0){
        for(int i=0;i<(int)midcode_num.size();i++){
            if(i == 0){
                int first_asc = midcode_sym.at(i);
                string str(bitset<8>(first_asc).to_string());
                enc += str;
                enc_cnt++;
            } else {
                int temp_num_enc = midcode_num.at(i);
                string num_str = ten_two(enc_cnt, temp_num_enc); 
                enc += num_str;
                int num_to_two = midcode_sym.at(i);
                string str2(bitset<8>(num_to_two).to_string());
                enc += str2;
                enc_cnt++;
            }
        }
    } 
    /*枝をたどっている途中に記号列の末尾に到達することがあった場合*/
    else if(flag == 1){
        for(int i=0;i<(int)midcode_num.size();i++){
            if(i<(int)midcode_num.size()-1){
                if(i == 0){
                    int first_asc = midcode_sym.at(i);
                    string str(bitset<8>(first_asc).to_string());
                    enc += str;
                    enc_cnt++;
                } else {
                    int temp_num_enc = midcode_num.at(i);
                    string num_str = ten_two(enc_cnt, temp_num_enc); 
                    enc += num_str;
                    int num_to_two = midcode_sym.at(i);
                    string str2(bitset<8>(num_to_two).to_string());
                    enc += str2;
                    enc_cnt++;
                }
            }
            else if(i == (int)midcode_num.size()-1){
                int final_num = midcode_num.at(i);
                string final_str = ten_two(enc_cnt, final_num);
                enc += final_str;
            }
        }
    }

    cout << "encoded: " << enc << endl;

    /*＊＊＊復号部分＊＊＊*/
    int cw_len = 0;
    string cw = ""; 
    string dec = ""; //復号結果はここに入れる
    string temp_num_ = "";
    string temp_char_ = "";
    vector<int> node_num; //中間符号語の第1要素を格納する配列
    vector<char> node_char; //中間符号語の第2要素を格納する配列
    int cnt_dec = 1;

    cout << "codewords> ";
    cin >> cw;

    while(cw.empty() == 0){
        if(cnt_dec == 1){
            temp_char_ = cw.substr(0,8);
            node_num.push_back(0);
            node_char.push_back(ascii_to_char(temp_char_));
            cw.erase(0,8);
            temp_char_ = "";
            cnt_dec++;
        } else {
            temp_num_ = cw.substr(0, ceil(log2(cnt_dec)));
            node_num.push_back(two_ten(temp_num_));
            cw.erase(0,ceil(log2(cnt_dec)));
            temp_char_ = cw.substr(0,8);
            node_char.push_back(ascii_to_char(temp_char_));
            cw.erase(0,8);
            temp_num_ = "";
            temp_char_ = "";
            cnt_dec++;
        }
    }

    map<int, pair<int, char>> node_; //中間符号語を連想配列で保存 key:参照番号 value:第1要素,第2要素

    for(int i=0;i<(int)node_num.size();i++){
        node_[i+1] = make_pair(node_num.at(i), node_char.at(i));
    }

    cw_len = node_num.size();

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