#include  <iostream>         //  cin, cout
#include  <fstream>          //  ifstream, ofstream
#include  <cstring>          //  strcpy, strlen, strncmp
#include  <cctype>           //  toupper



using namespace std;


const int MAX_EMPLOYEES = 100;

void printMenu();
char read();
int readNum(char* t, int min, int max);
char readChar(char* t, char alternative1, char alternative2);
char* readChar(char* t);
int exists(int employee_id);
void insert(int n);
void fromFile();
void toFile();
void newEmployee();
void updatePartner();
void newChild();
void employeeInfo();
void getYear();
void delEmployee();

#include "include/individual.h"
#include "include/adult.h"
#include "include/child.h"
#include "include/partner.h"
#include "include/employee.h"

employee* employees[MAX_EMPLOYEES+1];
int last_used;

int main()
{
    // User choice
    char cmd;

    // Set last_used to 0, and let's start!
    last_used = 0;

    fromFile();
    printMenu();

    // Get user input
    cmd = read();

    while(cmd != 'Q')
    {
        switch(cmd)
        {
            case 'N':
                newEmployee();
                break;
            case 'P':
                updatePartner();
                break;
            case 'B':
                newChild();
                break;
            case 'D':
                employeeInfo();
                break;
            case 'A':
                delEmployee();
                break;
            default:
                printMenu();
                break;
        }
        cmd = read();
    }

    return 0;
}

void printMenu()
{
    cout << "\n\nAvailable Commands:";
    cout << "\n\tN \tNew employee";
    cout << "\n\tP \tPartner-change";
    cout << "\n\tB \tnew Child";
    cout << "\n\tD \tInfo about employee";
    cout << "\n\tA \tAll children from a given year";
    cout << "\n\tF \tRemove employee";
    cout << "\n\tQ \tQuit";
}

char read()
{
    char ch;
    cout << "\n\nCommand: ";
    cin >> ch;
    cin.ignore();
    return (toupper(ch));
}

int readNum(char* t, int min, int max)
{
    int num;
    do
    {
        cout << "\n\t" << t << "(" << min << "-" << max << "): ";
        cin >> num;
        cin.ignore(1000,'\n');
    } while (num < min || num > max);
    return num;
}

int readNum(char* t)
{
    int num;
    cout << "\n\t" << t << ": ";
    cin >> num;
    cin.ignore();

    return num;
}

// This function returns a character out of two alternatives
char readChar(char* t, char alternative1, char alternative2)
{
    char w;
    do
    {
        cout << "\n\t" << t << "(" << alternative1 << "/" << alternative2 << "): ";
        cin >> w;
        cin.ignore();

     // Loop as long as none of the alternatives have been chosen
    } while(w != alternative1 && w != alternative2);

    return w;
}


// This function returns a char-string entered by the user
char* readChar(char* t)
{
    char* w;
    cout << "\n\t" << t << ": ";
    cin.getline(w,100);
   //cin.ignore(1000,'\n');

    return w;
}


int exists(int employee_id)
{
    if(last_used==0)
        return -1;
    // Returns employee with a given ID, or -1 if it doesnt exist
    for(int k = 0; k<last_used;k++)
    {
        if(employees[k]->getID() == employee_id)
            return employees[k]->getID();
    }
    return -1;
}

void insert(int n)
{
    // "Instikkssortering" av ETT objekt
    int d = exists(n);
    if(d>-1)
    {
        cout << "\nEmployee with ID " << n << " (" << d << ") already exists.";
        return;
    }

    // Set the index to last_used, because by default, we put the employee at the end of our array
    int index = last_used;

    // Now loop from 0, to our last employee
    for(int k = 0; k<last_used; k++)
    {
        // Check if the ID we want for this employee is lower than the ID of any employee
        // currently in the list.
        if(*employees[k] > n)
        {
            // As soon as we find an employee with a higher ID than the one
            // we wish to insert, change index from last_used to where we found it, and break.
            index = k;
            break;
        }

    }

    // If the index has changed now, loop from the end of the array, down to the new index.
    // Move each employee one step up in the array, and increase the last_used counter.
    if(index != last_used)
    {
        for(int i = last_used; i>=index; i--)
            employees[i+1] = employees[i];
    }
    last_used++;
    // Now, regardless of whether the index is at the end of the array, or at a new position,
    // we can accept information for a new employee for the determined position, with the
    // requested ID.
    employees[index] = new employee(n);
}

void fromFile()
{
    // Load from file
    ifstream in("db");
    if(!in.good())
    {
        cout << "\ndb file does not yet exist";
        return;
    }
    in >> last_used;
    for(int i=0;i<last_used;i++)
    {
        int tmpid;
        in >> tmpid;
        cout << "Creating employee #" << tmpid;
        employees[i] = new employee(tmpid,in);
    }
}

void toFile()
{
    // Outputs to file
    ofstream out("db");
    out << last_used << "\n";
    for(int i=0;i<last_used;i++)
        employees[i]->toFile(out);
}

// Adds a new employee
void newEmployee()
{
    // Check if we can add more employees
    if(last_used>=MAX_EMPLOYEES)
    {
        std::cout << "\nMaximum amount of employees already reached.";
        return;
    }

    // Request ID for new employee
    int id;
    std::cout << "\nEmployee ID: ";
    std::cin >> id;
    std::cin.ignore();

    insert(id);
    toFile();
}

void updatePartner()
{
    // P - update data about partner
    int id = readNum("\nEmployee ID");
    int e = exists(id);
    if(e>-1)
    {
        employees[e]->updatePartner();
    }
    else
    {
        cout << "\nEmployee with ID " << id << " does not exist";
    }

    toFile();
}

void newChild()
{
    // B - new child
    int edit = exists(readNum("\nEnter employee ID to add child"));
    if(edit>-1)
        employees[edit]->addChild();
    else
        std::cout << "\nNo employee with ID " << edit;
    toFile();
}

void employeeInfo()
{
    // D - Data about employee
    int which = exists(readNum("Employee ID"));

    if(which>-1)
        employees[which]->display();
    else
        cout << "\nNo employee with that ID exists.";

}

void getYear()
{
    // A - prints everyone with a child for a given year

    // Requests user-input for year
    int year = readNum("\nEnter year (yyyy)",1914,2013);

    // Strip away the millenias.
    year %= 1000;

    for(int i=0; i<last_used; i++)
        if(employees[i]->hasChildBornYear(year))
            employees[i]->printParent();
}

void delEmployee()
{
    // F - Removes employee
    // "Instikkssortering" av ETT objekt

    // Get user input, and index of employee
    int n = exists(readNum("\nID of employee to remove"));

    if(n<0)
    {
        cout << "\nEmployee with ID " << n << " does not exist.";
        return;
    }

    // Check if user to remove is at the end of the array and delete it,
    // if it's not at the end we need to resort the array.

    delete employees[n];

    if(last_used != n)
    {
        for(int i = last_used; i>n; i--)
            employees[i-1] = employees[i];
    }

    toFile();
}
