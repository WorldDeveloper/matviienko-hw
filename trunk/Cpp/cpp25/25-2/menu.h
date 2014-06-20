
class menu
{
	char mTitle[70];
	char** mItem;
	char mItemsNumber;
	char mItemMaxLength;
	bool* mStatus;
public:
	menu(char *name, const char size, const char length);
	void addItems(char* name[]);
	void setStatus(const bool* status);
	void showMenu(char x);
	void gotoxy(short x, short y);
	void line(unsigned const char c, const int length);
	~menu();
};