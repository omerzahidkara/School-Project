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
#include "Yigit.hpp"
#include <iostream>

using namespace std;

Yigit::Yigit()
{
	top = 0;
	veriSayisi = 0;
}
Yigit::~Yigit()
{
	if(veriSayisi > 0)
	{
		while(veriSayisi >= 0)
		{
			Pop();
		}
	}
}
void Yigit::Push(int veri)
{
	YigitDugum* dugum = new YigitDugum(veri);
	if(top != nullptr)
		dugum->ileri = top;
	
	top = dugum;
	veriSayisi++;	
}
void Yigit::Pop()
{
	if(veriSayisi > 0)
	{
		YigitDugum* silinecek = top;
		top = top->ileri;
		delete silinecek;
		veriSayisi--;
	}	
}
int Yigit::Peek()
{
	if(veriSayisi > 0)
	{
		return top->veri;
	}
	else
	{
		throw out_of_range("Yigin bos");
	}	
}