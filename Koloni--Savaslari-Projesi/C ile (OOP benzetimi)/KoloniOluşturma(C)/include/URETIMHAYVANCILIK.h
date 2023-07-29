#ifndef URETIMHAYVANCILIK_H
#define URETIMHAYVANCILIK_H

#include "URETIM.h"
#include <stdio.h>
#include <stdlib.h>

struct URETIMHAYVANCILIK// Hayvancilik baslik dosyasi
{
	Uretim koyun;
	void(*uretimiTerkEtHayvancilik)();
	
};
typedef struct URETIMHAYVANCILIK* UretimHayvancilik;

UretimHayvancilik hayvancilikYap();
int otlaklar();
void uretimiYokEtHayvancilik(const UretimHayvancilik);
#endif