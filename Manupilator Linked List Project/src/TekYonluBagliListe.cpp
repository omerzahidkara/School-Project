/** 
* @file TekYonluBagliListe.cpp
* @description Icerisinde satır satır iki basamaklı sayilari tutan bir txt dosyasini okur.
Bir adet bagli liste yapar ve bu ana bagli listenin dugumleri iki adet farkli bagli liste tutar.
Ana bagli listenin her dugumu txt dosyasindaki kacinci dugum olduguna gore ilgili satirdan sayilari gosterdigi 2 adet bagli listeye belirli bir kurala gore verir.
Kural yukari adli bagli listeye onlar basamaklari asagi adli bagli listeye ise birler basamaklari gonderilmesi seklindedir.
Kac adet satir varsa o kadar ana dugum olusur ve sayilari manupile ederek diger bagli liste dugumlerine yerlestirir.
Bu asamadan sonra kulalnicidan ust bagli listeler icin bir konum-indeks bilgisi ve alt icin bir konum bilgisi istenir.
Bu bagli listeler ana dugumde yer degistirilir.
En son asamada ise ust bagli listelerdeki her satirin sutun indekslerindeki sayilarin ortalamalari alinir ve kendi iclerinde toplanir.
Cikan iki degerden ust olan Ust alt olan Alt seklinde kullaniciya ondalikli olarak verilir ve program sonlanir. 
* @course 1B Birinci ogretim
* @assignment 1
* @date 23.07.2023
* @author Omer Zahid KARA/omer.kara7@ogr.sakarya.edu.tr   Hasan KOÇ/hasan.koc7@ogr.sakarya.edu.tr
*/
#include "TekYonluBagliListe.hpp"
#include <iostream>
using namespace std;


TekYonluBagliListe::TekYonluBagliListe()
{
	dugumSayisi = 0;
	bas = 0;
}	
TekYonluBagliListe::~TekYonluBagliListe()
{
	TekYonluBagliListeDugumu* gec = bas;
	while(gec !=0)
	{
		TekYonluBagliListeDugumu* sil = gec;
		gec = gec->sonraki;
		delete sil;
	}
}
void TekYonluBagliListe::setDugumSayisi(int sayisi)
{
	dugumSayisi = sayisi;
}
TekYonluBagliListeDugumu* TekYonluBagliListe::TekYonluBagliListeDugumGetir(int sira)
{
	TekYonluBagliListeDugumu* gec = bas;
	int sayac = 0;
	while(gec!=0)
	{
		if(sayac==sira)
		{
			return gec;
		}
		gec=gec->sonraki;
		sayac++;
	}
	return 0;
}
bool TekYonluBagliListe::DugumGecerliligiGetir(int siramiz)
{
	if(siramiz < dugumSayisi)
	{
		return true;
	}
	return false;
}
int TekYonluBagliListe::DugumVerisiGetir(int siramiz)
{
	TekYonluBagliListeDugumu* gecici = 0;
	int verimiz = 0;
	if(siramiz < dugumSayisi)
	{
		gecici = TekYonluBagliListeDugumGetir(siramiz);
		verimiz = gecici->veri;
		return verimiz;
	}
	return 0;
} 
void TekYonluBagliListe::ListeyeDugumEkle(int verisi)
{
	TekYonluBagliListeDugumu* yeniDugum = new TekYonluBagliListeDugumu(verisi);
	if(bas == 0)
	{
		bas = yeniDugum;
	}
	else
	{
		TekYonluBagliListeDugumu* gezer = bas;
		while(gezer->sonraki !=0)
		{
			gezer = gezer->sonraki;		
		}
		gezer->sonraki = yeniDugum;
	}
	
}
