#include "TAKTIKTOPLUHUCUM.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

TopluHucum topyekunHucumEt()//Yapi olusturma icinde soyut sinif benzetimi yapilmis olan TAKTIK yapisinin savas fonksiyonu hucum taktigi icin farkli sekilde kullanildi.
{
	TopluHucum thisHucum = (TopluHucum)malloc(sizeof(struct TAKTIKTOPLUHUCUM));
	thisHucum -> olayTopluHucum = taktikOlustur();
	thisHucum-> taktigiTerkEtTopluHucum = &taktigiYokEtTopluHucum;
	thisHucum -> olayTopluHucum -> savas = &ordu;
	return thisHucum; 
}
int ordu()//Bir koloninin kendisine oranla cok kucuk bir koloniye karsi kullanacagi taktik fonksiyonu ordudur. En az 200 guc ureterek nufus avantajiyla savascilik kulturunu birlestirir. Yenme ihtimali yuksektir.
{
	srand(time(NULL));
	int orduEtkisi;
	int koloniSavasciligi = rand()%550;
	int kalabalikCoskusu = 450;
	orduEtkisi = kalabalikCoskusu + koloniSavasciligi;
	return orduEtkisi;
}
void taktigiYokEtTopluHucum(const TopluHucum thisHucum)//Yapi yikimi
{
	if(thisHucum == NULL)
	{
		return;
	}
	else
	{
		thisHucum -> olayTopluHucum -> taktigiTerkEt(thisHucum -> olayTopluHucum);
		free(thisHucum);
	}
	
}