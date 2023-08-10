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
#include "IslemYonetici.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

IslemYonetici::IslemYonetici()
{
	dosyadakiSatirBoyutu = 0;
	dosyadakiSatirSayisi= 0;
	satirSayisiniBul();
	listeY = nullptr;
	listeA = nullptr;
}
IslemYonetici::~IslemYonetici()
{
		
}	
int IslemYonetici::getSatirSayisi()
{
	return dosyadakiSatirSayisi;
}
		
void IslemYonetici::setSatirSayisi(int sayi)
{
	dosyadakiSatirSayisi = sayi;
}
int IslemYonetici::getSatirBoyutu()
{
	return dosyadakiSatirBoyutu;
}
void IslemYonetici::setSatirBoyutu(int sayi)
{
	dosyadakiSatirBoyutu = sayi;
}
void IslemYonetici::satirSayisiniBul()
{
	string satir;
	ifstream dosyaNesnesi;
	dosyaNesnesi.open("Veri.txt");
	int sayac = 0;
	while(getline(dosyaNesnesi,satir))
	{				
		sayac++;
	}	
	setSatirSayisi(sayac);
	dosyaNesnesi.close();
}
bool IslemYonetici::ciftMi(int sayi)
{
	int kontrol = sayi%2; 
	if(kontrol == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IslemYonetici::yigitOlusturmaDonguBelirteci(int sayi,int sonrakiSayi)
{
	if(ciftMi(sonrakiSayi) && sonrakiSayi>sayi)
	{
		return false;
	}
	else if(ciftMi(sonrakiSayi) && sonrakiSayi<=sayi)
	{
		return true;
	}
	else if(!ciftMi(sonrakiSayi) && sonrakiSayi>=sayi)
	{
		return true;
	}
	else if(!ciftMi(sonrakiSayi) && sonrakiSayi<=sayi)
	{
		return true;
	}
}
void IslemYonetici::YigitAgacIslemiYapVeYazdir(int* satir,int boyut)
{	
	int satirBoyutu = boyut;
	int yigitSayisi = 0;
	int sayiSonraki = 0;
	int sayiAsil = 0;
	int sayiOncekii = 0;
	bool yigitSaymaKontrol = true;	
	for(int indEX = 0; indEX<satirBoyutu; indEX++)
	{		
		if(satirBoyutu == 1)
		{			
			yigitSayisi = 1;
			break;
		}
		sayiAsil = satir[indEX];
		if(indEX != satirBoyutu-1)
		{
			sayiSonraki = satir[indEX+1];
		}		
		if(yigitSaymaKontrol)
		{			
			yigitSayisi++;
		}
		if(indEX != satirBoyutu-1)
		{
			if(yigitOlusturmaDonguBelirteci(sayiAsil,sayiSonraki))
			{				
				yigitSaymaKontrol = false;
			}
			else if(!yigitOlusturmaDonguBelirteci(sayiAsil,sayiSonraki))
			{
				yigitSaymaKontrol = true;
			}
		}
	}
	if(listeY == nullptr)
	{			
		listeY = new Yigit*[yigitSayisi];	
	}
	else
	{
		return;
	}
	int sayi = 0;
	int sonrakiSayi = 0;
	int kullanilanDiziBoyutu = 0;
	bool yigitKontrol = true;
	Yigit* yeniYigit = 0;
	int yigitListeIND = -1;
	int oncekiSayi = 0;
	for(int ind = 0; ind<satirBoyutu; ind++)
	{
		if(satirBoyutu == 1)
		{
			yeniYigit = new Yigit();
			yeniYigit->Push(satir[0]);
			listeY[0] = yeniYigit;
			break;
		}
		sayi = satir[ind];
		if(ind != satirBoyutu-1)
		{
			sonrakiSayi = satir[ind+1];
		}		
		if(yigitKontrol)
		{
			yeniYigit = new Yigit();yigitListeIND++;	
		}
		if(ind != satirBoyutu-1)
		{
			if(yigitOlusturmaDonguBelirteci(sayi,sonrakiSayi))
			{
				yeniYigit->Push(sayi);
				yigitKontrol = false;
			}
			else if(!yigitOlusturmaDonguBelirteci(sayi,sonrakiSayi))
			{
				yeniYigit->Push(sayi);
				yigitKontrol = true;listeY[yigitListeIND] = yeniYigit;
			}
		}
		else
		{
			yeniYigit->Push(sayi);			
			yigitKontrol = false;listeY[yigitListeIND] = yeniYigit;				
		}		
	}			
	delete[] satir;
	int enUzunAgacYuksekligi = 0;
	Agac* yazilacakAgac = 0;
	Agac* karsilastirilanAgac = 0;		
	yigitlariAlAgaclariVer(yigitSayisi);	
	enUzunAgacYuksekligi = agaclardaEnUzunVerisiGetir(yigitSayisi);
	yazilacakAgac = listeA[0];
	int enBuyukAgacDegeri = yazilacakAgac->dugumlerToplamiBul();
	for(int sayacA = 1;sayacA<yigitSayisi;sayacA++)
	{
		karsilastirilanAgac = listeA[sayacA];
		if(karsilastirilanAgac->yukseklikBul() == enUzunAgacYuksekligi)
		{
			if(yazilacakAgac->yukseklikBul() == enUzunAgacYuksekligi)
			{
				if(karsilastirilanAgac->dugumlerToplamiBul() > enBuyukAgacDegeri)
				{
					yazilacakAgac = karsilastirilanAgac;
					enBuyukAgacDegeri = yazilacakAgac->dugumlerToplamiBul();
				}
			}
			else
			{
				yazilacakAgac = karsilastirilanAgac;
				enBuyukAgacDegeri = yazilacakAgac->dugumlerToplamiBul();
			}
		}
	}	
	agaciYazdir(yazilacakAgac);
	agaclariTemizle(yigitSayisi);
}
void IslemYonetici::yigitlariAlAgaclariVer(int kacYigit)
{
	int alinanSayi = 0;
	Yigit* kullanilanYigit = 0;	
	listeA = new Agac*[kacYigit];
	int donguLimit = 0;
	for(int index = 0;index<kacYigit;index++)
	{
		kullanilanYigit = listeY[index];
		Agac* yeniAgac = new Agac();
		donguLimit = kullanilanYigit->veriSayisi;
		for(int sayaci = 0;sayaci<donguLimit;sayaci++)
		{
			try
			{
				alinanSayi = kullanilanYigit->Peek();
			}
			catch(out_of_range& e)
			{
				cout << e.what()<<endl;				
			}
			kullanilanYigit->Pop();
			yeniAgac->Ekle(alinanSayi);
		}			
		listeA[index] = yeniAgac; 
		delete kullanilanYigit;
	}
	delete[] listeY;
	listeY = nullptr;	
}
void IslemYonetici::agaclariTemizle(int kacAgac)
{
	for(int index = 0;index<kacAgac;index++)
	{
		if(listeA[index] != nullptr)
		{
			delete listeA[index];
			listeA[index] = nullptr;
		}				
	}
	delete[] listeA;
	listeA = nullptr;
}
void IslemYonetici::agaciYazdir(Agac* agac)
{
	int deger = 0;
	Dizi* yazinDizisiD = 0;
	int* yazinDizisi = 0;
	char karakter = '*';
	int agacDugumSayisi = agac->getDugumSayisi();
	try
	{
		yazinDizisiD = agac->postOrderVeriGetir();
		yazinDizisi = yazinDizisiD->diziGetir();
	}
	catch(out_of_range& e)
	{
		cout << e.what()<<endl;
		return;
	}
	for(int index = 0;index<agacDugumSayisi;index++)
	{
		deger = yazinDizisi[index];
		karakter = deger;
		cout << karakter << " ";
	}
	cout << endl;
	delete yazinDizisiD;
}
int IslemYonetici::agaclardaEnUzunVerisiGetir(int kacAgac)
{	
	int* uzunlukListesi= new int[kacAgac];
	Agac* kullanilanAgac = 0;
	for(int i = 0;i<kacAgac;i++)
	{
		kullanilanAgac = listeA[i];		
		try
		{
			uzunlukListesi[i] = kullanilanAgac->yukseklikBul();
		}
		catch(out_of_range& e)
		{
			cout << e.what()<<endl;
		}	
	}
	int enBuyuk = uzunlukListesi[0];
	for (int index = 1; index < kacAgac; index++) 
	{
		if (uzunlukListesi[index] > enBuyuk) 
		{
            enBuyuk = uzunlukListesi[index];
        }
    }
	delete [] uzunlukListesi;
	return enBuyuk;
}

int* IslemYonetici::stringToInt(string dizi)
{
	int* diziInt = new int[dizi.length()];
	stringstream satirdakiVeri(dizi);
	int alinanSayi = 0;
	int sayac = 0;
	while(satirdakiVeri >> alinanSayi)
	{
		diziInt [sayac] = alinanSayi;
		sayac++;
	}
	setSatirBoyutu(sayac);
	return diziInt;
}
void IslemYonetici::OkuVeYazdir()
{
	int donguIndex = getSatirSayisi();	
	string satir;
	ifstream dosyaAnaNesnesi;
	int* satirInt = nullptr;
	int diziBoyutu = 0;
	dosyaAnaNesnesi.open("Veri.txt");
	for(int i=0; i<donguIndex; i++)
	{
		getline(dosyaAnaNesnesi,satir);		
		satirInt = stringToInt(satir);	
		YigitAgacIslemiYapVeYazdir(satirInt,dosyadakiSatirBoyutu);			
		satirInt = nullptr;
		Sleep (10);	
	}
	dosyaAnaNesnesi.close();	
}