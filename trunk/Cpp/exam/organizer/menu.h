#include <string>
#include <vector>
using namespace std;

class Menu
{
	string mTitle;
	vector<string> mItems;
	vector<bool> mStatus;
	const int mX;
	const int mY;
public:
	Menu(string title, vector<string> items, const int xCoord, const int yCoord);
	//void addItems(const char* name[]);
	void SetStatus(const int activeItem);
	void ShowMenu(const int activeItem = -2);
	void Line(unsigned const char c, const int length);
};