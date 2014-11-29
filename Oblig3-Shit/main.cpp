#include <iostream>
#include <cstdlib>
#include <time.h>
#include "doctor.h"

using namespace std;

List* doctors;

int main()
{
    doctors = new List(Sorted);

    // Set up char to store users command in
    char cmd;

    // Start main program loop
    do
    {
        // Request command
        cmd = readChar("Command");

        // Temporary doctors object
        Doctor* tmp;

        // Decide what to do depending on user command
        switch(cmd)
        {
            case 'r':
                getDoctorByName(readString("Doctor's Name"), true)->addPrescription();
                break;
            case 'l':
                tmp = getDoctorByName(readString("Doctor's Name"));
                if(tmp->getID() > 0)
                    tmp->displayPrescriptions();
                else
                {
                    cout << "\nNo doctor with this name exists";
                    delete tmp;
                }
                break;
            case 'p':
                displayPrescriptionsForPatient(readString("Patient's Name"));
                break;
            case 'f':
                purgePrescriptionsBefore(readDate("Date"));
                break;
            case 'u':
                break;
            case 'i':
                break;
            case 'h':
                printHelp();
                break;
        }

    } while(readChar("Command") != 'q');

    return 0;
}

void printHelp()
{
    cout << "\nAvailable commands: ";
    cout << "\n\tR\t-\tRegister new prescription";
    cout << "\n\tL\t-\tList prescriptions prescribed by specific doctor";
    cout << "\n\tP\t-\tList prescriptions prescribed to specific client";
    cout << "\n\tF\t-\tPurge all prescriptions prescribed before a specific date";
    cout << "\n\tU\t-\tPrint to file";
    cout << "\n\tI\t-\tLoad from file";
    cout << "\n\tH\t-\tPrint help menu";
    cout << "\n\tQ\t-\tExit";
}


// Global input functions
/**
 ** Reads a numeric value from stdin and makes sure it's
 ** in a valid dateformat of YYYYMMDD
 **
 ** @param std::string pretext      Text to print pre-input
 ** @return int
 **/
int readDate(std::string pretext)
{
    // We'll store users input in d
    int d;

    // and use these for time:
    int oldest, newest, formatted;

    // Set up a timestruct to get current time
    time_t timestamp = time(0);
    struct tm *now = localtime( &timestamp );


    // We require dates to be +- 1 year from now, so use our timestruct
    // to subtract one year, and make it a valid date
    now->tm_year -= 1;
    mktime(now);
    oldest = ((now->tm_year - 1) * 10000) + (now->tm_mon * 100) + now->tm_mday;

    // Now do the same, but add 1 year from now (2 since we subtracted)
    now->tm_year += 2;
    mktime(now);
    newest = ((now->tm_year + 1) * 10000) + (now->tm_mon * 100) + now->tm_mday;

    // Then we fetch it from the user ...
    d = readNum(pretext, oldest, newest);

    // But, we have to make sure it's an ACTUAL date we received. So, if it's not,
    // we automagically turn it into one like so:
    now->tm_year = d / 10000;
    now->tm_mon = d / 100;
    now->tm_mday = d % 100;
    mktime(now);

    // Then, we format it the way we want it ...
    formatted = ((now->tm_year) * 10000) + (now->tm_mon * 100) + now->tm_mday;

    // ... and return it
    return formatted;
}

/**
 ** Reads a numeric value from stdin
 ** and returns it as is
 **
 ** @param std::string pretext      Text to print pre-input
 **/
int readNum(std::string pretext)
{
    int n;

    cout << "\n" + pretext + ": ";
    cin >> n;
    cin.ignore();
    return n;
}

/**
 ** Reads a numeric value from stdin
 ** and returns it as is
 **
 ** @param std::string pretext      Text to print pre-input
 **/
int readNum(std::string pretext, int minimum, int maximum)
{
    int n = 0;
    do
    {
        if(n > 0)
        {
            pretext = "\nPlease enter a number greater than " + minimum;
            if (maximum > 0)
                pretext += " and less than " + maximum;
        }
        n = readNum(pretext);
    } while( n > minimum && (maximum > 0 ? n < maximum : true));

    return n;
}

/**
 ** Reads a string from stdin and returns it
 ** as is.
 **
 ** @param std::string pretext      Text to print pre-input
 ** @return std::string
 **/
std::string readString(std::string pretext)
{
    std::string str;
    cout << "\n" + pretext + ": ";
    getline(cin,str);
    return str;
}

/**
 ** Reads a character from stdin and returns it.
 **
 ** @param std::string pretext      Text to print before input
 ** @return char
 **/
char readChar(std::string pretext)
{
    char c;

    cout << "\n" + pretext + ": ";
    cin >> c;
    cin.ignore();
    return tolower(c);
}

/**
 ** Reads a character from stdin, but only accepts one
 ** of the provided alternatives. Continues until one
 ** of the alternatives have been entered.
 **
 ** @param std::string pretext      Text to print before input
 ** @param char alt1                Alternative #1
 ** @param char alt2                Alternative #2
 ** @return char
 **/
char readChar(std::string pretext, char alt1, char alt2)
{
    // Set up default value for our char, for error checking purposes
    char c = '-';

    // Make sure both our alternatives are lowercase
    alt1 = tolower(alt1);
    alt2 = tolower(alt2);
    do
    {
        // Unless the default value is set, and we're still in the loop,
        // and invalid character has been provided. Inform user of this.
        if(c != '-')
        {
            pretext = "Invalid character. Alternatives are: ";
            pretext += alt1;
            pretext += " or ";
            pretext += alt2;
        }

        // Get our string, then force it lowercase.
        c = readChar(pretext);

    } while(c != alt1 || c!=alt2);

    return c;
}

/**
 ** Checks if there's a doctor with a specific name,
 ** and returns it if found; and if add_if_no_exist
 ** is true, adds it if it doesn't exist.
 **
 ** @param std::string name
 ** @param bool add_if_no_exist
 ** @return Doctor*
 **/
Doctor* getDoctorByName(std::string name, bool add_if_no_exist)
{
    Doctor* tmp;

    // Loop through all doctors and pop each element out
    for(int i=1; i <= doctors->no_of_elements(); i++)
    {
        tmp = (Doctor*) doctors->remove_no(i);

        // ... and put it back in -_-
        doctors->add(tmp);

        // Compare the name provided with the doctors name...
        if(name.compare(tmp->getName()) == 0)
            // .. and return if they compare equal
            return tmp;
    }

    if(add_if_no_exist)
    {
        cout << "\nNo doctor named " + name + " found. Creating ...";
        tmp = new Doctor(LAST_DOCTOR_ID++);
        doctors->add(tmp);
    }
    else
        tmp = new Doctor(NO_DOCTOR_WITH_NAME);


    return tmp;
}

/**
 ** Displays all prescriptions for a specific patient,
 ** by asking each doctor to display prescriptions made
 ** for that patient, if any.
 ** Also displays which doctor prescribed it.
 **
 ** @param std::string patient
 **/
void displayPrescriptionsForPatient(std::string patient)
{
    Doctor* tmp;
    for(int i = 1; i <= doctors->no_of_elements(); i++)
    {
        tmp = (Doctor*) doctors->remove_no(i);
        doctors->add(tmp);

        tmp->display();
        tmp->displayPrescriptions(patient);
    }
}

/**
 ** Asks each doctor to remove any prescriptions
 ** older than a specific date
 **
 ** @param int date
 **/
void purgePrescriptionsBefore(int date)
{
    Doctor* tmp;
    for(int i = 1; i <= doctors->no_of_elements(); i++)
    {
        tmp = (Doctor*) doctors->remove_no(i);
        doctors->add(tmp);

        tmp->purgePrescriptionsBefore(date);
    }
}

