#pragma once
#include "../Solitare/Solitare.h"

class Commander {
private:
	Desk& desk;
	std::vector<std::string> parse(std::string);
public:
	Commander(Desk& desk) :desk(desk) {};
	void operator()(std::string&);

};