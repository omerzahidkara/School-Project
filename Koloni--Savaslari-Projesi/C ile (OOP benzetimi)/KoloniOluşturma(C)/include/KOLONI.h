#ifndef KOLONI_H
#define KOLONI_H

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#include "OYUN.h"

#include "TAKTIKVURKAC.h"
#include "TAKTIKTOPLUHUCUM.h"
#include "TAKTIKSABOTAJ.h"
#include "TAKTIKPUSU.h"

#include "URETIMAVCITOPLAYICI.h"
#include "URETIMTARIM.h"
#include "URETIMHAYVANCILIK.h"

struct KOLONI// Koloni niteliklerini tasiyan KOLONI yapisi baslik dosyasi
{	
	//Uretim yonelimleri
	UretimToplayiciAvci avciPtr;	//Koloni duruma gore avci toplayici olabilir.
	UretimHayvancilik cobanPtr;		//Koloni duruma gore hayvancilikla gecinebilir.
	UretimTarim ciftciPtr;			//Koloni duruma gore tarimci olabilir.
	//Taktik yonelimleri
	Sabotaj casusPtr;				//Koloni duruma gore sabotaj taktigini benimseyebilir. 
	Pusu cetePtr;					//Koloni duruma gore pusu taktigini benimseyebilir.
	Vurkac atliPtr;					//Koloni duruma gore vurkac taktigini benimseyebilir.
	TopluHucum orduPtr;				//Koloni duruma gore ordu yapilanmasini benimseyebilir.
	
	int nufus;				//nitelik           
	wchar_t* sembol;		//nitelik 
	int erzakStogu;			//nitelik 
	int kazanmaSayisi;		//nitelik 
	int kaybetmeSayisi;		//nitelik
	
	void (*koloniYokEtGosterici)(struct KOLONI*);
};
typedef struct KOLONI* Koloni;


Koloni koloniOlustur(int,wchar_t*,int);
void koloniYokEt(const Koloni);


#endif