/*  WorkTicket.cpp
    Bradley Oake
    CPRG 4202
    Oct 2012
*/
#ifndef _WORKTICKET
#define _WORKTICKET


#include <iostream>
#include <iomanip> // for output formatting
#include <sstream> // for stringstream
#include <cfloat>  // for minimum and maximum limts of type double
#include <climits> // for minimum and maximum limts of type int
using namespace std;

// Global, non-member console input/validation functions.
double GetValidDouble(istream& in, const double MIN = DBL_MIN, const double MAX = DBL_MAX);
int GetValidInt(istream& in, const int MIN = INT_MIN, const int MAX = INT_MAX); 

// WorkTicket class
class WorkTicket
{
public:
     WorkTicket();  // default constructor
     virtual bool SetTicket(int num, string client, int m, int d, int y, string descr); // mutator
     virtual void ShowTicket() const; // accessor  
     
     WorkTicket(const WorkTicket&); // copy constructor
     WorkTicket& operator=(const WorkTicket&); // assignment operator
     operator string (); // typecast converstion operator
     bool operator==(const WorkTicket&); // equality operator
     friend ostream& operator<<(ostream&, const WorkTicket&); // output operator
     friend istream& operator>>(istream&, WorkTicket&); // input operator
        
protected:
     // private attributes
     int workTicketNumber; // must be positive
     string clientNumber;  // alpha-numeric is fine, cannot be blank
     int workTicketDay;    // between 1 - 31
     int workTicketMonth;  // between 1 - 12
     int workTicketYear;   // between 2000 - 2099
     string issueDescription; // cannot be blank
};  // end of WorkTicket class

// WorkTicket copy constructor (Lab 3)
WorkTicket::WorkTicket(const WorkTicket& original)
{
     /*  A copy constructor that initializes a new WorkTicket object based 
         on an existing WorkTicket object. For testing purposes, include the 
         statement:
         cout << "\nA WorkTicket object was COPIED.\n";
     */
     workTicketNumber = original.workTicketNumber;
     clientNumber = original.clientNumber;
     workTicketDay = original.workTicketDay;
     workTicketMonth = original.workTicketMonth;
     workTicketYear = original.workTicketYear;
     issueDescription = original.issueDescription;
     
     //cout << "\nA WorkTicket object was COPIED.\n";
     
} // end of WorkTicket copy constructor

// Workticket assignment operator (Lab 3)
WorkTicket& WorkTicket::operator=(const WorkTicket& original)
{
     /*  Overload the assignment (=) operator to assign all of the attributes 
         of one WorkTicket object to another (member-wise assignment).  For 
         testing purposes, include the statement:
         cout << "\nA WorkTicket object was ASSIGNED.\n";
     */
     
     workTicketNumber = original.workTicketNumber;
     clientNumber = original.clientNumber;
     workTicketDay = original.workTicketDay;
     workTicketMonth = original.workTicketMonth;
     workTicketYear = original.workTicketYear;
     issueDescription = original.issueDescription; 
     
     //cout << "\nA WorkTicket object was ASSIGNED.\n";
     
     return *this;   
} // end of Workticket assignment operator

// WorkTicket typecast conversion operator (Lab 3)
WorkTicket::operator string ()
{
     /*  A conversion operator that converts a WorkTicket object to a string 
         in the following format: Work Ticket # Number (Date): Description; e.g.:
         "Work Ticket # 2 (10/3/2012): User cannot locate \'any\' key"
     */
     
     stringstream strStream;
     
     strStream << "Work Ticket # " << workTicketNumber << " (" << setw(2) 
               << setfill('0') << workTicketMonth << "/" 
               << setw(2) << setfill('0') << workTicketDay << "/" 
               << workTicketYear << "): " <<  issueDescription;
     return strStream.str();

} // WorkTicket typecast conversion operator 

// WorkTicket equality operator (Lab 3)
bool WorkTicket::operator==(const WorkTicket& original)
{
     /* Overload the equality ('==') operator  to compare a WorkTicket object 
        to another WorkTicket object using a member-wise comparison. Return 
        true if all the attributes of both objects are the same; false if they 
        are not all the same. 
     */
     
     return workTicketNumber == original.workTicketNumber &&
         clientNumber == original.clientNumber &&
         workTicketDay == original.workTicketDay &&
         workTicketMonth == original.workTicketMonth &&
         workTicketYear == original.workTicketYear &&
         issueDescription == original.issueDescription;
} // end of WorkTicket equality operator

// Overloaded input operator
ostream& operator<<(ostream& out, const WorkTicket& ticket)
{
     /* Overload the '<<' operator relative to the class to displays all the 
        object's attributes neatly on the console or to any ostream. This will 
        duplicate the functionality of the ShowWorkTicket() method however keep 
        the original method intact for legacy reasons. */
        
     out << "\nWork Ticket #: " << ticket.workTicketNumber
          << "\nClient Number: " << ticket.clientNumber
          << "\nDate:          " << setw(2) << setfill('0') << ticket.workTicketMonth
          << "/" << setw(2) << setfill('0') << ticket.workTicketDay
          << "/" << ticket.workTicketYear
          << "\nIssue:         " << ticket.issueDescription;  
     return out;       
} // end of overloaded input operator

// Overloaded output operator
istream& operator>>(istream& in, WorkTicket& ticket)
{
     /* Overload the '>>' operator relative to the class to allow the user 
        to enter all of the attributes of a WorkTicket object from the console 
        or any istream. Include validation.
     */
     
     const int MAX_DAY = 31;
     const int MAX_MONTH = 12;
     const int MIN_YEAR = 2000;
     const int MAX_YEAR = 2099;
     
     string client = "";
     string desc = "";
      
     cout << "\nWork Ticket Number: ";
     ticket.workTicketNumber = GetValidInt(in, 0);
     
     cout << "\nClient Number: ";
     do
     {
       in >> client;
     }while (client == "");
     ticket.clientNumber = client;

     
     cout << "\nDay: ";
     ticket.workTicketDay = GetValidInt(in, 1, MAX_DAY);
     cout << "\nMonth: ";
     ticket.workTicketMonth =  GetValidInt(in, 1, MAX_MONTH);
     cout << "\nYear: ";
     ticket.workTicketYear =  GetValidInt(in, MIN_YEAR, MAX_YEAR);

     cout << "\nDescription: ";
     do
     {
       getline(in, desc);
     }while(desc == "");
     ticket.issueDescription = desc; 
     return in;    
} // end of overloaded output operator 

/**
 * Gets a valid double value from the console with range checking
 *
 * @param  MIN the minimum value the user may enter.
 * @param  MIN the minimum value the user may enter.
 * @return A validated double input by the user.
 */
double GetValidDouble(istream& in, const double MIN, const double MAX)
{
       
       double validNumber = 0.0; // holds the user input
       string rubbish;           // holds garbage input.
       
       in >> validNumber;       // try to get input
       if(in.fail())            // if user input fails...
       {
           in.clear();              // reset the cin object
           in >> rubbish;           // cleans garbage from cin.

           // report the problem to the user.
           cerr << "\nInvalid input. Please try again and enter a numeric value: ";
           // Try again by calling the function again (recursion)
           validNumber = GetValidDouble(in, MIN, MAX);
       } 
       else if(validNumber < MIN || validNumber > MAX)// if value is outside range...
       {
           // report the problem to the user.
           cerr << "\nInvalid input. Please try again and enter a value between "
                << MIN << " and " << MAX << ": ";
           // Try again by call the function again (recursion)
           validNumber = GetValidDouble(in, MIN, MAX);
       }
       return validNumber; // returns a valid value to the calling function.
}
/**
 * Gets a valid int value from the console with range checking
 *
 * @see GetValidDouble()
 *
 * @param  MIN the minimum value the user may enter.
 * @param  MIN the minimum value the user may enter.
 * @return A validated integer input by the user.
 */
int GetValidInt(istream& in, const int MIN, const int MAX)
{
       double validNumber = 0.0; // holds the user input
       validNumber = GetValidDouble(in, MIN, MAX); // get a number
       if((int) validNumber < validNumber) // if the value is not a whole number...
       {
           cerr << "\nInvalid input. Please try again and enter a whole number: ";
           // Try again by calling the function again (recursion)
           validNumber = GetValidInt(in, MIN, MAX); 
       }
       return (int) validNumber; // returns a valid value to the calling function.
}

//  WorkTicket default constructor (Lab 2)
WorkTicket::WorkTicket()
{
     // set all attributes to default values
     workTicketNumber = 0;
     clientNumber = "";
     workTicketDay = 1;
     workTicketMonth = 1;
     workTicketYear = 2012;
     issueDescription = "";
} // end of WorkTicket constructor

// WorkTicket::SetTicket (Lab 2)
bool WorkTicket::SetTicket(int num, string client, int m, int d, int y, string descr)
{
     const int MAX_DAY = 31;
     const int MAX_MONTH = 12;
     const int MIN_YEAR = 2000;
     const int MAX_YEAR = 2099;
     bool valid = true; // flag for if parameters are valid
     
     // check numeric parameters
     if(num < 0 || m < 1 || m > MAX_MONTH || 
        d < 1 || d > MAX_DAY || 
        y < MIN_YEAR || y > MAX_YEAR)
          valid = false;
     // check string parameters     
     else if (client.length() < 1 || descr.length() < 1)
          valid = false;
     else // all parameters are valid
     {    
         // set atributes to parameter values
         workTicketNumber = num;
         clientNumber = client;
         workTicketDay = m;
         workTicketMonth = d;
         workTicketYear = y;
         issueDescription = descr;
     }
     // return true or false based on parameter validity
     return valid;
}

// WorkTicket::ShowTicket (Lab 2)
void WorkTicket::ShowTicket() const
{
     // display the attributes of the object neatly to the console
     cout << "\nWork Ticket #: " << workTicketNumber
          << "\nClient Number: " << clientNumber
          << "\nDate:          " << setw(2) << setfill('0') << workTicketMonth
          << "/" << setw(2) << setfill('0') << workTicketDay
          << "/" << workTicketYear
          << "\nIssue:         " << issueDescription;
}

#endif
