/*  LAB04B.cpp
    BRAD OAKE & ZAIN SHAFIQUE
    CPRG 4202
    Oct 2012
    
*/

#include <iostream>
#include <iomanip> // for output formatting
#include "WorkTicket.h" // my base class
using namespace std;

class WorkTicketArray
{	
	public:
		WorkTicketArray(int size = 1);
		~WorkTicketArray();
		WorkTicketArray(const WorkTicketArray& wtCopy);
		WorkTicketArray& operator=(const WorkTicketArray& wt);
		WorkTicket& operator[](int);
		int Size() const{return arraySize;}
	private:
		WorkTicket *ptrWorkTicket;
		int arraySize;
};
WorkTicketArray::WorkTicketArray(int size)
{
	try
	{
		ptrWorkTicket = new WorkTicket[size];
		arraySize = size;
	}
	catch(exception e)
	{
		throw e;
	}
}
WorkTicketArray::~WorkTicketArray()
{
	if(ptrWorkTicket)
	{
		delete[] ptrWorkTicket;
	}
}
WorkTicketArray::WorkTicketArray(const WorkTicketArray& wtCopy)
{
	try
	{
		arraySize = wtCopy.arraySize;
		ptrWorkTicket = new WorkTicket[wtCopy.arraySize];
		for(int count = 0; count < arraySize; count++)
		{
			this->ptrWorkTicket[count] = wtCopy.ptrWorkTicket[count];	
		}
	}
	catch(exception e)
	{
		throw e;
	}
}
WorkTicketArray& WorkTicketArray::operator=(const WorkTicketArray& wt)
{
	try
	{
		delete[] ptrWorkTicket;
		ptrWorkTicket = new WorkTicket[wt.arraySize];
		this->arraySize = wt.arraySize;
		
		for(int count = 0; count < arraySize; count++)
		{
			ptrWorkTicket[count] = wt.ptrWorkTicket[count];
		}
	}
	catch(exception e)
	{
		throw e;
	}
	return *this;
}
WorkTicket& WorkTicketArray::operator[](int position)
{
	if(position < 0 || position >= this->arraySize)
	{
		throw exception();
	}
	return ptrWorkTicket[position];
}
void ShowTickets(WorkTicketArray wt)
{
	cout << "***WORK TICKETS***\n\n";
		for(int count = 0; count < wt.Size(); count++)
		{
			cout << wt[count] << "\n";
		}
}
int main()
{
	int size;
	cout << "Brad Oake & Zain Shafique" << endl << endl;
	cout << "Please enter the number of tickets you want to process: ";
	
	size = GetValidInt(cin,0);
	WorkTicketArray wtaUserWorkTicket(size);
	for(int count = 0; count < size; count++)
	{
		cin >> wtaUserWorkTicket[count];		
	}
	for(int count = 0; count < size; count++)
	{
		wtaUserWorkTicket[count].ShowTicket();
		cout << endl;
	}
	return 0;
}
