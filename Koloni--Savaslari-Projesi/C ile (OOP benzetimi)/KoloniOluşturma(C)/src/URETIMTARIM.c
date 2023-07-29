#include "URETIMTARIM.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

UretimTarim tarimYap()//Yapi olusturma icinde soyut sinif benzetimi yapilmis olan URETIM yapisinin uretim fonksiyonu tarim icin farkli sekilde kullanildi.
{
	UretimTarim thisCiftci = (UretimTarim)malloc(sizeof(struct URETIMTARIM));
	thisCiftci -> orak = uretimOlustur();
	
	thisCiftci-> uretimiTerkEtTarim = &uretimiYokEtTarim;
	thisCiftci -> orak -> uret = &bereketliArazi;
	return thisCiftci;
}
int bereketliArazi()// nufusu 100 den buyuk kolonilerin kullandigi erzak uretim bicimi.6-10 arasi uretim yaparlar.
{
	srand(time(NULL));
	int tarimArazisi;
	int suKaynagi = rand()%5;
	tarimArazisi = suKaynagi+6;
	return tarimArazisi;
}
void uretimiYokEtTarim(const UretimTarim thisCiftci)//Yapi yikimi
{
	if(thisCiftci == NULL)
	{
		return;
	}
	else
	{
		thisCiftci -> orak -> uretimiTerkEt(thisCiftci -> orak);
		free(thisCiftci);
	}
	
}
