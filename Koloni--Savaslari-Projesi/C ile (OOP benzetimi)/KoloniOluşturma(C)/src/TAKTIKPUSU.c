#include "TAKTIKPUSU.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
Pusu pusuYap()//Yapi olusturma icinde soyut sinif benzetimi yapilmis olan TAKTIK yapisinin savas fonksiyonu pusu taktigi icin farkli sekilde kullanildi.
{
	Pusu thisPusu = (Pusu)malloc(sizeof(struct TAKTIKPUSU));
	thisPusu -> olayPusu = taktikOlustur();
	
	thisPusu-> taktigiTerkEtPusu = &taktigiYokEtPusu;
	thisPusu -> olayPusu -> savas = &pusuculuk;
	return thisPusu;
}
int pusuculuk()//Bir koloninin kendisinden en az 1.5 kat büyük bir koloniye karsi kullanacagi taktik etkisi. Yenme sansi pek yuksek degildir.
{
	srand(time(NULL));
	int pusuEtkisi;
	pusuEtkisi = rand()%300;
	return pusuEtkisi;
}
void taktigiYokEtPusu(const Pusu thisPusu)//Yapi yikimi
{
	if(thisPusu == NULL)
	{
		return;
	}
	else
	{
		thisPusu -> olayPusu -> taktigiTerkEt(thisPusu -> olayPusu);
		free(thisPusu);	
	}	
	
}