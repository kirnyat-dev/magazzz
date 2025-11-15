#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>

// ó÷åòíûå çàïèñè
const size_t userSize = 2;
std::string userStatus[3]{ "Ñóïåð Àäìèíèñòðàòîð", "Àäìèíèñòðàòîð", "Ñîòðóäíèê" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "admin","user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[2] };
std::string currentStatus;
//
// ñêëàä
size_t storageSize = 0;
bool staticStorageCreated = false;

int* idArr;
std::string* nameArr;
unsigned int* countArr;
double* priceArr;

void CreateStorage();
void ShowStorage(int mode);
void AddStorageItem();
void RemoveStorageItem();
void ChangePrice();

void ChangeStorage();
void AddNewItem();

template <typename Arr>
void FillArray(Arr* dynamicArr, Arr* staticArr, size_t size);
//
// ñëóæåáíûå
void Start();
bool Login();
void ShowSuperAdminMenu();
bool IsNumber(const std::string& str);

inline void GetLine(std::string& str);
inline void Err(int time = 1500);
//

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Start();
	delete[]loginArr, passArr, statusArr;

	if (staticStorageCreated)
	{
		delete[]idArr, nameArr, countArr, priceArr;
	}
}

void CreateStorage()
{
	const int staticSize = 10;

	int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10 };
	std::string name[staticSize]
	{
		"Glock 19", "Smith & Wesson 686", "ÀÊ-47",
		"Winchester Model 700", "Remington 870",
		"Franchi Affinity", "Marlin 1895",
		"Ruger 10/20", "Remington 700",
		"Weihrauch HW 100"
	};
	unsigned int count[staticSize]{ 25,15,20,8,20,8,6,30,5,6 };
	double price[staticSize]{ 75000.0,135000.0,90000.0,125000.0,80000.0,95000.0,155000.0,55000.0,210000.0,120000.0 };

	storageSize = staticSize;

	idArr = new int[storageSize];
	nameArr = new std::string[storageSize];
	countArr = new unsigned int[storageSize];
	priceArr = new double[storageSize];
	staticStorageCreated = true;

	FillArray(idArr, id, storageSize);
	FillArray(priceArr, price, storageSize);
	FillArray(countArr, count, storageSize);
	FillArray(nameArr, name, storageSize);
}

void ShowStorage(int mode)
{
	system("cls");

	if (mode == 0)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "íàçâàíèå òîâàðà\t\t" <<
			"Öåíà\t" << "Êîë-âî\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << '\t' << std::left << std::setw(25) << nameArr[i]
				<< "\t" << priceArr[i] << "\t" << countArr[i] << "\n";
		}
		system("pause");
		system("cls");
	}
	else if (mode == 1)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "íàçâàíèå òîâàðà\t\t" <<
			"Êîë-âî\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << '\t' << std::left << std::setw(25) << nameArr[i]
				<< "\t" << countArr[i] << "\n";
		}
	}
	else if (mode == 2)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "íàçâàíèå òîâàðà\t\t" <<
			"Öåíà\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << '\t' << std::left << std::setw(25) << nameArr[i]
				<< "\t" << priceArr[i] << "\n";
		}
	}
	else
	{
		std::cout << "StorageMode Error\n\n";
		std::invalid_argument("StorageMode Error");
	}
}

void AddStorageItem()
{
	std::string chooseId, chooseCount, choose;
	int id = 0;
	unsigned int count = 0;
	while (true)
	{
		system("cls");
		ShowStorage(1);

		std::cout << "Ââåäèòå ID òîâàðà èëè \"exit\" äëÿ âûõîäà: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Îòìåíà îïåðàöèè ïîïîëíåíèÿ òîâàðà\n";
			Sleep(1500);
			break;
		}
		std::cout << "Ââåäèòå êîë-âî äëÿ åãî ïîïîëíåíèÿ: ";
		GetLine(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > 50)
			{
				std::cout << "Íåêîððåêòíûé id èëè êîë-âî\nÌàêñèìàëüíîå êîë-âî 50\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] <<
					"\t" << countArr[id] << " --> " << countArr[id] + count << "\n\n";
				std::cout << "Ïîäòâåðäèòü?\n1 - Äà\n2 - Íåò\nÂâîä: ";
				GetLine(choose);
				if (choose == "1")
				{
					countArr[id] += count;
					std::cout << "Òîâàð óñïåøíî ïîïîëíåí\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Îòìåíà ïîïîëíåíèÿ òîâàðà\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void RemoveStorageItem()
{
	std::string chooseId, chooseCount, choose;
	int id = 0;
	unsigned int count = 0;
	while (true)
	{
		system("cls");
		ShowStorage(1);

		std::cout << "Ââåäèòå ID òîâàðà èëè \"exit\" äëÿ âûõîäà: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Îòìåíà îïåðàöèè ñïèñàíèÿ òîâàðà\n";
			Sleep(1500);
			break;
		}
		std::cout << "Ââåäèòå êîë-âî äëÿ åãî ñïèñàíèÿ: ";
		GetLine(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
			{
				std::cout << "Íåêîððåêòíûé id èëè êîë-âî\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] <<
					"\t" << countArr[id] << " --> " << countArr[id] - count << "\n\n";
				std::cout << "Ïîäòâåðäèòü?\n1 - Äà\n2 - Íåò\nÂâîä: ";
				GetLine(choose);
				if (choose == "1")
				{
					countArr[id] -= count;
					std::cout << "Òîâàð óñïåøíî ñïèñàí\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Îòìåíà ñïèñàíèÿ òîâàðà\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}
		}
	}
}

void ChangePrice()
{
	std::string chooseId, newPrice, choose;
	int id = 0;
	double Price = 0.0;
	while (true)
	{
		system("cls");
		ShowStorage(2);

		std::cout << "Ââåäèòå ID òîâàðà èëè \"exit\" äëÿ âûõîäà: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Îòìåíà îïåðàöèè èçìåíåíèå öåíû\n";
			Sleep(1500);
			break;
		}
		std::cout << "Ââåäèòå íîâóþ öåíó: ";
		GetLine(newPrice);


		if (IsNumber(chooseId) && IsNumber(newPrice))
		{
			id = std::stoi(chooseId) - 1;
			Price = std::stoi(newPrice);

			if (id < 0 || id > storageSize || Price < 0.0 || Price > 500000)
			{
				std::cout << "Íåêîððåêòíûé id èëè öåíà\nÌàêñèìàëüíàÿ öåíà 500000\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] <<
					"\t" << priceArr[id] << " --> " << Price << "\n\n";
				std::cout << "Ïîäòâåðäèòü?\n1 - Äà\n2 - Íåò\nÂâîä: ";
				GetLine(choose);
				if (choose == "1")
				{
					priceArr[id] = Price;
					std::cout << "Öåíà óñïåøíà èçìåíåíà\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Îòìåíà èçìåíåíèå öåíû\n";
					Sleep(1500);
				}
				else
				{
					Err();
				}
			}


		}
	}
}

void ChangeStorage()
{
	std::string choose;

	while (true)
	{
		system("cls");
		std::cout << "1 - Äîáàâèòü íîâûé òîâàð\n";
		std::cout << "2 - Èçìåíèòü èìÿ òîâàðà\n";
		std::cout << "3 - Óäàëèòü òîâàð\n";
		std::cout << "0 - âûéòè èç ðåäàêòîðà\n";
		std::cout << "Ââîä: ";
		GetLine(choose);

		if (choose == "1")
		{
			AddNewItem();
		}
		else if (choose == "2")
		{

		}
		else if (choose == "3")
		{

		}
		else if (choose == "0")
		{
			break;
		}
		else
		{
			Err();
		}
	}
}

void AddNewItem()
{
	std::string newName, newPrice, newCount, choose;
	double price = 0.0;
	unsigned int count = 0;
	bool exit = true;

	while (true)
	{

		while (true)
		{
			system("cls");
			std::cout << "\tÄîáàâëåíèå íîâîãî òîâàðà!\n\nÂåäèòå \"exit\" äëÿ ïðåêðàùåíèé îïåðàöèè\n";
			std::cout << "Ââåäèòå íàçâàíèå íîâîãî òîâàðà: ";
			GetLine(newName);
			if (newName == "exit")
			{
				std::cout << "Îïåðàöèÿ äîáàâëåíèÿ òîâàðà ïðåðâàíà!";
				Sleep(1500);
				exit = false;
				break;
			}
			
			if (newName.size() <= 0 || newName.size() >= 60)
			{
				std::cout << "Îøèáêà èìåíè. Ìàêñèìàëüíàÿ äëèíà 60 ñèìâîëîâ\n";
			}
			else
			{
				break;
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "\tÄîáàâëåíèå íîâîãî òîâàðà!\n\nÂåäèòå \"exit\" äëÿ ïðåêðàùåíèé îïåðàöèè\n";
			std::cout << "Ââåäèòå êîëè÷åñòâî íîâîãî òîâàðà: ";
			GetLine(newCount);
			if (newCount == "exit")
			{
				std::cout << "Îïåðàöèÿ äîáàâëåíèÿ òîâàðà ïðåðâàíà!";
				Sleep(1500);
				exit = false;
				break;
			}

			if (IsNumber(newCount))
			{
				count = std::stoi(newCount);
				if (count > 50)
				{
					std::cout << "Îøèáêà ìàêñèìàëüíîãî ðàçìåðà òîâàðà. Íå áîëåå 50 åä.\n";
					Sleep(1500);
				}
				else
				{
					break;
				}
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "\tÄîáàâëåíèå íîâîãî òîâàðà!\n\nÂåäèòå \"exit\" äëÿ ïðåêðàùåíèé îïåðàöèè\n";
			std::cout << "Ââåäèòå öåíó íîâîãî òîâàðà: ";
			GetLine(newPrice);
			if (newPrice == "exit")
			{
				std::cout << "Îïåðàöèÿ äîáàâëåíèÿ òîâàðà ïðåðâàíà!";
				Sleep(1500);
				exit = false;
				break;
			}

			if (IsNumber(newPrice))
			{
				price = std::stoi(newPrice);
				if (price > 499999.9)
				{
					std::cout << "Îøèáêà ìàêñèìàëüíîé öåíû òîâàðà. Íå áîëåå 500000 ðóá.\n";
					Sleep(1500);
				}
				else
				{
					break;
				}
			}
		}

		while (exit)
		{
			std::cout << "Íîâûé òîâàð: " << newName << "\n";
			std::cout << "êîë-âî: " << count << "\n";
			std::cout << "öåíà: " << price << "\n";
			std::cout << "Ïîäòâåðäèòü?\n1 - Äà\n2 - Íåò\nÂâîä: ";
			GetLine(choose);
			if (choose == "1")
			{
				storageSize++;
				int* idArrTemp = new int[storageSize];
				std::string* nameArrTemp = new std::string[storageSize];
				unsigned int* countArrTemp = new unsigned int[storageSize];
				double* priceArrTemp = new double[storageSize];

				FillArray(idArrTemp, idArr, storageSize - 1);
				FillArray(nameArrTemp, nameArr, storageSize - 1);
				FillArray(countArrTemp, countArr, storageSize - 1);
				FillArray(priceArrTemp, priceArr, storageSize - 1);

				idArrTemp[storageSize - 1] = storageSize;
				nameArrTemp[storageSize - 1] = newName;
				countArrTemp[storageSize - 1] = count;
				priceArrTemp[storageSize - 1] = price;

				std::swap(idArr, idArrTemp);
				std::swap(nameArr, nameArrTemp);
				std::swap(countArr, countArrTemp);
				std::swap(priceArr, priceArrTemp);

				delete[]idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
				exit = false;
			}
			else if (choose == "2")
			{
				std::cout << "Îòìåíà";
				Sleep(1500);
			}
			else
			{
				Err();
			}
		}


		if (exit == false)
		{
			break;
		}
	}
}

void Start()
{
	std::string choose;
	std::cout << "\n\n\n\t\tÓáèòüËåãêî\n\n\n";
	if (Login())
	{
		if (currentStatus == userStatus[0])
		{
			while (true)
			{
				std::cout << "Âûáåðòå ñêëàä\n1 - Ãîòîâûé\n2 - Ñîçäàòü íîâûé\nÂâîä: ";
				GetLine(choose);
				if (choose == "1")
				{
					CreateStorage();
					system("cls");
					ShowSuperAdminMenu();

					break;
				}
				if (choose == "2")
				{
					break;
				}
				else
				{
					Err();
				}
			}
		}
		else if (currentStatus == userStatus[1])
		{
			CreateStorage();
		}
		else if (currentStatus == userStatus[2])
		{
			CreateStorage();
		}
	}
	else
	{
		system("cls");
		std::cout << "Çàâåðøåíèå ðàáîòû ìàãàçèíà\n\n";
	}
}

bool Login()
{
	std::string login, pass;
	while (true)
	{
		std::cout << "Ââåäèòå ëîãèí: ";
		GetLine(login);
		std::cout << "Ââåäèòå ïàðîëü: ";
		GetLine(pass);

		if (login == "exit" && pass == "exit")
		{
			currentStatus = "";
			return false;
		}

		for (size_t i = 0; i < userSize; i++)
		{
			if (login == loginArr[i] && pass == passArr[i])
			{
				system("cls");
				std::cout << "Ïîëüçîâàòåëü: " << loginArr[i] << " Äîáðî ïîæàëîâàòü!\n";
				std::cout << "Âàø ñòàòóñ: " << statusArr[i] << "\n\n";
				currentStatus = statusArr[i];
				return true;
			}
		}
		Err();
	}
}

void ShowSuperAdminMenu()
{
	std::string choose;

	while (true)
	{
		std::cout << "1 - Íà÷àòü ïðîäàæó\n";
		std::cout << "2 - Ïîêàçàòü ñêëàä\n";
		std::cout << "3 - Ïîïîëíèòü ñêëàä\n";
		std::cout << "4 - Ñïèñàòü òîâàð\n";
		std::cout << "5 - Èçìåíèòü öåíó\n";
		std::cout << "6 - Ðåäàêòèðîâàòü ñêëàä\n";
		std::cout << "7 - Ðåäàêòèðîâàòü ïåðñîíàë\n";
		std::cout << "8 - Îò÷¸ò î ïðèáûëè\n";
		std::cout << "0 - Çàêðûòü ñìåíó\n";
		std::cout << "Ââîä: ";
		GetLine(choose);
		if (choose == "1")
		{

		}
		else if (choose == "2")
		{
			ShowStorage(0);
		}
		else if (choose == "3")
		{
			AddStorageItem();
		}
		else if (choose == "4")
		{
			RemoveStorageItem();
		}
		else if (choose == "5")
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{

		}
		else if (choose == "8")
		{

		}
		else if (choose == "0")
		{

		}
		else
		{
			Err();
		}
	}
}

bool IsNumber(const std::string& str)
{
	if (str.size() <= 0 || str.size() >= 10)
	{
		std::cout << "Íåêîððåêòíûé ââîä\n";
		std::cout << "Îøèáêà äëèíû ÷èñëà. Îò 1 äî 9 öèôð âêëþ÷èòåëüíî\n\n";
		Sleep(1500);
		return false;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Íåêîððåêòíûé ââîä\n";
			std::cout << "Ââåä¸íàÿ äàííûå íå ÿâëÿþòñÿ ÷èñëîì\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
}

inline void GetLine(std::string& str)
{
	std::getline(std::cin, str, '\n');
}

inline void Err(int time)
{
	std::cout << "Íåêîððåêòíûé ââîä\n";
	Sleep(time);
	system("cls");
}

template<typename Arr>
void FillArray(Arr* dynamicArr, Arr* staticArr, size_t size)
{
	for (int i = 0; i < size; i++)
	{
		dynamicArr[i] = staticArr[i];
	}
}
