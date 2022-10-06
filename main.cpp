//Reads and encodes patient data

// TODO (alissa#1#): Implement open last file

#include "mainwindow.h"
#include "main.h"

using namespace std;

IMPLEMENT_APP(PatientEncoderApp);

bool PatientEncoderApp::OnInit(void){
	mw=new MainWindow(NULL);
	mw->Show();
	SetTopWindow(mw);
	return true;
}
