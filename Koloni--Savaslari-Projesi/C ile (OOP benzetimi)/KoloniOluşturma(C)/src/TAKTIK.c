#include "TAKTIK.h"

Taktik taktikOlustur()
{
	Taktik yeniTaktik = (Taktik)malloc(sizeof(struct TAKTIK));
	
	yeniTaktik -> taktigiTerkEt = &taktigiYokEt;
	
	return yeniTaktik;
}
void taktigiYokEt(const Taktik yeniTaktik)
{
	if(yeniTaktik == NULL)
	{
		return;
	}
	else
	{
		free(yeniTaktik);
	}
		
}