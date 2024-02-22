#include<iostream>
#include <windows.h>
#include "../Solitare/Solitare.h"
#include "Commander.h"
#include <stdlib.h>

int main() {
	Desk desk = Desk();
	std::string command;
	Commander commander(desk);
	while (command != "quit") {
		system("cls");
		commander(command);
		if (desk.checkWin()) {
			std::cout << "You win!";
		}
		else {
			std::cout << desk.Draw() << std::endl;
		}
		std::getline(std::cin, command);
	}
	
}

