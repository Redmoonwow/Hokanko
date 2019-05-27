// 5-1.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

class coord {
	int x, y; // 座標値
public:
	coord() { x = 0; y = 0; }
	coord(int i, int j) { x = i; y = j; }
	void get_xy(int& i, int& j) { i = x; j = y; }
	coord operator+(coord ob2);
	coord operator-(coord ob2);
	coord operator=(coord ob2);
	coord operator*(coord ob2);
	friend coord operator*(int i, coord ob2);
	friend coord operator*(coord ob2, int i);
	coord operator/(coord ob2);
	void operator--();
	void operator--(int notused);
	void operator+();
	bool operator<(coord ob2);
	bool operator>(coord ob2);
};

// +をcoordクラスに対してオーバーロードする
coord coord::operator+(coord ob2)
{
	coord temp;

	temp.x = x + ob2.x;
	temp.y = y + ob2.y;

	return temp;
}

// -をcoordクラスに対してオーバーロードする
coord coord::operator-(coord ob2)
{
	coord temp;

	temp.x = x - ob2.x;
	temp.y = y - ob2.y;

	return temp;
}

// =をcoordクラスに対してオーバーロードする
coord coord::operator=(coord ob2)
{
	

	x = ob2.x;
	y = ob2.y;

	return *this; // 代入されたオブジェクトを返す
}

coord coord::operator*(coord ob2) {

	coord temp;

	temp.x = x * ob2.x;
	temp.y = y * ob2.y;

	return temp;
}

coord operator*(int i, coord ob2) {

	coord temp;

	temp.x = i * ob2.x;
	temp.y = i * ob2.y;

	return temp;
}

coord operator*(coord ob2, int i) {

	coord temp;

	temp.x = i * ob2.x;
	temp.y = i * ob2.y;

	return temp;

}

coord coord::operator/(coord ob2) {

	coord temp;

	temp.x = x / ob2.x;
	temp.y = y / ob2.y;

	return temp;
}

void coord::operator--() {
	x -= 1;
	y -= 1;
}

void coord::operator--(int notused) {
	x -= 1;
	y -= 1;
}

void coord::operator+() {
	if (0 > x) { x = -x; }
	if (0 > y) { y = -y; }
}

bool coord::operator>(coord ob2) {
	if (ob2.x <= x && ob2.y <= y) { return true; }
	else { return false; }
}

bool coord::operator<(coord ob2) {
	if (ob2.x >= x && ob2.y >= y) { return true; }
	else { return false; }
}

int main()
{
	coord x(-10,-10),y(15,10);
	int i, j;
	x = 10 * x;
	x.get_xy(i, j);
	std::cout << i << ":" << j << "\n";


	// ...
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
