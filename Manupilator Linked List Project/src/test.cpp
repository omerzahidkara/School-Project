/** 
* @file test.cpp
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
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "AnaListe.hpp"
using namespace std;
int main()
{	
	AnaListe* yeniListe = new AnaListe();
	yeniListe->KullaniciIslemSon();
	//yeniListe->Oku();
	//cout << yeniListe->getEnKalabalikDugumedekiSatirSayisi() << endl;
	//cout << yeniListe->getAnaDugumSayisi() << endl;
	system("PAUSE");
	delete yeniListe;
	return 0;
}