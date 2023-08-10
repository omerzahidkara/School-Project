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
#include "Dizi.hpp"
#include <iostream>
using namespace std;

Dizi::Dizi()
{
	elemanSayisi = 0;
	diziBoyutu = 12;
	diziCekirdek = new int[diziBoyutu];	
}
Dizi::~Dizi()
{
	if(diziCekirdek != nullptr)
	{
		delete[] diziCekirdek;
	}
}
int Dizi::diziElemanlariToplami()
{
	if(!bosMu())
	{
		int toplam = 0;
		for(int indeks = 0; indeks<elemanSayisi; indeks++)
		{
			toplam += diziCekirdek[indeks];
		}
		return toplam;
	}
	return 0;
}
int Dizi::ekle(int deger)
{
	if(doluMu())
	{
		genislet();
	}
	diziCekirdek[elemanSayisi] = deger;
	elemanSayisi++;
}
bool Dizi::bosMu()
{
	if(diziCekirdek != nullptr)
	{
		return elemanSayisi == 0;
	}	
}
bool Dizi::doluMu()
{
	if(diziCekirdek != nullptr)
	{
		return elemanSayisi == diziBoyutu;
	}	
}
void Dizi::genislet()
{
	diziBoyutu += 12;
	int* kopya = new int[diziBoyutu];	
	for(int i = 0; i<elemanSayisi;i++)
	{
		kopya[i] = diziCekirdek[i];
	}
	delete[] diziCekirdek;
	diziCekirdek = kopya;
}
void Dizi::sonElemanSil()
{
	if(!bosMu())
	{
		elemanSayisi--;
	}
	else
	{
		throw out_of_range("sonElemanSil()dizi yok veya bos!");
	}	
}
void Dizi::guncelle(int indeks,int deger)
{
	if(diziBoyutu > indeks && indeks >= 0)
	{
		diziCekirdek[indeks] = deger;
	}
}
int Dizi::getirSon()
{
	if(!bosMu())
	{
		return diziCekirdek[elemanSayisi-1];
	}
	else
	{
		throw out_of_range("getirSon():dizi yok veya bos!");
	}
}
int Dizi::getirIndeksle(int indeks)
{
	if(diziBoyutu > indeks && indeks >= 0)
	{
		return diziCekirdek[indeks];
	}
	else
	{
		throw out_of_range("getirIndeksle():eleman yok!");
	}
}
int* Dizi::diziGetir()
{
	if(diziCekirdek != nullptr)
	{
		return diziCekirdek;
	}
	else
	{
		throw out_of_range("diziGetir():dizi yok!");
	}
}