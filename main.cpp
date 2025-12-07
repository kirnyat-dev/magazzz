#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <unordered_set>

// учетные записи
size_t userSize = 2;
size_t staffCount = 1;
std::string userStatus[3]{ "Супер Администратор", "Администратор", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "admin","user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[2] };
double* awardArr = new double[userSize] {0.0, 0.0};
unsigned int* userIdArr = new unsigned int[userSize] {1, 2};
std::string currentStatus;
int currentId = 0;

void ChangeUsers();
void AddNewUser();
void ShowUsers(int mode = 0);
void ChangePass();
void DeleteUser();

// склад
size_t storageSize = 0;
bool staticStorageCreated = false;

int* idArr;
std::string* nameArr;
unsigned int* countArr;
double* priceArr;

void CreateStorage(int mode = 0);
void ShowStorage(int mode = 0);
void AddStorageItem();
void RemoveStorageItem();
void ChangePrice();

void ChangeStorage();
void AddNewItem();
void ChangeName();
void DeleteItem();

template <typename Arr>
void FillArray(Arr* dynamicArr, Arr* staticArr, size_t size);

// Продажи
size_t checkSize = 0;
int* idArrCheck;
std::string* nameArrCheck;
unsigned int* countArrCheck;
double* priceArrCheck;
double* totalPriceArrCheck;

double cash = 30000 + rand() % 70000;
double cashIncome = 0.0;
double bankIncome = 0.0;

void Selling();
void CheckArrAppend();
void PrintCheck(double& totalSum);
void StorageReturner();

// служебные
void Start();
bool Login();
bool Logout();
void ShowSuperAdminMenu();
void ShowAdminMenu();
void ShowUserMenu();
bool IsNumber(const std::string& str);
bool CheckLogin(const std::string& str);
bool CheckPass(const std::string& str);
void ShowIncome();

inline void GetLine(std::string& str);
inline void Err(int time = 1500);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Start();
	delete[]loginArr;
	delete[]passArr;
	delete[]statusArr;
	delete[]awardArr;
	delete[]userIdArr;

	if (staticStorageCreated)
	{
		delete[]idArr;
		delete[]nameArr;
		delete[]countArr;
		delete[]priceArr;
	}

	return 0;
}

void ChangeUsers()
{
	std::string choose;

	while (true)
	{
		system("cls");
		std::cout << "1 - Добавить новый пользователя\n";
		std::cout << "2 - Показать пользователей\n";
		std::cout << "3 - Изменить пароль\n";
		std::cout << "4 - Удалить пользователя\n";
		std::cout << "0 - выйти из редактора\n";
		std::cout << "Ввод: ";
		GetLine(choose);

		if (choose == "1")
		{
			AddNewUser();
		}
		else if (choose == "2" && userSize > 1)
		{
			ShowUsers(0);
		}
		else if (choose == "3" && userSize > 1)
		{
			ChangePass();
		}
		else if (choose == "4" && userSize > 1)
		{
			DeleteUser();
		}
		else if (choose == "0")
		{
			system("cls");
			break;
		}
		else
		{
			if (userSize <= 1)
			{
				std::cout << "Пользоветелей нет!\n";
			}
			Err();
		}
	}
}

void AddNewUser()
{
	std::string newLogin, newPass, newStatus, choose;
	bool exit = true;
	while (true)
	{
		exit = true;

		while (true)
		{
			system("cls");
			std::cout << "\tСоздание нового пользователя!\n\n";
			std::cout << "Введите логин нового пользователя или \"exit\" для выхода: ";
			GetLine(newLogin);
			if (newLogin == "exit")
			{
				std::cout << "Создание нового пользователя прервано!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (CheckLogin(newLogin))
			{
				break;
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "\tСоздание нового пользователя!\n\n";
			std::cout << "Введите пароль нового пользователя или \"exit\" для выхода: ";
			GetLine(newPass);
			if (newPass == "exit")
			{
				std::cout << "Создание нового пользователя прервано!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (CheckPass(newPass))
			{
				break;
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "\tСоздание нового пользователя!\n\n";
			std::cout << "Введите статус нового пользователя или \"exit\" для выхода\n";
			std::cout << "1 - Администратор\n2 - Сотрудник\nВвод: ";
			GetLine(choose);
			if (choose == "exit")
			{
				std::cout << "Создание нового пользователя прервано!\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			if (choose == "1")
			{
				newStatus = userStatus[1];
				break;
			}
			else if (choose == "2")
			{
				newStatus = userStatus[2];
				break;
			}
			else
			{
				Err();
			}
		}

		while (exit)
		{
			std::cout << "Пользователь: " << newLogin << "\n";
			std::cout << "Пароль: " << newPass << "\n";
			std::cout << "Статус: " << newStatus << "\n";
			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
			GetLine(choose);
			if (choose == "1")
			{
				userSize++;
				std::string* loginArrTemp = new std::string[userSize];
				std::string* passArrTemp = new std::string[userSize];
				std::string* statusArrTemp = new std::string[userSize];
				double* awardArrTemp = new double[userSize];
				unsigned int* userIdArrTemp = new unsigned int[userSize];

				FillArray(loginArrTemp, loginArr, userSize - 1);
				FillArray(passArrTemp, passArr, userSize - 1);
				FillArray(statusArrTemp, statusArr, userSize - 1);
				FillArray(awardArrTemp, awardArr, userSize - 1);
				FillArray(userIdArrTemp, userIdArr, userSize - 1);

				loginArrTemp[userSize - 1] = newLogin;
				passArrTemp[userSize - 1] = newPass;
				statusArrTemp[userSize - 1] = newStatus;
				awardArrTemp[userSize - 1] = 0.0;
				userIdArrTemp[userSize - 1] = userSize;

				std::swap(loginArr, loginArrTemp);
				std::swap(passArr, passArrTemp);
				std::swap(statusArr, statusArrTemp);
				std::swap(awardArr, awardArrTemp);
				std::swap(userIdArr, userIdArrTemp);

				delete[]loginArrTemp;
				delete[]passArrTemp;
				delete[]statusArrTemp;
				delete[]awardArrTemp;
				delete[]userIdArrTemp;

				if (newStatus == userStatus[2])
				{
					staffCount++;
				}

				std::cout << "Подготовка...\n";
				Sleep(2000);
				std::cout << "Пользователь успешно создан\n\n";
				Sleep(1500);
				exit = false;
				break;
			}
			else if (choose == "2")
			{
				std::cout << "Отмена создания пользователя\n";
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

void ShowUsers(int mode)
{
	system("cls");

	if (mode == 0)
	{
		std::cout << "№\t" << std::left << std::setw(20) << "Логин\t"
			<< std::left << std::setw(30) << "Пароль\t" << "Статус\n";

		for (size_t i = 1; i < userSize; i++)
		{
			std::cout << userIdArr[i] << '\t' << std::left << std::setw(20) << loginArr[i]
				<< std::left << std::setw(30) << passArr[i] << statusArr[i] << "\n";
		}
		system("pause");
		system("cls");
	}
	if (mode == 1)
	{
		std::cout << "№\t" << std::left << std::setw(15) << "Логин\t" << std::setw(15) <<
			"Пароль\t" << "Статус\n";

		for (size_t i = 1; i < userSize; i++)
		{
			std::cout << userIdArr[i] << '\t' << std::left << std::setw(20) << loginArr[i]
				<< std::left << std::setw(30) << passArr[i] << statusArr[i] << "\n";
		}
		Sleep(1500);
		system("cls");
	}
}

void ChangePass()
{
	std::string newPass1, newPass2, choose;
	int userNumber = 0;
	int isAdmin = 0;

	while (true)
	{
		if (currentStatus == userStatus[0])
		{
			ShowUsers(1);
			isAdmin = 0;
		}
		else
		{
			ShowUsers(0);
			isAdmin = 1;
		}

		std::cout << "\nВыберите номер пользователя для смены пароля или \"exit\" для выхода: ";
		GetLine(choose);
		if (choose == "exit")
		{
			std::cout << "Отмена изменения пароля!\n";
			Sleep(1500);
			break;
		}
		else if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);
			size_t userIndex = -1;

			for (size_t i = 0; i < userSize; ++i)
			{
				if (userIdArr[i] == userNumber)
				{
					userIndex = i;
					break;
				}
			}

			if (userIndex == (size_t)-1 || userIndex < (size_t)isAdmin || userIndex >= userSize)
			{
				std::cout << "Пользователь с таким номером не существует!\n";
				Sleep(1500);
			}
			else
			{
				while (true)
				{
					system("cls");

					if (currentStatus == userStatus[1] && statusArr[userIndex] == userStatus[1])
					{
						std::cout << "Нельзя менять пароли Администраторам!\n";
						Sleep(1500);
						break;
					}

					std::cout << "Введите новый пароль для пользователя " << loginArr[userIndex] << " : ";
					GetLine(newPass1);
					std::cout << "Подтвердите пароль для пользователя " << loginArr[userIndex] << " : ";
					GetLine(newPass2);
					if (CheckPass(newPass1) && CheckPass(newPass2) && newPass1 == newPass2)
					{
						passArr[userIndex] = newPass1;
						std::cout << "Успешно\n";
						Sleep(1500);
						break;
					}
					else
					{
						std::cout << "Повторите попытку\n";
						Sleep(1500);
					}
				}
			}
		}
		else
		{
			Err();
		}

	}
}

void DeleteUser()
{
	std::string chooseNumber, checkPass, choose;
	int userNumber = 0;

	while (true)
	{
		if (currentStatus == userStatus[0])
		{
			if (userSize < 2)
			{
				std::cout << "Нет доступных пользователей для удаления!\n";
				Sleep(1500);
				return;
			}
		}

		else if (currentStatus == userStatus[1])
		{
			if (staffCount < 1)
			{
				std::cout << "Нет доступных пользователей для удаления!\n";
				Sleep(1500);
				return;
			}
		}

		ShowUsers(0);

		std::cout << "\nВыберите номер пользователя для удаления или \"exit\" для выхода: ";
		GetLine(choose);
		if (choose == "exit")
		{
			std::cout << "Отмена удаления пароля!\n";
			Sleep(1500);
			break;
		}
		else if (IsNumber(choose))
		{
			userNumber = std::stoi(choose);
			size_t userIndexToRemove = (size_t)-1;
			int isAdmin = 1;

			for (size_t i = 0; i < userSize; ++i)
			{
				if (userIdArr[i] == userNumber)
				{
					userIndexToRemove = i;
					break;
				}
			}

			if (userIndexToRemove == (size_t)-1 || userIndexToRemove < (size_t)isAdmin || userIndexToRemove >= userSize)
			{
				std::cout << "Пользователя с таким номером не существует!\n";
				Sleep(1500);
				continue;
			}

			while (true)
			{
				system("cls");

				if (currentStatus == userStatus[1] && statusArr[userIndexToRemove] != userStatus[2])
				{
					std::cout << "Нельзя удалять администратора\n";
					Sleep(1500);
					break;
				}

				std::cout << "Удаление пользователя: " << loginArr[userIndexToRemove] << "\n";
				std::cout << "Для подтверждения введите пароль супер администратора или \"exit\" для выхода: ";
				GetLine(checkPass);

				if (checkPass == "exit")
				{
					std::cout << "Отмена удаления пользователя: " << loginArr[userIndexToRemove] << "\n\n";
					Sleep(1500);
					break;
				}

				else if (checkPass == passArr[0])
				{
					if (statusArr[userIndexToRemove] == userStatus[2])
					{
						staffCount--;
					}

					userSize--;
					std::string* loginArrTemp = new std::string[userSize];
					std::string* passArrTemp = new std::string[userSize];
					std::string* statusArrTemp = new std::string[userSize];
					double* awardArrTemp = new double[userSize];
					unsigned int* userIdArrTemp = new unsigned int[userSize];

					for (size_t i = 0, c = 0; i < userSize; i++, c++)
					{
						if (userIndexToRemove == c)
						{
							c++;
						}
						loginArrTemp[i] = loginArr[c];
						passArrTemp[i] = passArr[c];
						statusArrTemp[i] = statusArr[c];
						awardArrTemp[i] = awardArr[c];
						userIdArrTemp[i] = userIdArr[c];
					}

					std::swap(loginArrTemp, loginArr);
					std::swap(passArrTemp, passArr);
					std::swap(statusArrTemp, statusArr);
					std::swap(awardArrTemp, awardArr);
					std::swap(userIdArrTemp, userIdArr);

					delete[]loginArrTemp;
					delete[]passArrTemp;
					delete[]statusArrTemp;
					delete[]awardArrTemp;
					delete[]userIdArrTemp;

					std::cout << "Идет подготовка... ";
					Sleep(2000);
					std::cout << "Пользователь успешно удалён!\n\n";
					Sleep(1500);
					break;

				}
				else
				{
					std::cout << "Некорректный пароль\n";
					Sleep(1500);
				}
			}
		}
		else
		{
			Err();
		}
	}
}

void CreateStorage(int mode)
{
	if (mode == 0)
	{
		const int staticSize = 10;

		int id[staticSize]{ 1,2,3,4,5,6,7,8,9,10 };
		std::string name[staticSize]
		{
			"Glock 19", "Smith & Wesson 686", "АК-47",
			"Winchester Model 700", "Remington 870",
			"Franchi Affinity", "Marlin 1895",
			"Ruger 10/20", "Remington 700",
			"Weihrauch HW 100"
		};
		unsigned int count[staticSize]{ 25,15,20,8,20,8,6,30,5,6 };
		double price[staticSize]{ 75000.0,135000.0,90000.0,125000.0,80000.0,95000.0,155000.0,55000.0,210000.0,120000.0 };

		if (staticStorageCreated)
		{
			delete[]idArr;
			delete[]nameArr;
			delete[]countArr;
			delete[]priceArr;
			staticStorageCreated = false;
		}

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
	else if (mode == 1)
	{
		std::string choose;
		std::cout << "Создание склада с нуля\n";
		Sleep(2000);
	}
}

void ShowStorage(int mode)
{
	system("cls");

	if (mode == 0)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" <<
			"Цена\t" << "Кол-во\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << '\t' << std::left << std::setw(25) << nameArr[i]
				<< "\t" << std::fixed << std::setprecision(2) << priceArr[i] << "\t" << countArr[i] << "\n";
		}
		system("pause");
		system("cls");
	}
	else if (mode == 1)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" <<
			"Кол-во\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << '\t' << std::left << std::setw(25) << nameArr[i]
				<< "\t" << countArr[i] << "\n";
		}
	}
	else if (mode == 2)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара\t\t" <<
			"Цена\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << '\t' << std::left << std::setw(25) << nameArr[i]
				<< "\t" << std::fixed << std::setprecision(2) << priceArr[i] << "\n";
		}
	}
	else if (mode == 3)
	{
		std::cout << "ID\t" << std::left << std::setw(25) << "Название товара"
			<< "\n";

		for (size_t i = 0; i < storageSize; i++)
		{
			std::cout << idArr[i] << '\t' << std::left << std::setw(25) << nameArr[i] << "\n";
		}
	}
	else
	{
		std::cout << "StorageMode Error\n\n";
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

		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции пополнения товара\n";
			Sleep(1500);
			break;
		}
		std::cout << "Введите кол-во для его пополнения: ";
		GetLine(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > 50)
			{
				std::cout << "Некорректный id или кол-во\nМаксимальное кол-во 50\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] <<
					"\t" << countArr[id] << " --> " << countArr[id] + count << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				GetLine(choose);
				if (choose == "1")
				{
					countArr[id] += count;
					std::cout << "Товар успешно пополнен\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена пополнения товара\n";
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

		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции списания товара\n";
			Sleep(1500);
			break;
		}
		std::cout << "Введите кол-во для его списания: ";
		GetLine(chooseCount);


		if (IsNumber(chooseId) && IsNumber(chooseCount))
		{
			id = std::stoi(chooseId) - 1;
			count = std::stoi(chooseCount);

			if (id < 0 || id > storageSize - 1 || count < 0 || count > countArr[id])
			{
				std::cout << "Некорректный id или кол-во\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] <<
					"\t" << countArr[id] << " --> " << countArr[id] - count << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				GetLine(choose);
				if (choose == "1")
				{
					countArr[id] -= count;
					std::cout << "Товар успешно списан\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена списания товара\n";
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

		std::cout << "Введите ID товара или \"exit\" для выхода: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции изменение цены\n";
			Sleep(1500);
			break;
		}
		std::cout << "Введите новую цену: ";
		GetLine(newPrice);


		if (IsNumber(chooseId) && IsNumber(newPrice))
		{
			id = std::stoi(chooseId) - 1;
			Price = std::stod(newPrice);

			if (id < 0 || id > storageSize - 1 || Price < 0.0 || Price > 500000)
			{
				std::cout << "Некорректный id или цена\nМаксимальная цена 500000\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] <<
					"\t" << std::fixed << std::setprecision(2) << priceArr[id] << " --> " << Price << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				GetLine(choose);
				if (choose == "1")
				{
					priceArr[id] = Price;
					std::cout << "Цена успешна изменена\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена изменение цены\n";
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
		std::cout << "1 - Добавить новый товар\n";
		std::cout << "2 - Изменить имя товара\n";
		std::cout << "3 - Удалить товар\n";
		std::cout << "0 - выйти из редактора\n";
		std::cout << "Ввод: ";
		GetLine(choose);

		if (choose == "1")
		{
			AddNewItem();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ChangeName();
		}
		else if (choose == "3" && storageSize > 0)
		{
			DeleteItem();
		}
		else if (choose == "0")
		{
			system("cls");
			break;
		}
		else
		{
			if (storageSize == 0)
			{
				std::cout << "Склад пустой!\n";
			}
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
			std::cout << "\tДобавление нового товара!\n\nВедите \"exit\" для прекращений операции\n";
			std::cout << "Введите название нового товара: ";
			GetLine(newName);
			if (newName == "exit")
			{
				std::cout << "Операция добавления товара прервана!";
				Sleep(1500);
				exit = false;
				break;
			}

			if (newName.size() <= 0 || newName.size() >= 30)
			{
				std::cout << "Ошибка имени. Максимальная длина 30 символов\n";
				Sleep(1500);
			}
			else
			{
				break;
			}
		}

		while (exit)
		{
			system("cls");
			std::cout << "\tДобавление нового товара!\n\nВедите \"exit\" для прекращений операции\n";
			std::cout << "Введите количество нового товара: ";
			GetLine(newCount);
			if (newCount == "exit")
			{
				std::cout << "Операция добавления товара прервана!";
				Sleep(1500);
				exit = false;
				break;
			}

			if (IsNumber(newCount))
			{
				count = std::stoi(newCount);
				if (count > 50)
				{
					std::cout << "Ошибка максимального размера товара. Не более 50 ед.\n";
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
			std::cout << "\tДобавление нового товара!\n\nВедите \"exit\" для прекращений операции\n";
			std::cout << "Введите цену нового товара: ";
			GetLine(newPrice);
			if (newPrice == "exit")
			{
				std::cout << "Операция добавления товара прервана!";
				Sleep(1500);
				exit = false;
				break;
			}

			if (IsNumber(newPrice))
			{
				price = std::stod(newPrice);
				if (price > 500000)
				{
					std::cout << "Ошибка максимальной цены товара. Не более 500000 руб.\n";
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
			std::cout << "Новый товар: " << newName << "\n";
			std::cout << "кол-во: " << count << "\n";
			std::cout << "цена: " << std::fixed << std::setprecision(2) << price << "\n";
			std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
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

				delete[]idArrTemp;
				delete[]nameArrTemp;
				delete[]countArrTemp;
				delete[]priceArrTemp;
				std::cout << "Подготовка...\n";
				Sleep(2000);
				std::cout << "Товар успешно добавлен!";
				Sleep(1500);
				break;
			}
			else if (choose == "2")
			{
				std::cout << "Отмена";
				Sleep(1500);
				break;
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

void ChangeName()
{
	std::string newName, choose, chooseId;
	unsigned int id = 0;
	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товараn или \"exit\" для прекращений операции\nВвод: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			std::cout << "Отмена операции измнение названия товара\n";
			Sleep(1500);
			break;
		}
		std::cout << "Введите новое название товара: ";
		GetLine(newName);
		if (newName.size() <= 0 || newName.size() >= 30)
		{
			std::cout << "Ошибка имени. Максимальная длина 30 символов\n";
			Sleep(1500);
		}
		else if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID!";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) <<
					nameArr[id] << " --> " << newName << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				GetLine(choose);
				if (choose == "1")
				{
					nameArr[id] = newName;
					std::cout << "Имя успешно изменено\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена изменение имени\n";
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

void DeleteItem()
{
	std::string chooseId, choose;
	unsigned int id = 0;
	while (true)
	{
		system("cls");
		ShowStorage(3);
		std::cout << "\nВведите ID товара для удаление или \"exit\" для выхода: ";
		GetLine(chooseId);
		if (chooseId == "exit")
		{
			break;
		}

		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;
			if (id < 0 || id > storageSize - 1)
			{
				std::cout << "Ошибка ID!";
				Sleep(1500);
			}
			else
			{
				std::cout << "\n\n";
				std::cout << "Подтвердить?\n1 - Да\n2 - Нет\nВвод: ";
				GetLine(choose);
				if (choose == "1")
				{
					storageSize--;
					int* idArrTemp = new int[storageSize];
					std::string* nameArrTemp = new std::string[storageSize];
					unsigned int* countArrTemp = new unsigned int[storageSize];
					double* priceArrTemp = new double[storageSize];

					for (size_t i = 0, c = 0; i < storageSize; i++, c++)
					{
						if (id == c)
						{
							c++;
						}
						idArrTemp[i] = i + 1;
						nameArrTemp[i] = nameArr[c];
						countArrTemp[i] = countArr[c];
						priceArrTemp[i] = priceArr[c];
					}

					std::swap(idArr, idArrTemp);
					std::swap(nameArr, nameArrTemp);
					std::swap(countArr, countArrTemp);
					std::swap(priceArr, priceArrTemp);

					delete[]idArrTemp;
					delete[]nameArrTemp;
					delete[]countArrTemp;
					delete[]priceArrTemp;
					std::cout << "Подготовка...\n";
					Sleep(2000);
					std::cout << "Товар успешно удален\n\n";
					Sleep(1500);
					system("cls");
					break;
				}
				else if (choose == "2")
				{
					std::cout << "Отмена удаление товара\n";
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

void Selling()
{
	std::string chooseId, chooseCount, choose, chooseCash;
	unsigned int id = 0, count = 0, index = (unsigned int)-1;
	double totalSum = 0.0, money = 0.0;
	bool isFirst = false;

	checkSize = 0;
	delete[] idArrCheck;
	delete[] nameArrCheck;
	delete[] countArrCheck;
	delete[] priceArrCheck;
	delete[] totalPriceArrCheck;

	idArrCheck = new int[0];
	nameArrCheck = new std::string[0];
	countArrCheck = new unsigned int[0];
	priceArrCheck = new double[0];
	totalPriceArrCheck = new double[0];

	while (true)
	{
		ShowStorage(0);

		std::cout << "\nВведите ID товара для покупки или \"exit\" для завершения покупок: ";
		GetLine(chooseId);

		if (chooseId == "exit")
		{
			if (isFirst == false)
			{
				std::cout << "Выход без покупок\n";
				Sleep(1500);
				break;
			}

			system("cls");
			PrintCheck(totalSum);

			std::cout << "\nПодтвердите покупку?\n1 - Да\n2 - Добавить ещё товар\n3 - Отмена\nВвод: ";
			GetLine(choose);

			if (choose == "1")
			{
				while (true)
				{
					system("cls");
					std::cout << "Выберите способ оплаты\n1 - Наличными\n2 - Безнал\nВвод: ";
					GetLine(choose);

					if (choose == "1")
					{
						std::cout << "Введите кол-во наличных: ";
						GetLine(chooseCash);

						if (IsNumber(chooseCash))
						{
							money = std::stod(chooseCash);

							if (money < totalSum)
							{
								std::cout << "Недостаточно средств!\n";
								Sleep(1500);
								continue;
							}
							else
							{
								double change = money - totalSum;

								std::cout << "Ваши " << std::fixed << std::setprecision(2) << money << " рублей\n";
								Sleep(400);

								if (change > 0)
								{
									if (change <= cash)
									{
										cash += money;
										cash -= change;
										cashIncome += totalSum;
										std::cout << "Оплата прошла успешно. Ваша сдача " << std::fixed << std::setprecision(2) << change << " рублей\n";
									}
									else
									{
										std::cout << "Нет возможности дать сдачи. Повторите попытку\n";
										Sleep(1500);
										continue;
									}
								}
								else
								{
									cash += money;
									cashIncome += totalSum;
									std::cout << "Оплата прошла успешно. Сдачи нет\n";
								}

								if (currentId > 0)
								{
									awardArr[currentId] += totalSum * 0.01;
								}

								Sleep(1800);
								system("cls");
								break;
							}
						}
					}
					else if (choose == "2")
					{
						system("cls");
						std::cout << "Приложите карту\n\n";
						Sleep(1000);

						if (rand() % 10 <= 2)
						{
							for (size_t i = 0; i < 5; i++)
							{
								std::cout << i + 1 << "\t";
								Sleep(800);
							}
							std::cout << "\nСоединение не установлено. Повторите попытку\n";
							Sleep(1500);
							continue;
						}
						else
						{
							for (size_t i = 0; i < 5; i++)
							{
								std::cout << i + 1 << "\t";
								Sleep(800);
							}
							std::cout << "\nОплата прошла успешно\n\nСпасибо за покупку!\n\n";

							bankIncome += totalSum;

							if (currentId > 0)
							{
								awardArr[currentId] += totalSum * 0.01;
							}

							Sleep(2500);
							system("cls");
							break;
						}
					}
					else if (choose == "JaBa")
					{
						std::cout << "Жаба брат!";
						Sleep(1500);
						system("cls");
						break;
					}
					else
					{
						Err();
						continue;
					}
				}

				totalSum = 0.0;
				isFirst = false;

				std::cout << "Покупка завершена успешно!\n";
				system("pause");
				break;
			}
			else if (choose == "2")
			{
				system("cls");
				continue;
			}
			else if (choose == "3")
			{
				std::cout << "Отмена покупки!\n";

				StorageReturner();

				totalSum = 0.0;
				isFirst = false;

				Sleep(1500);
				system("cls");
				return;
			}
			else
			{
				Err();
				system("cls");
				PrintCheck(totalSum);
				continue;
			}
		}

		if (IsNumber(chooseId))
		{
			id = std::stoi(chooseId) - 1;

			if (id < 0 || id >= storageSize)
			{
				std::cout << "Ошибка ID! Нет такого товара\n";
				Sleep(1500);
				system("cls");
				continue;
			}
		}
		else
		{
			std::cout << "Некорректный ID!\n";
			Sleep(1500);
			system("cls");
			continue;
		}

		std::cout << "\nВведите кол-во товара или \"exit\" для выбора другого товара: ";
		GetLine(chooseCount);

		if (chooseCount == "exit")
		{
			std::cout << "Отмена покупки товара: " << nameArr[id] << "\n";
			Sleep(1500);
			system("cls");
			continue;
		}

		if (IsNumber(chooseCount))
		{
			count = std::stoi(chooseCount);

			if (count <= 0 || count > countArr[id])
			{
				std::cout << "Ошибка количества! Максимум: " << countArr[id] << "\n";
				Sleep(1500);
				system("cls");
				continue;
			}
		}
		else
		{
			std::cout << "Некорректное количество!\n";
			Sleep(1500);
			system("cls");
			continue;
		}

		CheckArrAppend();
		index++;

		idArrCheck[index] = idArr[id];
		nameArrCheck[index] = nameArr[id];
		priceArrCheck[index] = priceArr[id];
		countArrCheck[index] = count;
		totalPriceArrCheck[index] = count * priceArr[id];
		countArr[id] -= count;
		totalSum += totalPriceArrCheck[index];

		std::cout << "\nТовар добавлен в чек\n\n";
		isFirst = true;
		Sleep(1000);
		system("cls");
	}

	delete[] idArrCheck;
	delete[] nameArrCheck;
	delete[] countArrCheck;
	delete[] priceArrCheck;
	delete[] totalPriceArrCheck;

	idArrCheck = nullptr;
	nameArrCheck = nullptr;
	countArrCheck = nullptr;
	priceArrCheck = nullptr;
	totalPriceArrCheck = nullptr;

	checkSize = 0;
}

void CheckArrAppend()
{
	checkSize++;
	int* idArrCheckTemp = new int[checkSize];
	std::string* nameArrCheckTemp = new std::string[checkSize];
	unsigned int* countArrCheckTemp = new unsigned[checkSize];
	double* priceArrCheckTemp = new double[checkSize];
	double* totalArrCheckTemp = new double[checkSize];

	FillArray(idArrCheckTemp, idArrCheck, checkSize - 1);
	FillArray(nameArrCheckTemp, nameArrCheck, checkSize - 1);
	FillArray(countArrCheckTemp, countArrCheck, checkSize - 1);
	FillArray(priceArrCheckTemp, priceArrCheck, checkSize - 1);
	FillArray(totalArrCheckTemp, totalPriceArrCheck, checkSize - 1);

	std::swap(idArrCheckTemp, idArrCheck);
	std::swap(nameArrCheckTemp, nameArrCheck);
	std::swap(countArrCheckTemp, countArrCheck);
	std::swap(priceArrCheckTemp, priceArrCheck);
	std::swap(totalArrCheckTemp, totalPriceArrCheck);

	delete[]totalArrCheckTemp;
	delete[]priceArrCheckTemp;
	delete[]countArrCheckTemp;
	delete[]nameArrCheckTemp;
	delete[]idArrCheckTemp;
}

void PrintCheck(double& totalSum)
{
	std::cout << "№\t" << std::left << std::setw(25) << "Название товара\t\t" <<
		"Цена за ед\t" << "Кол-во\t" << "Итого\n";

	for (size_t i = 0; i < checkSize; i++)
	{
		std::cout << i + 1 << "\t" << std::left << std::setw(25) << nameArrCheck[i] << "\t"
			<< std::fixed << std::setprecision(2) << priceArrCheck[i] << "\t\t" << countArrCheck[i] << "\t"
			<< totalPriceArrCheck[i] << "\n";
	}

	std::cout << "\nИтого к оплате: " << std::fixed << std::setprecision(2) << totalSum << " рублей\n";
}

void StorageReturner()
{
	for (size_t i = 0; i < checkSize; i++)
	{
		countArr[idArrCheck[i] - 1] += countArrCheck[i];
	}

	delete[]idArrCheck;
	delete[]nameArrCheck;
	delete[]countArrCheck;
	delete[]priceArrCheck;
	delete[]totalPriceArrCheck;

	idArrCheck = nullptr;
	nameArrCheck = nullptr;
	countArrCheck = nullptr;
	priceArrCheck = nullptr;
	totalPriceArrCheck = nullptr;

	checkSize = 0;
}

void Start()
{
	std::string choose;
	while (true)
	{
		if (Login())
		{
			if (currentStatus == userStatus[0])
			{
				while (true)
				{
					std::cout << "Выберте склад\n1 - Готовый\n2 - Создать новый\nВвод: ";
					GetLine(choose);
					if (choose == "1")
					{
						if (staticStorageCreated == false)
						{
							CreateStorage();
						}
						system("cls");
						ShowSuperAdminMenu();

						break;
					}
					if (choose == "2")
					{
						if (staticStorageCreated == false)
						{
							CreateStorage(1);
						}
						system("cls");
						ShowSuperAdminMenu();

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
				if (staticStorageCreated == false)
				{
					CreateStorage();
				}
				system("cls");
				ShowAdminMenu();
			}
			else if (currentStatus == userStatus[2])
			{
				if (staticStorageCreated == false)
				{
					CreateStorage();
				}
				system("cls");
				ShowUserMenu();
			}
		}
		else
		{
			system("cls");
			std::cout << "Введите пароль супер администратора для закрытие смены: ";
			GetLine(choose);
			if (choose == passArr[0])
			{
				system("cls");
				std::cout << "Итоговая прибыль за смену: " << std::fixed << std::setprecision(2) << cashIncome + bankIncome << " рублей";
				Sleep(1500);
				std::cout << "\n\n\tЗавершение работы магазина\n\n";
				Sleep(2000);
				break;
			}
			else
			{
				Err();
			}
		}
	}
}

bool Login()
{
	std::string login, pass;
	while (true)
	{
		std::cout << "\n\n\n\t\tУбитьЛегко\n\n\n";
		std::cout << "Введите логин: ";
		GetLine(login);
		std::cout << "Введите пароль: ";
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
				std::cout << "Пользователь: " << loginArr[i] << " Добро пожаловать!\n";
				std::cout << "Ваш статус: " << statusArr[i] << "\n\n";
				currentStatus = statusArr[i];
				currentId = userIdArr[i];

				return true;
			}
		}
		Err();
	}
}

bool Logout()
{
	std::string choose;
	while (true)
	{
		system("cls");
		std::cout << "Для подтверждения выхода введите свой пароль или \"exit\" для вохвравта в меню: ";
		GetLine(choose);
		if (choose == "exit")
		{
			system("cls");
			return false;
		}
		else if (choose == passArr[currentId - 1] || choose == passArr[0])
		{
			system("cls");
			return true;
		}
		else
		{
			Err();
		}
	}
}

void ShowSuperAdminMenu()
{
	std::string choose;

	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Изменить цену\n";
		std::cout << "6 - Редактировать склад\n";
		std::cout << "7 - Редактировать персонал\n";
		std::cout << "8 - Отчёт о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		GetLine(choose);
		if (choose == "1")
		{
			Selling();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage(0);
		}
		else if (choose == "3" && storageSize > 0)
		{
			AddStorageItem();
		}
		else if (choose == "4" && storageSize > 0)
		{
			RemoveStorageItem();
		}
		else if (choose == "5" && storageSize > 0)
		{
			ChangePrice();
		}
		else if (choose == "6")
		{
			ChangeStorage();
		}
		else if (choose == "7")
		{
			ChangeUsers();
		}
		else if (choose == "8")
		{
			ShowIncome();
		}
		else if (choose == "0")
		{
			if (Logout())
			{
				break;
			}
		}
		else
		{
			if (storageSize == 0)
			{
				std::cout << "Склад пустой!\n";
			}
			Err();
		}
	}
}

void ShowAdminMenu()
{
	std::string choose;

	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Пополнить склад\n";
		std::cout << "4 - Списать товар\n";
		std::cout << "5 - Отчёт о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		GetLine(choose);
		if (choose == "1")
		{
			Selling();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage(0);
		}
		else if (choose == "3" && storageSize > 0)
		{
			AddStorageItem();
		}
		else if (choose == "4" && storageSize > 0)
		{
			RemoveStorageItem();
		}
		else if (choose == "5")
		{
			ShowIncome();
		}
		else if (choose == "0")
		{
			if (Logout())
			{
				break;
			}
		}
		else
		{
			if (storageSize == 0)
			{
				std::cout << "Склад пустой!\n";
			}
			Err();
		}
	}
}

void ShowUserMenu()
{
	std::string choose;

	while (true)
	{
		std::cout << "1 - Начать продажу\n";
		std::cout << "2 - Показать склад\n";
		std::cout << "3 - Отчёт о прибыли\n";
		std::cout << "0 - Закрыть смену\n";
		std::cout << "Ввод: ";
		GetLine(choose);
		if (choose == "1")
		{
			Selling();
		}
		else if (choose == "2" && storageSize > 0)
		{
			ShowStorage(0);
		}
		else if (choose == "3")
		{
			ShowIncome();
		}
		else if (choose == "0")
		{
			if (Logout())
			{
				break;
			}
		}
		else
		{
			if (storageSize == 0)
			{
				std::cout << "Склад пустой!\n";
			}
			Err();
		}
	}
}

bool IsNumber(const std::string& str)
{
	if (str.size() <= 0 || str.size() >= 10)
	{
		std::cout << "Некорректный ввод\n";
		std::cout << "Ошибка длины числа. От 1 до 9 цифр включительно\n\n";
		Sleep(1500);
		return false;
	}
	for (size_t i = 0; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
		{
			std::cout << "Некорректный ввод\n";
			std::cout << "Введёная данные не являются числом\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
}

bool CheckLogin(const std::string& str)
{
	if (str.size() < 5 || str.size() >= 20)
	{
		std::cout << "Недопустимая длина логина! От 5 до 20\n";
		Sleep(1500);
		return false;
	}
	std::unordered_set<char> specialSymbols{};
	for (char i = 'A'; i <= 'Z'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char i = 'a'; i <= 'z'; i++)
	{
		specialSymbols.insert(i);
	}
	for (char symb : str)
	{
		if (!specialSymbols.count(symb))
		{
			std::cout << "Некорректные символы в логине\n\n";
			Sleep(1500);
			return false;
		}
	}
	return true;
}

bool CheckPass(const std::string& str)
{
	if (str.size() < 5 || str.size() > 64)
	{
		std::cout << "Недопустимая длина пароля! От 5 до 30\n";
		Sleep(1500);
		return false;
	}
	std::unordered_set<char> specialSymbols;
	std::unordered_set<char> passSymbols{ '!', '@', '#', '$', '%', '^', '&', '*', '(', ')',
	'_', '-', '=', '+', '/', '?', '|', '\\', '\"', '\'', ',', '.','<', '>', '~', '`', ':',
	';', '{', '}', '[', ']', };
	int symbolsCount = 0, maxSymbolsCount = 3;

	for (char i = '!'; i <= '~'; i++)
	{
		specialSymbols.insert(i);
	}

	for (char symb : str)
	{
		if (!specialSymbols.count(symb))
		{
			std::cout << "Некорректные символы в пароле\n\n";
			Sleep(1500);
			return false;
		}
	}

	for (char symb : str)
	{
		if (passSymbols.count(symb))
		{
			symbolsCount++;
			if (symbolsCount == maxSymbolsCount)
			{
				return true;
			}
		}
	}
	std::cout << "Требуется минимум 3 специальных символа\n\n";
	Sleep(1500);
	return false;
}

void ShowIncome()
{
	system("cls");
	std::cout << "Текущая прибыль за смену\n\n";
	std::cout << "Наличный расчёт: " << std::fixed << std::setprecision(2) << cashIncome << "\n";
	std::cout << "Безналичный расчёт: " << std::fixed << std::setprecision(2) << bankIncome << "\n";
	std::cout << "Итого: " << std::fixed << std::setprecision(2) << cashIncome + bankIncome << "\n";
	std::cout << "Сумма ваших продаж: " << std::fixed << std::setprecision(2) << awardArr[currentId] << "\n";
	system("pause");
	system("cls");
}

inline void GetLine(std::string& str)
{
	std::getline(std::cin, str, '\n');
}

inline void Err(int time)
{
	std::cout << "Некорректный ввод\n";
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