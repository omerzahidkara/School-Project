#ifndef TAKTIK_H
#define TAKTIK_H


#include <stdio.h>
#include <stdlib.h>

struct TAKTIK// Taktik soyut sinifi, farkli sekilde kullanilabilecek savas fonksiyon gostericisini barindirir.
{	
	int (*savas)();
	void (*taktigiTerkEt)();
};
typedef struct TAKTIK* Taktik;

Taktik taktikOlustur();
void taktigiYokEt(const Taktik);

#endif