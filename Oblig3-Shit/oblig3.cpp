/* generated by dia/codegen.py */
/*(NULL)*/
class Person : Doctor 
{
public:
	std::string getName ();
	void setName (std::string nme);
	std::string name;
};

/*(NULL)*/
class Prescription 
{
public:
	std::string getDrugName ();
	int getDoctorID ();
	int getDosage ();
	Person* getPatient ();
	void setDrugName (std::string name);
	void setDoctorID (int docID);
	void setDosage (int milligram);
	void setClient (Person* ptnt);
	void setDate (int formatted_date);
	int getDate ();
private:
	std::string drug;
	int doctorID;
	int dosage;
	Person* client;
	int date;
};

/*(NULL)*/
class Doctor 
{
public:
	std::string getAddress ();
	int getPhone ();
private:
	std::string address;
	int phone;
};

