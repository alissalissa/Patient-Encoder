//Dialog to delete a patient

#ifndef __PE_DELETE_PT_H__
#define __PE_DELETE_PT_H__

//STL include
#include <algorithm>
#include <string>
#include <vector>

//wx includes
#include <wx/wx.h>

using namespace std;

class DeletePatientDialog : public wxDialog {
private:

	wxStaticText* m_staticText12;
	wxComboBox* code_selector;
	wxButton* ok_button;
	wxButton* cancel_button;

	string selected_code;

public:

	DeletePatientDialog( wxWindow* parent,vector<string> codes, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE );
	~DeletePatientDialog();

	void OnOK(wxCommandEvent&);
	void OnCancel( wxCommandEvent&);

	//Returns the selected code on a modal of OK
	string getSelected(void){return selected_code;}

};

#endif // __PE_DELETE_PT_H__
