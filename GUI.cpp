///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 3.10.1-0-g8feb16b3)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(126, 58, 156));

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer(wxHORIZONTAL);

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer(wxVERTICAL);


	m_panel_left = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	m_panel_left->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));
	bSizer4->Add(m_panel_left, 1, wxEXPAND | wxALL, 4);


	bSizer1->Add(bSizer4, 1, wxEXPAND, 4);

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer(wxVERTICAL);

	m_panel_right = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	bSizer5->Add(m_panel_right, 1, wxEXPAND | wxALL, 4);

	bSizer1->Add(bSizer5, 1, wxEXPAND, 4);



	////////////////////
	bSizerOptions = new wxBoxSizer(wxVERTICAL);

	// Create the radio button groups
	wxRadioBox* group_image = new wxRadioBox(this, wxID_ANY, "Image", wxDefaultPosition, wxDefaultSize,
		3, group1Choices, 1, wxRA_SPECIFY_COLS);
	wxRadioBox* group_elements = new wxRadioBox(this, wxID_ANY, "Elements", wxDefaultPosition, wxDefaultSize,
		3, group2Choices, 1, wxRA_SPECIFY_COLS);
	wxRadioBox* group_tempo = new wxRadioBox(this, wxID_ANY, "Tempo", wxDefaultPosition, wxDefaultSize,
		3, group3Choices, 1, wxRA_SPECIFY_COLS);

	// Create the button
	wxButton* button_start = new wxButton(this, wxID_ANY, "Start");

	// Add the button to the sizer
	bSizerOptions->Add(button_start, 0, wxALIGN_CENTER_HORIZONTAL | wxBOTTOM, 10);



	//m_panel_options = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	//bSizerOptions->Add(m_panel_options, 1, wxEXPAND | wxALL, 2);
	// Add radio button groups to the sizer
	bSizerOptions->Add(group_image, 0, wxALL, 10);
	bSizerOptions->Add(group_elements, 0, wxALL, 10);
	bSizerOptions->Add(group_tempo, 0, wxALL, 10);

	bSizer1->Add(bSizerOptions, 0, wxEXPAND, 0);


	this->SetSizer(bSizer1);
	this->Layout();

	this->Centre(wxBOTH);
	// Connect Events
	m_panel_right->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::OnSize), NULL, this);
	m_panel_left->Connect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::OnSize), NULL, this);
	this->Connect(wxEVT_TIMER, wxTimerEventHandler(MyFrame1::StartTimer), NULL, this);

	group_image->Bind(wxEVT_RADIOBOX, &MyFrame1::OnRadioImage, this);
	group_elements->Bind(wxEVT_RADIOBOX, &MyFrame1::OnRadioElements, this);
	group_tempo->Bind(wxEVT_RADIOBOX, &MyFrame1::OnRadioTempo, this);
	button_start->Bind(wxEVT_BUTTON, &MyFrame1::OnButtonStartClicked, this);



}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_panel_right->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::OnSize), NULL, this);
	m_panel_left->Disconnect(wxEVT_SIZE, wxSizeEventHandler(MyFrame1::OnSize), NULL, this);
	this->Disconnect(wxEVT_TIMER, wxTimerEventHandler(MyFrame1::StartTimer), NULL, this);

}

