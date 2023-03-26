#include "pedit.h"

///////////////////////////////////////////////////////////////////////////

EditPatientDialog::EditPatientDialog( wxWindow* parent, Patient *p, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer21 = new wxBoxSizer( wxVERTICAL );

	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("Modify Patient Data"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer21->Add( m_staticText12, 0, wxALL, 5 );

	wxBoxSizer* bSizer22 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText14 = new wxStaticText( this, wxID_ANY, wxT("Code:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	bSizer22->Add( m_staticText14, 0, wxALL, 5 );

	code_entry = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer22->Add( code_entry, 0, wxALL, 5 );
	code_entry->SetValue(make_wx_string(p->Code()));

	bSizer21->Add( bSizer22, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer23 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText15 = new wxStaticText( this, wxID_ANY, wxT("Patient Name: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	bSizer23->Add( m_staticText15, 0, wxALL, 5 );

	name_entry = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	name_entry->SetValue(make_wx_string(p->Name()));
	bSizer23->Add( name_entry, 0, wxALL, 5 );

	bSizer21->Add( bSizer23, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer28 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText181 = new wxStaticText( this, wxID_ANY, wxT("Age: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText181->Wrap( -1 );
	bSizer28->Add( m_staticText181, 0, wxALL, 5 );

	age_entry = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	age_entry->SetValue(make_wx_string(p->Age()));
	bSizer28->Add( age_entry, 0, wxALL, 5 );


	bSizer21->Add( bSizer28, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer24 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText16 = new wxStaticText( this, wxID_ANY, wxT("Gender"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	bSizer24->Add( m_staticText16, 0, wxALL, 5 );

	wxString gender_selectionChoices[] = { wxT("Male"), wxT("Female"), wxT("Trans") };
	int gender_selectionNChoices = 3;
	int current=0;
	switch(p->Gender()){
		case peGENDER_FEMALE:
			current=1;
			break;
		case peGENDER_TRANS:
			current=2;
			break;
		default:
			current=0;
			break;
	}
	gender_selection = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, gender_selectionNChoices, gender_selectionChoices, 0 );
	gender_selection->SetSelection( current );
	bSizer24->Add( gender_selection, 0, wxALL, 5 );

	bSizer21->Add( bSizer24, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer25 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText17 = new wxStaticText( this, wxID_ANY, wxT("Patient Race"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	bSizer25->Add( m_staticText17, 0, wxALL, 5 );

	wxString race_selectorChoices[] = { wxT("White"), wxT("Black"), wxT("Hispanic"), wxT("Asian"), wxT("Biracial"), wxT("Other"), wxT("Unknown") };
	int race_selectorNChoices = 7;
	switch(p->Race()){
		case peRACE_BLACK:
			current=1;
			break;
		case peRACE_HISPANIC:
			current=2;
			break;
		case peRACE_ASIAN:
			current=3;
			break;
		case peRACE_BIRACIAL:
			current=4;
			break;
		case peRACE_OTHER:
			current=5;
			break;
		default:
			current=0;
			break;
	}
	race_selector = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, race_selectorNChoices, race_selectorChoices, 0 );
	race_selector->SetSelection( current );
	bSizer25->Add( race_selector, 0, wxALL, 5 );

	bSizer21->Add( bSizer25, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer26 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText18 = new wxStaticText( this, wxID_ANY, wxT("Sexual Orientation"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	bSizer26->Add( m_staticText18, 0, wxALL, 5 );

	wxString orientation_selectorChoices[] = { wxT("Heterosexual"), wxT("Homosexual"), wxT("Bisexual"), wxT("Other"), wxT("Unknown") };
	int orientation_selectorNChoices = 5;
	switch(p->Orientation()){
		case peORIENTATION_GAY:
			current=1;
			break;
		case peORIENTATION_BI:
			current=2;
			break;
		case peORIENTATION_OTHER:
			current=3;
			break;
		case peORIENTATION_UNKNOWN:
			current=4;
			break;
		default:
			current=0;
			break;
	}
	orientation_selector = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, orientation_selectorNChoices, orientation_selectorChoices, 0 );
	orientation_selector->SetSelection( current );
	bSizer26->Add( orientation_selector, 0, wxALL, 5 );

	bSizer21->Add( bSizer26, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer27 = new wxBoxSizer( wxHORIZONTAL );

	save_button = new wxButton( this, wxID_ANY, wxT("Save Changes"), wxDefaultPosition, wxDefaultSize, 0 );

	save_button->SetDefault();
	bSizer27->Add( save_button, 0, wxALL, 5 );

	cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer27->Add( cancel_button, 0, wxALL, 5 );

	bSizer21->Add( bSizer27, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer21 );
	this->Layout();
	bSizer21->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	save_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPatientDialog::OnSaveButton ), NULL, this );
	cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPatientDialog::OnCancel ), NULL, this );
}

EditPatientDialog::~EditPatientDialog(){
	// Disconnect Events
	save_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPatientDialog::OnSaveButton ), NULL, this );
	cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditPatientDialog::OnCancel ), NULL, this );

}

//Event handlers
void EditPatientDialog::OnSaveButton(wxCommandEvent &event){
	this->EndModal(wxOK);
}

void EditPatientDialog::OnCancel(wxCommandEvent &event){
	this->EndModal(wxCANCEL);
}

//Accessors
char EditPatientDialog::NewGender(void){
	switch(gender_selection->GetSelection()){
		case 0:
			return peGENDER_MALE;
			break;
		case 1:
			return peGENDER_FEMALE;
			break;
		case 2:
			return peGENDER_TRANS;
			break;
		default:
			return peGENDER_DEFAULT;
			break;
	}
	return peGENDER_DEFAULT;
}

char EditPatientDialog::NewRace(void){
	switch(race_selector->GetSelection()){
		case 0:
			return peRACE_WHITE;
			break;
		case 1:
			return peRACE_BLACK;
			break;
		case 2:
			return peRACE_HISPANIC;
			break;
		case 3:
			return peRACE_ASIAN;
			break;
		case 4:
			return peRACE_BIRACIAL;
			break;
		case 5:
			return peRACE_OTHER;
			break;
		default:
			return peRACE_DEFAULT;
			break;
	}
	return peRACE_DEFAULT;
}

char EditPatientDialog::NewOrientation(void){
	switch(orientation_selector->GetSelection()){
		case 0:
			return peORIENTATION_STRAIGHT;
			break;
		case 1:
			return peORIENTATION_GAY;
			break;
		case 2:
			return peORIENTATION_BI;
			break;
		case 3:
			return peORIENTATION_OTHER;
			break;
		case 4:
			return peORIENTATION_UNKNOWN;
			break;
		default:
			return peORIENTATION_DEFAULT;
			break;
	}
	return peORIENTATION_DEFAULT;
}
