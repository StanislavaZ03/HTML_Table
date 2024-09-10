#include "Cell.h"
#include<iostream>
#include<cstring>

bool isValidValue(const char* value)
{
	if (!value || strlen(value) > MAX_VALUE)
	{
		return false;
	}
	return true;
}

const char* Cell::getValue() const
{
	return value;
}

void Cell::setValue(const char* value)
{
	if (isValidValue(value))
	{
		strcpy(this->value, value);
	}
	else
	{
		strcpy(this->value, " ");
		std::cout << "Invalid value" << std::endl;
	}
}

Cell::Cell(const char* value)
{
	setValue(value);
}

Cell::Cell() :Cell(" ") {}
