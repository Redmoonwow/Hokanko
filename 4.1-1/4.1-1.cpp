﻿// 4.1-1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>


class letters {
private:
	char ch;
public:
	letters(char c) { ch = c; }
	char get_ch() { return ch; }
};

int main()
{
	int cnt = 0;
	letters obj[] = {
		letters('A'),
		letters('B'),
		letters('C'),
		letters('D'),
		letters('E'),
		letters('F'),
		letters('G'),
		letters('H'),
		letters('I'),
		letters('J')
	};
	while (true) {
		std::cout << obj[cnt].get_ch() << '\n';
		if (obj[cnt].get_ch() == 'J') {
			break;
		}
			cnt++;
	}	
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
