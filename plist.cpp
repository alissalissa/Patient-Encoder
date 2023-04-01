//Implementation for Patient lists

#include "plist.h"

using namespace std;

//Utility
bool PList::contains_code(string code){
	bool c=false;
	for_each(patients.begin(),patients.end(),[&](Patient *p){
		if(p->Code()==code) c=true;
	});
	return c;
}

//Constructors
PList::PList(void){
    gen=new SuffixGenerator();
}

PList::PList(SuffixGenerator *g){
	gen=g;
}

PList::PList(const PList& haystack){
    //if(gen->is_initialized()) delete gen;
	patients=haystack.Patients();
	groups=haystack.Groups();
	gen=new SuffixGenerator(patients);
}

//Add/remove
void PList::AddPatient(Patient *p){
	Patient *np=new Patient(*p);
	patients.push_back(np);
	gen->update(p);
}

void PList::AddPatientToGroup(Patient *p,PatientGroup &g){
	g.Add(p);
}

void PList::AddPatientToGroup(string pcode,string gcode){
	Patient *ref=NULL;
	for(vector<Patient*>::iterator it=patients.begin();it!=patients.end();++it){
		if((*it)->Code()==pcode){
			ref=(*it);
			it=patients.end();
			--it;
		}
	}
	if(!ref) throw CODE_DOES_NOT_EXIST;
	for(vector<PatientGroup>::iterator it=groups.begin();it!=groups.end();++it){
		if((*it).Code()==gcode){
			(*it).Add(ref);
		}
	}
}

void PList::DeletePatient(string pc){
	//First we search all the groups to pop this patient out
	for(vector<PatientGroup>::iterator it=groups.begin();it!=groups.end();++it){
		//We can just delete without checking, since PatientGroup removes safely
		(*it).Remove(pc);
	}
	//The patient has been removed from all groups
	//Now we delete the master patient
	Patient *p=NULL;
	vector<Patient*>::iterator ref=patients.end();
	for(vector<Patient*>::iterator it=patients.begin();it!=patients.end();++it){
		if((*it)->Code()==pc){
			p=*it;
			ref=it;
			it=patients.end();
			--it;
		}
	}
	if(p && ref!=patients.end()){
		patients.erase(ref);
		delete p;
	}
}

void PList::CreateNewGroup(string gc){
	PatientGroup g(gc);
	groups.push_back(g);
}

void PList::DeleteGroup(string c){
	for(vector<PatientGroup>::iterator it=groups.begin();it!=groups.end();++it){
		if((*it).Code()==c){
			groups.erase(it);
			it=groups.end();
			--it;
		}
	}
}

void PList::Clear(){
	patients.clear();
	groups.clear();
	delete gen;
	gen=new SuffixGenerator();
}

/********************END ADD/REMOVE*****************************/

//Accessors
PatientGroup &PList::Group(string c){
	for(int i=0;i<(int)groups.size();i++){
		if(groups[i].Code()==c) return groups[i];
	}
	throw CODE_DOES_NOT_EXIST;
}

Patient *PList::GetPatient(string pc){
	for(vector<Patient*>::iterator it=patients.begin();it != patients.end();++it){
		if((*it)->Code()==pc) return (*it);
	}
	return NULL;
}

vector <PatientGroup> PList::Groups(void) const{
	return groups;
}

vector<Patient*> PList::Patients(void) const{
	return patients;
}

PList *PList::operator=(PList haystack){

	patients=haystack.Patients();
	groups=haystack.Groups();
	delete gen;
	gen=haystack.AccessSuffixGenerator();
	return this;

}

void PList::Digest(PList *source){
	delete gen;
	for_each(patients.begin(),patients.end(),[&](Patient *p){
		delete p;
	});
	patients.clear();
	groups.clear();

	gen=new SuffixGenerator();
	for(size_t i=0;i<source->Patients().size();i++)
		AddPatient(new Patient(source->Patients()[i]->Name(),source->Patients()[i]->Code(),source->Patients()[i]->Age(),source->Patients()[i]->Gender(),source->Patients()[i]->Race(),source->Patients()[i]->Orientation()));
	for_each(source->Groups().begin(),source->Groups().end(),[&](PatientGroup g){
		CreateNewGroup(g.Code());
		for(size_t i=0;i<g.Patients().size();i++)
			AddPatientToGroup(g.Patients()[i]->Code(),g.Code());
	});
}

/****************************END ACCESSORS*******************/

//Serialization

bool PList::printToFile(string fp){

	fstream output_file(fp,fstream::binary|fstream::out);
	if(!output_file.is_open()){
		//We need to alert that this file can't be written to
		wxMessageBox(wxT("Unable to open this file for writing.\nCheck that you have permission to edit in this directory."),wxT("Unable to Complete"));
		return false;
	}

	//The file is open.  Start writing.
	//Must begin with the magic number, otherwise the file will be read as invalid
	output_file.put(MAGIC_NUMBER);
	//Next we start listing patients.
	//Each patient will be marked by a magic number, followed by a magic number for every variable
	//Every variable magic number will be followed by the length of the data to follow
	for(size_t patient_index=0;patient_index<patients.size();patient_index++){
		//Start the patient
		output_file.put(NEW_PATIENT);
		//Start the code
		output_file.put(CODE);
		//Length of the patient identifier code
		size_t lb=patients[patient_index]->Code().length(); //lb = length buffer
		output_file.write(reinterpret_cast<char*>(&lb),sizeof(size_t));
		//Follow with the identifier code
		output_file.write(patients[patient_index]->Code().c_str(),lb);
		//Start the name
		output_file.put(NAME);
		//Follow with the length of the name
		lb=patients[patient_index]->Name().length();
		output_file.write(reinterpret_cast<char*>(&lb),sizeof(size_t));
		//And then the name
		output_file.write(patients[patient_index]->Name().c_str(),patients[patient_index]->Name().length());
		//Same process with age
		output_file.put(AGE);
		int ab=patients[patient_index]->Age(); //ab = age buffer
		output_file.write(reinterpret_cast<char*>(&ab),sizeof(int));
		//Same process with gender
		output_file.put(GENDER);
		output_file.put(patients[patient_index]->Gender());
		//Same process with race
		output_file.put(RACE);
		output_file.put(patients[patient_index]->Race());
		//Same process with orientation
		output_file.put(ORIENTATION);
		output_file.put(patients[patient_index]->Orientation());
		//End the patient
		output_file.put(END_PATIENT);
	}

	//Now encode the groups, but only if there are any
	if(groups.size()>0){
		//The start of group encoding
		output_file.put(START_GROUPS);

		//Cycle through the groups
		for(size_t group_index=0;group_index<groups.size();group_index++){

			//Identify that we're starting a group
			output_file.put(GROUP_CODE);
			//Size of the group code
			size_t lb=groups[group_index].Code().length();
			output_file.write(reinterpret_cast<char*>(&lb),sizeof(size_t));
			//The actual code
			output_file.write(groups[group_index].Code().c_str(),lb);

			//Encode the patients
			if(groups[group_index].Patients().size()>0){

                //Cycle through the patients
                for(size_t patient_index=0;patient_index<groups[group_index].Patients().size();patient_index++){

					//Indicate that a patient code is coming
					output_file.put(GROUP_PATIENT_CODE);
					//Size of the code
					lb=groups[group_index].Patients()[patient_index]->Code().length();
					output_file.write(reinterpret_cast<char*>(&lb),sizeof(size_t));
					//The code
					output_file.write(groups[group_index].Patients()[patient_index]->Code().c_str(),lb);
					//End the patient
					output_file.put(END_PATIENT);

                }

			}

			//End the group
			output_file.put(END_GROUP);

		}

	}

	//End the file with the magic number
	output_file.put(MAGIC_NUMBER);

	//close the file
	output_file.close();

	return true;

}

bool PList::readFromFile(string fp){

	PList *p=new PList(new SuffixGenerator());

    //Open up the file from reading
	fstream file;
	file.open(fp,fstream::binary|fstream::in);

	if(!file.is_open()) return false;

	//Start reading
	//Does our file begin with the magic number?
	char buffer='\0';
	file.get(buffer);
	if(buffer!=MAGIC_NUMBER){
        delete p;
        file.close();
        return false;
    }
	//Are there patients to encode?
	file.get(buffer);
	while(buffer==NEW_PATIENT){

		//lets collect the patient data
		file.get(buffer);
		if(buffer!=CODE){
			file.close();
			return false;
		}
		size_t length=0;
		file.read(reinterpret_cast<char*>(&length),sizeof(size_t));
		//cout<<"Length of code: "<<length<<endl;
        //Get the actual code
        char *code_buffer=(char*)malloc(length+1);
        file.read(code_buffer,length);
        code_buffer[length]='\0';

        //Next up should be name
        file.get(buffer);
        if(buffer!=NAME){
			file.close();
			free(code_buffer);
			return false;
        }
        //Get the length of the name
        file.read(reinterpret_cast<char*>(&length),sizeof(size_t));
        //Get the name
        char *name_buffer=(char*)malloc(length+1);
        file.read(name_buffer,length);
        name_buffer[length]='\0';

        //Next up should be age
        file.get(buffer);
        if(buffer!=AGE){
			file.close();
			free(code_buffer);
			free(name_buffer);
			return false;
        }
        int age_buffer=-1;
        //get the age
        file.read(reinterpret_cast<char*>(&age_buffer),sizeof(int));

        //Next up should be gender
        file.get(buffer);
        if(buffer!=GENDER){
			file.close();
			free(code_buffer);
			free(name_buffer);
			return false;
        }
        char gender_buffer='\0';
        file.get(gender_buffer);

        //Next up should race
        file.get(buffer);
        if(buffer!=RACE){
            file.close();
            free(code_buffer);
            free(name_buffer);
            return false;
        }
        char race_buffer='\0';
        file.get(race_buffer);

        //Next up should be orientation
        file.get(buffer);
        if(buffer!=ORIENTATION){
            file.close();
            free(code_buffer);
            free(name_buffer);
            return false;
        }
        char orientation_buffer='\0';
        file.get(orientation_buffer);

        //Finally we should end the patient
        file.get(buffer);
        if(buffer!=END_PATIENT){
            file.close();
            free(code_buffer);
            free(name_buffer);
            return false;
        }

        string cbs(code_buffer);
        string nbs(name_buffer);
        //cout<<"Adding patient to PList object"<<endl;
        p->AddPatient(new Patient(nbs,cbs,age_buffer,gender_buffer,race_buffer,orientation_buffer));
        //cout<<"Patient added..."<<endl;

        free(code_buffer);
        free(name_buffer);

        file.get(buffer);

	}

    //if there are groups, start reading them
	while(buffer==START_GROUPS){
        file.get(buffer);
        //Look for the group code tag
        if(buffer!=GROUP_CODE){
            file.close();
            return false;
        }
        //Get the length of the group code
        size_t lb=0;
        file.read(reinterpret_cast<char*>(&lb),sizeof(size_t));
        //Allocate memory for the group code
        char *gcbuf=(char*)malloc(lb);
        //Read in the group code
        file.read(gcbuf,lb);
        //Next up we should see a patient code tag or the end of the group
        file.get(buffer);
        //Set aside some memory to store patient codes
        vector <string> gpcodes;
        while(buffer==GROUP_PATIENT_CODE){
			//Read in the length
			lb=0;
			file.read(reinterpret_cast<char*>(&lb),sizeof(size_t));
			//Set aside some memory and read in the code
			char *gpcbuf=(char*)malloc(lb);
			file.read(gpcbuf,lb);
			//Add it to the vector of codes
			string temp(gpcbuf);
			gpcodes.push_back(temp);
			free(gpcbuf);
			//read in the next code
			file.get(buffer);
			if(buffer!=END_PATIENT){
				free(gcbuf);
				file.close();
				return false;
			}
			file.get(buffer);
        }

        //Create a group and add the patients
        string group_code(gcbuf);
        free(gcbuf);

        //Check to make sure all the codes are actually in the patient list
		bool c=true;
		for_each(gpcodes.begin(),gpcodes.end(),[&](string cotemp){
			if(!contains_code(cotemp)) c=false;
		});
		if(!c){
			file.close();
			return false;
		}
		//All the codes are valid
		p->CreateNewGroup(group_code);
		for_each(gpcodes.begin(),gpcodes.end(),[&](string cotemp){
			p->AddPatientToGroup(cotemp,group_code);
		});

		if(buffer!=END_GROUP){
			file.close();
			return false;
		}

		file.get(buffer);

	}

	if(buffer!=MAGIC_NUMBER){
		file.close();
		return false;
	}
	file.close();

	this->Clear();
	this->Digest(p);
	delete p;
	return true;

}

int match_term(vector<Patient*> haystack,string term){

	for(int i=0;i<(int)haystack.size();i++){
		//Cycle through each term and see if the term matches
		//Start by grabbing the pointer to the patient so we don't have to keep re-accessing
		Patient p=*(haystack[i]);
		if(string_to_lower(p.Name()).find(term)!=string::npos) return i;
		if(string_to_lower(p.Code()).find(term)!=string::npos) return i;
		//now we need to do some type conversions
		if(term.length()==1){
			char char_term=term[0];
			if(tolower(p.Race())==char_term) return i;
			if(tolower(p.Gender())==char_term) return i;
			if(tolower(p.Orientation())==char_term) return i;
		}
		int int_term=atoi(term.c_str());
		if(p.Age()==int_term) return i;
	}
	return -1;
}
