#ifndef GLOBALS_H
#define GLOBALS_H
#include <string>
#include "listtool.h"
#include "consts.h"

class Doctor;

void printHelp();
int readNum(std::string pretext);
int readNum(std::string pretext, int minimum, int maximum);
int readDate(std::string pretext);
char readChar(std::string pretext);
char readChar(std::string pretext, char alt1, char alt2);
std::string readString(std::string pretext);
Doctor* getDoctorByName(std::string name, bool add_if_no_exist = false);
void displayPrescriptionsForPatient(std::string patient);
void purgePrescriptionsBefore(int date);

#endif // GLOBALS_H
