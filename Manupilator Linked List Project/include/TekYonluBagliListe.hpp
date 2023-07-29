#ifndef TekYonluBagliListe_hpp
#define TekYonluBagliListe_hpp

#include "TekYonluBagliListeDugumu.hpp"
class TekYonluBagliListe
{
	private:
		TekYonluBagliListeDugumu* bas;
		int dugumSayisi;
	public:
		TekYonluBagliListe();	
		~TekYonluBagliListe();
		void setDugumSayisi(int sayisi);
		TekYonluBagliListeDugumu* TekYonluBagliListeDugumGetir(int sira);
		bool DugumGecerliligiGetir(int siramiz);
		int DugumVerisiGetir(int siramiz);
		void ListeyeDugumEkle(int verisi);	
};


#endif