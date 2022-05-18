//Reads and encodes patient data
// TODO (alissa#2#05/15/22): Why does the program crash when loading from a file twice?
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
