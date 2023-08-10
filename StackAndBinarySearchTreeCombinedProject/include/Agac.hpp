#ifndef Agac_hpp
#define Agac_hpp
#include "Dizi.hpp"
#include "AgacDugum.hpp"
class Agac
{
	private:
		int dugumSayisi;
		AgacDugum* kok;
		void Ekle(AgacDugum* dugum,int veri);
		void postOrderVeriGetir(AgacDugum* dugum,Dizi* dizi);
		void Temizle(AgacDugum* dugum);
		int yukseklikBul(AgacDugum* dugum);
		int dugumlerToplamiBul(AgacDugum* dugum);
	public:
		Agac();
		~Agac();
		void Ekle(int veri);
		void Temizle();
		int dugumlerToplamiBul();
		int getDugumSayisi();
		int yukseklikBul();
		Dizi* postOrderVeriGetir();
};


#endif