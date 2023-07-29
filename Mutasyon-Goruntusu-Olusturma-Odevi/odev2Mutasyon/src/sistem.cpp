/** 
* @file sistem.cpp
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
#include "sistem.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

sistem::sistem()
{	
	sistemGorevlisi = new organ*[100];
}
sistem::~sistem()
{	
	sistemSil();
}
void sistem::sistemOlustur(string* sistemSatiri)
{	
	string* organaGonderilenDokular = new string[20];
	
	for(int Indeks = 0;Indeks<100;Indeks++)
	{	
		for(int i = 1; i<21 ;i++)
		{
			
			organaGonderilenDokular[i-1] = sistemSatiri[((Indeks*20)-1)+i];
			
		}
		organ *yeniOrgan = new organ();
		yeniOrgan->organOlustur(organaGonderilenDokular);
		
		sistemGorevlisi[Indeks] = yeniOrgan;
	}
}
void sistem::sistemSil()
{
	for(int sOrgan = 0; sOrgan < 100 ; sOrgan++)
	{
		organ* sistemGorevlisiYardimcisi = sistemGorevlisi[sOrgan];
		delete sistemGorevlisiYardimcisi;				
	}
}
void sistem::sistemYazdir()
{				
	for(int Indeks = 0;Indeks<100;Indeks++)
	{
		doku* kontrolEdilenKok = sistemGorevlisi[Indeks]->organinAgaci->kok;
		kontrol *kontrolNesnesi = new kontrol();
		bool denge = kontrolNesnesi -> dengeOlc(kontrolEdilenKok);	
		if(denge)
		{
			cout << " ";
		}
		else
		{
			cout << "#";
		}
		delete kontrolNesnesi;					
	}
	cout << endl;
}




