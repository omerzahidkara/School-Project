#ifndef URETIM_H
#define URETIM_H


#include <stdio.h>
#include <stdlib.h>

struct URETIM// Uretim soyut sinifi, farkli sekilde kullanilabilecek uret fonksiyon gostericisini barindirir.
{
	
	int (*uret)();
	void (*uretimiTerkEt)();
	
};
typedef struct URETIM* Uretim;

Uretim uretimOlustur();

void uretimiYokEt(const Uretim);

#endif