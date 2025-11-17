#include <iostream>
#include <Windows.h>
#include <string>
#include <iomanip>
#include <unordered_set>

// учетные записи
size_t userSize = 2;
std::string userStatus[3]{ "Супер Администратор", "Администратор", "Сотрудник" };
std::string* loginArr = new std::string[userSize]{ "admin","user" };
std::string* passArr = new std::string[userSize]{ "admin","user" };
std::string* statusArr = new std::string[userSize]{ userStatus[0],userStatus[2] };
std::string currentStatus;

void ChangeUsers();
void AddNewUser();
void ShowUsers();
//
// склад
size_t storageSize = 0;
bool staticStorageCreated = false;

int* idArr;
std::string* nameArr;
unsigned int* countArr;
double* priceArr;

void CreateStorage();
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
//
// служебные
void Start();
bool Login();
void ShowSuperAdminMenu();
bool IsNumber(const std::string& str);
bool CheckLogin(const std::string& str);
bool CheckPass(const std::string& str);

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
			ShowUsers();
		}
		else if (choose == "3" && userSize > 1)
		{

		}
		else if (choose == "4" && userSize > 1)
		{

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
	bool exit;
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

				FillArray(loginArrTemp, loginArr, userSize - 1);
				FillArray(passArrTemp, passArr, userSize - 1);
				FillArray(statusArrTemp, statusArr, userSize - 1);

				loginArrTemp[userSize - 1] = newLogin;
				passArrTemp[userSize - 1] = newPass;
				statusArrTemp[userSize - 1] = newStatus;

				std::swap(loginArr, loginArrTemp);
				std::swap(passArr, passArrTemp);
				std::swap(statusArr, statusArrTemp);

				delete[]loginArrTemp, passArrTemp, statusArrTemp;
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

void ShowUsers()
{
	system("cls");
	
	std::cout << "№\t" << std::left << std::setw(10) << "Логин\t" <<
		"Пароль\t" << "Статус\n";

	for (size_t i = 1; i < userSize; i++)
	{
		std::cout << i << '\t' << std::left << std::setw(12) << loginArr[i]
			<< passArr[i] << "\t" << statusArr[i] << "\n";
	}
	system("pause");
	system("cls");
}

void CreateStorage()
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
		delete[]idArr, nameArr, countArr, priceArr;
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
				<< "\t" << priceArr[i] << "\t" << countArr[i] << "\n";
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
				<< "\t" << priceArr[i] << "\n";
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
		//std::invalid_argument("StorageMode Error");
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
			Price = std::stoi(newPrice);

			if (id < 0 || id > storageSize || Price < 0.0 || Price > 500000)
			{
				std::cout << "Некорректный id или цена\nМаксимальная цена 500000\n\n";
				Sleep(1500);
			}
			else
			{
				std::cout << std::left << std::setw(25) << nameArr[id] <<
					"\t" << priceArr[id] << " --> " << Price << "\n\n";
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
				price = std::stoi(newPrice);
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
			std::cout << "цена: " << price << "\n";
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

				delete[]idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
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

					delete[]idArrTemp, nameArrTemp, countArrTemp, priceArrTemp;
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

void Start()
{
	std::string choose;
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
		}
		else if (currentStatus == userStatus[2])
		{
			if (staticStorageCreated == false)
			{
				CreateStorage();
			}
		}
	}
	else
	{
		system("cls");
		std::cout << "Завершение работы магазина\n\n";
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

		}
		else if (choose == "0")
		{

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
		std::cout << "Недопустимая длина пароля! От 5 до 64\n";
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