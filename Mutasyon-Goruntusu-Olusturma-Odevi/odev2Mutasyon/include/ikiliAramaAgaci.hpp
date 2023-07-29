#ifndef ikiliAramaAgaci_hpp
#define ikiliAramaAgaci_hpp
#include <iostream>
#include <string>
#include "doku.hpp"
#include "hucre.hpp"

class ikiliAramaAgaci
{
	public:
		ikiliAramaAgaci();
		~ikiliAramaAgaci();
		void ekle(int veri, doku* aktifDoku);
		void agacOlustur(string* agactakiSatirlar);
		void mutasyonSonrasiAgacOlustur(int *hucreVerisi);
		void preOrderIslem(doku* aktifDoku,int *dizgin);		
		void agaciMutasyonaUgrat(doku* aktifDoku);
		void postOrderIslem(doku* aktifDoku,int *dizgin);
		bool bosMu();
		void temizle();
		int sayac;
		doku* kok;		
		bool dokuSil(doku *&aktifDoku);				
};
#endif
