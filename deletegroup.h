//Dialog to delete a group

#ifndef __PATIENTENCODER_DELETEGROUP_H__
#define __PATIENTENCODER_DELETEGROUP_H__

//System includes
#include <string>
#include <vector>

//wx includes
#include <wx/wx.h>

//local includes
#include "group.h"

using namespace std;

class DeleteGroupDialog : public wxDialog {
private:

	wxStaticText* m_staticText10;
	wxChoice* group_selector;
	wxButton* ok_button;
	wxButton* cancel_button;

	vector <PatientGroup> groups;
	string selected;

	//Event Handlers
	void OnOK( wxCommandEvent& event );
	void OnCancel( wxCommandEvent& event );

public:

	//Constructors / Destructor
	DeleteGroupDialog( wxWindow* parent, vector <PatientGroup> g,wxWindowID id = wxID_ANY, const wxString& title = wxT("Delete Group"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,150 ), long style = wxDEFAULT_DIALOG_STYLE );
	~DeleteGroupDialog();

	//Accessors
	string get_selected(void);

};

#endif // __PATIENTENCODER_DELETEGROUP_H__
