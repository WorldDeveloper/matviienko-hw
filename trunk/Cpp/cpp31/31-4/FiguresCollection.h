#include "Figure.h";

class FiguresCollection
{
	vector<Figure*> mCollection;
public:
	FiguresCollection(const int figuresCount)
	{
		for (int i = 0; i < figuresCount; ++i)
		{
			cout << "\nFIGURE #" << i + 1 << endl;

			try{
				mCollection.push_back(new Figure);
			}
			catch (bad_alloc){
				throw "Out of memory";
			}
		}
	}
	~FiguresCollection()
	{
		for (auto figure : mCollection)
		{
			delete figure;
		}
	}
	void ShowCollection() const
	{
		cout << "\nCOLLECTION\n";
		cout << "\tNumber of figures: " << mCollection.size();
		int i = 1;
		for (auto figure : mCollection)
		{
			cout << "\nFIGURE #" << i++;
			(*figure).ShowFigure();
		}
	}
};