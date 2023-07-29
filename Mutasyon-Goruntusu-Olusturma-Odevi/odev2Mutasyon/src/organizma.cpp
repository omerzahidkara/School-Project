/** 
* @file organizma.cpp
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
#include "organizma.hpp"
#include "sistem.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


organizma::organizma()
{	
	sistemSayisi = sistemSayisiBul();
	dosyadakiSistemleriOlusturYaz();
}
organizma::~organizma()
{
	if(organizmaGorevlisi != 0)
	{
		cout << endl << "ORGANIZMA YOK EDILDI" << endl << endl;
		anaSistemiSil();
	}			
}
int organizma::sistemSayisiBul()
{
	string depoSatir;
	ifstream dosyaNesnesi;
	dosyaNesnesi.open("veri.txt");
	int sayac = 0;	
	while(getline(dosyaNesnesi,depoSatir))
	{		
		sayac++;
	}
	dosyaNesnesi.close();
	return sayac/2000;
}

void organizma::dosyadakiSistemleriOlusturYaz()
{
	string depoSatir;
	ifstream dosyaNesnesi;
	dosyaNesnesi.open("veri.txt");
	string* tumDokular = new string[sistemSayisi*2000];
	int sayac = 1;
	organizmaGorevlisi = new sistem*[sistemSayisi];
	cout << "                ORGANIZMA" << endl;
	while(getline(dosyaNesnesi,depoSatir))
	{	
		tumDokular[sayac-1] = depoSatir;
	
		if(sayac%2000 == 0)
		{				
			string* sistemeGonderilenDokular = new string[2000];
			int Indeks = (sayac/2000)-1;			
			for(int i = 1; i<2001 ;i++)
			{
				sistemeGonderilenDokular[i-1] = tumDokular[((Indeks*2000)-1)+i];				
			}			
			sistem *yeniSistem = new sistem();			
			yeniSistem->sistemOlustur(sistemeGonderilenDokular);			
			yeniSistem->sistemYazdir();
			organizmaGorevlisi[Indeks] = yeniSistem;
		}					
		sayac++;
	}
	dosyaNesnesi.close();
	
}
//Burada organizmanın kurucusuyla olusan ana organizma göstericisinden veriler alınıp mutasyona uğramıs yeni organizma olusturulur ve yazdırılır. Ana organizma silinir ve ana göstericiye mutasyonlu organizma atılır. En son mutasyon göstericisi silinir. Böylece mutasyonlu organzima tekrar mutasyona uğrayabilir.
void organizma::mutasyonaUgrat()
{		
	mutasyonluOrganizmaGorevlisi = new sistem*[sistemSayisi];
	for(int sisT = 0; sisT < sistemSayisi; sisT++)
	{	
		sistem* mSistem = new sistem();
		for(int orG = 0; orG < 100; orG++)
		{			
			kontrol *kontrolNesnesiMutasyon = new kontrol();			
			bool olcum = kontrolNesnesiMutasyon->mutasyonDurumuOlc(organizmaGorevlisi[sisT]->sistemGorevlisi[orG]->organinAgaci->kok);			
			if(olcum)
			{
				organ* mOrgan = new organ();
				int *mutasyonluHucreVerileri = new int[20];
				organizmaGorevlisi[sisT]->sistemGorevlisi[orG]->organinAgaci->preOrderIslem(organizmaGorevlisi[sisT]->sistemGorevlisi[orG]->organinAgaci->kok,mutasyonluHucreVerileri);
				mOrgan->organinAgaci->mutasyonSonrasiAgacOlustur(mutasyonluHucreVerileri);								
				delete [] mutasyonluHucreVerileri;													
				mOrgan->organinAgaci->agaciMutasyonaUgrat(mOrgan->organinAgaci->kok);
				int *mutasyonluHucreVerileri2 = new int[20];
				mOrgan->organinAgaci->postOrderIslem(mOrgan->organinAgaci->kok,mutasyonluHucreVerileri2);
				delete mOrgan;
				organ* mOrgan2 = new organ();
				mOrgan2->organinAgaci->mutasyonSonrasiAgacOlustur(mutasyonluHucreVerileri2);																
				delete kontrolNesnesiMutasyon;
				delete [] mutasyonluHucreVerileri2;					
				mSistem->sistemGorevlisi[orG] = mOrgan2;
			}
			else
			{	
				organ* mOrgan = new organ();
				int *saglamAgacVerileri = new int[20];
				organizmaGorevlisi[sisT]->sistemGorevlisi[orG]->organinAgaci->preOrderIslem(organizmaGorevlisi[sisT]->sistemGorevlisi[orG]->organinAgaci->kok,saglamAgacVerileri);				
				mOrgan->organinAgaci->mutasyonSonrasiAgacOlustur(saglamAgacVerileri);
				delete [] saglamAgacVerileri;	
				delete kontrolNesnesiMutasyon;
				mSistem->sistemGorevlisi[orG] = mOrgan;
			}		
		}
		mutasyonluOrganizmaGorevlisi[sisT] = mSistem;		
	}
	anaSistemiSil();
	cout << "                ORGANIZMA (MUTASYONA UGRADI) " << endl;
	for(int sSistem = 0; sSistem < sistemSayisi ; sSistem++)
	{	
		mutasyonluOrganizmaGorevlisi[sSistem]->sistemYazdir();  	
	}
	organizmaGorevlisi = new sistem*[sistemSayisi];
	for(int sisT2 = 0; sisT2 < sistemSayisi; sisT2++)
	{	
		sistem* esasSistem = new sistem();
		for(int orG2 = 0; orG2 < 100; orG2++)
		{
			organ* esasOrgan = new organ();
			int *esasAgacVerileri = new int[20];
			mutasyonluOrganizmaGorevlisi[sisT2]->sistemGorevlisi[orG2]->organinAgaci->preOrderIslem(mutasyonluOrganizmaGorevlisi[sisT2]->sistemGorevlisi[orG2]->organinAgaci->kok,esasAgacVerileri);				
			esasOrgan->organinAgaci->mutasyonSonrasiAgacOlustur(esasAgacVerileri);
			delete [] esasAgacVerileri;	
			esasSistem->sistemGorevlisi[orG2] = esasOrgan;
		}
		organizmaGorevlisi[sisT2] = esasSistem;
	}
	mutasyonluSistemiSil();
}

void organizma::anaSistemiSil()
{
	for(int sSistem = 0; sSistem < sistemSayisi ; sSistem++)
	{	
		sistem* organizmaGorevlisiYardimcisi = organizmaGorevlisi[sSistem];
		delete organizmaGorevlisiYardimcisi;       	
	}	
}
void organizma::mutasyonluSistemiSil()
{
	for(int sSistem2 = 0; sSistem2 < sistemSayisi ; sSistem2++)
	{	
		sistem* organizmaGorevlisiYardimcisiMutasyonik = mutasyonluOrganizmaGorevlisi[sSistem2];
		delete organizmaGorevlisiYardimcisiMutasyonik;       	
	}
}


