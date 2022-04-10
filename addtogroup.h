#ifndef __PATIENT_ENCODER_ADDTOGROUPDIALOG_H__
#define __PATIENT_ENCODER_ADDTOGROUPDIALOG_H__

//STL includes
#include <string>
#include <vector>

//wx includes
#include <wx/wx.h>

//local includes
#include "group.h"

using namespace std;

class AddToGroupDialog : public wxDialog{
private:
    wxChoice* group_choice;
    wxButton* ok_button;
    wxButton* cancel_button;
	vector <string> group_names;

	vector <string> parse_groups(vector<PatientGroup>);

public:
    AddToGroupDialog(wxWindow* parent, vector <PatientGroup> groups,wxWindowID id = wxID_ANY, const wxString& title = _("Add Patient to Group"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(400,150), long style = wxDEFAULT_DIALOG_STYLE);
    virtual ~AddToGroupDialog();

	//Event handlers
	void OnOK(wxCommandEvent& event);
    void OnCancel(wxCommandEvent& event);

	//Accessors
	string selected_group(void);
};

#endif // __PATIENT_ENCODER_ADDTOGROUPDIALOG_H__
