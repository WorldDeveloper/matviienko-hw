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
	const short mActiveItemColour = 0x9E;
	const short mInactiveItemColour = 0x96;
	const short mMenuColour = 0x96;
	const short mSystemColour = 0xF0;

	void Line(unsigned const char c, const int length);
public:
	Menu(string title, vector<string> items, const int xCoord, const int yCoord);
	void SetStatus(const int activeItem);
	void RepaintMenu(const int activeItem = -2);
	void ShowMenu();
	int GetStatus() const;
};