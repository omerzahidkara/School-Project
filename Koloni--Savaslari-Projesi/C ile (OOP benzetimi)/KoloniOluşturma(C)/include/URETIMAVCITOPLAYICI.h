#ifndef URETIMAVCITOPLAYICI_H
#define URETIMAVCITOPLAYICI_H

#include "URETIM.h"
#include <stdio.h>
#include <stdlib.h>

struct URETIMAVCITOPLAYICI// Avci toplayici baslik dosyasi
{
	Uretim mizrak;	
	void(*uretimiTerkEtAvcilik)(struct URETIMAVCITOPLAYICI*);
};
typedef struct URETIMAVCITOPLAYICI* UretimToplayiciAvci;

UretimToplayiciAvci avYap();
int avcilik();
void uretimiYokEtAvcilik(const UretimToplayiciAvci);

#endif