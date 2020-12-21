//Файл landlord.cpp содержит все определения методов
#include <iostream>
//using namespace std;
#include "Header.h"
void getaLine(string& inStr) // получение строки текста
{
	char temp[21];
	cin.get(temp, 20, '\n');
	cin.ignore(20, '\n'); //число пропускаемых символов и символ разделения
	inStr = temp;
}
//---------------------------------------------------------
char getaChar() // получение символа
{
	char ch = cin.get();
	cin.ignore(80, '\n'); //число пропускаемых символов и символ разделения
	return ch;
}
//---------------------------------------------------------


//---------------------------------------------------------
//метод класса TenantInputScreen
void ClientInputScreen::setClient() // добавить данные о клиенте
{

	cout << "Введите имя клиента (Иванов И И): " << endl;
	getaLine(tName);
	cout << "Введите номер телефона клиента (89008753626): " << endl;
	getaLine(clientPhone);
	Client* ptrClient = new Client(tName, clientPhone); // создать клиента
	ptrClientList->insertClient(ptrClient); // занести в список клиентов
}
//---------------------------------------------------------
//методы класса ClientList
ClientList::~ClientList() // деструктор
{
	while (!setPtrsClients.empty()) // удаление всех клиентов,
	{ // удаление указателей из контейнера
		iter = setPtrsClients.begin();
		delete* iter;

		setPtrsClients.erase(iter);
	}
}
//---------------------------------------------------------
void ClientList::insertClient(Client* ptrT)
{
	setPtrsClients.push_back(ptrT); // вставка нового клиента в список
}
//---------------------------------------------------------
string ClientList::getphNum(string tName) // получить номер телефона по имени клиента
{
	string phoneNo;
	iter = setPtrsClients.begin();
	while (iter != setPtrsClients.end())
	{ // поиск клиента в списке (достаем у каждого клиента номер телефона)
		phoneNo = (*iter)->getPhoneNumber();
		if (tName == ((*iter)->getName())) // сравниваем по именам и
		{
			// если получившаяся пара совпадает - значит,
			//если запись об этом клиенте найдена в списке клиентов, в этом случае
			return phoneNo; // возвращаем номер телефона
		}
		iter++;
	}
	return ""; // если нет - возвращаем -1
}
//--------------------------------------------------------

void ClientList::display() // вывод списка клиентов
{
	cout << "\nНомер телефона\tИмя клиента\n-------------------\n";
	if (setPtrsClients.empty()) // если список клиентов пуст
		cout << "***Нет клиентов***\n" << endl; // выводим запись, что он пуст)
	else
	{
		iter = setPtrsClients.begin();
		while (iter != setPtrsClients.end()) // распечатываем всех клиентов
		{
			cout << (*iter)->getPhoneNumber() << " || " << (*iter)->getName() << endl;
			*iter++;
		}
	}
}
//---------------------------------------------------------
//методы класса PayRow//

PayRow::PayRow(string an) : clName() //конструктор
{ //конструктор с одним параметром

}
//---------------------------------------------------------
void PayRow::setPay(string cl, string ph, int m, float am, int serv) // сеттер оплата за месяц m, сумма - am
{
	pay = am; // привязываем оплату к месяцу
	clName = cl;
	month = m;
	service = serv;
}
//---------------------------------------------------------

string PayRow::getName() // геттер запрос имени клиента
{
	return clName;
}
//---------------------------------------------------------
float PayRow::getPayNo() //Геттер запрос платежа
{
	return pay;
}
//------------------------------------------------------------
int PayRow::getMonth() //геттер запрос месяца
{
	return (month+1); //+1 из-за специфики счета: считается с 0
}
//-------------------------------------------------------------
string PayRow::getService() //Геттер запрос услуги
{
	switch (service)
	{
	case 1:
		return "Подготовка покойника";
		break;
	case 2:
		return "Продажа гроба       ";
		break;
	case 3:
		return "Копка могилы        ";
		break;
	case 4:
		return "Другое              ";
		break;
	default:
		return "Выберите ДРУГОЕ";
		break;
	}
}

//---------------------------------------------------------
//методы класса rentRecord
PayRecord::~PayRecord() // деструктор
{ // удалить строки с платежами,
// удалить указатели из множества.
	while (!setPtrsRR.empty())
	{
		iter = setPtrsRR.begin();
		delete* iter;
		setPtrsRR.erase(iter);
	}
}
//---------------------------------------------------------
void PayRecord::insertPay(string name, string phNo, int month, float amount, int serv)
{

	iter = setPtrsRR.begin(); // Инициализация итератора
	while (iter != setPtrsRR.end()) // условие выхода
	{ // если текущий объект совпадает с созданным для поиска,
		if (phNo == (*iter)->getName())
		{ // заносим платеж в список
			(*iter)->setPay(name, phNo, month, amount, serv);
			return;
		}
		else
			iter++;
	} // если не нашли строку - создаем новую
	PayRow* ptrRow = new PayRow(name);
	ptrRow->setPay(name, phNo, month, amount, serv); // заносим в нее платеж
	setPtrsRR.push_back(ptrRow); // заносим строку в вектор
}
//---------------------------------------------------------
void PayRecord::display() // отобразить все строки с доходами
{
	cout << "\nИмя клиента\tТип услуги\tМесяц\t Сумма\n" << endl
		<< "------------------------------------------------------------------\n" << endl;
	if (setPtrsRR.empty())
		cout << "***Нет платежей!***\n" << endl;
	else
	{
		iter = setPtrsRR.begin(); //итератор на список с указателями на объекты PayRow
		while (iter != setPtrsRR.end())
		{
			cout << (*iter)->getName() << '\t'; // вывести имя клиента
			cout << (*iter)->getService() << "\t";
			cout << (*iter)->getMonth() << "\t";
			cout << (*iter)->getPayNo() << " ";
			cout << endl;
			iter++;
		}
		cout << endl;
		cout << endl;
	}
}
//---------------------------------------------------------
float PayRecord::getSumOfRents() // сумма всех платежей
{
	float sumRents = 0.0;
	iter = setPtrsRR.begin();

	while (iter != setPtrsRR.end())
	{ // плюсуем суммы всех платежей клиентов за все время
		sumRents += (*iter)->getPayNo();
		iter++;
	}
	return sumRents;
}
//---------------------------------------------------------
//методы класса rentInputScreen
//SumInputScreen::SumInputScreen(ClientList* ptrTL, PayRecord* ptrRR) : ptrClientList(ptrTL),
//ptrRentRecord(ptrRR)
//{
	/*тут пусто*/
//}

void SumInputScreen::setPay()
{
	cout << "Введите имя клиента: ";
	getaLine(clientName);
	// получить номер телефона по имени клиента
	phoneNo = ptrClientList->getphNum(clientName);
	if (phoneNo == "") // если имя найдено, и такой клиент существует -
	{ // получить сумму платежа
		cout << "Введите сумму платежа (2000.37): " << endl;
		cin >> sumPaid; // вводим сумму платежа
		cin.ignore(80, '\n');
		cout << "Введите номер месяца оплаты (1-12): " << endl;
		cin >> month;
		cin.ignore(80, '\n');
		month--; // (внутренняя нумерация 0-11)
		cout << "Введите тип услуги (Подготовка покойника (1), Продажа гроба(2), Копка могилы (3), Другое (4)): " << endl;
		cin >> service; // вводим ренту
		cin.ignore(80, '\n');
		// вставляем данные в запись об оплате
		ptrRentRecord->insertPay(clientName, phoneNo, month, sumPaid, service);
		//ptrRentRecord->insertPay(phoneNo, month, sumPaid, service);
	}
	else
		cout << "Такого клиента нет.\n" << endl;
}
//---------------------------------------------------------
//методы класса expenseRecord
ExpenseRecord::~ExpenseRecord() // деструктор
{ // удалить объекты expense
// удалить указатели на вектор
	while (!vectPtrsExpenses.empty())
	{
		iter = vectPtrsExpenses.begin();
		delete* iter;
		vectPtrsExpenses.erase(iter);
	}
}
//--------------------------------------------------------
void ExpenseRecord::insertExp(Expense* ptrExp)
{

	vectPtrsExpenses.push_back(ptrExp);
}
//---------------------------------------------------------
void ExpenseRecord::display() // распечатываем все расходы
{
	cout << "\nДата\tПолучатель\tСумма\tКатегория\n"
		<< "----------------------------------------\n" << endl;
	if (vectPtrsExpenses.size() == 0) // В контейнере нет расходов
		cout << "***Расходов нет***\n" << endl;
	else
	{
		iter = vectPtrsExpenses.begin();
		while (iter != vectPtrsExpenses.end())
		{ // распечатываем все расходы
			cout << (*iter)->month << '/' << (*iter)->day << '\t' << (*iter)->payee << '\t' << '\t';
			cout << (*iter)->amount << '\t' << (*iter)->category << endl;
			iter++;
		}
		cout << endl;
	}
}
//--------------------------------------------------------
// используется при составлении годового отчета
float ExpenseRecord::displaySummary()
{
	float totalExpenses = 0; // Сумма по всем категориям расходов
	if (vectPtrsExpenses.size() == 0)
	{
		cout << "\tВсе категории\t0\n";
		return 0;
	}
	iter = vectPtrsExpenses.begin();
	while (iter != vectPtrsExpenses.end())
	{
		//выводим на экран категории расходов
		cout << '\t' << ((*iter)->category) << '\t' << ((*iter)->amount) << endl;
		totalExpenses += (*iter)->amount; //подсчитываем все расходы
		iter++;
	}
	return totalExpenses;
}
//--------------------------------------------------------
//методы класса ExpenseInputScreen

// конструктор
ExpenseInputScreen::ExpenseInputScreen(ExpenseRecord* per) : ptrExpenseRecord(per)
{
	/*пусто*/
}
//------------------------------------------------------
void ExpenseInputScreen::setExpense()
{
	int month, day;
	string category, payee;
	float amount;
	cout << "Введите месяц (1-12): ";
	cin >> month;
	cin.ignore(80, '\n');
	cout << "Введите день (1-31): ";
	cin >> day;
	cin.ignore(80, '\n');
	cout << "Введите категорию расходов (Налоги, ремонт, аренда, крематорий и т.д.): ";
	getaLine(category);
	cout << "Введите получателя (ИП Могилки): ";
	getaLine(payee);
	cout << "Введите сумму (3900.99): ";
	cin >> amount;
	cin.ignore(80, '\n');
	// создаем новый расход
	Expense* ptrExpense = new Expense(month, day, category, payee, amount);
	// вставляем расход в список всех расходов
	ptrExpenseRecord->insertExp(ptrExpense);
}
//---------------------------------------------------------
//методы класса AnnualReport
//Конструктор
AnnualReport::AnnualReport(PayRecord* pRR, ExpenseRecord* pER) : ptrRR(pRR), ptrER(pER)
{ /* пусто */
}
//---------------------------------------------------------
void AnnualReport::display()
{
	cout << "Годовой отчет\n--------------\n" << endl;
	cout << "Доходы\n" << endl;
	cout << "\tПлатежи клиентов:\t\t";
	rents = ptrRR->getSumOfRents();
	cout << rents << endl;

	cout << "Расходы\n" << endl;
	expenses = ptrER->displaySummary();
	cout << "Расходы всего:\t\t";
	cout << expenses << endl;
	// вычисляем прибыльность
	cout << "\nЧистая прибыль:\t\t\t" << (rents - expenses) << endl;
}
//---------------------------------------------------------
//методы класса userInterface
UserInterface::UserInterface()
{
	ptrClientList = new ClientList;
	ptrRentRecord = new PayRecord;
	ptrExpenseRecord = new ExpenseRecord;
}
//---------------------------------------------------------
UserInterface::~UserInterface()
{
	delete ptrClientList;
	delete ptrRentRecord;
	delete ptrExpenseRecord;
}
//---------------------------------------------------------
void UserInterface::interact()
{
	while (true)
	{
		cout << "                            ВВЕСТИ ДАННЫЕ 'i', \n"
			<< "                            ВЫВЕСТИ ОТЧЕТ 'd', \n"
			<< "                            ВЫХОД 'q': \n";
		ch = getaChar();
		if (ch == 'i') // ввод данных
		{
			cout << " Добавить клиента 't', \n"
				<< " Записать проданную услугу/товар 'r', \n"
				<< " Добавить расходы 'e': \n";
			ch = getaChar();
			switch (ch)
			{
				//экраны ввода существуют только во время их
				//использования
			case 't': ptrClientInputScreen =
				new ClientInputScreen(ptrClientList);
				ptrClientInputScreen->setClient();
				delete ptrClientInputScreen;
				break;

			case 'r': ptrRentInputScreen =
				new SumInputScreen(ptrClientList, ptrRentRecord);
				ptrRentInputScreen->setPay();
				delete ptrRentInputScreen;
				break;
			case 'e': ptrExpenseInputScreen =
				new ExpenseInputScreen(ptrExpenseRecord);
				ptrExpenseInputScreen->setExpense();
				delete ptrExpenseInputScreen;
				break;
			default: cout << "Неизвестная функция\n";
				break;
			} // конец секции switch
		} // конец условия if
		else if (ch == 'd') // вывод данных
		{
			cout << " вывести список клиентов 't', \n"
				<< " Вывести проданные тавары и услуги 'r' \n"
				<< " Вывести расходы 'e', \n"
				<< " Вывести годовой отчет 'a': \n";
			ch = getaChar();
			switch (ch)
			{
			case 't': ptrClientList->display();
				break;
			case 'r': ptrRentRecord->display();
				break;
			case 'e': ptrExpenseRecord->display();
				break;
			case 'a':
				ptrAnnualReport = new AnnualReport(ptrRentRecord,
					ptrExpenseRecord);
				ptrAnnualReport->display();
				delete ptrAnnualReport;
				break;
			default: cout << "Такой функции нет\n";
				break;
			} // конец switch
		} // конец elseif
		else if (ch == 'q')
			return; // выход
		else
			cout << "Такой функции нет. Нажимайте только 'i', 'd' или 'q'\n";
	} // конец while
} // конец interact()
