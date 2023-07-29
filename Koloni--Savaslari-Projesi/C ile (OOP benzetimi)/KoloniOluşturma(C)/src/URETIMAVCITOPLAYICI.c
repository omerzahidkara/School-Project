#include "URETIMAVCITOPLAYICI.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

UretimToplayiciAvci avYap()//Yapi olusturma icinde soyut sinif benzetimi yapilmis olan URETIM yapisinin uretim fonksiyonu avcilik icin farkli sekilde kullanildi.
{
	UretimToplayiciAvci thisAvci = (UretimToplayiciAvci)malloc(sizeof(struct URETIMAVCITOPLAYICI));
	thisAvci -> mizrak = uretimOlustur();
	
	thisAvci-> uretimiTerkEtAvcilik = &uretimiYokEtAvcilik;
	thisAvci -> mizrak -> uret = &avcilik;
	return thisAvci;
}
int avcilik()// nufusu 20 yi gecmeyen kolonilerin kullandigi erzak uretim bicimi.1-3 arasi uretim yaparlar.
{
	srand(time(NULL));
	int avBolgesi;
	int avciYetenegi = rand()%3;
	avBolgesi = avciYetenegi+1;
	return avBolgesi;
}
void uretimiYokEtAvcilik(const UretimToplayiciAvci thisAvci)//Yapi yikimi
{
	if(thisAvci == NULL)
	{
		return;
	}
	else
	{
		thisAvci -> mizrak -> uretimiTerkEt(thisAvci -> mizrak);
		free(thisAvci);
	}
	
}