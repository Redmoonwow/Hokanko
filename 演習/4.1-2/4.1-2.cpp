// 4.1-2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

class squares {
	int num, sqr;
public:
	squares(int num) {
		this->num = num;
		sqr = num * num;
	}
	squares(int a, int b) { num = a; sqr = b; }
	void show() { std::cout << num << ' ' << sqr << "\n"; }
};



int main()
{
	int cnt;
	squares obj[] = {
		squares(1),
		squares(2),
		squares(3),
		squares(4),
		squares(5),
		squares(6),
		squares(7),
		squares(8),
		squares(9),
		squares(10),
	};
	for (cnt = 0;;) {
		obj[cnt].show();
		if (cnt >=9) { break; }
		cnt++;
	}
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
