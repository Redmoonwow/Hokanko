// 学習用.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>

#define LOOK_NUMBER_VALUME 20

class card {
public:

private:
	int BOOK_AMT[LOOK_NUMBER_VALUME] = {};
	char TITLE[LOOK_NUMBER_VALUME] = {};
	char AUTHER[LOOK_NUMBER_VALUME] = {};
	int LOOK_NUM = 0;

private:

	// Initialize method
	void INIT_NUMBER() {
		LOOK_NUM = 0;

	}

	void INIT_BOOK_AMT() {
		int TMP_LOOK_NUM = NULL;
		while (true) {
			BOOK_AMT[TMP_LOOK_NUM] = NULL;
			++TMP_LOOK_NUM;
			if (TMP_LOOK_NUM == LOOK_NUMBER_VALUME) {
				break;
			}
		}
	}


	void INIT_TITLE() {
		int TMP_LOOK_NUM = NULL;
		while (true) {
			TITLE[TMP_LOOK_NUM] = NULL;
			++TMP_LOOK_NUM;
			if (TMP_LOOK_NUM == LOOK_NUMBER_VALUME) {
				break;
			}
		}
	}
	////////////////////////////


public:

	void store(char IN_TITLE, char IN_AUTHER, int STACK_AMT) {//書籍保存メソッド
		char Y_N[1];
		
		if (LOOK_NUM >= 20) { // 件数オーバーフロー
			std::cout << "登録件数がオーバーしています。　初期化しますか？:";
			std::cin >> Y_N;

			if ((Y_N == "y") | (Y_N == "Y") ){
				std::cout << "初期化しました。";
				INIT_NUMBER();

			}
			else {
				std::cout << "登録に失敗しました。";
			}

		}

		else {
			TITLE[LOOK_NUM] = IN_TITLE;
			AUTHER[LOOK_NUM] = IN_AUTHER;
			BOOK_AMT[LOOK_NUM] = STACK_AMT;
		}
	}

	void show(char IN_TITLE) {//書籍検索、紹介メソッド
		bool BOOK_ON;
		int TMP_LOOK_NUM = 0;

		while (true) {

			if (IN_TITLE == TITLE[TMP_LOOK_NUM]) {
				BOOK_ON = true;
				break;
			}

			else if(TMP_LOOK_NUM >= 21){
				std::cout << "タイトル検索に失敗しました。";
				BOOK_ON = false;
				break;
			}
			++TMP_LOOK_NUM;
		}

		if (BOOK_ON == true) {
			std::cout << "タイトル:" << TITLE[TMP_LOOK_NUM] << "  著作者:" << AUTHER[TMP_LOOK_NUM] << "  在庫数:" << BOOK_AMT[TMP_LOOK_NUM] << "\n";
		}
	}

};


int main(void)
{
	card card1;
	bool SELECT1,SELECT2;
	char TITLE;
	char AUTHER;
	int BOOK;

	for (;;) {
		std::cout << "何をしますか 1 = 本を入力します　0 = 本を検索します";
		std::cin >> SELECT1;
		switch (SELECT1) {
		case 1:
			std::cout << "タイトル:";
			std::cin >> TITLE;
			std::cout << "著作者:";
			std::cin >> AUTHER;
			std::cout << "在庫数:";
			std::cin >> BOOK;
			if (BOOK == 0) {
				std::cout << "0または文字が入力されました入力しなおしてください";
				break;
			}
			card1.store(TITLE, AUTHER, BOOK);
			std::cout << "登録が終わりました。";
			break;

		case 0:
			std::cout << "タイトル:";
			std::cin >> TITLE;
			card1.show(TITLE);
			break;
		}
		std::cout << "続けて作業しますか:";
		std::cin >> SELECT2;
		if (!SELECT2) {
			break;
		}


		SELECT1 = NULL; //入力変数全初期化
		SELECT2 = NULL;
		AUTHER = NULL;
		TITLE = NULL;
		BOOK = NULL;

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
