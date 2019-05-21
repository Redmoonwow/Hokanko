// E_3.4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

class pr2;

class pr1 {
private:
	bool printing;

public:

	pr1() {
		printing = 0;
	}

	void set_printer() {
		printing = 1;
	}

	friend std::string serch_print_now(pr1 p1,pr2 p2);
};

class pr2 {
	bool printing;

public:
	pr2() {
		printing = 0;
	}

	void set_printer() {
		printing = 1;
	}

	friend std::string serch_print_now(pr1 p1, pr2 p2);
};

std::string serch_print_now(pr1 p1, pr2 p2) {
	if (p1.printing == 1) {
		return "pr1が使っています\n";
	}
	if (p2.printing == 1) {
		return "pr2が使っています\n";
	}
}

int main()
{
	pr1 p1;
	pr2 p2;

	p1.set_printer();
	std::cout << serch_print_now(p1, p2);
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
