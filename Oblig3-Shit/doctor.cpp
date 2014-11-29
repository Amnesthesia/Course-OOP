#include "doctor.h"

Doctor::Doctor(int drid) : Person(drid)
{
    this->id = drid;
    this->setAddress(readString("Address"));
    this->setPhone(readNum("Phone",1000000,99999999));
    this->prescribed = new List(FIFO);
}

/**
 ** Creates a new prescription and adds it to this
 ** doctor
 **
 */
void Doctor::addPrescription()
{
    prescribed->add(new Prescription());
}

/**
 ** Displays information about this doctor
 */
void Doctor::display()
{
    cout << "\nDoctor ID: " << this->getID();
    cout << "\nName: " << this->getName();
    cout << "\nAddress: " << this->getAddress();
}

/**
 ** Displays all prescriptions by this doctor
 **
 **
 */
void Doctor::displayPrescriptions()
{
    Prescription* tmp;
    for(int i = 1; i<= prescribed->no_of_elements(); i++)
    {
        tmp = (Prescription*) prescribed->remove();
        prescribed->add(tmp);

        tmp->display();
    }
}

/**
 ** Displays all prescriptions made for a specific client
 **
 ** @param std::string client_name
 **/
void Doctor::displayPrescriptions(std::string client_name)
{
    for(int i = 1; i<= prescribed->no_of_elements(); i++)
    {
        Prescription* tmp = (Prescription*) prescribed->remove();
        prescribed->add(tmp);

        if(client_name.compare(tmp->getPatient()->getName()) == 0)
            tmp->display();
    }
}

/**
 ** Purges all prescriptions made before a specified date
 **
 ** @param std::string client_name
 **/
void Doctor::purgePrescriptionsBefore(int date)
{
    for(int i = 1; i<= prescribed->no_of_elements(); i++)
    {
        Prescription* tmp = (Prescription*) prescribed->remove();
        if(tmp->getDate() < date)
            delete tmp;
        else
            prescribed->add(tmp);
    }
}
