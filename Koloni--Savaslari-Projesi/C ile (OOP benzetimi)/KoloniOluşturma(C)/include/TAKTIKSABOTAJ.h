#ifndef TAKTIKSABOTAJ_H
#define TAKTIKSABOTAJ_H

#include "TAKTIK.h"
#include <stdio.h>
#include <stdlib.h>

struct TAKTIKSABOTAJ// Sabotaj baslik dosyasi
{
	Taktik olaySabotaj;
	
	void (*taktigiTerkEtSabotaj)();
};
typedef struct TAKTIKSABOTAJ* Sabotaj;

Sabotaj sabotajYap();
int casusluk();
void taktigiYokEtSabotaj(const Sabotaj);

#endif