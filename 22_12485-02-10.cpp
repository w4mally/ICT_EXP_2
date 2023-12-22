// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-02-10.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
実行結果
[入力]
symbols> LZ77_and_LZ78_are_the_two_lossless_data_compression_algorithms_published_in_papers_by_Abraham_Lempel_and_Jacob_Ziv_in_1977_and_1978._They_are_also_known_as_LZ1_and_LZ2_respectively._These_two_algorithms_form_the_basis_for_many_variations_including_LZW,_LZSS,_LZMA_and_others._Besides_their_academic_influence,_these_algorithms_formed_the_basis_of_several_ubiquitous_compression_schemes,_including_GIF_and_the_DEFLATE_algorithm_used_in_PNG_and_ZIP.
codewords> 010101000011010000001100101000111100100001011111000011000010000111001001101011111000001100010000001101111000001110100001001011111101101101000001101101111011101100101101101101001000000110001100110011011000000001101100001000101111100000011001000000001101001100010111010010110011011110000001101110001100111001010100011000110101001100100000110111001000000011100110000000101110
[出力]
encoded: 0100110000101101000001101111101011111000011000010000110111000001100100000010111110001010110100011001110001000011000010000011100100000011001011000011101000000011010001101010111110000001110100000000111011100000011011110100001101100100110111001100000011100110000001101100011010111001110110010111110011101100001100010110000101000011000111001101101101000000111000001100011001011011001110011000000011010010100110110111000101101101100000000011001110100110111001010000101110100001111011011010110010111000000000001110101000000011000100101110110100101011001101000001101011001000010000110100100011001011111011110011000010111100110010100110001110011001000011000100000000111100100100001000001101010011100100001010110100000010101101101001000010011000011010110110111000101101100001011011011100001110101111100000001001010000101011000110100110110001000010000101101001000010111011001011100110111000010000011000100000000011100100000110011011101111000110010010001000011100100010100010111000010000101010000011110110010101101000101111100001010111001000100000110000100101110111001100100110101111100000000110101100001100110111100100100110111000010110111001101110010101101000000000011000110001110101111100010010011001000010000111001000110000111000000011010110001100100010110100100000000111011000011010110110001101000010111010010100110100000110000110010100011100111011110100000110000100101110110011101001010110100100100010110100000000000110110100110010110011001001010110110100011100110100000100000110001000001010111001101000010111001100010000110011001001010101111111001110110000100001100111100100010000111011010011010110100100001010111010001000010110111100001100111001110000110110001100101110111010100001110110100100001100110011110101010101011100000000010110010101010101001100000000101001111111000101111100010010100110100000000010000010101011101101111011001100110010100110010001011100000100001000010000110000110100100000111011001010001100101110100010010110110100100001100010111110011111101100001100001110110110100100001011000110100001101100110011110000110010100000110011000110000110100101100011010100110010100010110011001010010001101100111011001010111010000100111011100110110111001101111000011000110110100101101010111111000001101011111001010100110000100010110011010010001100101101111000000000110011000001000011100110000110101110110000011010111001000000101011011000000100001110101001010100110100100000000011100010010100101101001000100010110111100101001011100110001110001101111011001110111000000011111011100111001110001101111001011110111001100000000011000110100101101101101000110000010110001110111011011000010100101100100001000010110111000100100010111110000000001000111000000000100100100000000010001100101011101110100010010110101111100000000010001000000000001000101101101110100110010000001010101001011101101011111101000100110011110010101011010000110011101011111101010000110010100111101011010010010111101010000000000000100111010110101010111110000010101101110001111010101101010110110010100000000000000101110
decoded: They_are_both_theoretically_dictionary_coders.
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
入力s: 2進数を表す文字列
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
/*
関数 ten_two
intで入力された数値を2進数に変換してstringで返す関数
表示桁数はceil(log_2(cnt))
入力num: この値を2進数に変換する
入力cnt: これを使って表示桁数を決める
*/
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

    /*生成した中間符号語を用いて符号化を行う*/
    int enc_cnt = 1;
    /*枝をたどっている途中に記号列の末尾に到達することがなかった場合*/
    if(flag == 0){
        for(int i=0;i<(int)midcode_num.size();i++){
            /*最初はASCIIコードのみを符号語とする*/
            if(i == 0){
                int first_asc = midcode_sym.at(i);
                string str(bitset<8>(first_asc).to_string()); //最初の中間符号語の第2要素を8桁の2進数にする
                enc += str;
                enc_cnt++;
            } else {
                int temp_num_enc = midcode_num.at(i);
                string num_str = ten_two(enc_cnt, temp_num_enc); //中間符号語の第1要素を2進数にする
                enc += num_str; //第1要素を2進数にしたものを符号語の末尾に追加
                int num_to_two = midcode_sym.at(i); //
                string str2(bitset<8>(num_to_two).to_string()); //中間符号語の第2要素を8桁の2進数にする
                enc += str2; //第2要素を2進数にしたものを符号語の末尾に追加
                enc_cnt++;
            }
        }
    } 
    /*枝をたどっている途中に記号列の末尾に到達することがあった場合*/
    /*基本は上と同じ*/
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

    /*符号化結果の出力*/
    cout << "encoded: " << enc << endl;

    /*＊＊＊復号部分＊＊＊*/
    int cw_len = 0;
    string cw = ""; 
    string dec = ""; //復号結果はここに入れる
    string temp_num_ = "";
    string temp_char_ = "";
    vector<int> node_num; //中間符号語の第1要素を格納する配列
    vector<char> node_char; //中間符号語の第2要素を格納する配列
    int cnt_dec = 1; // 復号に使うカウント変数

    cout << "codewords> ";
    cin >> cw;

    /*
    符号語から中間符号語を復元
    中間符号語に変換した部分は符号語から削除
    符号語が空になるまで繰り返す
    */
    while(cw.empty() == 0){
        /*最初は第2要素だけ*/
        if(cnt_dec == 1){
            temp_char_ = cw.substr(0,8); // 符号語から先頭8文字を切り出す
            node_num.push_back(0); // 第1要素は必ず0
            node_char.push_back(ascii_to_char(temp_char_)); // 符号語先頭8文字をアスキーコードと見たときにそれが指している文字を第2要素として格納
            cw.erase(0,8);
            temp_char_ = "";
            cnt_dec++;
        } else {
            temp_num_ = cw.substr(0, ceil(log2(cnt_dec))); // 第1要素の桁数はceil(log2(cnt_dec))　その分だけ先頭から切り出す
            node_num.push_back(two_ten(temp_num_)); // 切り出した第1要素分の2進数を10進数に変換して格納
            cw.erase(0,ceil(log2(cnt_dec))); // 第1要素が格納できたらその分は削除
            temp_char_ = cw.substr(0,8); // 符号語から先頭8文字を切り出す
            node_char.push_back(ascii_to_char(temp_char_)); // 切り出した8文字をアスキーコードと見たときにそれが指している文字を第2要素として格納
            cw.erase(0,8); // 第2要素が格納出来たらその分は削除
            temp_num_ = "";
            temp_char_ = "";
            cnt_dec++;
        }
        /*
        符号化の際に、枝をたどっている途中に記号列の末尾に到達することがあったような符号を扱うときの例外処理
        node_numの末尾に最後の参照番号を10進数にして追加
        node_charの末尾は存在しないが、添え字の最大値をそろえるためにnull文字を末尾に追加
        */
        if((int)cw.size() == ceil(log2(cnt_dec))){
            temp_num_ = cw;
            node_num.push_back(two_ten(temp_num_));
            node_char.push_back('\0');
            cw = "";
            temp_num_ = "";
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