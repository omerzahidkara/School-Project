/** 
* @file kontrol.cpp
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
#include "kontrol.hpp"
#include <cmath>
#include <iostream>
#include <string>
using namespace std;

kontrol::kontrol()
{

}
kontrol::~kontrol()
{	
	
}
bool kontrol::dengeOlc(doku* aktifKok)
{	
	if(aktifKok)
	{
		if(aktifKok->sag && !aktifKok->sol)
		{
			int yuk1 = yukseklik(aktifKok->sag);
			if(yuk1 >0)
			{
				return false;
			}
		}
		if(aktifKok->sol && !aktifKok->sag)
		{
			int yuk2 = yukseklik(aktifKok->sol);
			if(yuk2 >0)
			{
				return false;
			}		
		}		
		if(aktifKok->sol && aktifKok->sag)
		{
			int yuk4 = yukseklik(aktifKok->sag);
			int yuk5 = yukseklik(aktifKok->sol);
			int fark = abs(yuk4-yuk5);
			if(fark>1)
			{
				return false;
			}			
			else
			{
				bool ayiklamaSag2;
				bool ayiklamaSol2;
				doku* gezici = aktifKok; 
				while(!gezici->sag)
				{
					ayiklamaSag2 = dengeOlc(gezici->sag);
					if(ayiklamaSag2)
					{
						gezici = gezici->sag;
					}
					else
					{
						return false;
					}
				}
				while(!gezici->sol)
				{
					ayiklamaSol2 = dengeOlc(gezici->sol);
					if(ayiklamaSol2)
					{
						gezici = gezici->sol;
					}
					else
					{
						return false;
					}
				}
			}				
			
		}
		return true;
	}
}
int kontrol::yukseklik(doku* aktifDugum)
{		
	if(aktifDugum)
	{	
		return 1+max(yukseklik(aktifDugum->sol), yukseklik(aktifDugum->sag));
	}
	return -1;
}
bool kontrol::mutasyonDurumuOlc(doku* aktifKok)
{
	int olculenHucreVerisi = aktifKok -> ortaHucreVerisi;
	if(olculenHucreVerisi%50 == 0)
	{		
		return true;
	}		
	else
	{		
		return false;	
	}		
}