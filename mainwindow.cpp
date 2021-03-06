#include "mainwindow.h"

using namespace std;

//Constructors/Destructors
MainWindow::MainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style ){

	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	main_menu_bar = new wxMenuBar( 0 );
	file_menu = new wxMenu();

	wxMenuItem* menu_new;
	menu_new = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("New") ) + wxT('\t') + wxT("CTRL+N"), wxT("Create a new patient file"), wxITEM_NORMAL );
	file_menu->Append( menu_new );

	wxMenuItem* menu_load;
	menu_load = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Load") ) + wxT('\t') + wxT("CTRL+O"), wxT("Load a patient file"), wxITEM_NORMAL );
	file_menu->Append( menu_load );

	wxMenuItem* menu_save;
	menu_save = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Save") ) + wxT('\t') + wxT("CTRL+S"), wxT("Save the current patient file"), wxITEM_NORMAL );
	file_menu->Append( menu_save );

	wxMenuItem* quit_menu;
	quit_menu = new wxMenuItem( file_menu, wxID_ANY, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	file_menu->Append( quit_menu );

	main_menu_bar->Append( file_menu, wxT("File") );

	this->SetMenuBar( main_menu_bar );

	wxBoxSizer* main_sizer;
	main_sizer = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* select_sizer;
	select_sizer = new wxBoxSizer( wxHORIZONTAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, wxT("What Patient set would you like to view?"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	m_staticText3->Wrap( -1 );
	select_sizer->Add( m_staticText3, 0, wxALL, 5 );

	group_selector_box = new wxComboBox( this, wxID_ANY, wxT("Combo!"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_DROPDOWN|wxCB_READONLY|wxRAISED_BORDER|wxTAB_TRAVERSAL );
	group_selector_box->Append( wxT("All Patients") );
	group_selector_box->SetSelection( 0 );
	select_sizer->Add( group_selector_box, 0, wxALL, 5 );

	new_group_btn = new wxButton( this, wxID_ANY, wxT("New Group"), wxDefaultPosition, wxDefaultSize, 0 );
	select_sizer->Add( new_group_btn, 0, wxALL, 5 );

	new_pt_btn = new wxButton( this, wxID_ANY, wxT("New Patient"), wxDefaultPosition, wxDefaultSize, 0 );
	select_sizer->Add( new_pt_btn, 0, wxALL, 5 );

	delete_pt_btn = new wxButton( this, wxID_ANY, wxT("Delete Patient"), wxDefaultPosition, wxDefaultSize, 0 );
	select_sizer->Add( delete_pt_btn, 0, wxALL, 5 );

	delete_group_btn = new wxButton( this, wxID_ANY, wxT("Delete Group"), wxDefaultPosition, wxDefaultSize, 0 );
	select_sizer->Add( delete_group_btn, 0, wxALL, 5 );


	main_sizer->Add( select_sizer, 1, wxEXPAND, 5 );

	wxBoxSizer* add_remove_btn_sizer;
	add_remove_btn_sizer = new wxBoxSizer( wxHORIZONTAL );

	add_pt_grp_btn = new wxButton( this, wxID_ANY, wxT("Add Patient to Group"), wxDefaultPosition, wxDefaultSize, 0 );
	add_pt_grp_btn->Enable(false);
	add_remove_btn_sizer->Add( add_pt_grp_btn, 0, wxALL, 5 );

	remove_pt_grp_btn = new wxButton( this, wxID_ANY, wxT("Remove Patient from Group"), wxDefaultPosition, wxDefaultSize, 0 );
	remove_pt_grp_btn->Enable(false);
	add_remove_btn_sizer->Add( remove_pt_grp_btn, 0, wxALL, 5 );


	main_sizer->Add( add_remove_btn_sizer, 1, wxEXPAND, 5 );

	view_label = new wxStaticText( this, wxID_ANY, wxT("Currently Viewing: All Patients"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	view_label->Wrap( -1 );
	main_sizer->Add( view_label, 0, wxALL, 5 );

	patient_view = new wxListView( this, wxID_ANY, wxDefaultPosition, wxSize( 999,600 ), wxLC_HRULES|wxLC_REPORT|wxLC_VRULES );
	main_sizer->Add( patient_view, 0, wxALL, 5 );

	patient_view->AppendColumn(wxT("Code"));
	patient_view->AppendColumn(wxT("Name"));
	patient_view->AppendColumn(wxT("Gender"));
	patient_view->AppendColumn(wxT("Race"));
	patient_view->AppendColumn(wxT("Orientation"));


	this->SetSizer( main_sizer );
	this->Layout();

	this->Centre( wxBOTH );

	//Suffix generator
	suffix=new SuffixGenerator();
	//suffix->test();

	//Patient list
	patients=new PList(suffix);

	selected=-1;

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWindow::OnCloseWindow ) );
	this->Connect(menu_new->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler(MainWindow::OnMenuNew), NULL, this);
	this->Connect( menu_save->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::SavePatientFile ) );
	this->Connect(menu_load->GetId(),wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::LoadPatientFile));
	this->Connect( quit_menu->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::OnCloseWindowMenu ) );
	group_selector_box->Connect(wxEVT_COMBOBOX, wxCommandEventHandler( MainWindow::OnGroupSelection ), NULL, this );
	new_pt_btn->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::OnNewPatient ), NULL, this );
	new_group_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnNewGroup),NULL,this);
	delete_group_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnDeleteGroup),NULL,this);
	patient_view->Connect(wxEVT_LIST_ITEM_SELECTED,wxListEventHandler(MainWindow::OnSelection),NULL,this);
	patient_view->Connect(wxEVT_LIST_ITEM_DESELECTED,wxListEventHandler(MainWindow::OnListDeselect),NULL,this);
	add_pt_grp_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnAddToGroup),NULL,this);
	remove_pt_grp_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnRemoveFromGroup),NULL,this);
	delete_pt_btn->Connect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnDeletePatient),NULL,this);

}

MainWindow::~MainWindow(){

	delete patients;
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainWindow::OnCloseWindow ) );
	this->Disconnect(wxID_ANY,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::OnMenuNew));
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::SavePatientFile ) );
	this->Disconnect(wxID_ANY,wxEVT_COMMAND_MENU_SELECTED,wxCommandEventHandler(MainWindow::LoadPatientFile));
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::OnCloseWindowMenu ) );
	group_selector_box->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( MainWindow::OnGroupSelection ), NULL, this );
	new_pt_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::OnNewPatient ), NULL, this );
	new_group_btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnNewGroup),NULL,this);
	delete_group_btn->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainWindow::OnDeleteGroup ), NULL, this );
	patient_view->Disconnect( wxEVT_LIST_ITEM_SELECTED, wxListEventHandler( MainWindow::OnSelection ), NULL, this );
	patient_view->Disconnect(wxEVT_LIST_ITEM_DESELECTED,wxListEventHandler(MainWindow::OnListDeselect),NULL,this);
	add_pt_grp_btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnAddToGroup),NULL,this);
	remove_pt_grp_btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnRemoveFromGroup),NULL,this);
	delete_pt_btn->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED,wxCommandEventHandler(MainWindow::OnDeletePatient),NULL,this);

}

/******************END CONSTRUCTORS/DESTRUCTORS*****************/

//Patient Management

void MainWindow::update(Patient *p){
	//Add the patient to the internal list
	//	The suffix generator is updated within the AddPatient method
	patients->AddPatient(p);

	//Update the view
	int ni=patient_view->GetItemCount();
	//Code - name - gender - race - orientation
	wxString code(p->Code());
	patient_view->InsertItem(ni,code);
	wxString name(p->Name());
	patient_view->SetItem(ni,1,name);
	wxString gender(p->Gender());
	patient_view->SetItem(ni,2,gender);
	wxString race(p->Race());
	patient_view->SetItem(ni,3,race);
	wxString orientation(p->Orientation());
	patient_view->SetItem(ni,4,orientation);

	patient_view->Update();
	this->Update();

}

void MainWindow::updateView(void){

	//Clear out the display
    patient_view->ClearAll();
    //Re-draw columns
    patient_view->AppendColumn(wxT("Code"));
    patient_view->AppendColumn(wxT("Name"));
    patient_view->AppendColumn(wxT("Gender"));
    patient_view->AppendColumn(wxT("Race"));
    patient_view->AppendColumn(wxT("Orientation"));

    //Set aside some memory for all the patients we need to update the view with
    vector<Patient*> ptu;
    if(group_selector_box->GetSelection()==0){
        //This is all patients
        ptu=patients->Patients();
    }else{
        //Get the current group code
        string gc=group_selector_box->GetStringSelection().ToStdString();
        //Debug code
        //int s=(int)(patients->Group(gc).Patients().size());
        //End debug code

		//Do we have patients to load in this group yet?
		if(patients->Group(gc).Patients().size()>0){
			//cout<<patients->Group(gc).Patients().size()<<endl;
			for(int i=0;i<(int)(patients->Group(gc).Patients().size());i++){
				ptu.push_back(patients->Group(gc).Patients()[i]);
				//Debug code
				//cout<<(*it)->Code()<<"\t\t"<<(*it)->Name()<<"\t\t"<<(*it)->Age()<<"\t\t"<<(*it)->Gender()<<endl;
			}
		}
    }

    //Update from the ptu
    if(ptu.size()>0){
		int item_index=0;
		for(vector<Patient*>::iterator it=ptu.begin();it!=ptu.end();++it){
			//Code - name - gender - race - orientation
			wxString code((*it)->Code());
			patient_view->InsertItem(item_index,code);
			wxString name((*it)->Name());
			patient_view->SetItem(item_index,1,name);
			wxString gender((*it)->Gender());
			patient_view->SetItem(item_index,2,gender);
			wxString race((*it)->Race());
			patient_view->SetItem(item_index,3,race);
			wxString orientation((*it)->Orientation());
			patient_view->SetItem(item_index,4,orientation);
			item_index++;
		}
    }
    //update the view
    this->Update();

	//Recreate the group menu
	int selected_group_buffer=group_selector_box->GetSelection();
	wxString selected_group_key_buffer=group_selector_box->GetString(selected_group_buffer);
	//Clear out the control
	group_selector_box->Clear();
	//Add in the default
	group_selector_box->Append(wxT("All Patients"));
	//tracker for the selected group
	size_t new_selected=0;
	//Sort all the groups
	vector <string> group_codes_sorted;
	for(size_t i=0;i<patients->Groups().size();i++)
		group_codes_sorted.push_back(patients->Groups()[i].Code());
	sort(group_codes_sorted.begin(),group_codes_sorted.end());
	for_each(group_codes_sorted.begin(),group_codes_sorted.end(),[&](string gcs){
		wxString sbuf(gcs);
		group_selector_box->Append(sbuf);
	});
	//Re-find the index of the selected
	for(size_t i=0;i<group_codes_sorted.size();i++){
		if(group_codes_sorted[i]==selected_group_key_buffer.ToStdString()) new_selected=i+1; //The +1 is because index 0 is always All Patients
	}
	group_selector_box->SetSelection((int)new_selected);

	//Re-disable to add and remove from group buttons since we no longer have a selection
	selected=-1;
	add_pt_grp_btn->Enable(false);
	remove_pt_grp_btn->Enable(false);

}

/**************************END PATIENT MANAGEMENT************************/

//Event Handlers
void MainWindow::OnCloseWindow(wxCloseEvent &event){
	wxExit();
}

void MainWindow::OnCloseWindowMenu(wxCommandEvent &event){
	wxExit();
}

void MainWindow::OnMenuNew(wxCommandEvent & event){
	//Clear out the model
	patients->Clear();
	//re-grab the suffix generator
	suffix=patients->AccessSuffixGenerator();
	//update the view
	updateView();
}

void MainWindow::OnSelection(wxListEvent &event){
	add_pt_grp_btn->Enable(true);
	remove_pt_grp_btn->Enable(true);

	//Set the selected patient number
	selected=(int)event.GetIndex();
	//Test code
	//cout<<"Selected patient #"<<selected<<endl;

}

void MainWindow::OnGroupSelection(wxCommandEvent &event){
	//Update the current view
	this->updateView();
}

void MainWindow::OnNewPatient(wxCommandEvent &event){
	NewPatientDialog *diag=new NewPatientDialog(this,suffix);
	int outcome=diag->ShowModal();
	if(outcome==wxOK){
		Patient *pt=diag->getPatient();
		//add the patient to the list
		update(pt);
	}
	//Scrap the dialog memory
	delete diag;
}

void MainWindow::OnNewGroup(wxCommandEvent& event){
	NewGroupDialog *diag=new NewGroupDialog(this);
	int outcome=diag->ShowModal();
	if(outcome==wxID_OK){
		//cout<<"patients::groups size before addition: "<<patients->Groups().size()<<endl;
		//Create a new group based on the entered name
        string n=diag->get_name();
		patients->CreateNewGroup(n);
		//cout<<"Created group named "<<diag->get_name()<<endl;
		//cout<<"patients::groups size after addition: "<<patients->Groups().size()<<endl;
		//Add it to the selector
		wxString t(n);
		group_selector_box->Append(t);
	}
	//Scrap the dialog memory
	delete diag;

	//some debug code
	//cout<<"Group created is named "<<patients->Groups()[0].Code()<<endl;
}

void MainWindow::OnDeleteGroup(wxCommandEvent &event){

	//Are there groups to delete?
	if(patients->Groups().size()<1){
		wxMessageBox(wxT("No groups to delete!"),wxT("Unable!"));
	}else{
		DeleteGroupDialog *diag=new DeleteGroupDialog(this,patients->Groups());
		//cout<<"Passed "<<patients->Groups().size()<<" group codes to diag"<<endl;
		int outcome=diag->ShowModal();
		if(outcome==wxID_OK){
			//Establish the code of the group to delete
			string del_code=diag->get_selected();
			//Delete the group from the patient list
			patients->DeleteGroup(del_code);
			//Remove the group from the selector
			for(int i=0;i<(int)group_selector_box->GetCount();i++){
				if(group_selector_box->GetString(i).ToStdString()==del_code){
					//This is the one to delete
					group_selector_box->Delete(i);
				}
			}
		}

		delete diag;

	}
}

void MainWindow::OnAddToGroup(wxCommandEvent &event){
	AddToGroupDialog *diag=new AddToGroupDialog(this,patients->Groups());
	int outcome = diag->ShowModal();
	if(outcome==wxID_OK){
		//which patient are we dealing with?
		//	ID by code (column zero)
		string c=patient_view->GetItemText(selected,0).ToStdString();
		string gc=diag->selected_group();
		//Add patient to group
		patients->AddPatientToGroup(c,gc);
		//Done!
	}
}

void MainWindow::OnRemoveFromGroup(wxCommandEvent &event){

	//What group is currently selected?  If we're in all patients, we need to pop up an alert saying that isn't allowed
	int gc=group_selector_box->GetSelection();
	if(gc==0){
		//We are selecting all patients.  Time to pop up an alert
		wxMessageBox(wxT("Unable to remove a patient from the group \"All Patients\"."),wxT("Alert!"));
	}else{
		//What is the code of the patient we're trying to remove?
		string c=patient_view->GetItemText(selected,0).ToStdString();
		//What group is selected?
		int g=group_selector_box->GetCurrentSelection();
		//What is the code of the selected group
		string gc=group_selector_box->GetString(g).ToStdString();
		//Remove the patient from the group
		patients->Group(gc).Remove(c);
		//Next we have to update the view
	}

	//Update the view
	this->updateView();

}

void MainWindow::OnListDeselect(wxListEvent &event){

	//Change the selection index
	selected=-1;

	//Disbale the buttons
	add_pt_grp_btn->Enable(false);
	remove_pt_grp_btn->Enable(false);

}

void MainWindow::SavePatientFile(wxCommandEvent &event){

	//We need to get the file we're saving to
	wxFileDialog saveSelector(this,wxT("Save the current patient load"),wxT(""),wxT(""),wxT("*.dat"),wxFD_SAVE);
	bool success=false;

	if(saveSelector.ShowModal()==wxID_OK){

		//Some quick test code
		//cout<<saveSelector.GetPath().ToStdString()<<endl;

		success = patients->printToFile(saveSelector.GetPath().ToStdString());

	}

	if(!success){
		wxMessageDialog unableToAccessFile(this,wxT("Unable to open file for writing!"),wxT("Failure!"));
		unableToAccessFile.ShowModal();
	}

}

void MainWindow::LoadPatientFile(wxCommandEvent &event){

	//Get the path
	wxFileDialog loadSelector(this,wxT("Load a set oatient data"),wxT(""),wxT(""),wxT("*.dat"),wxFD_OPEN);
	bool success=false;
	PList *temp=new PList();

	if(loadSelector.ShowModal()==wxID_OK){
		success=temp->readFromFile(loadSelector.GetPath().ToStdString());
	}

	if(!success){
		wxMessageDialog unableToAccessFile(this,wxT("Unable to read file.  May be corrupted.  Veryfiy permissions."),wxT("Failure!"));
		unableToAccessFile.ShowModal();
	}else{
		patients=new PList(*temp);
		cout<<patients->Patients().size()<<endl;
		suffix=patients->AccessSuffixGenerator();
	}

	this->updateView();
	selected=-1;

}

void MainWindow::OnDeletePatient(wxCommandEvent &evt){
	//First we need to decide if there are any patients to delete
	if(patients->Size()<1){
		//Display an alert
		wxMessageDialog no_patients(this,wxT("No patients to delete!"),wxT("Error!"));
		no_patients.ShowModal();
	}else{ //We need to display the selection dialog
		//Collect all the codes
		vector <string> codes;
		for(int i=0;i<patients->Patients().size();i++){
			codes.push_back(patients->Patients()[i]->Code());
		}
		DeletePatientDialog *diag=new DeletePatientDialog(this,codes);
		int code=diag->ShowModal();
		if(code==wxOK){
			//The user pressed OK, so now we process the selection
			patients->DeletePatient(diag->getSelected());
			this->updateView();
		}
		delete diag;
	}
}
