// 6-5.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class strtype {
	char* p;
	int len;
public:
	strtype(const char* s);
	~strtype() {
		cout << (unsigned)p << "を解放する" << "\n";
		delete[] p;
	}
	char* get() { return p; }
	strtype& operator=(strtype& ob);
	char operator[](int i);
};

strtype::strtype(const char* s)
{
	int l;

	l = strlen(s) + 1;

	p = new char[l];
	if (!p) {
		cout << "メモリ割り当てエラー\n";
		exit(1);
	}

	len = l;
	strcpy_s(p,len, s);
}

char strtype::operator[](int i) {
	return p[i];
}

// オブジェクトを代入する
strtype& strtype::operator=(strtype& ob)
{
	// さらにメモリが必要か調べる
	if (len < ob.len) { // さらにメモリの割り当てが必要
		delete[] p;
		p = new char[ob.len];
		if (!p) {
			cout << "メモリ割り当てエラー\n";
			exit(1);
		}
	}
	len = ob.len;
	strcpy_s(p,len,ob.p);
	return *this;
}


int main()
{
	strtype obj("Hello World");


	std::cout << obj[4] <<"\n";

	return 0;
}


// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
