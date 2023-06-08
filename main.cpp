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
 SetProcessDPIAware();
 GUIMyFrame1 *mainFrame = new GUIMyFrame1(NULL);
wxImage::AddHandler(new wxJPEGHandler);           // Dodajemy handlery do formatow
 wxImage::AddHandler(new wxPNGHandler);            // z jakich bedziemy korzytsac
 wxImage image;
 {
     wxLogNull logNo;
     if (!image.LoadFile("Alicja.jpg"))
     {
         wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
         mainFrame->Destroy();
         return true;
     }
     else
     {
         mainFrame->Img_Org = image.Copy();              // Kopiujemy obrazek do Img_Org
     }
 }

 mainFrame->Show(true);
 SetTopWindow(mainFrame);

 return true;
}