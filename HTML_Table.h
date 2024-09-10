#pragma once
#include<fstream>
#include"Cell.h"
#pragma warning(disable:4996)
constexpr int MAX_ROWS = 100;
constexpr int MAX_COLUMNS = 15;

class Row
{
public:
	Cell cells[MAX_COLUMNS];
};

class HTML_Table
{
private:
	int currentCountOfRows = 0;
	int countOfColumns = 0;
public:
	Row rows[MAX_ROWS];

	int getCurrentCountOfRows() const;
	int getCountOfColumns() const;

	void setCurrentCountOfRows(int countOfRows);
	void addRow(const Row& newRow, int position);
	void deleteRow(int rowNumber);
	void changeCellValue(int rowNumber, int columnNumber, const char* newValue);


	void readTableFromFile(const char* fileName);

	void saveOneRowToFile(std::ofstream& out, const Row& row) const;
	void saveToFile(std::ofstream& out) const;

	void printOneRow(const Row& row) const;
	void print() const;

	HTML_Table() = default;
	HTML_Table(int currentCountOfRows, int countOfColumns, Row rows[MAX_ROWS]);
};
