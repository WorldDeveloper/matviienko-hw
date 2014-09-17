/*
В разделе урока "Агрегирование и композиция" приведен пример на альянс
класса "точки" и класса "фигура". Ваша задача добавить к программе класс,
который будет содержать в себе несколько объектов класса фигура,
создавая тем самым композицию.
*/

#include <iostream>
#include <vector>
#include <new>
#include "FiguresCollection.h"
using namespace std;

void main()
{
	int fNumber = 0;
	while (fNumber < 2)	{
		cout << "Enter a number of figures in collection: ";
		cin >> fNumber;
	}

	try{
		FiguresCollection collection(fNumber);
		collection.ShowCollection();
	}
	catch (char* err){
		cout << "\nError: " << err << "\n\n";
		exit(1);
	}
}