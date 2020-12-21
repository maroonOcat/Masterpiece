//Header.h
//заголовочный файл содержит объявления классов и т.п.

#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;
// ГЛОБАЛЬНЫЕ МЕТОДЫ
void getaLine(string& inStr); // получение строки текста
char getaChar(); // получение символа

// класс Client (клиенты)
//Он хранит имя клиента и его номер телефона.
class Client
{
private:

	string name; // имя клиента
	string phoneNumber; // номер телефона клиента

public:
	Client(string n, string cl);
	~Client();
	string getPhoneNumber(); //возвращает номер телефона клиента
	string getName(); //возвращает имя клиента
};

//класс ClientList
//класс ClientList — список всех клиентов.
//Он содержит множество указателей на класс Client и оперирует ими при выводе
class ClientList
{
private:
	// установить указатели на клиентов
	list <Client*> setPtrsClients; // указатели на класс клиентов
	list <Client*>::iterator iter; //итератор
public:
	~ClientList(); // деструктор (удаление клиентов)
	void insertClient(Client*); // добавить клиента в список
	string getphNum(string); // возвращает номер телефона
	void display(); // вывод списка клиентов
};

//класс ClientInputScreen
//класс ClientInputScreen. Это класс, отвечающий за отображение «экрана»,
//куда пользователь может ввести данные о новом клиенте:
class ClientInputScreen

{
private:
	ClientList* ptrClientList;
	string tName;
	string clientPhone;
public:
	ClientInputScreen(ClientList* ptrTL) : ptrClientList(ptrTL)
	{
		/* тут пусто */
	}
	void setClient(); // добавить данные о клиенте
};

//класс PayRow
//класс, хранящий одну табличную строку доходов (оплаченной услуги)
// одна строка таблицы прибыли:  имя клиента, тип услуги, месяц сделки, сумма
class PayRow
{
private:
	string clName; // имя клиента
	float pay = 0; // месяцы
	int service = 0;
	int month = 0;
public:
	PayRow(string); // конструктор с одним параметром
	void setPay(string, string, int, float, int); // добавить плату за месяц
	//сумма платежей из одной строки (плата одного клиента за все месяцы)
	//float getSumOfRow();
	string getName(); //Запрос имени
	float getPayNo(); //Запрос платы за месяц
	string getService();
	int getMonth();
};

// класс PayRecord
//класс PayRecord. Он хранит непосредственно записи об оплате услуг.
//С ним будет взаимодействовать экран добавления оплаты.
class PayRecord
{
private:
	list <PayRow*> setPtrsRR; // указатели на объекты PayRow (по одному на клиента)
	list <PayRow*>::iterator iter;
public:
	~PayRecord();
	void insertPay(string, string, int, float, int); // добавить платеж
	void display(); // отобразить все строки с платежами
	float getSumOfRents(); // подсчитать сумму всех платежей всех клиентов
};

//класс SumInputScreen
//Экран для добавления платежа
class SumInputScreen
{
private:
	ClientList* ptrClientList; // список клиентов
	PayRecord* ptrRentRecord; // список записей об оплате услуг
	string clientName; // имя клиента, который оплатил услугу
	float sumPaid = 0; // сумма платежа
	int month = 0; // за месяц
	string phoneNo; // номер телефона
	int service = 0; // тип услуги
public:
	SumInputScreen(ClientList* ptrTL, PayRecord* ptrRR) : ptrClientList(ptrTL),
		ptrRentRecord(ptrRR)
	{
		/*тут пусто*/
	}
	void setPay(); // добавить оплату одной услуги клиентом
};

//класс Expense
//Класс затрат
class Expense
{
public:
	int month;
	int day; // месяц и день уплаты расходов
	string category; // категория расходов (газ, свет, ремонт и тд)
	string payee; // кому платим (поставщики газа, света, сервисный центр...)
	float amount; // сколько платим
	Expense():
		month(0), 
		day(0),
		amount(0)
	{ }
	Expense(int m, int d, string c, string p, float a) :
		month(m), day(d), category(c), payee(p), amount(a)
	{
		/* тут пусто! */
	}
};

//класс ExpenseRecord
//Класс записей о затратах
class ExpenseRecord
{
private:
	vector<Expense*> vectPtrsExpenses; //вектор указателей на расходы
	vector<Expense*>::iterator iter;
public:
	~ExpenseRecord();

	void insertExp(Expense*);
	void display();
	float displaySummary(); // нужно для годового отчета
};

//класс ExpenseInputScreen
//Класс для ввода расходов
class ExpenseInputScreen
{
private:
	ExpenseRecord* ptrExpenseRecord; // запись о расходах
public:
	ExpenseInputScreen(ExpenseRecord*);
	void setExpense();
};


//класс AnnualReport
//Класс годового отчета
class AnnualReport
{
private:
	PayRecord* ptrRR; // записи доходов
	ExpenseRecord* ptrER; // записи расходов
	float expenses, rents; // суммы доходов и расходов
public:
	AnnualReport(PayRecord*, ExpenseRecord*);
	void display(); // отображение годового отчета
};

// Класс UserInterface
//Главный класс для запуска приложения:
//этот класс определяет взаимодействие юзера с программой.
class UserInterface
{
private:
	ClientList* ptrClientList;
	ClientInputScreen* ptrClientInputScreen;
	PayRecord* ptrRentRecord;
	SumInputScreen* ptrRentInputScreen;
	ExpenseRecord* ptrExpenseRecord;
	ExpenseInputScreen* ptrExpenseInputScreen;
	AnnualReport* ptrAnnualReport;
	char ch;
public:

	UserInterface();
	~UserInterface();
	void interact();
}; // конец класса userInterface
