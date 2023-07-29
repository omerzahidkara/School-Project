/** 
* @file ikiliAramaAgaci.cpp
* @description Program satırlarında tek sayı adedince tamsayı bulunduran bir txt dosyasındaki verileri okur.
					Bu dosyanın her satırı organizmada okunurken hiyerarşik bir şekilde 2000 satır kadarıyla sistem ve her sistemin 20 şer satırıyla toplam 100 organ oluşur.
					Organlar oluşururken ikili arama ağacına sahip olurlar ve aldıkları 20 lik satırları burada her satır 1 doku olacak şekilde işlerler.
					Satırların verileri hücre anlamına gelir. Her satır bir radix sort algoirtması kullanılarak küçükten büyüğe sıralanır ve ortadaki değer dokuya ait hücre DNA uzunluğu olur.
					Her 100 organ tamamlandığında bir sistem oluşur. Organizma en başta sistem sayısını dosyadaki veirleri okuyarak hesaplar. Her sistem oluştuğunda bu sistemlerin organları kontrol edilip yazdırılır.
					Yapılan kontrol organın ağaç yapısının AVL ağacı mantığına göre dengeli veya dengesiz olmasına göre kararlaştırılır. Eğer ağaçlar dengesiz ise # karateri yazılır dengeli ise boşluk bırakılır.
					Bütün organizma yazdırıldıktan sonra kullanıcıdan enter tuşuna basması beklenir. Kullanıcı tuşa basarsa organizma mutasyona uğrar ve organlar yeniden düzenlenir.
					Organların kokleri 50 ye tam bölünebiliyorsa organın tamamı mutasyona uğrar ve dokularının çift olanlarının değerleri ikiye bölünür. Daha sonra ağaç yeniden oluşur.
					Aynı hiyerarşik yapıyla bütün sistemler kontrol edilir ve mutasyonlu organizma yazdırılır.
					Program farklı satırlara ve sayı değerlerine sahip bir txt okursa farklı şekiller çizecektir.
** @course Bilgisayar mühendisliği lisans ikinci sınıf veri yapıları dersi 
* @assignment 2
* @date 25.12.2022
* @author Ömer Zahid KARA omer.kara7@ogr.sakarya.edu.tr
*/
#include "ikiliAramaAgaci.hpp"
#include <iostream>
#include <string>
using namespace std;

ikiliAramaAgaci::ikiliAramaAgaci()
{
	kok = 0;
	sayac = 0;
}
ikiliAramaAgaci::~ikiliAramaAgaci()
{
					
}
void ikiliAramaAgaci::ekle(int veri, doku* aktifDoku)
{
	if(kok == 0)
	{
		kok = new doku(veri);
	}
	else
	{
		if(aktifDoku -> ortaHucreVerisi >= veri)
		{
			if(aktifDoku -> sol)
			{
				return ekle(veri, aktifDoku -> sol);
			}
			else
			{
			aktifDoku -> sol = new doku(veri);
			}
		}
		else if(aktifDoku -> ortaHucreVerisi < veri)
		{
			if(aktifDoku -> sag)
			{
				return ekle(veri, aktifDoku -> sag);
			}
			else
			{
				aktifDoku -> sag = new doku(veri);
			}
		}
		else return;
	}		
}
void ikiliAramaAgaci::agacOlustur(string* agactakiSatirlar)
{		
	for(int j=0; j<20 ; j++)
	{			
		hucre *hucreNesnesi = new hucre();
        string dokununSatiri = agactakiSatirlar[j];		
		int hucreVerisi = hucreNesnesi->hucreVerisiGetir(dokununSatiri);
		delete hucreNesnesi;
		ekle(hucreVerisi,kok);
	}		
}
void ikiliAramaAgaci::mutasyonSonrasiAgacOlustur(int *hucreVerisi)
{	
	for(int m = 0;  m < 20; m++)
	{
		int hucreVerisiGonderilen = hucreVerisi[m];
		ekle(hucreVerisiGonderilen,kok);
	}
}
void ikiliAramaAgaci::preOrderIslem(doku* aktifDoku,int *dizgin)
{
	if(aktifDoku == 0)
	{
		return;													
	}
	dizgin[sayac] = aktifDoku->ortaHucreVerisi;
	sayac++;							
	preOrderIslem(aktifDoku->sol,dizgin);
	preOrderIslem(aktifDoku->sag,dizgin);
}

void ikiliAramaAgaci::agaciMutasyonaUgrat(doku* aktifDoku)
{
	if(aktifDoku == 0)
	{
		return;
	}		
	if(aktifDoku->sol != 0)
	{	
		agaciMutasyonaUgrat(aktifDoku->sol);
		if(aktifDoku->ortaHucreVerisi%2 == 0)
		{			
			aktifDoku->ortaHucreVerisi = aktifDoku->ortaHucreVerisi/2;								
		}			
	}
	if(aktifDoku->sag != 0)
	{	
		agaciMutasyonaUgrat(aktifDoku->sag);
		if(aktifDoku->ortaHucreVerisi%2 == 0)
		{			
			aktifDoku->ortaHucreVerisi = aktifDoku->ortaHucreVerisi/2;								
		}
	}							
	
}
void ikiliAramaAgaci::postOrderIslem(doku* aktifDoku,int *dizgin)
{	
	if(aktifDoku == 0)
	{
		return;													
	}		
	postOrderIslem(aktifDoku->sol,dizgin);		
	postOrderIslem(aktifDoku->sag,dizgin);				
	dizgin[sayac] = aktifDoku->ortaHucreVerisi;
	sayac++;					
}
bool ikiliAramaAgaci::bosMu()
{
	return kok == 0;
}
void ikiliAramaAgaci::temizle()
{	
	while(!bosMu())
	{	
		dokuSil(kok);		
	}	
}
bool ikiliAramaAgaci::dokuSil(doku *&aktifDoku)
{
	doku *silinecekDoku = aktifDoku;
	if(aktifDoku->sag == 0)
	{
		aktifDoku = aktifDoku->sol;
	}
	else if(aktifDoku->sol == 0)
	{
		aktifDoku = aktifDoku->sag;
	}
	else
	{
		silinecekDoku = aktifDoku->sol;
		doku *ebeveyn = aktifDoku;		
		while(silinecekDoku->sag != NULL)
		{			
			ebeveyn = silinecekDoku;
			silinecekDoku = silinecekDoku->sag;			
		}
		aktifDoku->ortaHucreVerisi = silinecekDoku->ortaHucreVerisi;
		if(ebeveyn == aktifDoku)
		{
			aktifDoku->sol = silinecekDoku->sol;
		}
		else
		{
			ebeveyn->sag = silinecekDoku->sol;
		}
	}
	delete silinecekDoku;	
	return true;
}