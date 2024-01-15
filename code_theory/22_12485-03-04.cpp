// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-03-04.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
03-04 (b)
M=65536
R=0.5
d_min=5
G'=
10000000000000000110111000001000
01000000000000000001011010001001
00100000000000001011100011011011
00010000000000000111111011000011
00001000000000000000101011100111
00000100000000000100011101001001
00000010000000001001100110101101
00000001000000001010011101110011
00000000100000001101111010001101
00000000010000000011001000100111
00000000001000000011100110000100
00000000000100001001010110111010
00000000000010001001111110000011
00000000000001000110110101000101
00000000000000100000101111000100
00000000000000011001101100110011
H'=
00100011100110011000000000000000
10010100100001000100000000000000
10110001011001000010000000000000
01110010111110010001000000000000
10111010101011110000100000000000
11010101100111000000010000000000
11011101110010110000001000000000
00000111001111110000000100000000
01111010101110100000000010000000
00111101000001100000000001000000
00001011010100010000000000100000
00100001000100010000000000010000
11100110100100000000000000001000
00001010111001100000000000000100
00111001010110010000000000000010
01111111110011010000000000000001
G(H')^T=
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
G'(H')^T=
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
0000000000000000
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
関数 ten_two
intで入力された数値を2進数に変換してstringで返す関数
表示桁数はk
入力num: この値を2進数に変換する
*/
string ten_two(int k, int num){
    string ans;
    for(int i=0;i<k;i++){
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

/*
関数 add_vec
入力された二つの長さが等しいベクトルの各成分を足した結果を出力する
length : ベクトルの長さ
vec1 : たすベクトル1つめ
vec2 : たすベクトル2つめ
result : 足した結果をここに入れる
*/
void add_vec(int length, vector<int> &vec1, vector<int> &vec2, vector<int> &result){
    for(int i=0;i<length;i++){
        int temp = vec1.at(i)+ vec2.at(i);
        result.at(i) = temp%2;
    }
}

/*
関数 t_mat
行列を転置する
n : 転置する行列の行数
m : 転置する行列の列数
matrix : 転置する行列
matrix_t : matrixの転置結果
*/
void t_mat(int n, int m, vector<vector<int>> &matrix, vector<vector<int>> &matrix_t){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            matrix_t.at(j).at(i) = matrix.at(i).at(j);
        }
    }
}
/*
関数 t_mult
行列mat1, mat2についてmat1*mat2を計算する
n1 : mat1の行数
m1 : mat1の列数
n2 : mat2の行数
m2 : mat2の列数
mat1 : かけられる行列
mat2 : かける行列
result : mat1*mat2の結果

正しく出力したら0を返す
掛け算が実行できない行列が入力されたら-1を返して終了する
*/
int mat_mult(int n1, int m1, int n2, int m2, vector<vector<int>> &mat1, vector<vector<int>> &mat2, vector<vector<int>> &result){
    if(m1 != n2){
        return -1;
    } else {
        for(int i=0;i<n1;i++){
            for(int j=0;j<m2;j++){
                for(int k=0;k<m1;k++){
                    result.at(i).at(j) += mat1.at(i).at(k)*mat2.at(k).at(j);
                }
                result.at(i).at(j) = result.at(i).at(j)%2;
            }
        }
        return 0;
    } 
}

int main(void){
    int n = 0; // 符号長
    int m = 0; // 符号の要素数
    int k = 0; // 次元
    double r = 0; // 符号化率
    int d = 0; // 最小距離
    string temp = "";

    /*符号長、要素数の受け取り*/
    cout << "n=";
    cin >> n;
    cout << "k=";
    cin >> k;

    d = n; // 最小距離は考えられる最大値であるnで初期化する

    m = pow(2, k); // 符号語数の計算
    r = (double)k/n; // 符号化率の計算

    vector<vector<int>> g(k, vector<int>(n)); // 生成行列
    vector<vector<int>> g_(k, vector<int>(n)); // 標準型生成行列
    vector<vector<int>> h_(n-k, vector<int>(n)); // 標準型パリティ検査行列
    vector<vector<int>> h_t(n, vector<int>(n-k)); // h_を転置した行列
    vector<vector<int>> result1(k, vector<int>(n-k)); // g*h_tの結果
    vector<vector<int>> result2(k, vector<int>(n-k)); // g_*h_tの結果
    vector<vector<int>> vec(m, vector<int>(k)); // 長さkのベクトル全パターン

    /*生成行列の入力*/
    cout << "G=" << endl;
    for(int i=0;i<k;i++){
        cin >> temp;
        for(int j=0;j<n;j++){
            if(temp.at(j) == '0') g.at(i).at(j) = 0;
            else if(temp.at(j) == '1') g.at(i).at(j) = 1;
        }
    }

    /*生成行列のコピーを作っておく*/
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            g_.at(i).at(j) = g.at(i).at(j);
        }
    }

    /*長さkのベクトル全パターンを生成 O(2^k)なのでkが20程度まででないと終わらなくなる*/
    for(int i=0;i<m;i++){
        string temp = ten_two(k, i);
        for(int j=0;j<k;j++){
            vec.at(i).at(j) = temp.at(j) - '0';
        }
    }

    /*最小距離を求める 生成した長さkの全ベクトルを符号化して実際に調べる*/
    int cnt_d = 0; // ハミング重みを調べるカウンタ
    int c = 0; // 作業用変数
    for(int i=0;i<m;i++){
        for(int j=0;j<n;j++){
            c = 0;
            for(int l=0;l<k;l++){
                c += vec.at(i).at(l)*g.at(l).at(j);
            }
            if(c%2 == 1) cnt_d++; // 符号化結果に1の要素があるたびにインクリメント
        }
        if(cnt_d < d && cnt_d != 0) d = cnt_d; // より小さいハミング重みが見つかったらdを更新
        cnt_d = 0;
    }

    vector<int> tempvec(n); // 作業用配列
    /*行の入れ替えと基本変形で標準型生成行列を求める*/
    for(int i=0;i<k;i++){
        for(int j=i;j<k;j++){
            /*i番目の成分が1である行をi列目以下の行の中から探索*/
            if(g_.at(j).at(i) == 1){
                /*i番目の成分が1である行が見つかったらi行目とその行を入れ替える*/
                tempvec = g_.at(j);
                g_.at(j) = g_.at(i);
                g_.at(i) = tempvec;
                /*i列目のi行i列成分以外の成分を全て0にする*/
                for(int i_=0;i_<k;i_++){
                    if(g_.at(i_).at(i) == 1 && i_ != i){
                        add_vec(n, g_.at(i), g_.at(i_), g_.at(i_));
                    }
                }  
                break;
            }
        }
    }

    /*標準型パリティ検査行列を求める*/
    /*P^t部分の入力*/
    for(int i=0;i<k;i++){
        for(int j=0;j<n-k;j++){
            h_.at(j).at(i) = g_.at(i).at(k+j);
        }
    }
    /*単位行列部分の入力*/
    for(int i=0;i<n-k;i++){
        for(int j=0;j<n-k;j++){
            if(i == j) h_.at(i).at(k+j) = 1;
            else h_.at(i).at(k+j) = 0;
        }
    }

    t_mat(n-k, n, h_, h_t); // パリティ検査行列を転置

    /*mat_multを用いて生成行列とパリティ検査行列の積を計算*/
    mat_mult(k, n, n, n-k, g, h_t, result1);
    mat_mult(k, n, n, n-k, g_, h_t, result2);

    /*符号語数,符号化率,最小距離の出力*/
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "M=" << m << endl;
    cout << "R=" << r << endl;
    cout << "d_min=" << d << endl;

    /*標準型生成行列の出力*/
    cout << "G'=" << endl;
    for(int i=0;i<k;i++){
        for(int j=0;j<n;j++){
            cout << g_.at(i).at(j);
        }
        cout << endl;
    }

    /*標準型パリティ検査行列の出力*/
    cout << "H'=" << endl;
    for(int i=0;i<n-k;i++){
        for(int j=0;j<n;j++){
            cout << h_.at(i).at(j);
        }
        cout << endl;
    }

    /*生成行列と標準型パリティ検査行列(の転置)の積の出力*/
    cout << "G(H')^T=" << endl;
    for(int i=0;i<k;i++){
        for(int j=0;j<n-k;j++){
            cout << result1.at(i).at(j);
        }
        cout << endl;
    }

    /*標準型生成行列と標準型パリティ検査行列(の転置)の積の出力*/
    cout << "G'(H')^T=" << endl;
    for(int i=0;i<k;i++){
        for(int j=0;j<n-k;j++){
            cout << result1.at(i).at(j);
        }
        cout << endl;
    }

    return 0;
}