#ifndef URETIMTARIM_H
#define URETIMTARIM_H

#include "URETIM.h"
#include <stdio.h>
#include <stdlib.h>

struct URETIMTARIM// Tarim yapisi baslik dosyasi
{
	Uretim orak;
	void(*uretimiTerkEtTarim)();
	
};
typedef struct URETIMTARIM* UretimTarim;

UretimTarim tarimYap();
int bereketliArazi();
void uretimiYokEtTarim(const UretimTarim);

#endif