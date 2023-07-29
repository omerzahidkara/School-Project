#include "TAKTIKVURKAC.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Vurkac vurkacYap()//Yapi olusturma icinde soyut sinif benzetimi yapilmis olan TAKTIK yapisinin savas fonksiyonu vurkac taktigi icin farkli sekilde kullanildi.
{
	Vurkac thisAtli = (Vurkac)malloc(sizeof(struct TAKTIKVURKAC));
	thisAtli -> olayVurkac = taktikOlustur();
	
	thisAtli-> taktigiTerkEtVurkac = &taktigiYokEtVurkac;
	thisAtli -> olayVurkac -> savas = &atlilar;
	return thisAtli;
}
int atlilar()//Bir koloninin kendisinin en fazla 1.5 kati buyuk olan dusman bir koloniye karsi savasacagi zaman kullanacagi fonksiyondur. Yenme ihtimali daha yuksek degildir ama azimsanamaz.
{
	srand(time(NULL));
	int atliEtkisi;
	int atliOkculuk = rand()%400;
	int atliCoskusu = 400;
	atliEtkisi = atliOkculuk + atliCoskusu;
	return atliEtkisi;
}
void taktigiYokEtVurkac(const Vurkac thisAtli)//Yapi yikimi
{
	if(thisAtli == NULL)
	{
		return;
	}
	else
	{
		thisAtli -> olayVurkac -> taktigiTerkEt(thisAtli -> olayVurkac);
		free(thisAtli);	
	}	

}