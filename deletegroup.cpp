#include "deletegroup.h"

using namespace std;

//Constructors / Destructors
DeleteGroupDialog::DeleteGroupDialog( wxWindow* parent, vector<PatientGroup> g,wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, wxDefaultSize, style ){
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText10 = new wxStaticText( this, wxID_ANY, wxT("Select Group to Delete:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	bSizer16->Add( m_staticText10, 0, wxALL, 5 );

	//Create the string array so that we can create the group selector
	groups=g;
	cout<<"Received "<<g.size()<<" group codes from MainWindow and stored "<<groups.size()<<" codes in groups"<<endl;
	cout<<"groups[0]="<<groups[0].Code()<<endl;
	wxArrayString group_selectorChoices;
	for(vector<PatientGroup>::iterator it=groups.begin();it!=groups.end();++it){
		wxString temp((*it).Code());
		cout<<(*it).Code()<<endl;
		group_selectorChoices.Add(temp);
	}

	group_selector = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, group_selectorChoices, 0 );
	group_selector->SetSelection( 0 );
	bSizer16->Add( group_selector, 0, wxALL, 5 );


	bSizer15->Add( bSizer16, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	ok_button = new wxButton( this, wxID_ANY, wxT("OK!"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( ok_button, 0, wxALL, 5 );

	cancel_button = new wxButton( this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( cancel_button, 0, wxALL, 5 );


	bSizer15->Add( bSizer17, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer15 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	ok_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteGroupDialog::OnOK ), NULL, this );
	cancel_button->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteGroupDialog::OnCancel ), NULL, this );

}

DeleteGroupDialog::~DeleteGroupDialog(){
	// Disconnect Events
	ok_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteGroupDialog::OnOK ), NULL, this );
	cancel_button->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DeleteGroupDialog::OnCancel ), NULL, this );

}
/*****************************END CONSTRUCTORS / DESTRUCTOR********************************/

//Accessors
string DeleteGroupDialog::get_selected(void){
	return selected;
}
/*********************END ACCESSORS*****************/

//Event Handlers
void DeleteGroupDialog::OnOK(wxCommandEvent &event){
	selected=group_selector->GetString(group_selector->GetSelection()).ToStdString();
	this->EndModal(wxID_OK);
}

void DeleteGroupDialog::OnCancel(wxCommandEvent &event){
	this->EndModal(wxID_CANCEL);
}
/******************END EVENT HANDLERS****************/
