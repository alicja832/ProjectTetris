///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/frame.h>
#include <wx/wxprec.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MyFrame1
///////////////////////////////////////////////////////////////////////////////
class MyFrame1 : public wxFrame
{
	private:

		wxRadioButton* radioImage1;
		wxRadioButton* radioImage2;
		wxRadioButton* radioImage3;

		wxRadioButton* radioElements1;
		wxRadioButton* radioElements2;
		wxRadioButton* radioElements3;

		wxRadioButton* radioTempo1;
		wxRadioButton* radioTempo2;
		wxRadioButton* radioTempo3;

	protected:

		wxPanel* m_panel_left;
		wxPanel* m_panel_right;
		wxPanel* m_panel_options;

		wxBoxSizer* bSizerOptions;
		wxStaticText* WxStaticText1;

	// Define choices for each radio button group
		wxString group1Choices[3] = { "Mountains", "Powershell", "Thuja" };
		wxString group2Choices[3] = { "2", "3", "4" };
		wxString group3Choices[3] = { "Slow", "Normal", "Fast" };

		virtual void OnSize(wxSizeEvent& event) { event.Skip(); }
		virtual void StartTimer(wxTimerEvent& e) { e.Skip(); }

			//odpowiedzialne za menu
		virtual void OnRadioImage(wxCommandEvent& event) { event.Skip(); }
		virtual void OnRadioElements(wxCommandEvent& event) { event.Skip(); }
		virtual void OnRadioTempo(wxCommandEvent& event) { event.Skip(); }
		virtual void OnButtonStartClicked(wxCommandEvent& event) { event.Skip(); }

	public:

		MyFrame1( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = "Tetris", const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(800, 600), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);


		~MyFrame1();

};

