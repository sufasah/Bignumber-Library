#include "bignumber.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
	bigNum n,n2;
	while(1)
	{
		cout << "1. sayi" << endl;
		string s1;
		getline(cin, s1);
		n.set(s1);
		cout << "2. sayi" << endl;
		string s2;
		getline(cin, s2);
		n2.set(s2);
		cout << "sonuc" << endl;
		cout << (n + n2) << endl;
		cout << "beklenen sonuc" << endl;
		string s3;
		getline(cin, s3);
		cout <<"Esit Mi -> "<<((n+n2).get()==s3?"EVET":"HAYIR")<<endl;	

	}
}