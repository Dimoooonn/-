#include "Word.h"
// 
Word::Word(bool mandatory_meaning, std::string eng, std::string ua1, std::string ua2) : m_mandatory_meaning(mandatory_meaning), m_eng(eng), m_ua1(ua1), m_ua2(ua2)
{
}

const std::string Word::getua()
{
	if (m_ua2 == "0")
		return m_ua1;
	else
		return m_ua1 + ", " + m_ua2;
}

const std::string Word::getEng()  // Повертає англійський еквівалент слова


{
	return m_eng;
}