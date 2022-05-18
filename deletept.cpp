//Implementation of the dialog to delete a patient

#include "deletept.h"

using namespace std;

//Constructor/Destructor
DeletePatientDialog::DeletePatientDialog( wxWindow* parent, vector<string> codes,wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText12 = new wxStaticText( this, wxID_ANY, wxT("Which patient would you like to delete?"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	bSizer19->Add( m_staticText12, 0, wxALL, 5 );

	code_selector = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, 0 );
	for_each(codes.begin(),codes.end(),[&](string ssc){
		wxString *t=new wxString(ssc);
		code_selector->Append(*t);
		delete t;
	});
	code_selector->SetSelection(0);
	bSizer19->Add( code_selector, 0, wxALL, 5 );


	bSizer18->Add( bSizer19, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxHORIZONTAL );

	ok_button = new wxButton( this, wxID_ANY, wxT("Ok!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( ok_button, 0, wxALL, 5 );

	cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer20->Add( cancel_button, 0, wxALL, 5 );


	bSizer18->Add( bSizer20, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer18 );
	this->Layout();
	bSizer18->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeletePatientDialog::OnOK ), NULL, this );
	cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeletePatientDialog::OnCancel ), NULL, this );

	selected_code="";

}

DeletePatientDialog::~DeletePatientDialog(){
	// Disconnect Events
	ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeletePatientDialog::OnOK ), NULL, this );
	cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeletePatientDialog::OnCancel ), NULL, this );
}

//Event Handlers
void DeletePatientDialog::OnOK(wxCommandEvent &evt){
	selected_code=code_selector->GetStringSelection().ToStdString();
	this->EndModal(wxOK);
}

void DeletePatientDialog::OnCancel(wxCommandEvent &evt){
	selected_code="-1";
	this->EndModal(wxCANCEL);
}
