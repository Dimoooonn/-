#include "Application.h"

void Application::run()  //  �� ������� ������� �� ������ ������� � ��������� ���� �������� ����.
{
	bool flag = true;
	int k;
	while (flag) //����, ���� ������������, ���� ����� flag � ��������. � ����� ���� ���������� ����� ���� ��� ����������� � ��������� ���� ����.
	//������� �� ������ ����������� ����������� ���� 䳿, ��� �� ��������� �������� ��� ��� ���������� ���������. ���� ���������� ������ ����� "4", �������� �����������.
	{ 
		std::cout << std::endl << "1 - �������� ������� ���" << std::endl;
		std::cout << "2 - ������ ���������� ���������� � ��������� �� ���������" << std::endl;
		std::cout << "3 - ������ ���������� ���������� � ��������� �� ���������" << std::endl;
		std::cout << "4 - ������� ��������" << std::endl;
		std::cin >> k;
		std::cin.get();

		switch (k)
		{
		case 1:
		{
			std::string filename;
			std::cout << std::endl << "���� �����, ������ ����� �� ��'� ����� �������� ��� (�� �������� ���������� �����):" << std::endl;
			getline(std::cin, filename);
			filename += ".txt";
			createSet(filename);
			std::cout << std::endl << "������� ��� ��� ������ ���������!\n�� ������ ������ ����������." << std::endl;
			break;
		}
		case 2:
			if (m_word_bank.empty())
				std::cout << std::endl << "�� �� �������� ������� ���. ������� ������ ����� ���� � ��������� �� ���!" << std::endl;
			else
			{
				fromuaTrain();
				std::cout << "\n ���������� ��������!\n";
			}
			break;
		case 3:
			if (m_word_bank.empty())
				std::cout << std::endl << "�� �� �������� ������� ���. ������� ������ ����� ���� � ��������� �� ���!" << std::endl;
			else
			{
				fromEngTrain();
				std::cout << "\n ���������� ��������!\n";
			}
			break;
		case 4:
			flag = false;
			break;
		default:
			std::cout << "\n�� �� ������� ������� ������ ����. ��������� �� ���!\n";
			break;
		}
	}
	std::cout << "\n�������� �������!\n";
}

void Application::createSet(std::string filename) //�� ������� ������� �� ��������� �������� ���. ���� ������ ������ �� ��'� ����� �������� ��� � ������ ����� filename. ������� ����� ��� � ����� � ������� ������� ��� m_word_bank, ��� ��������������� ��� ���������� ���������.
{
	std::ifstream dictionary(filename);
	std::vector<Word> Bank;
	std::string word_pair;

	if (!dictionary)
	{
		std::cout << "��������� ������� ���'����� � �������!";
	}
	else
	{
		while (dictionary)
		{
			getline(dictionary, word_pair);
			if (word_pair == "")
				continue;
			word_pair.erase(word_pair.begin());

			auto iter = word_pair.begin();
			std::string eng;
			std::string ua1;

			while (*iter != '/')
			{
				eng.push_back(*iter);
				++iter;
			}

			eng.pop_back();

			iter += 2;
			while ((iter != word_pair.end()) && (*iter != '|') && (*iter != '&'))
			{
				ua1.push_back(*iter);
				++iter;
			}

			bool flag;
			std::string ua2;
			if (iter != word_pair.end())
			{
				ua1.pop_back();

				if (*iter == '|')
					flag = false;
				else
					flag = true;

				iter += 2;
				while (iter != word_pair.end())
				{
					ua2.push_back(*iter);
					++iter;
				}

				Bank.emplace_back(flag, eng, ua1, ua2);
			}
			else
				Bank.emplace_back(false, eng, ua1);
		}
		m_word_bank = std::move(Bank);
		m_word_bank.pop_back();
	}
}

void Application::printSet() //�� ������� �������� �� ����� ������� ���, ���������� � ������ m_word_bank. ����� ����� ������ ��������� ����� �� ���� ���������� ��������.
{
	for (auto iter = m_word_bank.cbegin(); iter != m_word_bank.cend(); ++iter)
	{
		if (iter->m_ua2 == "0")
			std::cout << iter->m_eng << " - " << iter->m_ua1 << std::endl;
		else
			std::cout << iter->m_eng << " - " << iter->m_ua1 << ", " << iter->m_ua2 << std::endl;
	}
}

void Application::fromuaTrain() //�� ������� ������� �� ���������� ��������� � ��������� ���� �� ���������. ���� ����������� ������� ��� m_word_bank, ���� �� ���� ��������� ����� �������� ����������. ������� ������� ������������ ������� �������� ����� �� �� �������� ��������� � ���� �� �� ��������. ���������� �����������, ���� ���������� ����� �������� ��������.


{
	std::cout << "\n�� ������ ���������->���������� ����� ����������!\n �� ������ �������� ���������� ��������� �� ��������� ����� �� ��������� Enter.\n\n";
	std::cout << "�� �������� ����������� \"to\" ����� 䳺������� =))\n\n";
	std::cout << "���� �� ������ �������� ���������� ������ /stop \n";
	std::cout << "_________________________________________________________________________" << std::endl;
	std::random_device rd;
	std::mt19937 r(rd());
	std::shuffle(m_word_bank.begin(), m_word_bank.end(), r);

	std::string ans;
	for (auto iter = m_word_bank.begin(); iter != m_word_bank.end(); ++iter)
	{
		if (iter->m_ua2 != "0")
			std::cout << iter->m_ua1 << ", " << iter->m_ua2 << " - ";
		else
			std::cout << iter->m_ua1 << " - ";

		getline(std::cin, ans);
		if (ans == "/stop")
			break;

		if (ans != iter->m_eng)
			std::cout << "������! ��������� ������� \"" << iter->m_eng << "\"\n";

		std::cout << std::endl;
	}
}

void Application::fromEngTrain() // ³������ �� ���������� ��������� � ��������� ���� �� ���������. ���� ������ ��������� �� ������� fromuaTrain(), ��� ���������� ������� �������� ����� �� �� �������� ���������.
{
	std::cout << "\n�� ������ ���������->���������� ����� ����������!\n �� ������ �������� ���������� ��������� �� ��������� ����� �� ��������� Enter.\n\n";
	std::cout << "���� ����� ��� ����� �� ���� ��������, ��������� ������� ������ ��������, ��������� �� ����� �� ��������� (��������� \"light - ������, ������\")\n";
	std::cout << "������ (���� �� ������ ����� ��������) ��� ���� �������� ������� �������.\n\n";
	std::cout << "���� �� ������ �������� ���������� ������ /stop\n";
	std::cout << "_____________________________________________________________________________________" << std::endl;
	std::random_device rd;
	std::mt19937 r(rd());
	std::shuffle(m_word_bank.begin(), m_word_bank.end(), r);

	std::string ans;
	for (auto iter = m_word_bank.begin(); iter != m_word_bank.end(); ++iter)
	{
		std::cout << iter->m_eng << " - ";

		getline(std::cin, ans);
		if (ans == "/stop")
			break;

		if ((iter->m_mandatory_meaning == true) && (ans == iter->m_ua1))
			std::cout << "�� ����� �� ���� �������� - " << "\"" << iter->m_ua2 << "\"\n";
		else if ((iter->m_mandatory_meaning == true) && (ans == iter->m_ua2))
			std::cout << "�� ����� �� ���� �������� - " << "\"" << iter->m_ua1 << "\"\n";
		else if ((iter->m_mandatory_meaning == true) && (ans != iter->m_ua1 + ", " + iter->m_ua2) && (ans != iter->m_ua2 + ", " + iter->m_ua1))
		{
			if (iter->m_ua2 != "0")
				std::cout << "������! ��������� ������� \"" << iter->m_ua1 << ", " << iter->m_ua2 << "\"\n";
			else
				std::cout << "������! ��������� ������� \"" << iter->m_ua1 << "\"\n";
		}

		if ((iter->m_mandatory_meaning == false) && (ans != iter->m_ua1) && (ans != iter->m_ua2) && (ans != iter->m_ua1 + ", " + iter->m_ua2) && (ans != iter->m_ua2 + ", " + iter->m_ua1))
		{
			if (iter->m_ua2 != "0")
				std::cout << "������! ��������� ������� \"" << iter->m_ua1 << ", " << iter->m_ua2 << "\"\n";
			else
				std::cout << "������! ��������� ������� \"" << iter->m_ua1 << "\"\n";
		}
			
		std::cout << std::endl;
	}
}