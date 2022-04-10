#ifndef __PATIENTENCODER_MAIN_WINDOW_H__
#define __PATIENTENCODER_MAIN_WINDOW_H__

//wx
#include <wx/wx.h>
#include <wx/listctrl.h>

//System/STL
#include <algorithm>
#include <string>

//local includes
#include "addtogroup.h"
#include "deletegroup.h"
#include "newgroup.h"
#include "newptdialog.h"
#include "plist.h"
#include "suffix.h"

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

	//The code generator
	SuffixGenerator *suffix;

	//The patient and group data
	PList *patients;

	//The currently selected patient
	int selected;

	//List Management
	void update(Patient*);
	void updateView(void);

	//Event Handlers
	void OnCloseWindow( wxCloseEvent&);
	void SavePatientFile( wxCommandEvent& event );
	void LoadPatientFile(wxCommandEvent & event);
	void OnMenuNew(wxCommandEvent & event);
	void OnCloseWindowMenu( wxCommandEvent& event );
	void OnSelection( wxListEvent& event ); //When a patient is selected
    void OnGroupSelection (wxCommandEvent& event);
	void OnNewPatient( wxCommandEvent& event );
	void OnNewGroup(wxCommandEvent&);
	void OnDeleteGroup(wxCommandEvent&);
	void OnAddToGroup(wxCommandEvent&);
	void OnRemoveFromGroup(wxCommandEvent&);
	//The patient list control is deselected
	void OnListDeselect(wxListEvent&);

public:

	//Constructor/destructor
	MainWindow( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Patient Encoder"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 1000,800 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );
	~MainWindow();

};

#endif // __PATIENTENCODER_MAIN_WINDOW_H__
