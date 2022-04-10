#include "newgroup.h"

using namespace std;

//Constructor / Destructor
NewGroupDialog::NewGroupDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style ){
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText9 = new wxStaticText( this, wxID_ANY, wxT("Enter New Group Name:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer13->Add( m_staticText9, 0, wxALL, 5 );

	name_entry = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	bSizer13->Add( name_entry, 0, wxALL, 5 );


	bSizer12->Add( bSizer13, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxHORIZONTAL );

	ok_button = new wxButton( this, wxID_ANY, wxT("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( ok_button, 0, wxALL, 5 );

	cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer14->Add( cancel_button, 0, wxALL, 5 );


	bSizer12->Add( bSizer14, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer12 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewGroupDialog::OnOK ), NULL, this );
	cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewGroupDialog::OnCancel ), NULL, this );

	name="";
}

NewGroupDialog::~NewGroupDialog(){
	// Disconnect Events
	ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewGroupDialog::OnOK ), NULL, this );
	cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( NewGroupDialog::OnCancel ), NULL, this );
}

/*********************END CONSTRUCTOR/DESTRUCTOR************************/

//Event Handlers
void NewGroupDialog::OnCancel(wxCommandEvent &evt){
	//Nothing to do but end it
	this->EndModal(wxID_CANCEL);
}

void NewGroupDialog::OnOK(wxCommandEvent &evt){
	//First we get the name
	name=name_entry->GetValue().ToStdString();
	this->EndModal(wxID_OK);
}
/*******************END EVENT HANDLERS***********************/

//Accessors
string NewGroupDialog::get_name(void){
	return name;
}
/*******************END ACCESSORS*********************/
