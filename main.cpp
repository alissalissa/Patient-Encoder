//Reads and encodes patient data

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
