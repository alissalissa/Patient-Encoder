//Main App

#include <wx/wx.h>

//Local includes
#include "mainwindow.h"

using namespace std;

class PatientEncoderApp : public wxApp{
private:

	//Application variables
	MainWindow *mw;

public:

	bool OnInit(void);

};
