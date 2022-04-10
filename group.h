//Defines an object containing a sorted group of patients

#ifndef __PATIENTENCODER_GROUP_H__
#define __PATIENTENCODER_GROUP_H__

//STL includes
#include <set>
#include <string>
#include <vector>

//Local includes
#include "patient.h"

class PatientGroup{
private:

	vector <Patient*> patients;
	string code;

public:

	//Constructors
	PatientGroup(void)=default;
	PatientGroup(string);
	PatientGroup(string,vector<Patient*>);
	PatientGroup(const PatientGroup&);
	~PatientGroup()=default;

	//Accessors
	Patient *operator[](string); //Takes a code string, returns the patient object
	vector<Patient*> Patients(void);
	void Add(Patient*);
	void Remove(Patient*);
	void Remove(string);
	size_t Size(void);
	string &Code(void);

	//Comparators
	bool operator==(PatientGroup);
	bool operator!=(PatientGroup);

};

#endif // __PATIENTENCODER_GROUP_H__
