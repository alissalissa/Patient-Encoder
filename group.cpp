//Implementation file for a patient group

#include "group.h"

using namespace std;

//Constructors
PatientGroup::PatientGroup(string c){
	code=c;
}

PatientGroup::PatientGroup(string c,vector<Patient*> h){
	code=c;
	patients=h;
}

//Copy constructor
PatientGroup::PatientGroup(const PatientGroup& h){
	//debug code
	cout<<"Incoming object patient list size: "<<h.patients.size()<<endl;
	patients=h.patients;
	code=h.code;
}
/*******************END CONSTRUCTORS****************/

//Accessors
Patient *PatientGroup::operator[](string code){
	for(vector<Patient*>::iterator it=patients.begin();it!=patients.end();++it){
		if((*it)->Code()==code) return *it;
	}
	return NULL;
}

vector<Patient*> PatientGroup::Patients(void){
	return patients;
}

void PatientGroup::Add(Patient* h){
	patients.push_back(h);
}

void PatientGroup::Remove(Patient *p){
	vector<Patient*>::iterator r=patients.end();
	for(vector<Patient*>::iterator it=patients.begin();it!=patients.end();++it){
		if((*it)->operator==(*p)){
			r=it;
			it=patients.end();
			--it;
		}
	}
	if(r!=patients.end()) patients.erase(r);
}

void PatientGroup::Remove(string c){

	vector<Patient*>::iterator r=patients.end();
	for(vector<Patient*>::iterator it=patients.begin();it!=patients.end();++it){
		if((*it)->Code() == c){
			r=it;
			it=patients.end();
			--it;
		}
	}

	if(r!=patients.end()) patients.erase(r);

}

size_t PatientGroup::Size(void){
	return patients.size();
}

string &PatientGroup::Code(void){
	return code;
}
/********************END ACCESSORS**********************/

//Comparators
bool PatientGroup::operator==(PatientGroup pg){
	if(code!=pg.Code()) return false;
	if(patients.size()!=pg.Size()) return false;
	//We know the two groups are guarenteed to be the same size at this point
	for(vector<Patient*>::iterator it1=this->Patients().begin(),it2=pg.Patients().begin();it1!=this->Patients().end() && it2!=pg.Patients().end();++it1,++it2){ //Cycle through all the patients in both groups simultaneously
		if((*it1)->operator!=(*(*it2))) return false;
	}
	return true;
}

bool PatientGroup::operator!=(PatientGroup pg){
	return !this->operator==(pg);
}
