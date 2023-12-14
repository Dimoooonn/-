#include "Application.h"

void Application::run()  //  Ця функція відповідає за запуск додатку і управління його основним меню.
{
	bool flag = true;
	int k;
	while (flag) //Цикл, який продовжується, поки змінна flag є істинною. У цьому циклі виводяться опції меню для користувача і зчитується його вибір.
	//Залежно від вибору користувача виконуються певні дії, такі як створення словника слів або тренування перекладу. Якщо користувач вибирає опцію "4", програма закривається.
	{ 
		std::cout << std::endl << "1 - Створити словник слів" << std::endl;
		std::cout << "2 - Почати тренування переклдаду з Української на Англійську" << std::endl;
		std::cout << "3 - Почати тренування переклдаду з Англійської на Українську" << std::endl;
		std::cout << "4 - Закрити програму" << std::endl;
		std::cin >> k;
		std::cin.get();

		switch (k)
		{
		case 1:
		{
			std::string filename;
			std::cout << std::endl << "Будь ласка, введіть адрес та ім'я файлу Словника слів (не вказуючи розширення файлу):" << std::endl;
			getline(std::cin, filename);
			filename += ".txt";
			createSet(filename);
			std::cout << std::endl << "Словник слів був успішно створений!\nВи можете почати тренування." << std::endl;
			break;
		}
		case 2:
			if (m_word_bank.empty())
				std::cout << std::endl << "Ви не створили словник слів. Виберіть перший пункт меню і спробуйте ще раз!" << std::endl;
			else
			{
				fromuaTrain();
				std::cout << "\n Тренування закінчено!\n";
			}
			break;
		case 3:
			if (m_word_bank.empty())
				std::cout << std::endl << "Ви не створили словник слів. Виберіть перший пункт меню і спробуйте ще раз!" << std::endl;
			else
			{
				fromEngTrain();
				std::cout << "\n Тренування закінчено!\n";
			}
			break;
		case 4:
			flag = false;
			break;
		default:
			std::cout << "\nВи не вибрали жодного пункту меню. Спробуйте ще раз!\n";
			break;
		}
	}
	std::cout << "\nПрограму закрито!\n";
}

void Application::createSet(std::string filename) //Ця функція відповідає за створення словника слів. Вона отримує адресу та ім'я файлу словника слів у вигляді рядка filename. Функція зчитує дані з файлу і створює множину слів m_word_bank, яка використовується для тренування перекладу.
{
	std::ifstream dictionary(filename);
	std::vector<Word> Bank;
	std::string word_pair;

	if (!dictionary)
	{
		std::cout << "Трапилась помилка пов'язана з файлами!";
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

void Application::printSet() //Ця функція виводить на екран словник слів, збережений у множині m_word_bank. Кожен рядок містить англійське слово та його український переклад.
{
	for (auto iter = m_word_bank.cbegin(); iter != m_word_bank.cend(); ++iter)
	{
		if (iter->m_ua2 == "0")
			std::cout << iter->m_eng << " - " << iter->m_ua1 << std::endl;
		else
			std::cout << iter->m_eng << " - " << iter->m_ua1 << ", " << iter->m_ua2 << std::endl;
	}
}

void Application::fromuaTrain() //Ця функція відповідає за тренування перекладу з української мови на англійську. Вона використовує словник слів m_word_bank, який має бути створений перед початком тренування. Функція пропонує користувачеві вводити українські слова та їх англійські переклади і додає їх до словника. Тренування завершується, коли користувач вирішує зупинити введення.


{
	std::cout << "\nВи обрали Українсько->Англійський режим тренування!\n Ви повинні написати англійський еквівалент на українське слово та натиснути Enter.\n\n";
	std::cout << "Не забудьте використати \"to\" перед дієсловами =))\n\n";
	std::cout << "Якщо ви хочете закінчити тренування введіть /stop \n";
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
			std::cout << "Невірно! Правильна відповідь \"" << iter->m_eng << "\"\n";

		std::cout << std::endl;
	}
}

void Application::fromEngTrain() // Відповідає за тренування перекладу з англійської мови на українську. Вона працює аналогічно до функції fromuaTrain(), але користувач вводить англійські слова та їх українські переклади.
{
	std::cout << "\nВи обрали Англійсько->Український режим тренування!\n Ви повинні написати український еквівалент на англійське слово та натиснути Enter.\n\n";
	std::cout << "Якщо слово або вираз має інше значення, необхідно вводити обидва значення, розділяючи їх комою та пропуском (Наприклад \"light - світлий, легкий\")\n";
	std::cout << "Інакше (якщо ви забули друге значення) вам буде показано відсутню відповідь.\n\n";
	std::cout << "Якщо ви хочете закінчити тренування введіть /stop\n";
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
			std::cout << "Це слово має інше значення - " << "\"" << iter->m_ua2 << "\"\n";
		else if ((iter->m_mandatory_meaning == true) && (ans == iter->m_ua2))
			std::cout << "Це слово має інше значення - " << "\"" << iter->m_ua1 << "\"\n";
		else if ((iter->m_mandatory_meaning == true) && (ans != iter->m_ua1 + ", " + iter->m_ua2) && (ans != iter->m_ua2 + ", " + iter->m_ua1))
		{
			if (iter->m_ua2 != "0")
				std::cout << "Невірно! Правильна відповідь \"" << iter->m_ua1 << ", " << iter->m_ua2 << "\"\n";
			else
				std::cout << "Невірно! Правильна відповідь \"" << iter->m_ua1 << "\"\n";
		}

		if ((iter->m_mandatory_meaning == false) && (ans != iter->m_ua1) && (ans != iter->m_ua2) && (ans != iter->m_ua1 + ", " + iter->m_ua2) && (ans != iter->m_ua2 + ", " + iter->m_ua1))
		{
			if (iter->m_ua2 != "0")
				std::cout << "Невірно! Правильна відповідь \"" << iter->m_ua1 << ", " << iter->m_ua2 << "\"\n";
			else
				std::cout << "Невірно! Правильна відповідь \"" << iter->m_ua1 << "\"\n";
		}
			
		std::cout << std::endl;
	}
}