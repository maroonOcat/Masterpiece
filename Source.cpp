//���� landlord.cpp �������� ��� ����������� �������
#include <iostream>
//using namespace std;
#include "Header.h"
void getaLine(string& inStr) // ��������� ������ ������
{
	char temp[21];
	cin.get(temp, 20, '\n');
	cin.ignore(20, '\n'); //����� ������������ �������� � ������ ����������
	inStr = temp;
}
//---------------------------------------------------------
char getaChar() // ��������� �������
{
	char ch = cin.get();
	cin.ignore(80, '\n'); //����� ������������ �������� � ������ ����������
	return ch;
}
//---------------------------------------------------------


//---------------------------------------------------------
//����� ������ TenantInputScreen
void ClientInputScreen::setClient() // �������� ������ � �������
{

	cout << "������� ��� ������� (������ � �): " << endl;
	getaLine(tName);
	cout << "������� ����� �������� ������� (89008753626): " << endl;
	getaLine(clientPhone);
	Client* ptrClient = new Client(tName, clientPhone); // ������� �������
	ptrClientList->insertClient(ptrClient); // ������� � ������ ��������
}
//---------------------------------------------------------
//������ ������ ClientList
ClientList::~ClientList() // ����������
{
	while (!setPtrsClients.empty()) // �������� ���� ��������,
	{ // �������� ���������� �� ����������
		iter = setPtrsClients.begin();
		delete* iter;

		setPtrsClients.erase(iter);
	}
}
//---------------------------------------------------------
void ClientList::insertClient(Client* ptrT)
{
	setPtrsClients.push_back(ptrT); // ������� ������ ������� � ������
}
//---------------------------------------------------------
string ClientList::getphNum(string tName) // �������� ����� �������� �� ����� �������
{
	string phoneNo;
	iter = setPtrsClients.begin();
	while (iter != setPtrsClients.end())
	{ // ����� ������� � ������ (������� � ������� ������� ����� ��������)
		phoneNo = (*iter)->getPhoneNumber();
		if (tName == ((*iter)->getName())) // ���������� �� ������ �
		{
			// ���� ������������ ���� ��������� - ������,
			//���� ������ �� ���� ������� ������� � ������ ��������, � ���� ������
			return phoneNo; // ���������� ����� ��������
		}
		iter++;
	}
	return ""; // ���� ��� - ���������� -1
}
//--------------------------------------------------------

void ClientList::display() // ����� ������ ��������
{
	cout << "\n����� ��������\t��� �������\n-------------------\n";
	if (setPtrsClients.empty()) // ���� ������ �������� ����
		cout << "***��� ��������***\n" << endl; // ������� ������, ��� �� ����)
	else
	{
		iter = setPtrsClients.begin();
		while (iter != setPtrsClients.end()) // ������������� ���� ��������
		{
			cout << (*iter)->getPhoneNumber() << " || " << (*iter)->getName() << endl;
			*iter++;
		}
	}
}
//---------------------------------------------------------
//������ ������ PayRow//

PayRow::PayRow(string an) : clName() //�����������
{ //����������� � ����� ����������

}
//---------------------------------------------------------
void PayRow::setPay(string cl, string ph, int m, float am, int serv) // ������ ������ �� ����� m, ����� - am
{
	pay = am; // ����������� ������ � ������
	clName = cl;
	month = m;
	service = serv;
}
//---------------------------------------------------------

string PayRow::getName() // ������ ������ ����� �������
{
	return clName;
}
//---------------------------------------------------------
float PayRow::getPayNo() //������ ������ �������
{
	return pay;
}
//------------------------------------------------------------
int PayRow::getMonth() //������ ������ ������
{
	return (month+1); //+1 ��-�� ��������� �����: ��������� � 0
}
//-------------------------------------------------------------
string PayRow::getService() //������ ������ ������
{
	switch (service)
	{
	case 1:
		return "���������� ���������";
		break;
	case 2:
		return "������� �����       ";
		break;
	case 3:
		return "����� ������        ";
		break;
	case 4:
		return "������              ";
		break;
	default:
		return "�������� ������";
		break;
	}
}

//---------------------------------------------------------
//������ ������ rentRecord
PayRecord::~PayRecord() // ����������
{ // ������� ������ � ���������,
// ������� ��������� �� ���������.
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

	iter = setPtrsRR.begin(); // ������������� ���������
	while (iter != setPtrsRR.end()) // ������� ������
	{ // ���� ������� ������ ��������� � ��������� ��� ������,
		if (phNo == (*iter)->getName())
		{ // ������� ������ � ������
			(*iter)->setPay(name, phNo, month, amount, serv);
			return;
		}
		else
			iter++;
	} // ���� �� ����� ������ - ������� �����
	PayRow* ptrRow = new PayRow(name);
	ptrRow->setPay(name, phNo, month, amount, serv); // ������� � ��� ������
	setPtrsRR.push_back(ptrRow); // ������� ������ � ������
}
//---------------------------------------------------------
void PayRecord::display() // ���������� ��� ������ � ��������
{
	cout << "\n��� �������\t��� ������\t�����\t �����\n" << endl
		<< "------------------------------------------------------------------\n" << endl;
	if (setPtrsRR.empty())
		cout << "***��� ��������!***\n" << endl;
	else
	{
		iter = setPtrsRR.begin(); //�������� �� ������ � ����������� �� ������� PayRow
		while (iter != setPtrsRR.end())
		{
			cout << (*iter)->getName() << '\t'; // ������� ��� �������
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
float PayRecord::getSumOfRents() // ����� ���� ��������
{
	float sumRents = 0.0;
	iter = setPtrsRR.begin();

	while (iter != setPtrsRR.end())
	{ // ������� ����� ���� �������� �������� �� ��� �����
		sumRents += (*iter)->getPayNo();
		iter++;
	}
	return sumRents;
}
//---------------------------------------------------------
//������ ������ rentInputScreen
//SumInputScreen::SumInputScreen(ClientList* ptrTL, PayRecord* ptrRR) : ptrClientList(ptrTL),
//ptrRentRecord(ptrRR)
//{
	/*��� �����*/
//}

void SumInputScreen::setPay()
{
	cout << "������� ��� �������: ";
	getaLine(clientName);
	// �������� ����� �������� �� ����� �������
	phoneNo = ptrClientList->getphNum(clientName);
	if (phoneNo == "") // ���� ��� �������, � ����� ������ ���������� -
	{ // �������� ����� �������
		cout << "������� ����� ������� (2000.37): " << endl;
		cin >> sumPaid; // ������ ����� �������
		cin.ignore(80, '\n');
		cout << "������� ����� ������ ������ (1-12): " << endl;
		cin >> month;
		cin.ignore(80, '\n');
		month--; // (���������� ��������� 0-11)
		cout << "������� ��� ������ (���������� ��������� (1), ������� �����(2), ����� ������ (3), ������ (4)): " << endl;
		cin >> service; // ������ �����
		cin.ignore(80, '\n');
		// ��������� ������ � ������ �� ������
		ptrRentRecord->insertPay(clientName, phoneNo, month, sumPaid, service);
		//ptrRentRecord->insertPay(phoneNo, month, sumPaid, service);
	}
	else
		cout << "������ ������� ���.\n" << endl;
}
//---------------------------------------------------------
//������ ������ expenseRecord
ExpenseRecord::~ExpenseRecord() // ����������
{ // ������� ������� expense
// ������� ��������� �� ������
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
void ExpenseRecord::display() // ������������� ��� �������
{
	cout << "\n����\t����������\t�����\t���������\n"
		<< "----------------------------------------\n" << endl;
	if (vectPtrsExpenses.size() == 0) // � ���������� ��� ��������
		cout << "***�������� ���***\n" << endl;
	else
	{
		iter = vectPtrsExpenses.begin();
		while (iter != vectPtrsExpenses.end())
		{ // ������������� ��� �������
			cout << (*iter)->month << '/' << (*iter)->day << '\t' << (*iter)->payee << '\t' << '\t';
			cout << (*iter)->amount << '\t' << (*iter)->category << endl;
			iter++;
		}
		cout << endl;
	}
}
//--------------------------------------------------------
// ������������ ��� ����������� �������� ������
float ExpenseRecord::displaySummary()
{
	float totalExpenses = 0; // ����� �� ���� ���������� ��������
	if (vectPtrsExpenses.size() == 0)
	{
		cout << "\t��� ���������\t0\n";
		return 0;
	}
	iter = vectPtrsExpenses.begin();
	while (iter != vectPtrsExpenses.end())
	{
		//������� �� ����� ��������� ��������
		cout << '\t' << ((*iter)->category) << '\t' << ((*iter)->amount) << endl;
		totalExpenses += (*iter)->amount; //������������ ��� �������
		iter++;
	}
	return totalExpenses;
}
//--------------------------------------------------------
//������ ������ ExpenseInputScreen

// �����������
ExpenseInputScreen::ExpenseInputScreen(ExpenseRecord* per) : ptrExpenseRecord(per)
{
	/*�����*/
}
//------------------------------------------------------
void ExpenseInputScreen::setExpense()
{
	int month, day;
	string category, payee;
	float amount;
	cout << "������� ����� (1-12): ";
	cin >> month;
	cin.ignore(80, '\n');
	cout << "������� ���� (1-31): ";
	cin >> day;
	cin.ignore(80, '\n');
	cout << "������� ��������� �������� (������, ������, ������, ���������� � �.�.): ";
	getaLine(category);
	cout << "������� ���������� (�� �������): ";
	getaLine(payee);
	cout << "������� ����� (3900.99): ";
	cin >> amount;
	cin.ignore(80, '\n');
	// ������� ����� ������
	Expense* ptrExpense = new Expense(month, day, category, payee, amount);
	// ��������� ������ � ������ ���� ��������
	ptrExpenseRecord->insertExp(ptrExpense);
}
//---------------------------------------------------------
//������ ������ AnnualReport
//�����������
AnnualReport::AnnualReport(PayRecord* pRR, ExpenseRecord* pER) : ptrRR(pRR), ptrER(pER)
{ /* ����� */
}
//---------------------------------------------------------
void AnnualReport::display()
{
	cout << "������� �����\n--------------\n" << endl;
	cout << "������\n" << endl;
	cout << "\t������� ��������:\t\t";
	rents = ptrRR->getSumOfRents();
	cout << rents << endl;

	cout << "�������\n" << endl;
	expenses = ptrER->displaySummary();
	cout << "������� �����:\t\t";
	cout << expenses << endl;
	// ��������� ������������
	cout << "\n������ �������:\t\t\t" << (rents - expenses) << endl;
}
//---------------------------------------------------------
//������ ������ userInterface
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
		cout << "                            ������ ������ 'i', \n"
			<< "                            ������� ����� 'd', \n"
			<< "                            ����� 'q': \n";
		ch = getaChar();
		if (ch == 'i') // ���� ������
		{
			cout << " �������� ������� 't', \n"
				<< " �������� ��������� ������/����� 'r', \n"
				<< " �������� ������� 'e': \n";
			ch = getaChar();
			switch (ch)
			{
				//������ ����� ���������� ������ �� ����� ��
				//�������������
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
			default: cout << "����������� �������\n";
				break;
			} // ����� ������ switch
		} // ����� ������� if
		else if (ch == 'd') // ����� ������
		{
			cout << " ������� ������ �������� 't', \n"
				<< " ������� ��������� ������ � ������ 'r' \n"
				<< " ������� ������� 'e', \n"
				<< " ������� ������� ����� 'a': \n";
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
			default: cout << "����� ������� ���\n";
				break;
			} // ����� switch
		} // ����� elseif
		else if (ch == 'q')
			return; // �����
		else
			cout << "����� ������� ���. ��������� ������ 'i', 'd' ��� 'q'\n";
	} // ����� while
} // ����� interact()
