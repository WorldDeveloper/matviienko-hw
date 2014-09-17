#include <vector>
#include <new>
#include "Point.h"
using namespace std;

class Figure
{
	vector<Point*> mVertexes;
	int mColour;
public:
	Figure()
	{
		int colour;
		cout << "Enter a colour: ";
		cin >> mColour;

		int vertexNumber = 0;
		while (vertexNumber < 3)
		{
			cout << "Enter number of vertexes: ";
			cin >> vertexNumber;
		}

		for (int i = 1; i <= vertexNumber; ++i)
		{
			cout << "\tEnter \"x" << i << "\": ";
			int x;
			cin >> x;

			cout << "\tEnter \"y" << i << "\": ";
			int y;
			cin >> y;

			try{
				mVertexes.push_back(new Point(x, y));
			}
			catch (bad_alloc){
				throw "Out of memory";
			}
		}
	}

	~Figure()
	{
		for (auto point : mVertexes)
		{
			delete point;
		}
	}

	void ShowFigure() const
	{
		cout << "\n\tColour: " << mColour;
		cout << "\n\tNumber of Vertex: " << mVertexes.size();
		int i = 1;
		for (auto point : mVertexes)
		{
			cout << "\n\t\tp" << i++;
			(*point).ShowPoint();
		}
		cout << endl;
	}
};