#pragma once
#include "HTML_Table.h"
#include"Helper_Functions.h"
#include<iostream>
#include<sstream>
#include<algorithm>
#include<iomanip>

int HTML_Table::getCurrentCountOfRows() const
{
	return currentCountOfRows;
}

int HTML_Table::getCountOfColumns() const
{
	return countOfColumns;
}

void HTML_Table::setCurrentCountOfRows(int countOfRows)
{
	if (countOfRows > MAX_ROWS || countOfRows < 0)
	{
		return;
	}
	else
	{
		currentCountOfRows = countOfRows;
	}
}

HTML_Table::HTML_Table(int currentCountOfRows, int countOfColumns, Row rows[MAX_ROWS])
{
	setCurrentCountOfRows(currentCountOfRows);
}

void HTML_Table::addRow(const Row& newRow, int position)  
{
	if (currentCountOfRows + 1 > MAX_ROWS || position - 1 < 0 || position - 1 >= MAX_ROWS)
	{
		return;
	}

	for (int i = currentCountOfRows; i >= position - 1; --i) 
	{                                                       
		rows[i + 1] = rows[i];
	}

	rows[position - 1] = newRow;

	if (position - 1 <= currentCountOfRows) 
	{
		currentCountOfRows++;
	}
	else
	{
		currentCountOfRows = position - 1;
	}
}

void HTML_Table::deleteRow(int rowNumber) 
{
	if (rowNumber - 1 < 0 || rowNumber - 1  > currentCountOfRows)
	{
		std::cout << "Invalid row number." << std::endl;
		return;
	}

	for (int i = rowNumber - 1; i <= currentCountOfRows - 1; ++i)
	{
		rows[i] = rows[i + 1];
	}
	currentCountOfRows--;
}

void HTML_Table::changeCellValue(int rowNumber, int columnNumber, const char* newValue)
{
	if (rowNumber -1  < 0 || rowNumber - 1 >= currentCountOfRows || columnNumber - 1 < 0 || columnNumber - 1 >= countOfColumns)
	{
		std::cout << "Invalid row or column number." << std::endl;
		return;
	}
	rows[rowNumber - 1].cells[columnNumber - 1].setValue(newValue);
}


void HTML_Table::readTableFromFile(const char* fileName)
{
	std::ifstream ifs(fileName);
	if (!ifs.is_open())
	{
		std::cout << "Error while opening the file!";
	}

	int rowsCount = -1;
	int index = 0;
	int collsCount = 0;
	bool isNewCell = false; // <td> </td>
	bool isNewHeaderCell = false; // <th> </th>
	while (!ifs.eof())
	{
		char buffer[30];
		ifs.getline(buffer, 30, '>');
		removeWhiteSpaces(buffer);
		replaceCharEntity(buffer);
		if (strcmp(buffer, "<th") != 0 && strcmp(buffer, "<td") != 0) {
			ifs.ignore();
		}
		if (buffer[0] == '<')
		{
			removeFirstChar(buffer);
		}

		if (strcmp(buffer, "tr") == 0)
		{
			rowsCount++;
			index = 0;
		}
		else if (strcmp(buffer, "td") == 0)
		{
			isNewCell = true;
		}
		else if(strcmp(buffer, "th") == 0)
		{
			isNewHeaderCell = true;
		}
		else if (isNewCell)
		{
			removeLastChars(buffer);
			rows[rowsCount].cells[index].setValue(buffer);
			index++;
			isNewCell = false;
			collsCount = std::max(collsCount, index);
		}
		else if (isNewHeaderCell)
		{
			removeLastChars(buffer);
			addStars(buffer);
			rows[rowsCount].cells[index].setValue(buffer);
			index++;
			isNewHeaderCell = false;
			collsCount = std::max(collsCount, index);
		}
	}
	countOfColumns = collsCount;
	currentCountOfRows = rowsCount;
	ifs.close();
}




size_t getMaxLengthOfValue(const Row* rows, int countOfRows, int countOfColumns) 
{
	size_t maxLength = 0;

	for (int i = 0; i <= countOfRows; ++i)
	{
		for (int j = 0; j < countOfColumns; ++j)
		{
			size_t valueLength = strlen(rows[i].cells[j].getValue());
			if (valueLength > maxLength)
			{
				maxLength = valueLength;
			}
		}
	}
	return maxLength; 
}

void HTML_Table::saveOneRowToFile(std::ofstream& out, const Row& row) const //това трябва да се преправи
{
	out << "<tr>  ";
	for (size_t i = 0; i < countOfColumns; ++i)
	{
		if (strcmp(row.cells[i].getValue(), " ") != 0) 
		{
			out << "<td>";
				out << row.cells[i].getValue();
				out << "</td> ";
		}
	}
	out << "</tr> ";
}

void HTML_Table::saveToFile(std::ofstream& out) const  
{
	if (!out.is_open())
	{
		std::cout << "Error while opening the file!";
	}
	out << "<table>";
	
	for (size_t i = 0; i <= currentCountOfRows; ++i)
	{
		saveOneRowToFile(out, rows[i]);
	}
	out << "</table>";
	out.close();
}

void HTML_Table::printOneRow(const Row& row) const
{
	unsigned maxCountOfSpaces = getMaxLengthOfValue(rows, currentCountOfRows, countOfColumns);

	for (size_t i = 0; i < countOfColumns; ++i)
	{
		mySetW( row.cells[i].getValue(),maxCountOfSpaces);
		std::cout << "|";
	}
	std::cout << std::endl;
}

void HTML_Table::print() const
{
	
	for (size_t i = 0; i <= currentCountOfRows; ++i)
	{
		std::cout << "|";
			printOneRow(rows[i]);
	}
	std::cout << std::endl;
}



