
class Menu
{
	char mTitle[70];
	char** mItem;
	const int mItemsNumber;
	bool* mStatus;
	const int mX;
	const int mY;
public:
	Menu(char *name, const char size, const char* items[], const int xCoord, const int yCoord);
	void addItems(const char* name[]);
	void setStatus(const int activeItem);
	void showMenu(const int activeItem = -2);
	void gotoxy(short x, short y);
	void line(unsigned const char c, const int length);
	~Menu();
};