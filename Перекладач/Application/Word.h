#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <Windows.h>
#include <conio.h>

class Word
{
public:
	bool m_mandatory_meaning;

	std::string m_eng;

	std::string m_ua1;

	std::string m_ua2;

	Word(bool mandatory_meaning, std::string eng, std::string ua1, std::string ua2 = "0");

private:
	const std::string getua();

	const std::string getEng();
};