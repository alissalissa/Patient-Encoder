#ifndef __PATIENTENCODER_MAIN_WINDOW_H__
#define __PATIENTENCODER_MAIN_WINDOW_H__

//wx
#include <wx/wx.h>
#include <wx/listctrl.h>

//System/STL
#include <algorithm>
#include <cstdlib>
#include <ctype.h>
#include <filesystem>
#include <fstream>
#include <iostream> //for debug code
#include <string>

//local includes
#include "addtogroup.h"
#include "deletegroup.h"
#include "deletept.h"
#include "newgroup.h"
#include "newptdialog.h"
#include "peutility.h"
#include "plist.h"
#include "suffix.h"
#include "ses.h"

using namespace std;

class MainWindow : public wxFrame {
private:

	wxMenuBar* main_menu_bar;
	wxMenu* file_menu;
	wxStaticText* m_staticText3;
	wxComboBox* group_selector_box;
	wxButton* new_group_btn;
	wxButton* new_pt_btn;
	wxButton* delete_pt_btn;
	wxButton* delete_group_btn;
	wxButton* add_pt_grp_btn;
	wxButton* remove_pt_grp_btn;
	wxStaticText* view_label;
	wxListView* patient_view;
	wxTextCtrl *search_box;

	//The code generator
	SuffixGenerator *suffix;

	//The patient and group data
	PList *patients;

	//The currently selected patient
	int selected;

	//The last accessed file path
	string last_path;

	//List Management
	void update(Patient*);
	void updateView(void);

	//Saves a path to the config file ~/.local/share/PatientEncoder/pe.conf
	bool savelp(string);
	bool fetchlp(void);

	//Event Handlers
	void OnCloseWindow( wxCloseEvent&);
	void SavePatientFile( wxCommandEvent& event );
	void LoadPatientFile(wxCommandEvent & event);
	void OnMenuNew(wxCommandEvent & event);
	void OnTest(wxCommandEvent & event);
	void OnCloseWindowMenu( wxCommandEvent& event );
	void OnSelection( wxListEvent& event ); //When a patient is selected
    void OnGroupSelection (wxCommandEvent& event);
	void OnNewPatient( wxCommandEvent& event );
	void OnNewGroup(wxCommandEvent&);
	void OnDeleteGroup(wxCommandEvent&);
	void OnAddToGroup(wxCommandEvent&);
	void OnRemoveFromGroup(wxCommandEvent&);
	void OnDeletePatient(wxCommandEvent&);
	//The patient list control is deselected
	void OnListDeselect(wxListEvent&);
	void OnSearchTextChange(wxCommandEvent&);

	vector <Patient*> currently_displayed_patients(void);

public:

	//Constructor/destructor
	MainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Patient Encoder"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,800 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	~MainWindow();

};

#endif // __PATIENTENCODER_MAIN_WINDOW_H__
