#pragma once
#pragma warning(disable:4996)

constexpr int MAX_VALUE = 50;
bool isValidValue(const char* value);

class Cell
{
private:
	char value[MAX_VALUE + 1];
public:
	Cell();
	Cell(const char* value);
	const char* getValue() const;
	void setValue(const char* value);
};