#ifndef TAKTIKPUSU_H
#define TAKTIKPUSU_H

#include "TAKTIK.h"
#include <stdio.h>
#include <stdlib.h>


struct TAKTIKPUSU//Pusu baslik dosyasi
{
	Taktik olayPusu;
	
	void (*taktigiTerkEtPusu)();
};
typedef struct TAKTIKPUSU* Pusu;

Pusu pusuYap();
int pusuculuk();
void taktigiYokEtPusu(const Pusu);

#endif