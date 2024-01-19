// プログラミング言語:C++
// コンパイル方法:g++ -std=c++17 22_12485-05-01.cpp
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
	string plain_text;
	string cipher_text;
	string decipher_text;
	int table[256], inv_table[256];
	int t_table[256], t_inv_table[256];
	int KEY;
	int i, j, t;

	/*平文ファイルオープン*/
    ifstream ifs("plaintext_.txt");
    if(!ifs){ 
        cout << "file not open";
    }
    ofstream fo_e("cipher_.txt");
    if(!fo_e){
        cout << "er";
    }
    ofstream fo_d("decipher_.txt");
    if(!fo_d){
        cout << "er";
    }
    ofstream fo_t("subcipher_table_.txt");
    if(!fo_t){
        cout << "er";
    }
    ofstream fo_it("subcipher_inv_table_.txt");
    if(!fo_it){
        cout << "er";
    }
    ofstream fo_t_a("subcipher_table_a_.txt");
    if(!fo_t_a){
        cout << "er";
    }
    ofstream fo_it_a("subcipher_inv_table_a_.txt");
    if(!fo_it_a){
        cout << "er";
    }

	/*平文ファイルの読み込み、表示*/
	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "********    Plaintext data is displayed.   **********" << endl;
	cout << "*****************************************************" << endl;
    cout << endl;
    cout << endl;

	while(getline(ifs, plain_text)){
		cout << plain_text;
	}

	/* 暗号鍵の設定 */
	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "****             Input encryption key           ****" << endl;
	cout << "****         within 10 digit integer number     ****" << endl;
	cout << "*****************************************************" << endl;
    cout << endl;
    cout << endl;

	/*** ランダム換字テーブルの作成・保存 ****/

	/* ランダムテーブル鍵および初期値の入力・設定 */
	cin >> KEY;

	cout << "Encryption key = [" << KEY << "]\n\n";

	srand(KEY);

	for(i = 32; i < 128; i++){
		table[i] = i;
	}

	/*対象文字コードの設定*/
	/*スペース、カンマ、ピリオド、ハイフン*/
	t_table[0] = 32;
	t_table[1] = 44;
	t_table[2] = 46;
	t_table[55] = 45;

	/*A-Z*/
	for(i = 65; i < 91; i++){
		t_table[i - 62] = i;
	}

	/*a-z*/
	for(i = 97; i < 123; i++){
		t_table[i - 97 + 29] = i;
	}

	/*ランダム換字テーブルの設定*/
	for(i = 0;i < 56; i++){
		j = rand()%56;
		t = table[t_table[i]];
		table[t_table[i]] = table[t_table[j]];
		table[t_table[j]] = t;
	}


	/*ランダム換字テーブルの保存*/
	for(i = 32; i < 128; i++){
        fo_t << (char)i << ", " << (char)table[i] << endl;
	}

	for(i = 32; i < 128; i++){
        fo_t_a << i << ", " << table[i] << endl;
	}

	/*暗号化*/
	shuffle_ascii(plain_text, cipher_text, table);

	/*暗号ファイルの表示・書き込み*/
	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "**********    Cipher text is displayed.   ***********" << endl;
	cout << "*****************************************************" << endl;
    cout << endl;
    cout << endl;

	cout << cipher_text;
	fo_e << cipher_text;
	fo_e.flush();

	/* 復号鍵の設定 */
	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "****             Input decryption key           ****" << endl;
	cout << "****         within 10 digit integer number     ****" << endl;
	cout << "*****************************************************" << endl;
    cout << endl;
    cout << endl;

	/*** ランダム逆換字テーブルの作成・保存 ***/

	/*ランダムテーブルの鍵および初期値の入力・設定*/
	cin >> KEY;

	cout << "Decryption key = [" << KEY << "]\n\n";

	srand(KEY);

	for(i = 32; i < 128; i++){
		table[i] = i;
	}

	/* ランダム逆換字テーブルの設定 */
	for(i = 0;i < 56; i++){
		j = rand()%56;
		t = table[t_table[i]];
		table[t_table[i]] = table[t_table[j]];
		table[t_table[j]] = t;
	}

    /*逆換字テーブルの定義*/
    for(i = 32;i < 128; i++){
        inv_table[table[i]] = i; 
    }

	/* ランダム逆換字テーブルの保存 */
	for(i = 32; i < 128; i++){
		fo_it << (char)i << ", " << (char)inv_table[i] << endl;
	}

	for(i = 32; i < 128; i++){
        fo_it_a << i << ", " << inv_table[i] << endl;
	}

	/*復号*/
	shuffle_ascii(cipher_text, decipher_text, inv_table);

	/*復号ファイルの表示・書き込み*/
	cout << "\n\n";
	cout << "*****************************************************" << endl;
	cout << "*********    Decipher text is displayed.   **********" << endl;
	cout << "*****************************************************" << endl;
    cout << endl;
    cout << endl;

	cout << decipher_text;
	fo_d << decipher_text;
	fo_d.flush();

	cout << "\n\n";

	/*終了処理*/
	ifs.close();
	fo_e.close();
    fo_d.close();
	fo_t.close();
	fo_it.close();
	fo_t_a.close();
	fo_it_a.close();

	cout << "[End of substitution_cipher]" << endl;
    cout << endl;

    return 0;
}