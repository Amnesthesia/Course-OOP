#include "prescription.h"

Prescription::Prescription() : Num_element(0)
{
    // Set all other variables
    this->setDrugName(readString("Drug name"));
    this->setDosage(readNum("Dosage in mg"));
    this->setDate(readDate("Date prescribed"));
    this->setPatient(new Person());
}

void Prescription::display()
{
    std::cout << "\n\nDrug: " << this->getDrugName();
    std::cout << "\nDosage: " << this->getDosage() << "mg";
    std::cout << "\nClient: " << this->client->getName();
    std::cout << "\nPrescription date: " << this->getDate();
}
