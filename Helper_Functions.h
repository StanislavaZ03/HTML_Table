#pragma once
#include<cstring>
#include<iomanip>
#include<iostream>
#pragma warning(disable:4996)

void removeWhiteSpaces(char* arr)
{
	char* temp = new char[21];
	size_t index = 0, tempIndex = 0;
	while (arr[index] != '\0')
	{
		if (arr[index] == ' ' && (arr[index + 1] == ' ' || (arr[index + 1] != ' ' && (tempIndex == 0) || arr[index + 1] == '\0')))
		{
			index++;
			continue;
		}
		temp[tempIndex++] = arr[index++];
	}
	temp[tempIndex] = '\0';
	strcpy(arr, temp);
	delete[] temp;
}

void removeFirstChar(char* str)
{
	int len = strlen(str);
	for (int i = 1; i < len; ++i) {
		str[i - 1] = str[i];
	}
	str[len - 1] = '\0';
}

void replaceCharEntity(char* str)
{
	int index = 0;
	size_t length = strlen(str);
	char* str_result = new char[length + 1];

	for (int i = 0; i < length; ++i)
	{
		if (str[i] != '&')
		{
			str_result[index++] = str[i];
		}
		else if (str[i] == '&' && i + 2 < length && str[i + 1] == '#' && isdigit(str[i + 2]))
		{
			int number = 0;
			int j = i + 2;
			while (j < length && isdigit(str[j]))
			{
				number = number * 10 + (str[j] - '0');
				++j;
			}
			str_result[index++] = static_cast<char>(number);
			i = j - 1;
		}
		else
		{
			str_result[index++] = str[i];
		}
	}

	str_result[index] = '\0';
	strcpy(str, str_result);
	delete[] str_result;
}

void addStars(char* str)
{
	int length = std::strlen(str);
	char* result = new char[length + 3];
	result[0] = '*';

	std::strcpy(result + 1, str);

	result[length + 1] = '*';
	result[length + 2] = '\0';
	std::strcpy(str, result);
	delete[] result;
}

void removeLastChars(char* str)
{
	size_t length = strlen(str);
	if (length >= 4) {
		str[length - 4] = '\0';
	}
	else {

		str[0] = '\0';
	}
}

void mySetW(const char* source, int maxSpaces)
{
	int count = maxSpaces - strlen(source);

	if (count == 0)
	{
		std::cout << source << " ";
		return;
	}
	while (count >= 0)
	{
		std::cout << ' ';
		if (count == (maxSpaces - strlen(source)) / 2)
		{
			std::cout << source;
		}
		count--;
	}
}
