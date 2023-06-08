#include "GUIMyFrame1.h"
GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
	timer = new wxTimer();
	timer->SetOwner(this, 1001);

	WxStaticText1 = new wxStaticText(this, wxID_ANY, _("WxStaticText1"), wxPoint(500, 300), wxDefaultSize, 0, _("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(10, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, _("Tahoma")));

	sec = 0;

	l = 0;

}
void GUIMyFrame1::get_started()
{
	timer->Start(100);
	started = wxDateTime::Now();
}

void GUIMyFrame1::Repaint()
{
	int a = width / 10.;
		//rysujemy obrazek po lewej stronie
	for (int i = 0; i < 9; i++)
	{
		for(int j=0;j<14;j++)
			images[i][j] = (Img_Org.GetSubImage(wxRect(wxPoint(i*a, height-(j+1)*a),wxSize( a, a))));
	}
	Img_Cpy = Img_Org.Copy();
	wxImage Img_Tmp = Img_Cpy.ConvertToGreyscale();
	    wxBitmap bitmap(Img_Tmp);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
		wxClientDC dc(m_panel4);   // Pobieramy kontekst okna
		dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
		//próba podzielenia obrazka na mniejsze czêœci i wyœwietlenia
		//tutaj trzeba te¿ przekszta³ciæ nasz¹ macierz 
		

		//wxDateTime now = wxDateTime::Now();


}
void GUIMyFrame1::Timer1_Timer(wxTimerEvent& e)
{
	static int i = 0;
	static int j = 0;
	static int k = 0;
	static int x = 0;//mowi czy odwracac czy nie
	//narazie zak³adam taki rozmiar kwadratu
	int a = width / 10;
	//sprawdzamy stan klawiszy
	timer->Stop();
	if (wxGetKeyState(WXK_RIGHT))
		l++;
	if (wxGetKeyState(WXK_LEFT))
		l--;
	if (wxGetKeyState(WXK_UP))
		x++;
	if (wxGetKeyState(WXK_DOWN))
		x--;
	if (wxGetKeyState(WXK_TAB))
		h++;
	timer->Start();

	now_sec = sec;
	wxDateTime now = wxDateTime::Now();
	//czas trwania gry
	sec = now.GetSecond() - started.GetSecond();
	//wyœwietlanie czasu trwania gry
	WxStaticText1->SetLabel(
		wxString::Format("%02d", now.GetMinute()-started.GetMinute()) + ":" + 
		wxString::Format("%02d", sec));
	//tutaj zak³adam sobie jak¹œ szybkoœæ spadania
	if ((sec-now_sec)==0,1)
	{
		
			wxClientDC dc_two(m_panel3);
			dc_two.Clear();
			if(k==0)
				tmp = images[i][j].Copy();
			if (x < 0) {
				tmp = tmp.Rotate(-M_PI / 2.0, wxPoint(tmp.GetWidth() / 2.,tmp.GetHeight() / 2.));
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
			dc_two.DrawBitmap(wxBitmap(tmp), width / 2 + l * 10, 10 * k, true);
			for (auto r : v)
			{
				dc_two.DrawBitmap(r.image, r.x, r.y, true);
			}
			if ((width / 2 + l *10)>=(i*a-5) && (width / 2 + l * 10)<=(i * a + 5)
				&& (10*k) >= (height-j*a-40)&& (k* 10)<=(height - j*a))
			{
				if (*tmp.GetData() == *images[i][j].GetData())
				{
					//gwarantuje, że będzie ładnie ułożone
					v.push_back(Kwadrat(wxBitmap(images[i][j]),i*a, height - j * a - 40));
					k = 0;
					x = 0;
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
void GUIMyFrame1::Repaint_left()
{

	wxImage tmp = Img_Org.GetSubImage(wxRect(sec, sec, 10+sec, 10+sec));
	wxBitmap bitmap_tmp(tmp);
	wxClientDC dc_two(m_panel3);
	dc_two.Clear();
	dc_two.DrawBitmap(bitmap_tmp,sec , sec, true);
}
void GUIMyFrame1::hhh(wxKeyEvent& event) 
{
}

void GUIMyFrame1::ssize(wxSizeEvent& event) {
	//narazie tutaj
	
	//pobieramy aktualny rozmiar panelu z prawej strony dla dopasowania obrazka
	height = m_panel4->GetSize().GetHeight();
	width= m_panel4->GetSize().GetWidth();
	//resizujemy obrazek
	wxImage tmp = Img_Org.Scale(width, height);
	Img_Org = tmp.Copy();
	//Img_Org.Resize(m_panel4->GetSize(), m_panel4->GetPosition());
	Repaint();
	get_started();
}
