/** 
* @file hucre.cpp
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
#include "hucre.hpp"
#include "radix.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

hucre::hucre()
{
	
}
hucre::~hucre()
{
	
}	
int hucre::satiriSay(string aktifDokuSatiri)
{
	ifstream dosyaNesnesi;
	string aktifSatir = aktifDokuSatiri;	
	int satirdakiVeriSayisi = 0;			
	int alinanSayi= 0;
	stringstream satirdakiVeri(aktifSatir);
	while(satirdakiVeri >> alinanSayi)
	{
		satirdakiVeriSayisi++;
	}
	dosyaNesnesi.close();
	return satirdakiVeriSayisi;
}
int* hucre::satiriSirala(string aktifDokuSatiri)
{
	int aktifElemanSayisi = satiriSay(aktifDokuSatiri);
	stringstream satirdakiVeri(aktifDokuSatiri);
	int sayilar[aktifElemanSayisi];
		
	for(int indeks=0; indeks < aktifElemanSayisi;indeks++)
	{					
		satirdakiVeri>>sayilar[indeks];
	}
	radix *radixNesnesi = new radix(sayilar,aktifElemanSayisi);
		
	int* sirali = radixNesnesi->sort();
	delete radixNesnesi;
		
	return sirali;	
}
int hucre::hucreVerisiGetir(string dokuSatiri)
{
	ifstream dosyaNesnesi;
	int* aktifSatir = satiriSirala(dokuSatiri);		
	int aktifElemanSayisi = satiriSay(dokuSatiri);
	int ortaIndeksi = ((aktifElemanSayisi-1)/2)+1;	
	int ortaHucreSayisi = 0;
	for(int dIndex = 0; dIndex < ortaIndeksi; dIndex++)
	{
		ortaHucreSayisi = aktifSatir[dIndex];		
	}
	dosyaNesnesi.close();
	delete [] aktifSatir;
	return ortaHucreSayisi;	
}
