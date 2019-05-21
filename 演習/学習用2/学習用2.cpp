// 学習用2.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <string>
#include <algorithm>

#define store_size 5

class stack_process {
public://decle

private://decle
	std::string ORI_str_data[store_size];
	std::string ORI_str_adress[store_size];
	int str_number_stored = 0; //収納してあるところまでのナンバー
public://method
	//コンストラクタ
	//myclass() {
	//	INIT_ALL();//インスタンス作成時全て初期化
	//}

	//データ収納
	void store() {
		std::string Y_N;

		//オーバーフロー監視
		if (str_number_stored >= store_size) {
			std::cout << "データがオーバーフローしています。初期化しますか:";
			std::cin >> Y_N;

			if (Y_N_judge(Y_N) == 1) {
				std::cout << "初期化します";
				INIT_ALL();
				return store();
			}
			else if (Y_N_judge(Y_N) == 0) {
				std::cout << "初期化できませんでした。終了します。";
			}
		}

		//正常処理
		if (str_number_stored < store_size) {
			std::cout << "登録を開始します。" << "\n" << "名前:";
			std::cin >> ORI_str_data[str_number_stored];
			std::cout << "アドレス:";
			std::cin >> ORI_str_adress[str_number_stored];
			++str_number_stored;
			std::cout << "登録が終わりました。";
		}

	}

	//登録データの表示と検索
	void display() {
		int tmp_cnt;
		std::string str_name;
		std::cout << "名前を入力してください:";
		std::cin >> str_name;
		for (tmp_cnt = 0;;) {

			if (tmp_cnt >= store_size) {
				std::cout << "登録されていません";
				return;
			}

			if (str_name == ORI_str_data[tmp_cnt]) {
				break;
			}

			tmp_cnt++;
		}

		std::cout << "名前:" << ORI_str_data[tmp_cnt] << "\n" << "アドレス:" << ORI_str_adress;

	}

private://method

	//全て初期化
	void INIT_ALL() {
		INIT("number");
		INIT("data");
		INIT("adress");
	}

	//各自初期化
	void INIT(std::string mode) {
		int cnt = 0;

		if (mode == "number" | mode == "NUMBER") {
			str_number_stored = 0;
		}

		if (mode == "data" | mode == "DATA") {
			while(!((cnt - (store_size-1)))){
				ORI_str_data[cnt].clear();
				++cnt;
			}
		}

		if (mode == "adress" | mode == "adress") {
			while(!((cnt - (store_size - 1)))){
				ORI_str_adress[cnt].clear();
				++cnt;
			}
		}

	}

	//選択判断用
	bool Y_N_judge(std::string Y_N) {

		if (Y_N == "y" | Y_N == "Y") {
			return 1;

		}
		else if (Y_N == "n" | Y_N == "N") {
			return 0;
		}
		else {
			std::cout << "不明な文字が入力されました　入力しなおしてください";
			Y_N.clear();
			std::cin >> Y_N;
			return Y_N_judge(Y_N);
		}


	}

	//エラー処理
	//void ER_duplicate() {
	//	std::cout <<"データが重複しています。"
	//}
};


int main()
{
	stack_process a;
	for (;;) {
		bool mode = 0;
		bool select = 0;

		std::cout << "モードを選んでください 1:登録 0:表示 :";
		std::cin >> mode;
		switch (mode) {
		case 1:
			a.store();
			break;
		case 0:
			a.display();
			break;
		}

		std::cout << "\n" << "ソフトウェアを終了しますか";
		std::cin >> select;
		if (select == 1) {
			break;
		}
		else {
			select = 0;
			mode = 0;
		}
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
