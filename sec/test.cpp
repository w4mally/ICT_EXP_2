#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip>
#include <map>
#include <queue>
#include <bitset>
#include <algorithm>
#include <fstream>
using namespace std;

int main(void){
    string name;
    string plain_text;
    string decipher;

    // cout << "Filename?>";
    // cin >> name;
    ifstream ifs("plaintext.txt");
    if(!ifs){ 
        cout << "file not open";
    }
    ifstream ifs_("decipher.txt");
    if(!ifs_){ 
        cout << "file not open";
    }

    cout << "plaintext: " << endl;
    while(getline(ifs, plain_text)){
		cout << plain_text;
	}
    cout << endl;
    cout << "result: " << endl;
    while(getline(ifs_, decipher)){
		cout << decipher;
	}

    int cnt = 0;
    for(int i=0;i<(int)plain_text.length();i++){
        if(plain_text.at(i) != decipher.at(i)){
            cnt++;
        } 
    }
    cout << endl;
    cout << "err: " << cnt << endl;

    ifs.close();
    ifs_.close();
    return 0;
}