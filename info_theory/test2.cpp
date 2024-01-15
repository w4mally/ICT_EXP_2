#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
using namespace std;

char ascii_to_char(string s){
    int ascii = 0;
    for(int i=7;i>=0;i--){
        if(s.at(i) == '1') ascii += pow(2,7-i);
    }
    char ans = ascii;
    return ans;
}

int two_ten(string s){
    int ans = 0;
    int size = s.size();
    for(int i=size-1;i>=0;i--){
        if(s.at(i) == '1') ans += pow(2,size-1-i);
    }
    return ans;
}

int main(void){
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
}