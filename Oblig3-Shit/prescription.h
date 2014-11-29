#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H
#include "person.h"

class Prescription : public Num_element
{
public:
    Prescription();
    void display();

	// Getters
	std::string getDrugName () { return drug; }
	int getDosage () { return dosage; }
	int getDate () { return date; }
	Person* getPatient () { return client; }

	// Setters
	void setPatient (Person* ptnt) { client = ptnt; }
	void setDate (int formatted_date) { date = formatted_date; }
	void setDrugName (std::string name) { drug = name; }
	void setDosage (int milligram) { dosage = milligram; }

private:
	std::string drug;
	int dosage;
	Person* client;
	int date;
};

#endif // PRESCRIPTION_H
