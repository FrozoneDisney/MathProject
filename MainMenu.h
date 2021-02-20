#ifndef _MAINMENU_H
#define _MAINMENU_H
#include <iostream>
#include "EpicHeader.h" //the header where all the magic happens

//neat menu function in an infinite loop so that you can do as many calculations as you'd like.
void callMenu()
{
	while (true) {
		int arg; //declaring int arg
		std::cout << "What do you want to calculate today ?\n1. Distance From point to point\n2. distance or intersection between two lines\n3. Distance between point and line\n4. Line and plane intersection\n5. distance between plane and point\n9. Exit\n";
		std::cin >> arg; //taking user argument and piping it into the arg variable
		
		//switch case to easily index what option the user wants
		switch (arg)
		{
			case 1:
				distanceBetweenTwoPoints();
				break;
			case 2:
				distanceLineAndIntersect();
				break;
			case 3:
				distanceBetweenPointAndLine();
				break;
			case 4:
				lineAndPlaneIntersect();
				break;
			case 5:
				distanceBetweenPlaneAndPoint();
				break;
			case 9:
				return;
				
		}
	}
}

#endif // _MAINMENU_H
