//Dialog for creating a new patient record

#ifndef __PATIENT_ENCODER_NEW_PT_DIALOG__
#define __PATIENT_ENCODER_NEW_PT_DIALOG__

//System/STL includes
#include <cstdlib>
#include <ctime>
#include <sstream>

//wx includes
#include <wx/wx.h>

//local includes
#include "patient.h"
#include "suffix.h"

using namespace std;

class NewPatientDialog : public wxDialog{
private:

	wxStaticText* m_staticText3;
	wxTextCtrl* pt_name_input;
	wxStaticText* m_staticText4;
	wxTextCtrl* age_input;
	wxStaticText* m_staticText5;
	wxChoice* gender_selection;
	wxStaticText* m_staticText6;
	wxChoice* race_selector;
	wxStaticText* m_staticText7;
	wxChoice* orientation_selector;
	wxStaticText* m_staticText8;
	wxTextCtrl* patient_code_input;
	wxButton* gen_code_button;
	wxButton* ok_button;
	wxButton* m_button10;

	//Generator
	SuffixGenerator *gen;

	//Event Handlers
	void OnGenerate( wxCommandEvent& event );
	void OnOk( wxCommandEvent& event );
	void OnCancel( wxCommandEvent& event );

public:

	//Constructor/destructors
	NewPatientDialog( wxWindow* parent,SuffixGenerator *s,wxWindowID id = wxID_ANY, const wxString& title = wxT("New Patient"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500,500), long style = wxDEFAULT_DIALOG_STYLE );
	~NewPatientDialog();

	//Accessors
	Patient *getPatient(void);

};

#endif // __PATIENT_ENCODER_NEW_PT_DIALOG__
