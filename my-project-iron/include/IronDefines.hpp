

#ifndef IRON_DEFINES_HPP
#define IRON_DEFINES_HPP

#define WRONG_VALUE "No negative value allowed."
#define BASE_ATTACK_ENERGY (5)

#include <string>

int GetInt();
std:: string GetString();
std::string & tolower(std::string &);
int GetInPoints(int &);

int GetInRange(int, int);
int GetPointsInRange(int, int, int &);

void PropertyDisplayLoop(int, std::string *);

/*
#include "Effects.hpp"
#include "Attack.hpp"
#include "AffectsArray.hpp"
*/

//template class Array<Effect>;
//template class Array<Attack>;

#endif