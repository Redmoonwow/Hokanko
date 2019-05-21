// 練習3.cpp : このファイルには 'main' 関数が含まれています。プログラム実行の開始と終了がそこで行われます。
//

#include <iostream>
#include <chrono>
struct Status_flags {
	unsigned char bclass_flag   : 1; //インスタンスが存在する
	unsigned char bactive_flag : 1; //インスタンスでなにか稼働している
	unsigned char bData_exist :1; //データが存在する
	unsigned char : 5; //予備
};

class stopwatch {
public:

private:
	long long int time_on_program;
	long long int time_on_method_start;
	long long int time_on_method_end;
public:
	stopwatch() {
		time_on_program = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		time_on_method_start = 0;
	}

	~stopwatch() {
		long long calc = 0;
		calc = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) - time_on_program;
		std::cout << "プログラム稼働時間:" << calc << "\n";
	}

	void start() {
		time_on_method_start = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	void stop() {
		time_on_method_end = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	}

	void show() {
		long long int calc = 0;
		calc = time_on_method_end - time_on_method_start;
		std::cout << "時間:" << calc << "\n";;
	}
private:

};

class mainclass {
private:

	std::string select;
	Status_flags  flags;
	stopwatch *watch;

public:
private:

	void INIT_class(std::string classname) {//インスタンス作成メソッド
		if (classname == "stopwatch") {
			watch = new stopwatch;
			flags.bclass_flag = 1;
		}
	}

public:

	mainclass() {//初期化メソッド
		select = "0";
		flags.bclass_flag = 0;
		flags.bactive_flag = 0;
		flags.bData_exist = 0;
	}

	~mainclass() {

	}

	void main() {//メインメソッド
		
		for (;;) {
			std::cout << "コマンド入力待機:";
			std::cin >> select;
			if (select == "0") {//間違った文字入力時
				std::cout << "間違った文字が入力されました";
			}
			else if (select == "start") {//start開始
				if (flags.bclass_flag == 0 && flags.bactive_flag == 0) {
					INIT_class("stopwatch");
					watch -> start();
					flags.bactive_flag = 1;
				}
				else if(flags.bclass_flag == 1 && flags.bactive_flag == 0){
					watch -> start();
					flags.bactive_flag = 1;
				}
				else if (flags.bactive_flag == 1) {
					std::cout << "ストップウォッチを止めてください" << "\n";
				}
			}
			else if (select == "stop") {//stop開始
				if (flags.bactive_flag == 1) {
					watch -> stop();
					flags.bactive_flag = 0;
					flags.bData_exist = 1;
				}
				else {
					std::cout << "ストップウォッチを始めていません" << "\n";
				}
			}
			else if (select == "show") {//show開始
				if (flags.bData_exist == 0) {
					std::cout << "データが存在しませんでした\n";
				}
				else {
					watch -> show();
				}
			}
			else if (select == "end") {//end開始
				if (flags.bclass_flag == 1) {
					delete(watch);
					flags.bclass_flag = 0;
				}
				break;
			}
		}
	}

};


int main()
{
	mainclass main_c;
	main_c.main();
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
