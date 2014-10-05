/*
Описать класс "студент" с полями: имя, фамилия, курс. Переопределить у этого
класса оператор вывода в поток. Написать функцию заполнения вектора из класса
"студент" произволными данными. Написать функцию печати содержимого
вектора. Отсортировать вектор по именам студентов по возрастанию.
Отсортировать стабильно вектор по фамилиям студентов. Поставить в первые три
элемента вектора студентов самых младших курсов по возрастанию. После каждой
операции выводить список студентов в выходной поток.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include "Student.h"
#include "menu.h"
#include "Graphics.h"
#include <conio.h>

using namespace std;

ostream& operator<<(ostream& stream, const Student& student);

template <class T>
ostream& operator<<(ostream& stream, vector<T>& output);

Student Input();

bool cmp(const Student& s1, const Student& s2);


void main()
{
	system("color F0");
	Menu menu("Menu", { "F1 Add student", "F2 Sort by name", "F3  Stable sort by surname" }, 0, 0);
	menu.SetStatus(-2);
	menu.ShowMenu();

	vector<Student> students{
		Student("Sydorov", "Ivan", "1"),
		Student("Ivanov", "Petro", "1"),
		Student("Petrov", "Petro", "1"),
		Student("Ivanov", "Ivan", "2"),
		Student("Sydorov", "Sydor", "2")
	};

	while (true)
	{
		system("cls");
		menu.ShowMenu();
		HideCursor(true); 
		cout << students;
		
		enum{KEY_F1 = 59, KEY_F2, KEY_F3, KEY_F4 };
		unsigned char control = getch();

		if (control == 0 || control == 224 && kbhit())
		{
			unsigned char secondByte = getch();
			if (secondByte == KEY_F1)
			{				
				HideCursor(false); 
				students.push_back(Input());
			}
			else if (secondByte == KEY_F2)
			{				
				sort(students.begin(), students.end());
			}
			else if (secondByte == KEY_F3)
			{
				stable_sort(students.begin(), students.end(), cmp);
			}

		}
	}
}

ostream& operator<<(ostream& stream, const Student& student)
{
	stream << student.GetSurname() << "\t " << student.GetName() << "\t " << student.GetCourse();
	return stream;
}

template <class T>
ostream& operator<<(ostream& stream, vector<T>& output)
{
	for (auto& i : output)
	{
		stream << i << "\n";
	}

	return stream;
}

Student Input()
{
	cout << "\nSurname: ";
	string surname;
	getline(cin, surname);

	cout << "Name: ";
	string name;
	getline(cin, name);

	cout << "Course: ";
	string course;
	getline(cin, course);

	Student student(surname, name, course);
	return student;
}


bool cmp(const Student& s1, const Student& s2)
{
	if (s1.GetSurname() < s2.GetSurname()) return true;
	else return false;
}
