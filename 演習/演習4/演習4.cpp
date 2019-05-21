// 演習4.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

class area_c1 {
public:
	double height;
	double width;
};

class rectangle :public area_c1 {

public:
	rectangle(double i_height , double i_width) {
		height = i_height;
		width = i_width;
	}

	void area() {
		std::cout << "面積:" << (height * width) << "\n";
	}
};

class isosceles :public area_c1 {

public:
	isosceles(double i_height, double i_width) {
		height = i_height;
		width = i_width;
	}

	void area() {
		std::cout << "面積:" << ((height * width)/2) << "\n";
	}
};

int main()
{
	rectangle sikakukei(2, 5);
	isosceles sankaku(3, 5);

	sikakukei.area();
	sankaku.area();
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
