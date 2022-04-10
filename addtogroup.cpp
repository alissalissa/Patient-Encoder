//Implementation file for AddPatientToGroupDialog

#include "addtogroup.h"

using namespace std;

//Private utilities
vector <string> AddToGroupDialog::parse_groups(vector <PatientGroup> groups){
	vector <string> ret;
	for(vector<PatientGroup>::iterator it=groups.begin();it!=groups.end();++it)
		ret.push_back((*it).Code());

	return ret;
}


//Constructors/destructors

AddToGroupDialog::AddToGroupDialog(wxWindow* parent, vector <PatientGroup> groups,wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style)
    : wxDialog(parent, id, title, pos, size, style){

    wxBoxSizer* bSizer10 = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(bSizer10);

	//parse out the groups
	group_names=parse_groups(groups);

	//Add to menu
    wxArrayString m_choice4Arr;
    m_choice4Arr.Add(wxT("Select Group"));
	for(vector<string>::iterator it=group_names.begin();it!=group_names.end();++it){
		wxString b((*it));
		m_choice4Arr.Add(b);
	}
    group_choice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDLG_UNIT(this, wxSize(350,-1)), m_choice4Arr, 0);
    group_choice->SetSelection(0);

    bSizer10->Add(group_choice, 0, wxALL);

    wxBoxSizer* bSizer11 = new wxBoxSizer(wxHORIZONTAL);

    bSizer10->Add(bSizer11, 1, wxEXPAND);

    ok_button = new wxButton(this, wxID_ANY, _("Add"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    bSizer11->Add(ok_button, 0, wxALL);

    cancel_button = new wxButton(this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDLG_UNIT(this, wxSize(-1, -1)), 0);

    bSizer11->Add(cancel_button, 0, wxALL);

    SetName(wxT("AddToGroupDialog"));
    SetSize(400,150);
    // Connect events
    ok_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddToGroupDialog::OnOK), NULL, this);
    cancel_button->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddToGroupDialog::OnCancel), NULL, this);

}

AddToGroupDialog::~AddToGroupDialog()
{
    ok_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddToGroupDialog::OnOK), NULL, this);
    cancel_button->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AddToGroupDialog::OnCancel), NULL, this);

}

/*******************END CONSTRUCTORS***********************/

//Event handlers

void AddToGroupDialog::OnOK(wxCommandEvent &event){
	this->EndModal(wxID_OK);
}

void AddToGroupDialog::OnCancel(wxCommandEvent &event){
	this->EndModal(wxID_CANCEL);
}

/*******************END EVENT HANDLERS**********************/

//Accessors

string AddToGroupDialog::selected_group(void){
	return group_choice->GetString(group_choice->GetSelection()).ToStdString();
}
