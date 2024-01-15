// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-03-05.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

/*
03-05 (b)
A(X,Y)=
X^{64} + 3X^{41}Y^{23} + 3X^{40}Y^{24} 
+ 6X^{39}Y^{25} + 7X^{38}Y^{26} + 19X^{37}Y^{27} 
+ 16X^{36}Y^{28} + 10X^{35}Y^{29} + 31X^{34}Y^{30} 
+ 22X^{33}Y^{31} + 21X^{32}Y^{32} + 26X^{31}Y^{33} 
+ 16X^{30}Y^{34} + 22X^{29}Y^{35} + 16X^{28}Y^{36} 
+ 12X^{27}Y^{37} + 9X^{26}Y^{38} + 5X^{25}Y^{39} 
+ 5X^{24}Y^{40} + 2X^{23}Y^{41} + X^{22}Y^{42} 
+ X^{21}Y^{43} + 2X^{20}Y^{44} 
B(X,Y)=
X^{64} + 10X^{62}Y^{2} + 142X^{61}Y^{3} 
+ 2457X^{60}Y^{4} + 29775X^{59}Y^{5} + 292948X^{58}Y^{6} 
+ 2428124X^{57}Y^{7} + 17287905X^{56}Y^{8} + 107574778X^{55}Y^{9} 
+ 591704806X^{54}Y^{10} + 2904655842X^{53}Y^{11} + 12828944073X^{52}Y^{12} 
+ 51316014465X^{51}Y^{13} + 186936199792X^{50}Y^{14} + 623120671160X^{49}Y^{15} 
+ 1908309094309X^{48}Y^{16} + 5388164860724X^{47}Y^{17} + 14069095209962X^{46}Y^{18} 
+ 34062025918670X^{45}Y^{19} + 76639554783421X^{44}Y^{20} + 160578108163663X^{43}Y^{21} 
+ 313857223887964X^{42}Y^{22} + 573130576781892X^{41}Y^{23} + 979098059911925X^{40}Y^{24} 
+ 1566556930278102X^{39}Y^{25} + 2349835367096342X^{38}Y^{26} + 3307175640083986X^{37}Y^{27} 
+ 4370196475467805X^{36}Y^{28} + 5425071549308697X^{35}Y^{29} + 6329249996351400X^{34}Y^{30} 
+ 6941758027899024X^{33}Y^{31} + 7158688099951363X^{32}Y^{32} + 6941758156300568X^{31}Y^{33} 
+ 6329250020122414X^{30}Y^{34} + 5425071456360602X^{29}Y^{35} + 4370196436432267X^{28}Y^{36} 
+ 3307175685715621X^{27}Y^{37} + 2349835408467340X^{26}Y^{38} + 1566556919065252X^{25}Y^{39} 
+ 979098027173251X^{24}Y^{40} + 573130573949958X^{23}Y^{41} + 313857243687554X^{22}Y^{42} 
+ 160578112195542X^{21}Y^{43} + 76639545763835X^{20}Y^{44} + 34062024027995X^{19}Y^{45} 
+ 14069098178144X^{18}Y^{46} + 5388165442104X^{17}Y^{47} + 1908308443287X^{16}Y^{48} 
+ 623120452980X^{15}Y^{49} + 186936283102X^{14}Y^{50} + 51316139786X^{13}Y^{51} 
+ 12828936031X^{12}Y^{52} + 2904597053X^{11}Y^{53} + 591707460X^{10}Y^{54} 
+ 107592124X^{9}Y^{55} + 17287527X^{8}Y^{56} + 2425194X^{7}Y^{57} 
+ 292738X^{6}Y^{58} + 30006X^{5}Y^{59} + 2527X^{4}Y^{60} 
+ 139X^{3}Y^{61} + 8X^{2}Y^{62} 
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
関数 code_gen
生成行列を用いて符号化を行う
[入力]
code: ここに符号化結果が入る
pln: 符号化するベクトル
g: 生成行列
k: gが表す符号の次元
n: 符号長
*/
void code_gen(vector<int> &code, vector<int> pln, vector<vector<int>> g, int k, int n){
    for(int i=0;i<n;i++){
        code.at(i) = 0; // 初期化
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<k;j++){
            code.at(i) += pln.at(j)*g.at(j).at(i);
        }
        code.at(i) = code.at(i)%2;
    }
}

long long int comb[64][64]; // 二項係数nCrを格納する2次元配列
/*
関数 nck
動的計画法を用いて二項係数nCrをオーバーフローしないように計算する
[入力]
n: どこまで計算するかを指定

nCk = n-1Ck-1 + n-1Ckという関係式を使って階乗計算を回避している
(このように計算しないと計算途中でオーバーフロー)
*/
void nck(int n){
    for(int i=0;i<n+1;i++){
        comb[i][0] = 1;
        comb[i][i] = 1;
    }
    for(int i=1;i<n+1;i++){
        for(int j=1;j<i;j++){
            comb[i][j] = comb[i-1][j-1] + comb[i-1][j];
        }
    }
}

int main(void){
    /*符号長、次元の入力*/
    int n = 0; // 符号長
    cout << "n=";
    cin >> n;
    int dim = 0; // 次元
    cout << "k=";
    cin >> dim;

    int m = pow(2, dim);

    vector<vector<int>> g(dim, vector<int>(n)); // 生成行列
    vector<vector<int>> vec(m, vector<int>(dim)); // 長さkのベクトルを全て格納する
    vector<int> ham(n+1, 0); // Cの重み分布 i番目の要素はハミング重みiの符号語の数

    /*生成行列の入力*/
    for(int i=0;i<dim;i++){
        for(int j=0;j<n;j++){
            char c;
            cin >> c;
            g.at(i).at(j) = c - '0';
        }
    }

    /*次元kに対し、長さkのベクトルを全て生成*/
    for(int i=0;i<m;i++){
        string temp = ten_two(dim, i);
        for(int j=0;j<dim;j++){
            vec.at(i).at(j) = temp.at(j) - '0';
        }
    }

    /*vecの要素を実際に生成行列で符号化 生成された符号語のハミング重みを調べる*/
    vector<int> temp(n);
    int cnt = 0;
    for(int i=0;i<m;i++){
        cnt = 0;
        code_gen(temp, vec.at(i), g, dim, n);
        for(int i=0;i<n;i++){
            if(temp.at(i) == 1) cnt++;
        }
        ham.at(cnt)++;
    }

    /*生成行列Gで表される符号の重み分布多項式A(X,Y)を出力*/
    int z = 0; // 見やすいように適度に改行を入れるためのカウンタ 問題の本質には関係なし
    cout << endl;
    cout << "OUTPUT:" << endl;
    cout << "A(X,Y)=" << endl;
    for(int i=0;i<=n;i++){
        if(ham.at(i) != 0){
            if(i == 0){
                if(ham.at(i) == 1){
                    cout << "X^{" << n-i << "} ";
                    z++;
                } else {
                    cout << "+ " << ham.at(i) << "X^{" << n-i << "} ";
                    z++;
                }
            }
            else if(i == n){
                if(ham.at(i) == 1){
                    cout << "+ " << "Y^{" << i << "} ";
                    z++;
                } else {
                    cout << "+ " << ham.at(i) << "Y^{" << i << "} ";
                    z++;
                }
            } else {
                if(ham.at(i) == 1){
                    cout << "+ " << "X^{" << n-i << "}Y^{" << i << "} ";
                    z++;
                } else {
                    cout << "+ " << ham.at(i) << "X^{" << n-i << "}Y^{" << i << "} ";
                    z++;
                }
            }
            if(z%3 == 0 && z != 0) cout << endl; // 3つ項を出力するたびに改行(見やすくするため)
        }
    }
    cout << endl;

    nck(n); // 二項係数の事前計算
    /*MacWilliamsの恒等式を用いてB(X,Y)を求める*/
    vector<long long int> ham_(n+1, 0); // Cの双対符号の重み分布
    for(int i=0;i<=n;i++){
        vector<long long int> temp1(n-i+1, 0);
        vector<long long int> temp2(i+1, 0);
        if(ham.at(i) != 0){
            for(int j=0;j<=n-i;j++){
                nck(n-i);
                temp1.at(j) = comb[n-i][j]; // 関数nckで事前計算した二項係数を呼び出している
            }
            for(int j=0;j<=i;j++){
                temp2.at(j) = comb[i][j]*pow(-1, i-j); // 関数nckで事前計算した二項係数を呼び出している
            }
            
            for(int j=0;j<=n-i;j++){
                for(int k=0;k<=i;k++){
                    ham_.at(n-j-k) += temp1.at(j)*temp2.at(k)*ham.at(i);
                }
            }
        } 
    }
    for(int i=0;i<n+1;i++){
        ham_.at(i) = ham_.at(i)/m;
    }

    /*生成行列Gで表される符号の双対符号の重み分布多項式B(X,Y)を出力*/
    z = 0; // 見やすいように適度に改行を入れるためのカウンタ 問題の本質には関係なし
    cout << "B(X,Y)=" << endl;
    for(int i=0;i<=n;i++){
        if(ham_.at(i) != 0){
            if(i == 0){
                if(ham_.at(i) == 1){
                    cout << "X^{" << n-i << "} ";
                    z++;
                } else {
                    cout << "+ " << ham_.at(i) << "X^{" << n-i << "} ";
                    z++;
                }
            }
            else if(i == n){
                if(ham_.at(i) == 1){
                    cout << "+ " << "Y^{" << i << "} ";
                    z++;
                } else {
                    cout << "+ " << ham_.at(i) << "Y^{" << i << "} ";
                    z++;
                }
            } else {
                if(ham_.at(i) == 1){
                    cout << "+ " << "X^{" << n-i << "}Y^{" << i << "} ";
                    z++;
                } else {
                    cout << "+ " << ham_.at(i) << "X^{" << n-i << "}Y^{" << i << "} ";
                    z++;
                }
            }
            if(z%3 == 0 && z != 0) cout << endl; // 3つ項を出力するたびに改行(見やすくするため)
        }
    }
    cout << endl;

    return 0;
}