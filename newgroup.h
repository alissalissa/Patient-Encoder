//Declares a wxDialog for creating new patient groups
//	Really, this dialog just passes a name string back to MainWindow

#ifndef __PATIENT_ENCODER_NEWGROUP_H__
#define __PATIENT_ENCODER_NEWGROUP_H__

#include <wx/wx.h>
#include <string>

using namespace std;

class NewGroupDialog : public wxDialog {
private:

	wxStaticText* m_staticText9;
	wxTextCtrl* name_entry;
	wxButton* ok_button;
	wxButton* cancel_button;

	string name;

	//Event handlers
	void OnOK( wxCommandEvent& event );
	void OnCancel( wxCommandEvent& event );

public:

	//Constructor / destructor
	NewGroupDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("New Group"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 300,200 ), long style = wxDEFAULT_DIALOG_STYLE );
	~NewGroupDialog();

	//Accessors
	string get_name(void);

};

#endif // __PATIENT_ENCODER_NEWGROUP_H__
