/** 
* @file radix.cpp
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
#include "radix.hpp"
#include <cmath>
using namespace std;

int radix::maxBasamakSayisi()
{
	int max=0;
	for(int i=0;i<boyut;i++)
	{
		if(basamakSay(sayilar[i])>max) 
			max = basamakSay(sayilar[i]);
	}
	return max;
}
int radix::basamakSay(int sayi)
{
	sayi = abs(sayi);
	int basamak=0;
	while(sayi>0)
	{
		basamak++;
		sayi /= 10;
	}
	return basamak;
}
radix::radix(int *sayilar, int boyut)
{
	this->sayilar = new int[boyut];
	this->boyut = boyut;
	for(int i=0;i<boyut;i++)
	{ 
		this->sayilar[i] = sayilar[i]; 
	}
	kuyruklar = new queue *[10];
	for(int j=0;j<10;j++)
	{ 
		kuyruklar[j] = new queue(); 
	}
	maxBasamak = maxBasamakSayisi();
}
int* radix::queueAndakiBoyut()
{
	int *boyutlar = new int[10];
	for(int i=0;i<10;i++)
	{
		boyutlar[i] = kuyruklar[i]->say();
	}
	return boyutlar;
}
int* radix::sort()
{
	int sayiIndex=0;
	
	for(;sayiIndex<boyut;sayiIndex++)
	{
		int basamakDegeri = sayilar[sayiIndex]%10;
		int deger = sayilar[sayiIndex];
		kuyruklar[basamakDegeri]->ekle(deger);
	}			
	for(int i=1;i<maxBasamak;i++)
	{		
		int *kuyrukBoyutlar = queueAndakiBoyut();
		for(int index=0;index<10;index++)
		{
			int len = kuyrukBoyutlar[index];
			for(;len>0;len--)
			{
				int sayi = kuyruklar[index]->getir();
				kuyruklar[index]->eksilt();
				int basamakDegeri = (sayi/power(i))%10;	
				kuyruklar[basamakDegeri]->ekle(sayi);				
			}
		}
		delete [] kuyrukBoyutlar;
	}
	int* siralanmis = new int[boyut];
	sayiIndex=0;
	for(int index=0;index<10;index++)
	{
		while(!kuyruklar[index]->bosMu())
		{
			int sayi = kuyruklar[index]->getir();
			siralanmis[sayiIndex++] = sayi;
			kuyruklar[index]->eksilt();
		}
	}
		
	return siralanmis;
}
int radix::power(int e){
	int result=1;
	for(int i=0;i<e;i++) result *= 10;
	return result;
}
radix::~radix()
{	
	delete [] sayilar;
	for(int i=0;i<10;i++) delete kuyruklar[i];
	delete [] kuyruklar;
}
