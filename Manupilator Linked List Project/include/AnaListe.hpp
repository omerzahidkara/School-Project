#ifndef AnaListe_hpp
#define AnaListe_hpp

#include <iostream>
#include <string>
#include "TekYonluBagliListe.hpp"
#include "AnaListeDugum.hpp"
using namespace std;

class AnaListe
{
	private:
		AnaListeDugum* basDugum;
		int** satirlarinHepsi;
		int* dugumlerinMiktarBilgileri;
		int anaDugumSayisi;
		int enKalabalikDugumedekiSatirSayisi;
	public:
		AnaListe();
		~AnaListe();		
		AnaListeDugum* AnaListeDugumGetir(int sira);		
		void AnaListeyiBosOlustur();		
		int** getSayilarinHepsi();	
		int getAnaDugumSayisi();		
		void setAnaDugumSayisi(int sayi);		
		void SatirSayisiniBul();	
		int getSatirDakiVeriSayisi(string satir);	
		void MatrisOlustur();
		TekYonluBagliListe* UstListeyiOlustur(int dugumSirasiUst); //onlar basamakalari
		TekYonluBagliListe* AltListeyiOlustur(int dugumSirasi); // birler basamaklari
		void AnaListeyiOlustur();
		void Oku();
		void KullaniciIslemYerDegisme();
		double UstSatirOrtalamaBul(int satirSirasi);
		double AltSatirOrtalamaBul(int satirSirasi);
		double UstToplamlar();
		double AltToplamlar();
		void KullaniciIslemSon();
		int getEnKalabalikDugumedekiSatirSayisi();
};

#endif