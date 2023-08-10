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
#include "AgacDugum.hpp"
#include <iostream>
using namespace std;

AgacDugum::AgacDugum(int veri)
{
	this->veri = veri;
	sag = 0;
	sol = 0;
}
AgacDugum::~AgacDugum()
{
}