#include "GUIMyFrame1.h"
GUIMyFrame1::GUIMyFrame1(wxWindow* parent)
	:
	MyFrame1(parent)
{
	//definicja trzeba zrobić ENUM
	timer = new wxTimer();
	timer->SetOwner(this, 1001);

	WxStaticText1 = new wxStaticText(this, wxID_ANY, _("00:00"), wxPoint(500, 300), wxDefaultSize, 0, _("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _("Tahoma")));

	sec = 0;

	l = 0;


	//menu
	menubar = new wxMenuBar;
	file = new wxMenu;

	file->Append(wxID_NEW, wxT("&New"));
	file->Append(wxID_ANY, wxT("&Open"));
	file->Append(wxID_ANY, wxT("&Save"));
	file->AppendSeparator();

	imp = new wxMenu;
	imp->Append(wxID_ANY, wxT("Thuja"));
	imp->Append(wxID_ANY, wxT("Mountains"));
	imp->Append(wxID_ANY, wxT("Mountain of thujas"));

	file->AppendSubMenu(imp, wxT("I&mage"));

	quit = new wxMenuItem(file, wxID_EXIT, wxT("&Quit\tCtrl+W"));
	newGame = new wxMenuItem(file, wxID_NEW, wxT("&New Game\tCtrl+N"));
	file->Append(quit);
	file->Append(newGame);

	menubar->Append(file, wxT("&File"));
	SetMenuBar(menubar);

	Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(GUIMyFrame1::OnNewGame));
	Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
		wxCommandEventHandler(GUIMyFrame1::OnQuit));
	Centre();
}

void GUIMyFrame1::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Close(true);
}

void GUIMyFrame1::OnNewGame(wxCommandEvent& WXUNUSED(event))
{
	//nie mam pojęcia gdzie tę funkcję wstawić xd
	get_started();
}

void GUIMyFrame1::get_started()
{
	timer->Start(100);
	started = wxDateTime::Now();
}

void GUIMyFrame1::Repaint()
{
	int a = width / 10.;
	//dzielimy obrazek na kafelki
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 14; j++)
			images[i][j] = (Img_Org.GetSubImage(wxRect(wxPoint(i*a, height - (j + 1)*a), wxSize(a, a))));
	}

	wxBitmap bitmap(Img_Org);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
	wxClientDC dc(m_panel4);   // Pobieramy kontekst okna
	dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia

}
void GUIMyFrame1::Timer1_Timer(wxTimerEvent& e)
{
	static int i = 0;
	static int j = 0;
	static int k = 0;//zmienna ktora zmienia położenie y kafelka
	static int x = 0;//mowi czy odwracac czy nie
	//narazie zak³adam taki rozmiar kwadratu
	int a = width / 10;
	static int h = 0; //dopisane teraz D
	//sprawdzamy stan klawiszy
	timer->Stop();
	if (wxGetKeyState(WXK_RIGHT))
		//l=1 przesuwamy kafel w prawo
		l++;
	if (wxGetKeyState(WXK_LEFT))
		l--;
	if (wxGetKeyState(WXK_UP))
		//obracamy o 90 stopni
		x++;
	if (wxGetKeyState(WXK_DOWN))
		//obracamy o -90 stopni
		x--;
	if (wxGetKeyState(WXK_TAB))
		//odbicie lustrzane
		h++;
	timer->Start();

	now_sec = sec;
	wxDateTime now = wxDateTime::Now();
	//czas trwania gry
	sec = now.GetSecond() - started.GetSecond();
	//wyœwietlanie czasu trwania gry
	WxStaticText1->SetLabel(
		wxString::Format("%02d", now.GetMinute() - started.GetMinute()) + ":" +
		wxString::Format("%02d", sec));
	static wxClientDC dc_two(m_panel3);
	if (sec == 0)
	{	//tutaj tworzę tło po lewej stronie na początku działania zegara
		Img_Cpy = Img_Org.Copy();
		wxImage Img_Tmp = Img_Cpy.ConvertToGreyscale();
		wxBitmap bitmap(Img_Tmp);
		dc_two.SetBackground(bitmap);
	}
	//tutaj zak³adam sobie jak¹œ szybkoœæ spadania,tik czasowy
	if ((sec - now_sec) == 0, 1)
	{

		dc_two.Clear();
		if (k == 0)
			//pobieram kopie, aby nie modyfikować oryginału
			tmp = images[i][j].Copy();
		//wadą jest to że za każdym razem, za każdą iteracją to obracam-brak optymalizacji
		if (x < 0) {
			tmp = tmp.Rotate(-M_PI / 2.0, wxPoint(tmp.GetWidth() / 2., tmp.GetHeight() / 2.));
			x = 0;
			// TO DO: Obrot o -90 stopni
		}
		else if (x > 0)
		{
			//obrót o 90 stopni
			tmp = tmp.Rotate(M_PI / 2.0, wxPoint(tmp.GetWidth() / 2., tmp.GetHeight() / 2.));
			x = 0;
		}
		if (h)
		{
			//odbicie lustrzane wersja rozszerzona
			tmp = tmp.Mirror();
			h = 0;
		}
		//rysujemy kafelek
		dc_two.DrawBitmap(wxBitmap(tmp), width / 2 + l * 10, 10 * k, true);
		//tu wyświetlam już ułożone kafelki-także błąd optymalizacji-trzeba to zmienić!
		for (auto r : v)
		{
			dc_two.DrawBitmap(r.image, r.x, r.y, true);
		}
		//sprawdzam czy kafel trafił na miejsce-albo w okolice-myślę, że też można coś tutaj zmienić
		if ((width / 2 + l * 10) >= (i*a - 5) && (width / 2 + l * 10) <= (i * a + 5)
			&& (10 * k) >= (height - j * a - 40) && (k * 10) <= (height - j * a))
		{
			//tutaj  sprawdzam czy kwadrat nie jest jakoś odwrócony
			if (*tmp.GetData() == *images[i][j].GetData())
			{
				//gwarantuje, że będzie ładnie ułożone-jako współrzędne wpisuję pierwotne współrzędne
				v.push_back(Kwadrat(wxBitmap(images[i][j]), i*a, height - j * a - 40));
				k = 0;
				x = 0;
				//pobieram kolejny element z tablicy kafelków
				i++;
				l = 0;
			}
			else
			{
				k++;
			}
		}
		else
			k++;
		if ((10 * k) > height)
		{
			k = 0;
			l = 0;
			x = 0;
		}
		if (i > 8)
		{
			j++;
			i = 0;
			l = 0;
			k = 0;
		}

	}
}

void GUIMyFrame1::hhh(wxKeyEvent& event)
{
	//to chyba musi być xxd
}

void GUIMyFrame1::ssize(wxSizeEvent& event) {
	//narazie tutaj

	//pobieramy aktualny rozmiar panelu z prawej strony dla dopasowania obrazka// m_panel_right
	height = m_panel4->GetSize().GetHeight();
	width = m_panel4->GetSize().GetWidth();
	//resizujemy obrazek
	wxImage tmp = Img_Org.Scale(width, height);
	Img_Org = tmp.Copy();
	//Img_Org.Resize(m_panel4->GetSize(), m_panel4->GetPosition());
	Repaint();
}
