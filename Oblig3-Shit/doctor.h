#ifndef DOCTOR_H
#define DOCTOR_H
#include "prescription.h"

class Doctor : public Person
{
public:

    Doctor(int drid);

    void addPrescription();
    void display();
    void displayPrescriptions();
    void displayPrescriptions(std::string patient_name);
    void purgePrescriptionsBefore(int date);


	std::string getAddress() { return address; }
	int getPhone() { return phone; }
	int getID() { return id; }

	void setAddress(std::string adrs) { address = adrs; }
	void setPhone(int number) { phone = number; }
private:
    int id;
	std::string address;
	int phone;
	List* prescribed;
};

#endif // DOCTOR_H
