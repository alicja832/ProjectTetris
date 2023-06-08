///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_panel3 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer4->Add( m_panel3, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer4, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_panel4 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	bSizer5->Add( m_panel4, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer5, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();

	this->Centre( wxBOTH );
	// Connect Events
	m_panel4->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::ssize), NULL, this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(MyFrame1::Timer1_Timer), NULL, this);
	this->Connect(wxEVT_KEY_DOWN, wxKeyEventHandler(MyFrame1::hhh), NULL, this);

}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_panel4->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::ssize), NULL, this);
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(MyFrame1::Timer1_Timer), NULL, this);
	this->Disconnect(wxEVT_KEY_DOWN, wxKeyEventHandler(MyFrame1::hhh), NULL, this);

}
