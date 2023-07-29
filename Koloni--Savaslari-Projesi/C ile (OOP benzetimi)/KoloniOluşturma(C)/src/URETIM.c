#include "URETIM.h"
#include <stdio.h>
#include <stdlib.h>

Uretim uretimOlustur()
{
	Uretim yeniUretim = (Uretim)malloc(sizeof(struct URETIM));
	
	yeniUretim -> uretimiTerkEt = &uretimiYokEt;
	
	return yeniUretim;
}
void uretimiYokEt(const Uretim yeniUretim)
{
	if(yeniUretim == NULL)
	{
		return;
	}
	else
	{
		free(yeniUretim);
	}
		
}