#ifndef TAKTIKVURKAC_H
#define TAKTIKVURKAC_H

#include "TAKTIK.h"
#include <stdio.h>
#include <stdlib.h>
struct TAKTIKVURKAC//Vurkac baslik dosyasi
{
	Taktik olayVurkac;
	
	void (*taktigiTerkEtVurkac)();
};
typedef struct TAKTIKVURKAC* Vurkac;

Vurkac vurkacYap();
int atlilar();
void taktigiYokEtVurkac(const Vurkac);

#endif