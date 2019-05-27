#include <iostream>
#include <string>


class date {
	int day, month, year;
public:
	date (const char* str);
	date(const int m, const int d, const int y) {
		day = d;
		month = m;
		year = y;
	}
	void show() {
		std::cout << month << '/' << day << '/';
		std::cout << year << "\n";
	}
};

date::date(const char* str)
{
	/**str =  std::string::*/
	sscanf_s(str, "%d%*c%d%*c%d", &month, &day, &year);
}

int main()
{
	// 文字列を使用してdateオブジェクトを作成する
	date sdate("12/31/99");

	// 整数を使用してdateオブジェクトを作成する
	date idate(12, 31, 99);

	sdate.show();
	idate.show();
	return 0;
}