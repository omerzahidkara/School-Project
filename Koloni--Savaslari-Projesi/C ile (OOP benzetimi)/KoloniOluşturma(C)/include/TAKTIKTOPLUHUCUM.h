#ifndef TAKTIKTOPLUHUCUM_H
#define TAKTIKTOPLUHUCUM_H

#include "TAKTIK.h"
#include <stdio.h>
#include <stdlib.h>

struct TAKTIKTOPLUHUCUM//Hucum baslik dosyasi
{
	Taktik olayTopluHucum;
	
	void (*taktigiTerkEtTopluHucum)();
};
typedef struct TAKTIKTOPLUHUCUM* TopluHucum;

TopluHucum topyekunHucumEt();
int ordu();
void taktigiYokEtTopluHucum(const TopluHucum);

#endif