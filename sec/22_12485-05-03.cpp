// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-05-03.cpp
// 実行方法:コンパイルで生成したa.outというファイルを実行
// (Ubuntu 20.04.06 LTSで"./a.out"で実行できることを確認した)

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void shuffle_ascii(string &input, string &output, int *tbl){

	/*asciiコードは32~127の96個*/

	int i, j, t;
	int len;

	/*平文文字列の長さ*/
	len = input.length();

	/*暗号化/復号*/
	for(i = 0; i < len; i++){
        char tmp = tbl[input[i]];
        output.push_back(tmp);
	}
}

int main(void){
	string cipher_text;
	string decipher_text;
    FILE *fp_it;
	int inv_table[256];
	int i;

	/* ファイルオープン */
    ifstream fp_e("cipher_p.txt");
    if(!fp_e){
        cout << "file not open";
    }
    if((fp_it = fopen("subcipher_inv_table_a_p.txt", "r")) == NULL){
        cout << "file not open";
    }
    ofstream fo_d("decipher_p.txt");
    if(!fo_d){
        cout << "er";
    }

	/* 暗号化ファイルの読み込み・表示 */
	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "********    Ciphertext data is displayed.   *********" << endl;
	cout << "*****************************************************" << endl;
    cout << "\n\n";

	while (getline(fp_e, cipher_text)){
		cout << cipher_text;
	}

	/*** 復号テーブルの読み込み・表示　***/

	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "********    Dicipher talbe is displayed.   **********" << endl;
	cout << "*****************************************************" << endl;
    cout << "\n\n";


	/* 復号テーブルの読み込み */
	for(i = 32; i < 128; i++){
        fscanf(fp_it,"%d, %d\n",&i, &inv_table[i]);
		cout << '[' << i << ", " << inv_table[i] << ']' << endl;
	}

	/* 復号 */
	shuffle_ascii(cipher_text, decipher_text, inv_table);

	/* 復号ファイルの表示・書き込み */
	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "*********    Decipher text is displayed.   **********" << endl;
	cout << "*****************************************************" << endl;
    cout << "\n\n";

	/* 復号ファイルの書き込み */
	cout << decipher_text;
	fo_d << decipher_text;
	fo_d.flush();

	printf("\n\n");

	/* 終了処理 */
	fp_e.close();
	fclose(fp_it);
	fo_d.close();

	printf("[End of analyze_subcipher]\n\n");

    return 0;
}