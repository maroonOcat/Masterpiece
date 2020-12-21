// lordApp.cpp
#include "Header.h"
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <numeric> //для accumulate()
int main()
{
	//Функция setlocale() задаёт локализацию программы.
	setlocale(LC_ALL, "rus");
	UserInterface theUserInterface;
	theUserInterface.interact();
	return 0;
}
////////////////////конец файла lordApp.cpp////////////////

