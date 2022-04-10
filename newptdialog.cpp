//Implementation of a new Patient dialog

#include "newptdialog.h"

using namespace std;

NewPatientDialog::NewPatientDialog( wxWindow* parent, SuffixGenerator *s,wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){
	gen=s;

	this->SetSizeHints(wxDefaultSize,wxDefaultSize);

	wxBoxSizer* main_sizer;
	main_sizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("Patient Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer5->Add( m_staticText3, 0, wxALL, 5 );

	pt_name_input = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,-1 ), 0 );
	bSizer5->Add( pt_name_input, 0, wxALL, 5 );


	main_sizer->Add( bSizer5, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText4 = new wxStaticText( this, wxID_ANY, wxT("Patient Age:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText4->Wrap( -1 );
	bSizer6->Add( m_staticText4, 0, wxALL, 5 );

	age_input = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( age_input, 0, wxALL, 5 );

	m_staticText5 = new wxStaticText( this, wxID_ANY, wxT("Patient Gender:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizer6->Add( m_staticText5, 0, wxALL, 5 );

	wxString gender_selectionChoices[] = { wxT("Male"), wxT("Female"), wxT("Trans") };
	int gender_selectionNChoices = sizeof( gender_selectionChoices ) / sizeof( wxString );
	gender_selection = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, gender_selectionNChoices, gender_selectionChoices, 0 );
	gender_selection->SetSelection( 0 );
	bSizer6->Add( gender_selection, 0, wxALL, 5 );


	main_sizer->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText6 = new wxStaticText( this, wxID_ANY, wxT("Patient Race:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizer7->Add( m_staticText6, 0, wxALL, 5 );

	wxString race_selectorChoices[] = { wxT("White"), wxT("Black"), wxT("Hispanic"), wxT("Asian"), wxT("Biracial"), wxT("Other"), wxT("Unknown") };
	int race_selectorNChoices = sizeof( race_selectorChoices ) / sizeof( wxString );
	race_selector = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, race_selectorNChoices, race_selectorChoices, 0 );
	race_selector->SetSelection( 0 );
	bSizer7->Add( race_selector, 0, wxALL, 5 );

	m_staticText7 = new wxStaticText( this, wxID_ANY, wxT("Orientation: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	bSizer7->Add( m_staticText7, 0, wxALL, 5 );

	wxString orientation_selectorChoices[] = { wxT("Heterosexual"), wxT("Homosexual"), wxT("Bisexual"), wxT("Other"), wxT("Unknown") };
	int orientation_selectorNChoices = sizeof( orientation_selectorChoices ) / sizeof( wxString );
	orientation_selector = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, orientation_selectorNChoices, orientation_selectorChoices, 0 );
	orientation_selector->SetSelection( 0 );
	bSizer7->Add( orientation_selector, 0, wxALL, 5 );


	main_sizer->Add( bSizer7, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText8 = new wxStaticText( this, wxID_ANY, wxT("Patient Code:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	bSizer8->Add( m_staticText8, 0, wxALL, 5 );

	patient_code_input = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	patient_code_input->Enable( false );

	bSizer8->Add( patient_code_input, 0, wxALL, 5 );

	gen_code_button = new wxButton( this, wxID_ANY, wxT("Generate Code"), wxDefaultPosition, wxDefaultSize, 0 );
	gen_code_button->SetDefault();
	bSizer8->Add( gen_code_button, 0, wxALL, 5 );


	main_sizer->Add( bSizer8, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxHORIZONTAL );

	ok_button = new wxButton( this, wxID_ANY, wxT("OK!"), wxDefaultPosition, wxDefaultSize, 0 );
	ok_button->Enable( false );

	bSizer9->Add( ok_button, 0, wxALL, 5 );

	m_button10 = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer9->Add( m_button10, 0, wxALL, 5 );


	main_sizer->Add( bSizer9, 1, wxEXPAND, 5 );


	this->SetSizer( main_sizer );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	gen_code_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewPatientDialog::OnGenerate ), NULL, this );
	ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewPatientDialog::OnOk ), NULL, this );
	m_button10->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewPatientDialog::OnCancel ), NULL, this );

}

NewPatientDialog::~NewPatientDialog(){
	// Disconnect Events
	gen_code_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewPatientDialog::OnGenerate ), NULL, this );
	ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewPatientDialog::OnOk ), NULL, this );
	m_button10->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewPatientDialog::OnCancel ), NULL, this );
}

/******************END CONSTRUCTORS/DESTRUCTORS*************************/

//Event Handlers
void NewPatientDialog::OnGenerate(wxCommandEvent &event){

	string age=age_input->GetValue().ToStdString();
	string year="";
	time_t t=time(NULL);
	struct tm date=*localtime(&t);
	int y=date.tm_year+1900;
	ostringstream str;
	str<<y;
	year=str.str();
	year=year.substr(2,string::npos);
	string c=gen->nextCode(year,age);

	string code=year+age+c;
	wxString wc(code);

	//Pass the code to the proper field
	patient_code_input->SetValue(wc);

	//Enable the OK button
	ok_button->Enable(true);
	//Done!
}

void NewPatientDialog::OnCancel(wxCommandEvent &event){
	this->EndModal(wxCANCEL);
}

void NewPatientDialog::OnOk(wxCommandEvent &event){
	this->EndModal(wxOK);
}

/*******************END EVENT HANDLERS***************************/

//Accessors
Patient *NewPatientDialog::getPatient(void){
	//Collate all the dialog info into a new patient

	//First, we convert all data into STL strings
	string name=pt_name_input->GetValue().ToStdString();
	string age=age_input->GetValue().ToStdString();
	string gender=gender_selection->GetString(gender_selection->GetSelection()).ToStdString();
	string race=race_selector->GetString(race_selector->GetSelection()).ToStdString();
	string orientation=orientation_selector->GetString(orientation_selector->GetSelection()).ToStdString();
	string code=patient_code_input->GetValue().ToStdString();

	//Now we feed them into the patient pointer, converting where necessary
	Patient *ret=new Patient();
	ret->Name()=name;
	ret->Code()=code;
	ret->Age()=atoi(age.c_str());
	//We have to do some conversion for race, gender, and orientation.
	//Let's start with race: { wxT("White"), wxT("Black"), wxT("Hispanic"), wxT("Asian"), wxT("Biracial"), wxT("Other"), wxT("Unknown") };
	//	We'll do this switch-case for efficiency
	switch(race[0]){
		case 'W':
			ret->Race()=peRACE_WHITE;
			break;
		case 'B':
			ret->Race()=((race=="Black")?peRACE_BLACK:peRACE_BIRACIAL);
			break;
		case 'H':
			ret->Race()=peRACE_HISPANIC;
			break;
		case 'A':
			ret->Race()=peRACE_ASIAN;
			break;
		case 'O':
			ret->Race()=peRACE_OTHER;
			break;
		case 'U':
			ret->Race()=peRACE_OTHER;
			break;
	}

	//Next up is gender
	switch(gender[0]){
		case 'M':
			ret->Gender()=peGENDER_MALE;
			break;
		case 'F':
			ret->Gender()=peGENDER_FEMALE;
			break;
		case 'T':
			ret->Gender()=peGENDER_TRANS;
			break;
	}

	//And finally orientation
	switch(orientation[0]){
		case 'H':
			//Either heterosexual or homosexual
			ret->Orientation()=(orientation[1]=='o')?peORIENTATION_GAY:peORIENTATION_STRAIGHT;
			break;
		case 'B':
			ret->Orientation()=peORIENTATION_BI;
			break;
		case 'O':
			ret->Orientation()=peORIENTATION_OTHER;
			break;
		case 'U':
			ret->Orientation()=peORIENTATION_UNKNOWN;
			break;
	}

	//that's it!
	return ret;

}
