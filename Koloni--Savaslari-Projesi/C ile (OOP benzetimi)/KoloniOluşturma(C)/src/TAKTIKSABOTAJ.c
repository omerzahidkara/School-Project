#include "TAKTIKSABOTAJ.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
Sabotaj sabotajYap()//Yapi olusturma icinde soyut sinif benzetimi yapilmis olan TAKTIK yapisinin savas fonksiyonu sabotaj taktigi icin farkli sekilde kullanildi.
{
	Sabotaj thisSabotaj = (Sabotaj)malloc(sizeof(struct TAKTIKSABOTAJ));
	thisSabotaj -> olaySabotaj  = taktikOlustur();
	
	thisSabotaj-> taktigiTerkEtSabotaj = &taktigiYokEtSabotaj;
	thisSabotaj -> olaySabotaj -> savas = &casusluk;
	return thisSabotaj;
}
int casusluk()// Savasmaya takati olmayan ve erzak stoklari tukenmek uzere olan kolonilerin tercih ettigi cok riskli bir yontemdir. Cesur casuslarin tehlikeli hamleleri ya buyuk odul getirir ya da yok olusa surukler.
{
	srand(time(NULL));
	int casusEtkisi;
	int etkiKatmani = rand()%3;
	if(etkiKatmani == 0)
	{
		casusEtkisi = 600+rand()%200;
	}
	else if(etkiKatmani == 1)
	{
		casusEtkisi = 300+rand()%150;
	}
	else
	{
		casusEtkisi = 100+rand()%100;
	}
	return casusEtkisi;

}
void taktigiYokEtSabotaj(const Sabotaj thisSabotaj)//Yapi yikimi
{
	if(thisSabotaj == NULL)
	{
		return;
	}
	else
	{
		thisSabotaj -> olaySabotaj -> taktigiTerkEt(thisSabotaj -> olaySabotaj);
		free(thisSabotaj);
	}
	
}