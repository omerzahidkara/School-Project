/** 
* @file Agac.cpp
* @description Iki basamakli sayilardan satirlari olan bir txt 
			dosyasini bir kurala gore okur ve yazdirma islemi yapar.
			Satir okunurken okunan sayidan sonraki sayi eger okunan 
			sayidan buyuk ve cift ise okunan sayi dahil kendisinden
			onceki butun sayilari bir stack veri yapisi nesnesine atar.
			Butun satir boyunca farkli stackler olusur. Butun stacklerden
			ikili arama agaclari yapilir. Agaclardan ise en uzun olanlari secilir ve
			dugumleri degeri toplami en buyuk olan agac yazdirilmak uzere secilir.
			Agac postorder sekilde okunur ve her dugumu okunurken ASII koda gore 
			karakter yazdirir. Yazdirilan her karakterden sonra bosluk vardir.

* @course 1B Birinci ogretim
* @assignment 2
* @date 9.08.2023
* @author Omer Zahid KARA/omer.kara7@ogr.sakarya.edu.tr   Hasan KOÇ/hasan.koc7@ogr.sakarya.edu.tr
*/

#include "Agac.hpp"
#include <iostream>
#include <algorithm>
using namespace std;

Agac::Agac()
{
	kok = 0;
	dugumSayisi = 0;
}
Agac::~Agac()
{
	Temizle();
}
void Agac::Ekle(int veri)
{
	if(kok == 0)
	{
		kok = new AgacDugum(veri);
		dugumSayisi++;
	}
	else
	{
		Ekle(kok,veri);
	}
}
int Agac::getDugumSayisi()
{
	return dugumSayisi;
}
void Agac::Ekle(AgacDugum* dugum,int veri)
{
	if(veri > dugum->veri)
	{
		if(dugum->sag)
		{
			return Ekle(dugum->sag,veri);
		}
		else
		{
			dugum->sag = new AgacDugum(veri);
			dugumSayisi++;
		}
	}
	else if(veri < dugum->veri)
	{
		if(dugum->sol)
		{
			return Ekle(dugum->sol,veri);
		}
		else
		{
			dugum->sol = new AgacDugum(veri);
			dugumSayisi++;
		}
	}
}
void Agac::Temizle(AgacDugum* dugum)
{
	if(dugum)
	{
		if(dugum->sol)
		{
			Temizle(dugum->sol);
		}
		if(dugum->sag)
		{
			Temizle(dugum->sag);
		}	
		delete dugum;
		dugumSayisi--;
	}
}
void Agac::Temizle()
{
	if(kok!=0)
	{
		Temizle(kok);
		kok  = 0;
	}
				
}
Dizi* Agac::postOrderVeriGetir()
{
	if(kok)
	{
		Dizi* dizi = new Dizi();		
		postOrderVeriGetir(kok,dizi);
		return dizi;
	}
	else
	{
		throw out_of_range("postOrderVeriGetir():agac yok!");
	}
}
void Agac::postOrderVeriGetir(AgacDugum* dugum,Dizi* dizi)
{
	if(dugum)
	{		
		if(dugum->sol)
		{
			postOrderVeriGetir(dugum->sol,dizi);
		}
		if(dugum->sag)
		{
			postOrderVeriGetir(dugum->sag,dizi);
		}	
		dizi->ekle(dugum->veri);
	}
}

int Agac::yukseklikBul(AgacDugum* dugum)
{
	if(dugum)
	{
		return 1+max(yukseklikBul(dugum->sol),yukseklikBul(dugum->sag));
	}
	else
	{
		return -1;
	}
}
int Agac::yukseklikBul()
{
	if(kok)
	{
		return yukseklikBul(kok);	
	}
	else
	{
		throw out_of_range("yukseklikBul():agac yok!");
	}
}
int Agac::dugumlerToplamiBul(AgacDugum* dugum)
{
	if(dugum)
	{
		Dizi* dizi = postOrderVeriGetir();
		int toplam = dizi->diziElemanlariToplami();
		return toplam;
	}
	else
	{
		throw out_of_range("dugumlerToplamiBul():agac yok!");
	}
}
int Agac::dugumlerToplamiBul()
{
	dugumlerToplamiBul(kok);
}