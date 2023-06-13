// Thuja LLC @2215 wszyskie prawa zastrzeżone
#include <wx/wx.h>
#include "GUIMyFrame1.h"

class MyApp : public wxApp {

public:

	virtual bool OnInit();
	virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	wxImage::AddHandler(new wxJPEGHandler);           // Dodajemy handlery do formatow
	wxImage::AddHandler(new wxPNGHandler);            // z jakich bedziemy korzytsac

	wxImage image;
	wxLogNull logNo;
	if (!image.LoadFile("mountain_of_thujas.png"))
	{
		wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
		//mainFrame->Destroy();
		return true;
	}

	GUIMyFrame1 *mainFrame = new GUIMyFrame1(NULL);
	mainFrame->Img_Org = image.Copy();              // Kopiujemy obrazek do Img_Org
	mainFrame->Show(true);
	SetTopWindow(mainFrame);

	return true;
}
