#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#include <wchar.h>
#include "OYUN.h"

int main() 
{
	srand(time(NULL));
	int turSayisi = 0;
	int yenilenSayisi = 0;
	printf("Tur atlatmak icin enter a basiniz. Devam etmek icin enter...");
	getch();
	fflush(stdin);
	system("cls");
	Oyun yeniOyun = oyunKur();
	system("cls");
	int kolonilerinSayisi = yeniOyun -> mevcutKoloniSayisi;
	wchar_t** yazdirmac;
	wchar_t** yazdirmac2;
	wprintf(L"------------------------------------------------------------\nTur: %d\nKoloni  Populasyon  Yemek Stogu   Kazanma  Kaybetme\n", turSayisi);
	for(int lazer = 0; lazer<kolonilerinSayisi; lazer++)
	{
		yazdirmac = yeniOyun -> toString(yeniOyun,lazer+1);
		wprintf(L"%ls\n", yazdirmac[lazer]);
		free(yazdirmac[lazer]);
	}
	free(yazdirmac);
	wprintf(L"------------------------------------------------------------\n");
	while(1)
	{	
		turSayisi++;
		getch();
		fflush(stdin);
		system("cls");
		yeniOyun -> turAtlat(yeniOyun,turSayisi);
		yenilenSayisi = yeniOyun -> yenilmisKoloniSayisi;
		printf("\nYok olmus koloni sayisi: %d\n", yenilenSayisi);		
		wprintf(L"------------------------------------------------------------\nTur: %d\nKoloni  Populasyon  Yemek Stogu   Kazanma  Kaybetme\n", turSayisi);
		for(int lazer2 = 0; lazer2<kolonilerinSayisi; lazer2++)
		{
			yazdirmac2 = yeniOyun -> toString(yeniOyun,lazer2+1);
			wprintf(L"%ls\n", yazdirmac2[lazer2]);
			free(yazdirmac2[lazer2]);
		}
		free(yazdirmac2);
		wprintf(L"------------------------------------------------------------\n");
		if((kolonilerinSayisi-yenilenSayisi) < 2)
		{
			break;
		}
	}
	yeniOyun -> oyunYokEtGosterici(yeniOyun);
	getch();
	fflush(stdin);
    return 0;
}