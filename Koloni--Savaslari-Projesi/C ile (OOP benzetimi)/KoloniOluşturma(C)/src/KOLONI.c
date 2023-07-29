#include "KOLONI.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

Koloni koloniOlustur(int atanacakNufus,wchar_t* atanacakSembol,int atanacakErzak)// Bir koloni olusurken sembole nufusa ve ilk erzak atamasina sahiptir.
{
	Koloni thisKoloni;
	thisKoloni = (Koloni)malloc(sizeof(struct KOLONI));
	
	thisKoloni -> koloniYokEtGosterici = &koloniYokEt;// yoketme fonksiyon gostericisine islevsel fonksiyonu atama islemi yapiliyor.
	
	thisKoloni -> nufus = atanacakNufus;						//nitelik atamasi
	thisKoloni -> sembol = atanacakSembol;  					//nitelik atamasi
	thisKoloni -> erzakStogu = atanacakErzak;					//nitelik atamasi
	thisKoloni -> kazanmaSayisi = 0;							//nitelik atamasi
	thisKoloni -> kaybetmeSayisi = 0;							//nitelik atamasi
	return thisKoloni;
}
void koloniYokEt(const Koloni thisKoloni)
{
	if(thisKoloni == NULL)
	{
		return;
	}
	free(thisKoloni -> sembol);
	free(thisKoloni);	
}
