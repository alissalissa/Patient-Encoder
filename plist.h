//The total set of all patients encoded in a file

#ifndef __PATIENTENCODER__PLIST_H__
#define __PATIENTENCODER__PLIST_H__

//STL includes
#include <algorithm>
#include <cstdlib> //for free() and malloc()
#include <fstream>
#include <string>
#include <vector>

//Local includes
#include "group.h"
#include "patient.h"
#include "suffix.h"

//macros
#define CODE_DOES_NOT_EXIST 0x34E5

#define MAGIC_NUMBER (char)0xEE
#define NEW_PATIENT (char)0x12
#define CODE (char)0x23
#define NAME (char)0x34
#define ORIENTATION (char)0x45
#define RACE (char)0x56
#define GENDER (char)0x67
#define AGE (char)0x78
#define START_GROUPS (char)0x89
#define GROUP_CODE (char)0x9a
#define GROUP_PATIENT_CODE (char)0xab
#define END_GROUP (char)0xbc
#define END_PATIENT (char)0xcd

class PList{
private:

	//Stores patients and groups as unsorted vectors
	//	PatientGroup stores patients as an un-sorted list
	vector <Patient*> patients;
	vector <PatientGroup> groups;
	//The code generator object
	SuffixGenerator *gen;

	//Utility function to search for a code
	bool contains(string);

public:

	//Constructors
	PList(void);
	PList(SuffixGenerator*);
	~PList(void)=default;
	PList(const PList&);

	//Add/Remove
	//These use actual patient pointers and group objects
	void AddPatient(Patient*);
	void AddPatientToGroup(Patient*,PatientGroup&);
	void Clear(void); //Deletes all patients and groups
	//Same thing using references to patient and group codes
	void AddPatientToGroup(string,string);
	void DeletePatient(string);
	//Creates/deletes new groups
	void CreateNewGroup(string);
	void DeleteGroup(string);

	//Accessors -- accessed using a string code
	PatientGroup &Group(string);
	Patient *GetPatient(string);
	vector<Patient*> Patients(void) const;
	vector<PatientGroup> Groups(void) const;
	SuffixGenerator *AccessSuffixGenerator(void)const{return gen;}
	//How many patients are in this list?
	size_t Size(void){return patients.size();}
	PList *operator=(PList);

	//Serialization
	// TODO (alissa#3#04/26/22): Implement encryption
	bool printToFile(string);
	bool readFromFile(string);

};

#endif // __PATIENTENCODER__PLIST_H__
