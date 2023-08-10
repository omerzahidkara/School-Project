#ifndef IslemYonetici_hpp
#define IslemYonetici_hpp
#include "Agac.hpp"
#include "Yigit.hpp"
#include <iostream>
#include <string>
using namespace std;

class IslemYonetici
{
	private:
		int dosyadakiSatirSayisi;
		int dosyadakiSatirBoyutu;		
		Yigit** listeY;
		Agac** listeA;
		int agaclardaEnUzunVerisiGetir(int kacAgac);
		void agaciYazdir(Agac* agac);
		int* stringToInt(string dizi);
		bool ciftMi(int sayi);
		void satirSayisiniBul();
		void YigitAgacIslemiYapVeYazdir(int* satir,int boyut);									
		void yigitlariAlAgaclariVer(int kacYigit);
		void agaclariTemizle(int kacAgac);
		bool yigitOlusturmaDonguBelirteci(int sayi,int sonrakiSayi);		
	public:
		IslemYonetici();
		~IslemYonetici();	
		int getSatirSayisi();
		int getSatirBoyutu();
		void setSatirBoyutu(int sayi);
		void setSatirSayisi(int sayi);
		void OkuVeYazdir();		
};

#endif