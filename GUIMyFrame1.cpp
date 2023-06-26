#include "GUIMyFrame1.h"
GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	dc_right = new wxClientDC(m_panel_right);
	dc_left = new wxClientDC(m_panel_left);
	timer = new wxTimer();
	timer->SetOwner(this, 1001);

	// initialize variables
	sec = 0;

	shiftAmount = 0;

	row = 0;
	col = 0;
	x = 2;

	Centre();
}

void GUIMyFrame1::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void GUIMyFrame1::OnButtonStartClicked(wxCommandEvent& WXUNUSED(event))
{
	DoImageTab();
	GetStarted();
	//Repaint();
	Game();
}
void GUIMyFrame1::StartTimer(wxTimerEvent& e)
{
	Game();
}

void GUIMyFrame1::GetStarted()
{
	img_cpy = img_org.Copy();
	wxImage Img_Tmp = img_cpy.ConvertToGreyscale();
	Img_Tmp.Rescale(width, height);
	wxBitmap bitmap(Img_Tmp);
	dc_left->SetBackground(bitmap);

	started = wxDateTime::Now();
	timer->Start(100);
}

void GUIMyFrame1::Repaint()
{

	img_cpy = img_org.Copy();
	wxImage Img_Tmp = img_cpy.Rescale(width, height);
	wxBitmap bitmap(Img_Tmp);
	dc_right->DrawBitmap(bitmap, 0, 0, true); 

}
void GUIMyFrame1::Game()
{
	if (v.size() >= x * ceil( height / 2 / b )) { //YOU WON
		timer->Stop();

		dc_left->Clear();
		img_cpy = img_org.Copy();
		wxImage Img_Tmp = img_cpy.Rescale(width, height);
		wxBitmap bitmap(Img_Tmp);
		dc_left->DrawBitmap(bitmap, 0, 0, true); 

		//Print the selected string
		wxMessageBox(wxT("Congratulations! You won with score " + wxString::Format("%02d", (sec < 0) ? (60 + sec) / 60 : sec / 60) + ":" +
			wxString::Format("%02d", (sec < 0) ? (60 + sec) % 60 : sec % 60)), "End of round", wxOK | wxICON_INFORMATION);
		return;
	}


	static int rotation = 0;// rotation
	static int act_rot = 0;//is rotation changed
	static int mirror_horizontal = 0; // mirror horizontally
	static int act_mirror_horizontal = 0; // check if mirrored horizontally
	static int mirror_vertical = 0; // mirror vertically
	static int act_mirror_vertical = 0; // check if mirrored vertically
	int mirror = 0;//zmienna która przechowuje infomacje o tym co się wydarzyło
	//check keys
	timer->Stop();
	if (wxGetKeyState(WXK_RIGHT))
		// tile to the left
		shiftAmount++;
	if (wxGetKeyState(WXK_LEFT))
		// tile to the right
		shiftAmount--;
	if (wxGetKeyState(WXK_UP))
		// +90 deg
		rotation++;
	if (wxGetKeyState(WXK_DOWN))
		// -90 deg
		rotation--;
	if (wxGetKeyState(WXK_TAB))
		// mirror horizontally
		mirror_horizontal++;
	if (wxGetKeyState(WXK_F1))
		// mirror vertically
		mirror_vertical--;
	timer->Start(100);

	wxDateTime now = wxDateTime::Now();
	sec = now.GetTicks() - started.GetTicks();
	// print time 
	WxStaticText1->SetLabel(
		wxString::Format("%02d", (sec < 0) ? (60 + sec) / 60 : sec / 60) + ":" +
		wxString::Format("%02d", (sec < 0) ? (60 + sec) % 60 : sec % 60));//dlaczego ta linijka? bo pojawialy sie ujemne liczby w licznku; dzięki niej modulo będzie zwracać liczby dodatnie


	if (true)
	{
		dc_left->Clear();
		if (moving_y == 0) {
			// get copy
			// get random rotation
			srand(time(NULL));
			rotation = rand() % 4;
			img_tmp = images[row][col].Copy();
		}
		if (rotation != act_rot) {
			img_tmp = images[row][col].Copy();
			img_tmp = img_tmp.Rotate(rotation * M_PI / 2.0, wxPoint(img_tmp.GetWidth() / 2., img_tmp.GetHeight() / 2.));
			act_rot = rotation;
		}

		if (mirror_horizontal != act_mirror_horizontal) {
				img_tmp = img_tmp.Mirror();
				act_mirror_horizontal = mirror_horizontal;
		}

		if (mirror_vertical != act_mirror_vertical)
		{
			img_tmp = img_tmp.Mirror(false);
			act_mirror_vertical = mirror_vertical;
		}

		dc_left->DrawBitmap(wxBitmap(img_tmp), width / 2 + shiftAmount * 10, moving_y, true);
		for (auto r : v)
		{
			dc_left->DrawBitmap(r.image, r.x, r.y, true);
		}
		// check which mirror
		mirror = mirror_vertical ? mirror_vertical : mirror_horizontal;
		// is tile on the proper place
		if (IsOnPlace(img_tmp, col, row, moving_y, rotation, mirror))
		{	// allows for little mismatch in placing
			v.push_back(Square(wxBitmap(images[row][col]), col * a, height - (row + 1) * b));
			moving_y = 0;
			rotation = 0;
			mirror_vertical = 0;
			mirror_horizontal = 0;
			// get next tile
			col++;
			shiftAmount = 0;
		}
		else
			moving_y += moving_y_change;
		if ((moving_y) > height)
		{
			moving_y = 0;
			shiftAmount = 0;
			rotation = 0;
			mirror_vertical = 0;
			mirror_horizontal = 0;
		}
		// go to the next row
		if (col > (x - 1))
		{
			row++;
			col = 0;
			shiftAmount = 0;
			moving_y = 0;
		}

	}


}
bool GUIMyFrame1::IsOnPlace(wxImage& image, int& c, int& r, int& _moving_y, int& rotation, int& mirror)
{
	int moving_x_change = 10;
	if ((width / 2 + shiftAmount * moving_x_change) >= (c * a - a / 5) && (width / 2 + shiftAmount * moving_x_change) <= (c * a + a / 5)
		&& (_moving_y) >= (height - ((r + 1) * b)) && (_moving_y) <= (height - r * b))
	{

		//is the square in proper angle
		if (rotation % 4 == 0 && mirror % 2 == 0)
		{
			return true;
		}
	}
	return false;
}


void GUIMyFrame1::OnSize(wxSizeEvent& event) {

	// This happens when the window is resized

	// get actoal dimensions
	height = m_panel_right->GetSize().GetHeight();
	width = m_panel_right->GetSize().GetWidth();
	a = width / x;
	b = a;

	img_cpy = img_org.Copy();
	wxImage Img_Tmp = img_cpy.Rescale(width, height);

	for (int row = 0; row < y; row++)
	{
		for (int col = 0; col < (x); col++)
			images[row][col] = (Img_Tmp.GetSubImage(wxRect(wxPoint(col * a, height - (row + 1) * b), wxSize(a, b))));
	}

	int r, c;
	for (int i = 0; i < v.size(); ++i) {
		r = i / x;
		c = i % x;
		v[i] = Square(wxBitmap(images[r][c]), c * a, height - (r + 1) * b);
	}
	for (auto r : v)
	{
		dc_left->DrawBitmap(r.image, r.x, r.y, true);
	}

	if (sec > 0) {
		img_tmp = images[row][col].Copy();
	}

	if (sec > 0) {
		delete WxStaticText1;
		WxStaticText1 = new wxStaticText(this, wxID_ANY, _("00:00"), wxPoint(width + 10, 10), wxDefaultSize, 0, _("WxStaticText1"));
		WxStaticText1->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _("Tahoma")));
	}

	Img_Tmp = img_cpy.ConvertToGreyscale();
	Img_Tmp.Rescale(width, height);
	wxBitmap bitmap(Img_Tmp);
	dc_left->SetBackground(bitmap);

	Repaint();
}
void GUIMyFrame1::OnRadioImage(wxCommandEvent& event)
{
	// Get the radio button group that triggered the event
	wxRadioBox* group = dynamic_cast<wxRadioBox*>(event.GetEventObject());

	// Get the selected string from the radio button group
	wxString selected = group->GetStringSelection();

	//take picture
	std::string name_picture;
	if (selected == group1Choices[0])
		name_picture = "mount1_half.png";
	if (selected == group1Choices[1])
		name_picture = "powershell_half.png";
	if (selected == group1Choices[2])
		name_picture = "thuja_half.png";
	//change picture
	wxImage::AddHandler(new wxJPEGHandler);           
	wxImage::AddHandler(new wxPNGHandler);            

	wxImage image;
	wxLogNull logNo;
	if (!image.LoadFile(name_picture))
	{
		wxMessageBox(_("Nie uda\u0142o si\u0119 za\u0142adowa\u0107 obrazka"));
	}

	img_org = image.Copy();
	img_cpy = img_org.Copy();
	wxImage Img_Tmp = img_cpy.ConvertToGreyscale();
	Img_Tmp.Rescale(width, height);
	wxBitmap bitmap(Img_Tmp);
	dc_left->SetBackground(bitmap);
	dc_left->DrawBitmap(bitmap, 0, 0, true);

	DoImageTab();
	Repaint();
	m_panel_left->SetFocus();
}

void GUIMyFrame1::OnRadioElements(wxCommandEvent& event)
{
	// Get the radio button group that triggered the event
	wxRadioBox* group = dynamic_cast<wxRadioBox*>(event.GetEventObject());

	// Get the selected string from the radio button group
	wxString selected = group->GetStringSelection();



	//take action-calculate the size of squares
	if (selected == '2')
		x = 2;
	if (selected == '3')
		x = 3;
	if (selected == '4')
		x = 4;


	img_cpy = img_org.Copy();
	wxImage Img_Tmp = img_cpy.ConvertToGreyscale();
	Img_Tmp.Rescale(width, height);
	wxBitmap bitmap(Img_Tmp);
	dc_left->SetBackground(bitmap);
	dc_left->DrawBitmap(bitmap, 0, 0, true);

	DoImageTab();
	m_panel_left->SetFocus();
}
void GUIMyFrame1::DoImageTab()
{
	timer->Stop();

	row = 0;
	col = 0;

	moving_y = 0;

	a = width / x;

	b = a;
	y = 10;
	delete[] images;
	images = new wxImage * [y];
	for (int row = 0; row < y; row++)
		images[row] = new wxImage[x];

	img_cpy = img_org.Copy();
	wxImage Img_Tmp = img_cpy.Rescale(width, height);
	for (int row = 0; row < y; row++)
	{
		for (int col = 0; col < (x); col++)
			images[row][col] = (Img_Tmp.GetSubImage(wxRect(wxPoint(col * a, height - (row + 1) * b), wxSize(a, b))));
	}


	v.clear();
	Repaint();
	m_panel_left->SetFocus();
	delete WxStaticText1;
	WxStaticText1 = new wxStaticText(this, wxID_ANY, _("00:00"), wxPoint(width + 10, 10), wxDefaultSize, 0, _("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _("Tahoma")));

}
void GUIMyFrame1::OnRadioTempo(wxCommandEvent& event)
{
	// Get the radio button group that triggered the event
	wxRadioBox* group = dynamic_cast<wxRadioBox*>(event.GetEventObject());

	// Get the selected string from the radio button group
	wxString tempo = group->GetStringSelection();

	// Print the selected string
	//wxLogMessage("%s is selected", selected);
	if (tempo == "Slow")
		moving_y_change = 4;
	if (tempo == "Normal")
		moving_y_change = 8;
	if (tempo == "Fast")
		moving_y_change = 12;

	m_panel_left->SetFocus();
}
GUIMyFrame1::~GUIMyFrame1()
{
	delete WxStaticText1;
	delete dc_left;
	delete dc_right;
	delete timer;
	//clear memory
	for (int i = 0; i < y; i++)
		delete[] images[i];
}

