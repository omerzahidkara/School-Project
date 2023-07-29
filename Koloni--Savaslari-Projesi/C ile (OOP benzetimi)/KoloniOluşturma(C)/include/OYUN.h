#ifndef OYUN_H
#define OYUN_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "KOLONI.h"

/*Test asamasinda oyun nesnesindeki fonksiyon cagricilar araciligiyla
olusturalacak kolonilerin nufus sayilari bir yazimda istenir.
Kac adet nufus istendigine gore farkli semboller uretilir ve koloniler sirayla o sayida 
olusturulup sembolleri atanir.
Sembol sayisi sinirli oldugu icin sembollerin karakter sayisi koloni sayisi arttikca artar. Bu sekilde her zaman farkli semboller uretilmis olur.
Her koloni icin populasyonunun karesi kadar erzak stogu verilir.
Koloniler olusurken nufusu 20 nin altinda olan koloniler kabile olarak uretim yaparlar ve uretimleri
avci-toplayici olarak atanir. Avci-toplayici 1-3 arasi uretim yapar.20 ile 100 arasi
olanlara boy denir ve havancilik yaparlar. Hayvancilikta ise 3-6 arasi uretim yapilir.
100 üstü olan kolonilere derebeylik denir ve tarimla ugrasirlar. Genelde 6-10 arasi uretim yaparlar fakat
10 turda bir kıtlık olur ve 1 uretim yaparlar. 

Koloniler olusup ilk tur basladiginda once uretimler yapilir. Sonra erzak stogu populasyonun iki kati kadar azalir ve her koloninin populasyonu
%20 oraninda artar. En son butun koloniler savasir.

Her turun basinda once kolonilerin kabile mi boy mu yoksa derebeylik mi oldugu kontrol edilir.
Ona gore uretim yaplir. Bu nitelikler koloni structina bagli degildir. Oyun tarafindan kontrol edilir.

Savasacak kolonilerin nufuslari esitse topyekun hucum yaparlar.
Savacak koloni karsisindaki kolonin en az 1.5 katiysa buyuk olarak
nitelenir. Karsisindakine ise kucuk denir. Eger 1 ile 1,5 kat arasi
ise ortanca olarak nitelenir.
Koloniler bu sartlara gore taktik belirler. Buyuk-kucuk savasinda
toplu hucum ve pusu taktikleri secilir. Ortanca-kucuk savasinda toplu hucum - vurkac taktikleri
secilir. Ayrica her koloni sabotaj taktigi de kullanabilir.  Eger erzak
stoklari nufuslarinin 4 katindan azsa ve nufusu 10 dan fazlaysa bunu tercih ederler. Bu taktik ya çok yüksek güç üretir ya da çok az.
Savasta yenen koloni yenilen koloninin güç puani farkinin 1000 e gore yuzde
kac olduguna gore erzak stogundan harac alir ve yenilen koloninin populasyonu o oranda azalir.
Her koloni birbiriyle bir kere savastiginde tur biter. Sona bir tane koloni kalana kadar
oyun tekrar eder ve sona kalan oyunu kazanir.
*/
typedef struct KOLONI** KoloniBakani;
struct OYUN
{
	KoloniBakani mevcutKoloniler;//Koloni structlarina erismeyi saglayan pointer
	int mevcutKoloniSayisi;//Koloni sayisini tutan degisken
	int* mevcutKoloniNufuslari;//Veri girisinde girilen sayilarin listesini tutan pointer	
	wchar_t** semboller;//Koloni sayisi kadar sembol farkli sembol olusur. Sonsuz adet sembol olusabilmesi adına string tutucu seklinde depolanir. 
	int yenilmisKoloniSayisi;//Test asamasinda (toplam koloni sayisi - yenilmiskoloni) == 1 oldugunda programi sonlandirabilmek icin kullanilacak degisken.
	
	int* (*koloniVerileriAlGosterici)();//  1
	int (*koloniSayisiHesaplaGosterici)(int*);//  2
	wchar_t** (*koloniSembolleriOlusturGosterici)(int);//  3
	KoloniBakani (*kolonileriOlusturGosterici)(struct OYUN*);//  4
	void (*turAtlat)(struct OYUN*,int);//  5
	wchar_t** (*toString)(struct OYUN*,int);//  6
	void (*oyunYokEtGosterici)(struct OYUN*);//  7		
};
typedef struct OYUN* Oyun;


Oyun oyunKur();

int* koloniVerileriAl();//kullanicidan sayi isteyip nufus listesine kaydeden fonksiyon  1
int koloniSayisiHesapla(int*);//nufus listesini donup kac sayi oldugunu bildiren fonksiyon  2
wchar_t** koloniSembolleriOlustur(int);//nufus sayisini parametre olarak alip o kadar sembol olusturan ve bunu bir adet string array pointeri olarak gonderen fonksiyon  3
KoloniBakani kolonileriOlustur(const Oyun);//veri girisinden sonra olusan sembol ve nufuslara gore ilk kez koloni structlarini yapan ve baslangic bilgilerini veren fonksiyon  4
void turYap(const Oyun,int);//Enter a basildikca tur yapan fonksiyon. Ayrica tur icinde kolonilerin nufuslarina gore nitelikleri ve savas taktikleri degisir. Bellek yonetimi tur icinde anlık gerceklesir.  5
wchar_t** yazdir (const Oyun,int);// Tur degisimi sonrasi ekrana basma fonksiyonu.  6
void oyunYokEt(const Oyun);// Sona kalan bellek coplerini toplayan fonksiyon.  7




#endif