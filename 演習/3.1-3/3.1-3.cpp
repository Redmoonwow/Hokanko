// 3.1-3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class strtype {
	char* p;
	int len;
public:
	strtype(const char* ptr);
	~strtype();
	void show();
	friend void kill(strtype obj);
	friend char* get_string(strtype obj);
};

strtype::strtype(const char* ptr)
{
	len = strlen(ptr);
	p = (char*)malloc(len + 1);
	if (!p) {
		cout << "メモリ割り当てエラー\n";
		exit(1);
	}
	strcpy_s(p, (len + 1), ptr);
}

strtype::~strtype()
{
}


void strtype::show()
{
	cout << p << " - 長さ: " << len;
	cout << "\n";
}

char* get_string(strtype obj) {
	return obj.p;
}



void kill(strtype obj) {
	free(obj.p);
}

int main()
{
	char* pointer;
	strtype s1("This is a test."), s2("I like C++.");

	std::cout << get_string(s1) << "\n";

	kill(s1);
	kill(s2);

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
