#include "OYUN.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>



Oyun oyunKur()//Oyun pointeri ile oyun structina erisim. Veriler alinir,semboller olusur,koloniler olusur ve baslangic yazdirilir. Fonksiyon gostericisi eslesmeleri yapilir.
{
	Oyun this;
	this = (Oyun)malloc(sizeof(struct OYUN));	
	
	this -> koloniVerileriAlGosterici = &koloniVerileriAl;				 //gosterici atamasi 1
	this -> koloniSayisiHesaplaGosterici = &koloniSayisiHesapla;		 //gosterici atamasi 2
	this -> koloniSembolleriOlusturGosterici = &koloniSembolleriOlustur; //gosterici atamasi 3
	this -> kolonileriOlusturGosterici = &kolonileriOlustur;			 //gosterici atamasi 4
	this -> turAtlat = &turYap;											 //gosterici atamasi 5
	this -> toString = &yazdir;											 //gosterici atamasi 6
	this -> oyunYokEtGosterici = &oyunYokEt;							 //gosterici atamasi 7
	
	this -> mevcutKoloniNufuslari = koloniVerileriAl();//Veriler alindi 
	this -> mevcutKoloniSayisi = koloniSayisiHesapla(this -> mevcutKoloniNufuslari);//Koloni sayisi hesaplandi
	this -> semboller = koloniSembolleriOlustur(this -> mevcutKoloniSayisi);  //Semboller olustu
	this -> mevcutKoloniler = kolonileriOlustur(this);//İlk koloniler olustu 
	this -> yenilmisKoloniSayisi = 0;
	return this;
}
int* koloniVerileriAl()//Kac adet sayi giriliecegi bilinmedigi icin dinamik bir yapi kullanildi. 
{	
	int kapasiteSatir = 30;
    char* satir = malloc(sizeof(char) * kapasiteSatir); 
    int karakterSayisi = 0;
    int karakter;
	printf("Nufuslari gir(x>0): ");
    while ((karakter = getchar()) != '\n') // Enter tusuna kadar karakter girisi saglanir.
	{
        if (karakterSayisi == kapasiteSatir)// Kapasiteye erisilirse bellek buyutulur. 
		{
            kapasiteSatir += 10;
            satir = realloc(satir, sizeof(char) * kapasiteSatir);
        }
        satir[karakterSayisi] = karakter;
        karakterSayisi++;
    }
    satir = realloc(satir, sizeof(char) * (karakterSayisi + 1));
    satir[karakterSayisi] = '\0';   
	int kapasiteInt = 10;
    int* diziInt = malloc(sizeof(int) * kapasiteInt); 
    int sayac = 0;
	char* elArabasi = strtok(satir, " "); 
    while (elArabasi != NULL) // stringden integer a donusum icin terim terim secilir.
	{
        diziInt[sayac] = atoi(elArabasi);
        sayac++;        
        if (sayac == kapasiteInt) 
		{
            kapasiteInt += 10;
            diziInt = realloc(diziInt, sizeof(int) * kapasiteInt);
        }        
        elArabasi = strtok(NULL, " ");
    }
	diziInt = realloc(diziInt, sizeof(int) * sayac +1);
	diziInt[sayac] = '\0';	
    return diziInt;// Nufuslar pointerla geri donderilir.
}
int koloniSayisiHesapla(int* nufusDizisi)// Nufus listesi alinir ve ayri bir pointer ile sayilir.
{
	int koloniSayisi = 0;
	int* sayiGezici = nufusDizisi; 
	while (*sayiGezici != 0)
	{
		sayiGezici++;
		koloniSayisi++;
	}
	return koloniSayisi;	
}
wchar_t* koloniSemboluUret(int uzunluk)// Koloniye atanacak sembolun kac karakter olacagi parametre olarak alinir. Bu yardimci fonksiyondur. Kac karakter olacagi belli bir sayiya erisildiginde artiyor.
{
	const wchar_t baslangic = 0x30;
    const int karakterSayisi = 43;
	int rastgeleSayi;
	wchar_t rastgeleKarakter;
	wchar_t* gonderilecek = malloc(sizeof(wchar_t)*(uzunluk+1));
	for(int c = 0; c < uzunluk; c++)
	{
		rastgeleSayi = rand() % karakterSayisi;
		rastgeleKarakter = (wchar_t)(baslangic + rastgeleSayi);
		gonderilecek[c] = rastgeleKarakter;
	}
	gonderilecek[uzunluk] = L'\0'; 
	return gonderilecek;
}
wchar_t** koloniSembolleriOlustur(int sayi)
{
	wchar_t** semboller = malloc(sizeof(wchar_t*)*sayi);
	int chMiktari = 1;
	semboller[0] = koloniSemboluUret(chMiktari);
	int kontrolcuSayac = 0;
	for(int o = 1; o< sayi; o++)// Daha onceden ayni sembol dizini kullanilmis mi diye kontrol edilir ve varsa özel olana kadar rastgele atama yapilir.
	{
		semboller[o] = koloniSemboluUret(chMiktari);
		kontrolcuSayac = 0;				
		while(kontrolcuSayac != o)
		{			
			if (wcscmp(semboller[o], semboller[kontrolcuSayac]) == 0)// Kontrol icin if blogu.
			{
				semboller[o] = L'\0';
				semboller[o] = koloniSemboluUret(chMiktari);
				kontrolcuSayac = -1;
			}			
			kontrolcuSayac++;
		}				
		if(o%42 == 0)// 42 kolonide bir sembollerin karakter sayisi artar. Cunku kullanilan sembol miktari bellidir. 
		{
			chMiktari++;
		}				
	}
	return semboller;
}
int ilkErzakAtamasi(int deger)// Erzak atamasi nufusun karesi kadar.
{
	return deger*deger;
}
//KOLONILERIN OLUSMASI***************************************************************************************************************
KoloniBakani kolonileriOlustur(const Oyun this)// İlk veri girisinden sonra koloniler sembol nufus ve erzaklariyla olusur ve saklanir.
{
	KoloniBakani gonderilecekKoloniler = (KoloniBakani)malloc(sizeof(Koloni)*this->mevcutKoloniSayisi);
	int gonderNufus ;
	wchar_t* gonderSembol;
	int gonderErzak;
	for(int donguIndeks = 0; donguIndeks<this -> mevcutKoloniSayisi; donguIndeks++)
	{		
		gonderNufus = this -> mevcutKoloniNufuslari[donguIndeks];
		gonderSembol = this -> semboller[donguIndeks];
		gonderErzak = ilkErzakAtamasi(gonderNufus);
		Koloni yeniKoloni = koloniOlustur(gonderNufus,gonderSembol,gonderErzak);
		gonderilecekKoloniler[donguIndeks] = yeniKoloni;
	}
	return gonderilecekKoloniler;
}
/* Bir turda ilk olarak erzak uretimi olur.
	Ikinci olarak erzak tuketimi olur.
	Ucuncu olarak populasyon artısı olur.
	En son savaslar olur.
	Her birinin sonuclari kolonilere aktarilir.
*/
void yokOlmusKolonileriSay(const Oyun this)
{
	int ezrak;
	int nuyfus;
	int saydirmac = 0;
	for(int ruh = 0; ruh<this->mevcutKoloniSayisi; ruh++)
	{
		ezrak = this->mevcutKoloniler[ruh] -> erzakStogu;
		nuyfus = this->mevcutKoloniler[ruh] -> nufus;
		if(ezrak == 0 && nuyfus == 0)
		{
			saydirmac++;
		}
	}
	this->yenilmisKoloniSayisi = saydirmac;
}
void turYap(const Oyun this,int turSayisiDurumu)
{
	int nufusSayisi = this -> mevcutKoloniSayisi;
	int nufusKontrol;
	int mevcutErzak;
	int harcanacakErzak;
	int kalanErzak;
	//ERZAK URETIMI
	for(int islemSayac = 0; islemSayac < nufusSayisi; islemSayac++)// nufusa gore koloniler tarim hayvancilik veya avcilik yaparak uretimlerini yapar
	{
		nufusKontrol = this -> mevcutKoloniler[islemSayac]-> nufus;
		if(nufusKontrol <= 0)//nufus varligi kontrolu
		{
			this -> mevcutKoloniler[islemSayac] -> erzakStogu = 0;
			this -> mevcutKoloniler[islemSayac] -> nufus = 0;
			this -> mevcutKoloniler[islemSayac] -> kazanmaSayisi = 0;
			this -> mevcutKoloniler[islemSayac] -> kaybetmeSayisi = 0;
			continue;
		}
		else if(nufusKontrol>0 && nufusKontrol<20)
		{
			this -> mevcutKoloniler[islemSayac] -> avciPtr = avYap();
			this -> mevcutKoloniler[islemSayac] -> erzakStogu += this -> mevcutKoloniler[islemSayac] -> avciPtr -> mizrak -> uret();
			this -> mevcutKoloniler[islemSayac] -> avciPtr -> uretimiTerkEtAvcilik(this -> mevcutKoloniler[islemSayac]-> avciPtr);
		}
		else if(nufusKontrol >= 20 && nufusKontrol<100)
		{
			this -> mevcutKoloniler[islemSayac] -> cobanPtr = hayvancilikYap();
			this -> mevcutKoloniler[islemSayac] -> erzakStogu += this -> mevcutKoloniler[islemSayac] -> cobanPtr -> koyun -> uret();
			this -> mevcutKoloniler[islemSayac] -> cobanPtr -> uretimiTerkEtHayvancilik(this -> mevcutKoloniler[islemSayac] -> cobanPtr);  		
		}
		else if(nufusKontrol >= 100)
		{
			if(turSayisiDurumu%10 == 0)
			{
				this -> mevcutKoloniler[islemSayac] -> erzakStogu += 1;
			}
			this -> mevcutKoloniler[islemSayac] -> ciftciPtr = tarimYap();
			this -> mevcutKoloniler[islemSayac] -> erzakStogu += this -> mevcutKoloniler[islemSayac] -> ciftciPtr -> orak -> uret();
			this -> mevcutKoloniler[islemSayac] -> ciftciPtr -> uretimiTerkEtTarim(this -> mevcutKoloniler[islemSayac] -> ciftciPtr); 		
		}
	}
	nufusKontrol = 0;
	//ERZAK TUKETIMI
	for(int islemSayacTuketim = 0; islemSayacTuketim < nufusSayisi; islemSayacTuketim++)//her tur her koloni nufusunun iki kati kadar erzak harcarlar
	{
		nufusKontrol = this -> mevcutKoloniler[islemSayacTuketim] -> nufus;
		if(nufusKontrol <= 0)//nufusu olmayanlara islem yapilmaz
		{
			this -> mevcutKoloniler[islemSayacTuketim] -> erzakStogu = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> nufus = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> kazanmaSayisi = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> kaybetmeSayisi = 0;
			continue; 
		}
		mevcutErzak = this -> mevcutKoloniler[islemSayacTuketim] -> erzakStogu;
		harcanacakErzak = nufusKontrol*2;
		kalanErzak = mevcutErzak-harcanacakErzak;
		if(mevcutErzak <= 0)//erzagi olmayanlara islem yapilmaz
		{
			this -> mevcutKoloniler[islemSayacTuketim] -> erzakStogu = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> nufus = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> kazanmaSayisi = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> kaybetmeSayisi = 0;
			continue; 
		}
		if(kalanErzak <= 1)//erzagi bitenler elenir
		{
			this -> mevcutKoloniler[islemSayacTuketim] -> erzakStogu = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> nufus = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> kazanmaSayisi = 0;
			this -> mevcutKoloniler[islemSayacTuketim] -> kaybetmeSayisi = 0;
		}
		else// erzagi kalanlarin tuketimi yapilir ve yeni erzak miktari guncellenir.
		{
			this -> mevcutKoloniler[islemSayacTuketim] -> erzakStogu = kalanErzak;
		}		
	}
	//NUFUS ATRISI
	int nufusArtisi = 0;
	int uretimcilerinNufuslari = 0;
	for(int islemSayacNufusArtis = 0; islemSayacNufusArtis < nufusSayisi; islemSayacNufusArtis++)//aktif kolonier tur basi populasyonlarının yuzde 20 si kadar nufus artisi yasarlar
	{
		uretimcilerinNufuslari = this -> mevcutKoloniler[islemSayacNufusArtis] -> nufus;
		if(uretimcilerinNufuslari > 0)//nufusu olmayanlarin nufusu artmaz
		{
			nufusArtisi = (uretimcilerinNufuslari*20)/100;
			this -> mevcutKoloniler[islemSayacNufusArtis] -> nufus += nufusArtisi;		 
		}		
	}
	//SAVASLAR
	int dostNufus;
	int dusmanNufus;
	int dostErzak;
	int dusmanErzak;
	int birBucukKati;
	int birBucukKatiDusman;
	int erzakKontrolcusu;
	int savasGucu1;
	int savasGucu2;
	int haracOrani;
	int populasyonKaybi;
	int populasyonYeni;
	int erzakKontrolcusuHarac;
	int erzakHaracEdilen;
	int erzakYenilen;
	for(int dost = 0; dost < nufusSayisi; dost++)
	{
		dostNufus = this -> mevcutKoloniler[dost] -> nufus;
		dostErzak = this -> mevcutKoloniler[dost] -> erzakStogu;
		if(dostNufus <= 0 || dostErzak <= 0)//nufusu olmayanlar savasamaz
		{
			continue; 
		}
		for(int dusman = dost+1; dusman < nufusSayisi; dusman++)
		{
			dusmanNufus = this -> mevcutKoloniler[dusman] -> nufus;
			dusmanErzak = this -> mevcutKoloniler[dusman] -> erzakStogu;
			birBucukKati = (dostNufus*150)/100;
			birBucukKatiDusman = (dusmanNufus*150)/100;
			if(dusman == nufusSayisi)
			{
				continue;
			}
			if(dusmanNufus <= 0 || dusmanErzak <= 0)//nufusu olmayanlar savasamaz
			{
				continue; 
			}
			//Durum 1 nufuslar esitken gerceklesen savas
			if(dusmanNufus == dostNufus)
			{
				this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
				savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();// toplu hucum gucu alir
				this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
				
				this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
				savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();// toplu hucum gucu alir
				this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);//
				
				erzakKontrolcusu = this -> mevcutKoloniler[dost] -> erzakStogu;
				if((dostNufus*4 > erzakKontrolcusu) && (dostNufus > 10))// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dost] -> casusPtr = sabotajYap();
					savasGucu1 = this -> mevcutKoloniler[dost] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dost] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dost] -> casusPtr);
				}
				erzakKontrolcusu = this -> mevcutKoloniler[dusman] -> erzakStogu;
				if((dusmanNufus*4 > erzakKontrolcusu) && (dusmanNufus > 10))// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dusman] -> casusPtr = sabotajYap();
					savasGucu2 = this -> mevcutKoloniler[dusman] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dusman] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dusman] -> casusPtr);
				}
				if(savasGucu1 == savasGucu2)//gucler esit gelirse surekli hucum yaparlar
				{
					while(savasGucu1 == savasGucu2) 
					{
						this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
						savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
						savasGucu1 = 450+rand()%550;
				
						this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
						savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);
					}
				}	
				if(savasGucu1 > savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu1-savasGucu2)*100)/1000;
					populasyonKaybi = (dusmanNufus*haracOrani)/100;
					populasyonYeni = dusmanNufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dusmanErzak*haracOrani)/100;
					erzakYenilen = dusmanErzak-erzakKontrolcusuHarac;
					if((populasyonYeni <= 1) || (erzakYenilen <= 1))//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dusman] -> erzakStogu = 0;
						this -> mevcutKoloniler[dusman] -> nufus = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dusman] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dusman] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dost] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;	
					}
				}		
				else if(savasGucu1 < savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu2-savasGucu1)*100)/1000;
					populasyonKaybi = (dostNufus*haracOrani)/100;
					populasyonYeni = dostNufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dostErzak*haracOrani)/100;
					erzakYenilen = dostErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dost] -> erzakStogu = 0;
						this -> mevcutKoloniler[dost] -> nufus = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dost] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dost] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dusman] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
				}
			}
			//Durum 2 kucuk-orta
			else if((dusmanNufus > dostNufus) && (dusmanNufus < birBucukKati)) 
			{
				this -> mevcutKoloniler[dost] -> atliPtr = vurkacYap();
				savasGucu1 = this -> mevcutKoloniler[dost] -> atliPtr -> olayVurkac -> savas();
				this -> mevcutKoloniler[dost] -> atliPtr -> taktigiTerkEtVurkac(this -> mevcutKoloniler[dost] -> atliPtr);
				
				this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
				savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();
				this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);
				
				erzakKontrolcusu = this -> mevcutKoloniler[dost] -> erzakStogu;
				if(dostNufus*4 > erzakKontrolcusu && dostNufus > 10)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dost] -> casusPtr = sabotajYap();
					savasGucu1 = this -> mevcutKoloniler[dost] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dost] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dost] -> casusPtr);
				}
				erzakKontrolcusu = this -> mevcutKoloniler[dusman] -> erzakStogu;
				if(dusmanNufus*4 > erzakKontrolcusu && dusmanNufus > 10)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dusman] -> casusPtr = sabotajYap();
					savasGucu2 = this -> mevcutKoloniler[dusman] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dusman] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dusman] -> casusPtr);
				}
				if(savasGucu1 == savasGucu2)//gucler esit gelirse surekli hucum yaparlar
				{
					while(savasGucu1 == savasGucu2) 
					{
						this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
						savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
				
						this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
						savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);
						savasGucu2 += 50; //kalabalik olanin kazanma sansi yuksektir
					}
				}	
				if(savasGucu1 > savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu1-savasGucu2)*100)/1000;
					populasyonKaybi = (dusmanNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dusman] -> nufus - populasyonKaybi;			
					erzakKontrolcusuHarac = (dusmanErzak*haracOrani)/100;
					erzakYenilen = dusmanErzak -erzakKontrolcusuHarac;	
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dusman] -> erzakStogu = 0;
						this -> mevcutKoloniler[dusman] -> nufus = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;
						this -> yenilmisKoloniSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dusman] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dusman] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dost] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;						
					}
				}		
				else if(savasGucu1 < savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu2-savasGucu1)*100)/1000;
					populasyonKaybi = (dostNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dost] -> nufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dostErzak*haracOrani)/100;
					erzakYenilen = dostErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dost] -> erzakStogu = 0;
						this -> mevcutKoloniler[dost] -> nufus = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dost] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dost] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dusman] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
				}			
			}
			//Durum 3 kucuk-buyuk
			else if(dusmanNufus > dostNufus && dusmanNufus > birBucukKati) //ikinci nufus buyuk iken ilk kontrol edilen kucuk tespiti
			{
				this -> mevcutKoloniler[dost] -> cetePtr = pusuYap();
				savasGucu1 = this -> mevcutKoloniler[dost] -> cetePtr -> olayPusu -> savas();
				this -> mevcutKoloniler[dost] -> cetePtr -> taktigiTerkEtPusu(this -> mevcutKoloniler[dost] -> cetePtr);
				
				this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
				savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();
				this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);
				
				erzakKontrolcusu = this -> mevcutKoloniler[dost] -> erzakStogu;
				if(dostNufus*4 > erzakKontrolcusu)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dost] -> casusPtr = sabotajYap();
					savasGucu1 = this -> mevcutKoloniler[dost] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dost] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dost] -> casusPtr);
				}
				erzakKontrolcusu = this -> mevcutKoloniler[dusman] -> erzakStogu;
				if(dusmanNufus*4 > erzakKontrolcusu)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dusman] -> casusPtr = sabotajYap();
					savasGucu2 = this -> mevcutKoloniler[dusman] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dusman] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dusman] -> casusPtr);
				}
				if(savasGucu1 == savasGucu2)//gucler esit gelirse surekli hucum yaparlar
				{
					while(savasGucu1 == savasGucu2) 
					{
						this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
						savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
				
						this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
						savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);
						savasGucu2 += 50; //kalabalik olanin kazanma sansi yuksektir
					}
				}	
				if(savasGucu1 > savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu1-savasGucu2)*100)/1000;
					populasyonKaybi = (dusmanNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dusman] -> nufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dusmanErzak*haracOrani)/100;
					erzakYenilen = dusmanErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dusman] -> erzakStogu = 0;
						this -> mevcutKoloniler[dusman] -> nufus = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dusman] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dusman] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dost] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;	
					}
				}		
				else if(savasGucu1 < savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu2-savasGucu1)*100)/1000;
					populasyonKaybi = (dostNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dost] -> nufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dostErzak*haracOrani)/100;
					erzakYenilen = dostErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dost] -> erzakStogu = 0;
						this -> mevcutKoloniler[dost] -> nufus = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dost] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dost] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dusman] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
				}
			}
			//Durum 4 orta-kucuk
			else if((dostNufus > dusmanNufus)  &&  (dostNufus < birBucukKatiDusman)) 
			{
				this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
				savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();
				this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
				
				this -> mevcutKoloniler[dusman] -> atliPtr = vurkacYap();
				savasGucu2 = this -> mevcutKoloniler[dusman] -> atliPtr -> olayVurkac -> savas();
				this -> mevcutKoloniler[dusman] -> atliPtr -> taktigiTerkEtVurkac(this -> mevcutKoloniler[dusman] -> atliPtr);
				
				erzakKontrolcusu = this -> mevcutKoloniler[dost] -> erzakStogu;
				if(dostNufus*4 > erzakKontrolcusu && dostNufus > 10)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dost] -> casusPtr = sabotajYap();
					savasGucu1 = this -> mevcutKoloniler[dost] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dost] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dost] -> casusPtr);
				}
				erzakKontrolcusu = this -> mevcutKoloniler[dusman] -> erzakStogu;
				if(dusmanNufus*4 > erzakKontrolcusu && dusmanNufus > 10)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dusman] -> casusPtr = sabotajYap();
					savasGucu2 = this -> mevcutKoloniler[dusman] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dusman] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dusman] -> casusPtr);
				}
				if(savasGucu1 == savasGucu2)//gucler esit gelirse surekli hucum yaparlar
				{
					while(savasGucu1 == savasGucu2) 
					{
						this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
						savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
						savasGucu1 += 50; //kalabalik olanin kazanma sansi yuksektir
				
						this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
						savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);
					}
				}	
				if(savasGucu1 > savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu1-savasGucu2)*100)/1000;
					populasyonKaybi = (dusmanNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dusman] -> nufus - populasyonKaybi;						
					erzakKontrolcusuHarac = (dusmanErzak*haracOrani)/100;
					erzakYenilen = dusmanErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dusman] -> erzakStogu = 0;
						this -> mevcutKoloniler[dusman] -> nufus = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dusman] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dusman] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dost] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;	
					}
				}		
				else if(savasGucu1 < savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu2-savasGucu1)*100)/1000;
					populasyonKaybi = (dostNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dost] -> nufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dostErzak*haracOrani)/100;
					erzakYenilen = dostErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dost] -> erzakStogu = 0;
						this -> mevcutKoloniler[dost] -> nufus = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dost] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dost] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dusman] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
				}
			}
			//Durum 5 buyuk-kucuk
			else if((dusmanNufus < dostNufus) && (dostNufus > birBucukKatiDusman)) 
			{
				this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
				savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();
				this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
				
				this -> mevcutKoloniler[dusman] -> cetePtr = pusuYap();
				savasGucu2 = this -> mevcutKoloniler[dusman] -> cetePtr -> olayPusu -> savas();
				this -> mevcutKoloniler[dusman] -> cetePtr -> taktigiTerkEtPusu(this -> mevcutKoloniler[dusman]-> cetePtr);
							
				erzakKontrolcusu = this -> mevcutKoloniler[dost] -> erzakStogu;
				if(dostNufus*4 > erzakKontrolcusu && dostNufus > 10)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dost] -> casusPtr = sabotajYap();
					savasGucu1 = this -> mevcutKoloniler[dost] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dost] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dost] -> casusPtr);
				}
				erzakKontrolcusu = this -> mevcutKoloniler[dusman] -> erzakStogu;
				if(dusmanNufus*4 > erzakKontrolcusu && dusmanNufus > 10)// erzak sorunu varsa sabotaj yapar
				{
					this -> mevcutKoloniler[dusman] -> casusPtr = sabotajYap();
					savasGucu2 = this -> mevcutKoloniler[dusman] -> casusPtr -> olaySabotaj -> savas();
					this -> mevcutKoloniler[dusman] -> casusPtr -> taktigiTerkEtSabotaj(this -> mevcutKoloniler[dusman] -> casusPtr);
				}
				if(savasGucu1 == savasGucu2)//gucler esit gelirse surekli hucum yaparlar
				{
					while(savasGucu1 == savasGucu2) 
					{
						this -> mevcutKoloniler[dost] -> orduPtr = topyekunHucumEt();
						savasGucu1 = this -> mevcutKoloniler[dost] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dost] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dost] -> orduPtr);
						savasGucu1 += 50;
				
						this -> mevcutKoloniler[dusman] -> orduPtr = topyekunHucumEt();
						savasGucu2 = this -> mevcutKoloniler[dusman] -> orduPtr -> olayTopluHucum -> savas();
						this -> mevcutKoloniler[dusman] -> orduPtr -> taktigiTerkEtTopluHucum(this -> mevcutKoloniler[dusman] -> orduPtr);
					}
				}	
				if(savasGucu1 > savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu1-savasGucu2)*100)/1000;
					populasyonKaybi = (dusmanNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dusman] -> nufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dusmanErzak*haracOrani)/100;						
					erzakYenilen = dusmanErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dusman] -> erzakStogu = 0;
						this -> mevcutKoloniler[dusman] -> nufus = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dusman] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dusman] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dost] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dusman] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi++;	
					}
				}		
				else if(savasGucu1 < savasGucu2)//yenen yenilen durumlari guncellemesi
				{
					haracOrani = ((savasGucu2-savasGucu1)*100)/1000;
					populasyonKaybi = (dostNufus*haracOrani)/100;
					populasyonYeni = this -> mevcutKoloniler[dost] -> nufus - populasyonKaybi;
					erzakKontrolcusuHarac = (dostErzak*haracOrani)/100;
					erzakYenilen = dostErzak-erzakKontrolcusuHarac;
					if(populasyonYeni <= 1 || erzakYenilen <= 1)//nufusu veya erzagi tukenenler elenir
					{
						this -> mevcutKoloniler[dost] -> erzakStogu = 0;
						this -> mevcutKoloniler[dost] -> nufus = 0;
						this -> mevcutKoloniler[dost] -> kazanmaSayisi = 0;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi = 0;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
					else
					{
						this -> mevcutKoloniler[dost] -> nufus = populasyonYeni;
						this -> mevcutKoloniler[dost] -> erzakStogu = erzakYenilen;
						this -> mevcutKoloniler[dusman] -> erzakStogu += erzakKontrolcusuHarac;
						this -> mevcutKoloniler[dost] -> kaybetmeSayisi++;
						this -> mevcutKoloniler[dusman] -> kazanmaSayisi++;
					}
				}
			}
			if(savasGucu1 == NULL || savasGucu2 == NULL)
			{
				dost = dost-1;
				continue;
			}
		}
	}
	yokOlmusKolonileriSay(this);	
}
/*

	Orn yazdirma
	------------------------------------------------------------
	Tur: ...
	Koloni  Populasyon  Yemek Stogu  Kazanma   Kaybetme		   			
	A         --            --         --         --
	B         29            54         12         25
    C         178           5690       37         17
	D		  5             14         3          11
	------------------------------------------------------------   

*/
int intUzunluk(int degeri)
{	
	char dizgin[50];
	sprintf(dizgin,"%ld",degeri);
	int uzunluk = strlen(dizgin);
	return uzunluk;
}
wchar_t** yazdir(const Oyun this,int donemec)
{
    int uzunluk = 56;
	wchar_t* sembolTasiyicisi;
	wchar_t** butunTablo = (wchar_t**)malloc(sizeof(wchar_t*)*this->mevcutKoloniSayisi);
    for (int tsIndeks1 = 0; tsIndeks1 < donemec; tsIndeks1++) 
    {
		sembolTasiyicisi = this->semboller[tsIndeks1];
        uzunluk += wcslen(sembolTasiyicisi);
        uzunluk += intUzunluk(this->mevcutKoloniler[tsIndeks1]->nufus);				
        uzunluk += intUzunluk(this->mevcutKoloniler[tsIndeks1]->erzakStogu);				
        uzunluk += intUzunluk(this->mevcutKoloniler[tsIndeks1]->kazanmaSayisi);				
        uzunluk += intUzunluk(this->mevcutKoloniler[tsIndeks1]->kaybetmeSayisi);	
    }
	wchar_t* yazdirilacakSatir = (wchar_t*)malloc(sizeof(wchar_t) * (uzunluk + 1));
    for (int tsIndeks2 = 0; tsIndeks2 < donemec; tsIndeks2++) 
    {
        swprintf(yazdirilacakSatir,L"%-10s  %-10ld  %-10ld  %-10ld  %-10ld\n",
        this->semboller[tsIndeks2],
		this->mevcutKoloniler[tsIndeks2]->nufus,
		this->mevcutKoloniler[tsIndeks2]->erzakStogu,
		this->mevcutKoloniler[tsIndeks2]->kazanmaSayisi,
		this->mevcutKoloniler[tsIndeks2]->kaybetmeSayisi);
		butunTablo[tsIndeks2] = yazdirilacakSatir;
    }   
    return butunTablo;
}																									
void oyunYokEt(const Oyun this)
{
	if(this == NULL)
	{
		return;
	}
	int koloniSayisiForDestroy = this -> mevcutKoloniSayisi;
	for(int destroyIndeks = 0; destroyIndeks < koloniSayisiForDestroy; destroyIndeks++)
	{
		this -> mevcutKoloniler[destroyIndeks] -> koloniYokEtGosterici(this -> mevcutKoloniler[destroyIndeks]);
		free(this -> mevcutKoloniler[destroyIndeks]);
	}
	free(this->mevcutKoloniNufuslari);
	free(this);	
}


