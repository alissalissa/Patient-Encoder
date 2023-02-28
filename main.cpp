//Reads and encodes patient data

#include "mainwindow.h"
#include "main.h"

using namespace std;

IMPLEMENT_APP(PatientEncoderApp);

bool PatientEncoderApp::OnInit(void){
	//Ensure the directory path exists for the app config file
	//As we go, we need to verify that our eventual paths exist
	//	So we create any missing directories within the config file path as we go
	string dl="/home/";
	dl+=getenv("USER");
	dl+="/.local";
	filesystem::path dot_local(dl);
	if(!filesystem::exists(dot_local)) filesystem::create_directory(dot_local);
	//~/.local now guaranteed to exist
	//Repeat that process with ~/.local/share
	dl+="/share";
	filesystem::path share(dl);
	if(!filesystem::exists(share)) filesystem::create_directory(share);
	//~/.local/share now guaranteed to exist
	//Repeat that process with ~/.local/share/PatientEncoder
	dl+="/PatientEncoder";
	filesystem::path pe(dl);
	if(!filesystem::exists(pe)) filesystem::create_directory(pe);

	mw=new MainWindow(NULL);
	mw->Show();
	SetTopWindow(mw);
	return true;
}
