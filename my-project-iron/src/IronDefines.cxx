
#include <iostream>
#include <string>
#include "IronDefines.hpp"


int GetInt()
{
	int target = -1;
	
	while (target < 0) {
		try {
			std::cin >> target;
		} catch (std::exception e) {
			std::cout << "You entered a wrong value: " << target << std::endl << "With error: " << e.what() << std::endl;
			target = -1;
		}
		//target = -1;
		std::cout << std::endl;
	}
	return target;
}

std::string GetString()
{
	std::string entry("");
	
	while (!entry.compare("")) {
		try {
			std::cin >> entry;
			std::cout << std::endl;
		} catch (std::exception e) {
			std::cout << "You entered a wrong value: " << entry << std::endl << "With error: " << e.what() << std::endl;
			entry = "";
		}
	}
	return entry;
}

std::string & tolower(std::string & str)
{
	for (int i = 0; i < str.length(); ++i) {
		str[i] = std::tolower(str[i]);
	}
	return str;
}

int GetInPoints(int & points)
{
	int leftPoints = -1;
	if (points == 0) {
		std::cout << "0" << std::endl;
		return 0;
	}
	while (leftPoints < 0 || leftPoints > points) {
		leftPoints = GetInt();
		//std::cout << std::endl;
		if (leftPoints > points) {
			std::cout << "You don't have enough points" << std::endl;
		} else if (leftPoints < 0) {
			std::cout << "Enter a nul or positive number" << std::endl;
		}
	}
	points -= leftPoints;
	return leftPoints;
}

int GetInRange(int begin, int end)
{
	int inRange = -1;
	
	while (inRange < begin || inRange > end) {
		std::cout << "Enter a value between " << begin << " and " << end << " : ";
		inRange = GetInt();
	}
	return inRange;
}


int GetPointsInRange(int begin, int end, int & points)
{
	int usedPoints = -1;
	
	while (usedPoints < 0 || usedPoints > points) {
		usedPoints = GetInRange(begin, end);
		if (usedPoints > points) {
			std::cout << "You dont have enough points" << std::endl;
			usedPoints = -1;
		}
	}
	points -= usedPoints;
	return usedPoints;
}

void PropertyDisplayLoop(int size, std::string * properties)
{
	for (int i = 0; i < size; ++i) {
		std::cout << (properties[i][0] == '-' ? "\t" : "") << properties[i] << std::endl;
	}
}

