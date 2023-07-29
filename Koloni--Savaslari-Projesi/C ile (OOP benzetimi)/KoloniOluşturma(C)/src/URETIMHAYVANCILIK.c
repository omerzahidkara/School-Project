#include "URETIMHAYVANCILIK.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

UretimHayvancilik hayvancilikYap()//Yapi olusturma icinde soyut sinif benzetimi yapilmis olan URETIM yapisinin uretim fonksiyonu tarim icin farkli sekilde kullanildi.
{
	UretimHayvancilik thisCoban = (UretimHayvancilik)malloc(sizeof(struct URETIMHAYVANCILIK));
	thisCoban -> koyun = uretimOlustur();
	
	thisCoban-> uretimiTerkEtHayvancilik = &uretimiYokEtHayvancilik;
	thisCoban -> koyun -> uret = &otlaklar;
	return thisCoban;
}
int otlaklar()// nufusu 20-50 arasi olan kolonilerin kullandigi erzak uretim bicimi.3-6 arasi uretim yaparlar.
{
	srand(time(NULL));
	int peynircilik;
	int cobanKopekleri = rand()%4;
	peynircilik = cobanKopekleri+3;
	return peynircilik;
}
void uretimiYokEtHayvancilik(const UretimHayvancilik thisCoban)//Yapi yikimi
{
	if(thisCoban == NULL)
	{
		return;
	}
	thisCoban -> koyun -> uretimiTerkEt(thisCoban -> koyun);
	free(thisCoban);	
}