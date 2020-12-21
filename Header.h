//Header.h
//������������ ���� �������� ���������� ������� � �.�.

#include <iostream>
#include <vector>
#include <list>
#include <string>
using namespace std;
// ���������� ������
void getaLine(string& inStr); // ��������� ������ ������
char getaChar(); // ��������� �������

// ����� Client (�������)
//�� ������ ��� ������� � ��� ����� ��������.
class Client
{
private:

	string name; // ��� �������
	string phoneNumber; // ����� �������� �������

public:
	Client(string n, string cl);
	~Client();
	string getPhoneNumber(); //���������� ����� �������� �������
	string getName(); //���������� ��� �������
};

//����� ClientList
//����� ClientList � ������ ���� ��������.
//�� �������� ��������� ���������� �� ����� Client � ��������� ��� ��� ������
class ClientList
{
private:
	// ���������� ��������� �� ��������
	list <Client*> setPtrsClients; // ��������� �� ����� ��������
	list <Client*>::iterator iter; //��������
public:
	~ClientList(); // ���������� (�������� ��������)
	void insertClient(Client*); // �������� ������� � ������
	string getphNum(string); // ���������� ����� ��������
	void display(); // ����� ������ ��������
};

//����� ClientInputScreen
//����� ClientInputScreen. ��� �����, ���������� �� ����������� �������,
//���� ������������ ����� ������ ������ � ����� �������:
class ClientInputScreen

{
private:
	ClientList* ptrClientList;
	string tName;
	string clientPhone;
public:
	ClientInputScreen(ClientList* ptrTL) : ptrClientList(ptrTL)
	{
		/* ��� ����� */
	}
	void setClient(); // �������� ������ � �������
};

//����� PayRow
//�����, �������� ���� ��������� ������ ������� (���������� ������)
// ���� ������ ������� �������:  ��� �������, ��� ������, ����� ������, �����
class PayRow
{
private:
	string clName; // ��� �������
	float pay = 0; // ������
	int service = 0;
	int month = 0;
public:
	PayRow(string); // ����������� � ����� ����������
	void setPay(string, string, int, float, int); // �������� ����� �� �����
	//����� �������� �� ����� ������ (����� ������ ������� �� ��� ������)
	//float getSumOfRow();
	string getName(); //������ �����
	float getPayNo(); //������ ����� �� �����
	string getService();
	int getMonth();
};

// ����� PayRecord
//����� PayRecord. �� ������ ��������������� ������ �� ������ �����.
//� ��� ����� ����������������� ����� ���������� ������.
class PayRecord
{
private:
	list <PayRow*> setPtrsRR; // ��������� �� ������� PayRow (�� ������ �� �������)
	list <PayRow*>::iterator iter;
public:
	~PayRecord();
	void insertPay(string, string, int, float, int); // �������� ������
	void display(); // ���������� ��� ������ � ���������
	float getSumOfRents(); // ���������� ����� ���� �������� ���� ��������
};

//����� SumInputScreen
//����� ��� ���������� �������
class SumInputScreen
{
private:
	ClientList* ptrClientList; // ������ ��������
	PayRecord* ptrRentRecord; // ������ ������� �� ������ �����
	string clientName; // ��� �������, ������� ������� ������
	float sumPaid = 0; // ����� �������
	int month = 0; // �� �����
	string phoneNo; // ����� ��������
	int service = 0; // ��� ������
public:
	SumInputScreen(ClientList* ptrTL, PayRecord* ptrRR) : ptrClientList(ptrTL),
		ptrRentRecord(ptrRR)
	{
		/*��� �����*/
	}
	void setPay(); // �������� ������ ����� ������ ��������
};

//����� Expense
//����� ������
class Expense
{
public:
	int month;
	int day; // ����� � ���� ������ ��������
	string category; // ��������� �������� (���, ����, ������ � ��)
	string payee; // ���� ������ (���������� ����, �����, ��������� �����...)
	float amount; // ������� ������
	Expense():
		month(0), 
		day(0),
		amount(0)
	{ }
	Expense(int m, int d, string c, string p, float a) :
		month(m), day(d), category(c), payee(p), amount(a)
	{
		/* ��� �����! */
	}
};

//����� ExpenseRecord
//����� ������� � ��������
class ExpenseRecord
{
private:
	vector<Expense*> vectPtrsExpenses; //������ ���������� �� �������
	vector<Expense*>::iterator iter;
public:
	~ExpenseRecord();

	void insertExp(Expense*);
	void display();
	float displaySummary(); // ����� ��� �������� ������
};

//����� ExpenseInputScreen
//����� ��� ����� ��������
class ExpenseInputScreen
{
private:
	ExpenseRecord* ptrExpenseRecord; // ������ � ��������
public:
	ExpenseInputScreen(ExpenseRecord*);
	void setExpense();
};


//����� AnnualReport
//����� �������� ������
class AnnualReport
{
private:
	PayRecord* ptrRR; // ������ �������
	ExpenseRecord* ptrER; // ������ ��������
	float expenses, rents; // ����� ������� � ��������
public:
	AnnualReport(PayRecord*, ExpenseRecord*);
	void display(); // ����������� �������� ������
};

// ����� UserInterface
//������� ����� ��� ������� ����������:
//���� ����� ���������� �������������� ����� � ����������.
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
}; // ����� ������ userInterface
