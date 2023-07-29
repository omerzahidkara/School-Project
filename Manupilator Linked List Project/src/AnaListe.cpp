/** 
* @file AnaListe.cpp
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
AnaListe::AnaListe()
{
	basDugum = 0;
	SatirSayisiniBul();
	satirlarinHepsi = new int*[anaDugumSayisi];
	MatrisOlustur();
	AnaListeyiOlustur();
	dugumlerinMiktarBilgileri = 0;
}	
AnaListe::~AnaListe()
{
	for(int s = 0;s<anaDugumSayisi; s++)
	{
		delete[] satirlarinHepsi[s];
	}		
	delete[] dugumlerinMiktarBilgileri;
	AnaListeDugum* gec = basDugum;
	while(gec !=0)
	{
		AnaListeDugum* sil = gec;
		gec = gec->sonraki;
		delete sil;
	}
}
		
AnaListeDugum* AnaListe::AnaListeDugumGetir(int sira)
{
	AnaListeDugum* gec = basDugum;
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
		
void AnaListe::AnaListeyiBosOlustur()
{
	int sayacu = anaDugumSayisi;
	while(sayacu != 0)
	{
		AnaListeDugum* yeniAnaDugum = new AnaListeDugum();
		if(basDugum == 0)
		{
			basDugum = yeniAnaDugum ;								
		}
		else
		{
			AnaListeDugum* gezer = basDugum;
			while(gezer->sonraki !=0)
			{
				gezer = gezer->sonraki;
			}
			gezer->sonraki = yeniAnaDugum;
		}
		sayacu--;
	}

}
		
int** AnaListe::getSayilarinHepsi()
{
	return satirlarinHepsi;
}
		
int AnaListe::getAnaDugumSayisi()
{
	return anaDugumSayisi;
}
		
void AnaListe::setAnaDugumSayisi(int sayi)
{
	anaDugumSayisi = sayi;
}
		
void AnaListe::SatirSayisiniBul()
{
	string satir;
	ifstream dosyaNesnesi;
	dosyaNesnesi.open("Sayilar.txt");
	int sayac = 0;
	while(getline(dosyaNesnesi,satir))
	{				
		sayac++;
	}
	setAnaDugumSayisi(sayac);
	dosyaNesnesi.close();
}
		
int AnaListe::getSatirDakiVeriSayisi(string satir)
{
	int sayac = 0;
	int alinanSayi = 0;
	stringstream satirdakiVeri(satir);
	while(satirdakiVeri >> alinanSayi)
	{
		sayac++;	
	}
	return sayac;
}
		
void AnaListe::MatrisOlustur()
{
	string satirString;
	ifstream dosyaNesnesi;
	dosyaNesnesi.open("Sayilar.txt");
	int genisSayac = 0;
	int satirdakiSayiMiktari = 0;
	dugumlerinMiktarBilgileri = new int[anaDugumSayisi];
	while(getline(dosyaNesnesi,satirString))
	{	
		int icSayac = 0;
		satirdakiSayiMiktari = getSatirDakiVeriSayisi(satirString);
		int* satir = new int[satirdakiSayiMiktari]; 
		int alinanSayi = 0;
		stringstream satirdakiVeri(satirString);
		while(satirdakiVeri >> alinanSayi)
		{
			satir [icSayac] = alinanSayi;
			icSayac++;			
		}
		dugumlerinMiktarBilgileri[genisSayac] = icSayac;
		if(genisSayac == 0)
		{
			enKalabalikDugumedekiSatirSayisi = icSayac;
		}
		if(genisSayac != 0)
		{
			if(icSayac >= enKalabalikDugumedekiSatirSayisi)
			{
				enKalabalikDugumedekiSatirSayisi = icSayac;
			}
		}
		satirlarinHepsi[genisSayac] = satir;
		genisSayac++;
	}
	dosyaNesnesi.close();			
}
TekYonluBagliListe* AnaListe::UstListeyiOlustur(int dugumSirasiUst) //onlar basamakalari
{
	TekYonluBagliListe* yeniListeUst = new TekYonluBagliListe();			
	int donguBelirteciUst = dugumlerinMiktarBilgileri[dugumSirasiUst];
	yeniListeUst->setDugumSayisi(donguBelirteciUst);
	int sayiBirlerUst = 0;
	int sayiUst = 0;
	for(int iUst = 0; iUst<donguBelirteciUst; iUst++)
	{
		sayiUst = satirlarinHepsi[dugumSirasiUst][iUst];
		sayiBirlerUst = sayiUst%10;
		sayiUst = sayiUst-sayiBirlerUst;
		sayiUst = sayiUst/10;
		yeniListeUst->ListeyeDugumEkle(sayiUst);
	}
	return yeniListeUst;
}
TekYonluBagliListe* AnaListe::AltListeyiOlustur(int dugumSirasi) // birler basamaklari
{
	TekYonluBagliListe* yeniListe = new TekYonluBagliListe();			
	int donguBelirteci = dugumlerinMiktarBilgileri[dugumSirasi];
	yeniListe->setDugumSayisi(donguBelirteci);
	int sayiBirler = 0;
	for(int i = 0; i<donguBelirteci; i++)
	{
		sayiBirler = satirlarinHepsi[dugumSirasi][i];
		sayiBirler = sayiBirler%10;
		yeniListe->ListeyeDugumEkle(sayiBirler);
	}
	return yeniListe;
}
void AnaListe::AnaListeyiOlustur()
{
	AnaListeyiBosOlustur();
	AnaListeDugum* temsilci = 0;
	for(int f = 0; f<anaDugumSayisi; f++)
	{
		temsilci = AnaListeDugumGetir(f);
		temsilci->ustListe = UstListeyiOlustur(f);
		temsilci->altListe = AltListeyiOlustur(f);
	}
}
void AnaListe::Oku()
{
	TekYonluBagliListeDugumu* tyTemsilciUst = 0;
	TekYonluBagliListeDugumu* tyTemsilciAlt = 0;
	AnaListeDugum* aTemsilci = 0;
	for(int i = 0; i<anaDugumSayisi; i++)
	{
		aTemsilci = AnaListeDugumGetir(i);
		for(int y = 0; y<dugumlerinMiktarBilgileri[i]; y++)
		{
			tyTemsilciUst = aTemsilci->ustListe->TekYonluBagliListeDugumGetir(y);
			tyTemsilciAlt = aTemsilci->altListe->TekYonluBagliListeDugumGetir(y);
			cout << i+1 << " siradaki ana dugumun ust-alt verileri: " << tyTemsilciUst->veri << ":" << tyTemsilciAlt->veri << endl;
		}
		cout <<	endl;	
	}
}
void AnaListe::KullaniciIslemYerDegisme()
{
	int konumA = 0;
	int konumB = 0;
	cout << "Mevcut konum sayisi: " << anaDugumSayisi << endl << endl;
	AnaListeDugum* aTemsilci = 0;
	AnaListeDugum* bTemsilci = 0;
	TekYonluBagliListe* tyTemsilciUst = 0;
	TekYonluBagliListe* tyTemsilciAlt = 0;
	TekYonluBagliListe* tutucuP = 0;
	cout << "Konum A: " ;
	cin >> konumA;
	cout<< endl << "Konum B: " ;
	cin >> konumB;
	aTemsilci = AnaListeDugumGetir(konumA);
	bTemsilci = AnaListeDugumGetir(konumB);
	tyTemsilciUst = aTemsilci->ustListe;
	tyTemsilciAlt = bTemsilci->altListe;
	tutucuP = bTemsilci->altListe;
	bTemsilci->altListe = tyTemsilciUst;
	aTemsilci->ustListe = tutucuP;
	cout<< endl;
}
double AnaListe::UstSatirOrtalamaBul(int satirSirasi)
{
	double satirOrt = 0;
	int alinanSayi = 0;
	int bolen = 0;
	bool gecerlilik = true;
	AnaListeDugum* gezer = basDugum;
	while(gezer != 0)
	{		
		alinanSayi = gezer->ustListe->DugumVerisiGetir(satirSirasi);
		gecerlilik = gezer->ustListe->DugumGecerliligiGetir(satirSirasi);
		satirOrt += alinanSayi;
		if(gecerlilik)
		{
			bolen++;
		}
		gezer = gezer->sonraki;
	}
	return satirOrt/bolen;
}
double AnaListe::AltSatirOrtalamaBul(int satirSirasi)
{
	double satirOrt = 0;
	int alinanSayi = 0;
	int bolen = 0;
	bool gecerlilik = true;
	AnaListeDugum* gezer = basDugum;
	while(gezer != 0)
	{	
		alinanSayi = gezer->altListe->DugumVerisiGetir(satirSirasi);
		gecerlilik = gezer->altListe->DugumGecerliligiGetir(satirSirasi);
		satirOrt += alinanSayi;
		if(gecerlilik)
		{
			bolen++;
		}
		gezer = gezer->sonraki;
	}
	return satirOrt/bolen;
}
double AnaListe::UstToplamlar()
{
	double ustToplami = 0;
	for(int r = 0; r<enKalabalikDugumedekiSatirSayisi; r++)
	{		
		ustToplami += UstSatirOrtalamaBul(r);
	}
	return ustToplami;
}
double AnaListe::AltToplamlar()
{
	double altToplami = 0;
	for(int r = 0; r<enKalabalikDugumedekiSatirSayisi; r++)
	{
		altToplami += AltSatirOrtalamaBul(r);
	}
	return altToplami;
}
void AnaListe::KullaniciIslemSon()
{
	KullaniciIslemYerDegisme();
	double ustToplam = UstToplamlar();
	double altToplam = AltToplamlar();
	cout << "Ust: " << ustToplam << endl;
	cout << "Alt: " << altToplam << endl;
}
int AnaListe::getEnKalabalikDugumedekiSatirSayisi()
{
	return enKalabalikDugumedekiSatirSayisi;
}
 

