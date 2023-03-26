#ifndef PEDIT_H
#define PEDIT_H

#include <cstdlib>

#include <wx/wx.h>

#include "patient.h"
#include "peutility.h"

///////////////////////////////////////////////////////////////////////////////
/// Class EditPatientDialog
///////////////////////////////////////////////////////////////////////////////
class EditPatientDialog : public wxDialog {
private:
	wxStaticText* m_staticText12;
	wxStaticText* m_staticText14;
	wxTextCtrl* code_entry;
	wxStaticText* m_staticText15;
	wxTextCtrl* name_entry;
	wxStaticText* m_staticText16;
	wxChoice* gender_selection;
	wxStaticText* m_staticText17;
	wxChoice* race_selector;
	wxStaticText* m_staticText18;
	wxChoice* orientation_selector;
	wxButton* save_button;
	wxButton* cancel_button;
	wxStaticText* m_staticText181;
	wxTextCtrl* age_entry;

	// Virtual event handlers, override them in your derived class
	virtual void OnSaveButton( wxCommandEvent& event );
	virtual void OnCancel( wxCommandEvent& event );

public:
	EditPatientDialog( wxWindow* parent, Patient *p,wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_DIALOG_STYLE );
	~EditPatientDialog();

	//Accessors
	string NewCode(void){return code_entry->GetValue().ToStdString();}
	string NewName(void){return name_entry->GetValue().ToStdString();}
	char NewGender(void);
	char NewRace(void);
	char NewOrientation(void);
	int NewAge(void){return atoi(age_entry->GetValue().ToStdString().c_str());}

};

#endif // PEDIT_H
