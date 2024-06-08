#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <unistd.h>
#include "fields.h"

// Dinamik karakter dizisi yapısı =>>> dur: komutuna kadar dosyayı dinamik şekilde saklayıp yöneteceğim, dur: komutu gelince işlemler sona erecek ve yazdırılacak
typedef struct 
{
    char *data;         // Karakter dizisinin verisi
    int size;        // Dizinin mevcut boyutu
    int capacity;    // Dizinin mevcut kapasitesi
	int imlec_indeks; // imleç takip için int değeri
} DynamicCharArray;

// Dinamik karakter dizisi oluşturma
DynamicCharArray* olusturDynamicCharArray() 
{
    DynamicCharArray* str = (DynamicCharArray*)malloc(sizeof(DynamicCharArray));
    if (str == NULL) 
	{
        return NULL; // Bellek tahsis hatası
    }
    str->data = NULL;
    str->size = 0;
    str->capacity = 0;
	str->imlec_indeks = 0;
    return str;
}

// Karakter ekleme
void karakterEkle(DynamicCharArray* str, char c) 
{
    if (str->size >= str->capacity) 
	{
        str->capacity = (str->capacity == 0) ? 10 : str->capacity+50;
        str->data = (char*)realloc(str->data, str->capacity * sizeof(char));
        if (str->data == NULL) 
		{
            // Bellek tahsis hatası
            printf("Bellek tahsis hatası!\n");
            exit(1);
        }
    }
	int ileri_indeks = str->size - 1;
	if(str->imlec_indeks > str->size || str->imlec_indeks < 0)
	{
		printf("imlec hatası bulunmakta, imleç sona getirildi\n"); str->imlec_indeks = str->size; 
	}
	else if(str->imlec_indeks != str->size)
	{
		if(str->size > 0)
		{
			for (int i = str->imlec_indeks; i <= ileri_indeks; ileri_indeks--) 
			{
				str->data[ileri_indeks+1] = str->data[ileri_indeks];
			}			
		}
	}
	
    str->data[str->imlec_indeks++] = c;
	str->size++;
}
//Silme
void karakterSil(DynamicCharArray* str, char bulunan_krktr) 
{
	int max_imlec_degeri = str->size;
	if(str->imlec_indeks > 0 )
	{	
		// Silinecek karakterin yerine bir sonraki karakterin yerleştirilmesi
		if(str->imlec_indeks <= max_imlec_degeri)
		{
			for (int geri_indeksleme = str->imlec_indeks-1; geri_indeksleme >= 0; geri_indeksleme--) 
			{
				if(str->data[geri_indeksleme]==bulunan_krktr)
				{
					for (int z = geri_indeksleme; z < str->size - 1; z++) 
					{
						str->data[z] = str->data[z + 1];
					}
					str->imlec_indeks = geri_indeksleme;
					str->size--;
					return;
				}
			}			
		}
		else
		{
			printf("Uyarı: imleç, geçerli alanın(str: yazımı olmuş karakterlerin indeks alanı - string) dışındadır, imleç başa getirildi \n");
		}			
	}
	else
	{
		if(str->size == 0)
		{
			printf("Uyarı: silinecek bir karakter bulunmamaktadır \n");
		}
		else if(str->imlec_indeks == 0)
		{
			printf("Uyarı: imleç, en baştadır; sil: komutu için imleç sona getirilmeli (sonagit:) \n");
		}
		else
		{
			printf("Uyarı: imleç, geçerli alanın(str: yazımı olmuş karakterlerin indeks alanı - string) dışındadır, imleç başa getirildi \n");
		}	
	}
	str->imlec_indeks = 0;
}

// Dinamik karakter dizisini temizleme ve belleği serbest bırakma
void serbestBirakDynamicCharArray(DynamicCharArray* str) {
    free(str->data);
    free(str);
}

/* ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^yukarısı program için gerekli dinamik dizi kodlarıdır^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ */
/* ==================================================================================================== */
		//prototipler
DynamicCharArray* butune_yaz(IS is,DynamicCharArray* str); // yaz: komutu alındığında bu fonksiyon çalışır ve dur: gelene kadar işlecenek stringe dosyadan komut işlemlerini çıkartır
void dur_kmt(DynamicCharArray* str, int dosya_fd); // her şeyi bitiren komut
DynamicCharArray* butunden_sil(IS is,DynamicCharArray* str); // yaz komutu benzeri fakat silme için
DynamicCharArray* sona_gotur(DynamicCharArray* str); // imlec bilgimiz işlenen dosyada sona gider


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "tr_TR.UTF-8"); // Türkçe karakterleri eklemek
	IS is;
	
	// Terminalden program çalıştırılırken hata kontrol
	if (argc != 3)  { fprintf(stderr, "usage: ./Program input_file_name output_file_name \n");  exit(1); }  
	
	is = new_inputstruct(argv[1]);
	
	 // Giriş dosyası mevcudiyeti kontrolü
	if (is ==NULL) {   
		perror(argv[1]);
		exit(1);
	}
	
    int dosya_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0777);
    if (dosya_fd == -1) {
        perror("Dosya oluşturma hatası\n");
        exit(EXIT_FAILURE);
    }
	
    DynamicCharArray* butunumuz = olusturDynamicCharArray();
    if (butunumuz == NULL) {
        printf("String oluşturma hatası!\n");
        return 1;
    }
	int dur_komutu_kontrol_sayaci = 0; // dur komutu yoksa bunun bilgisini vermek için bir kontrol değişkeni oluşturdum
	// Eğer bu komut yoksa bilgi verilecek ve dosya boş çıkacak, çünkü dur komutu dosyaya yazdırılmayı sağlar
	//Giriş dosyasını satır satır işlenecek
	while (get_line(is) >=0) 
	{ 
		if (strcmp(is->fields[0], "yaz:") == 0) 
		{
			butunumuz = butune_yaz(is,butunumuz);
		} 
		else if (strcmp(is->fields[0], "sil:") == 0) 
		{
			butunumuz = butunden_sil(is,butunumuz);
		} 
		else if (strcmp(is->fields[0], "sonagit:") == 0) 
		{		
			butunumuz = sona_gotur(butunumuz);
		}
		else if (strcmp(is->fields[0], "dur:") == 0) // dur: komutu o ana kadar gelen komutlarla işlenmiş str dinamik dizmizi alır ve çıktı dosyası yapar ve program biter
		{
			dur_komutu_kontrol_sayaci = 1;
			dur_kmt(butunumuz, dosya_fd);
			serbestBirakDynamicCharArray(butunumuz);
			break;
		}
		else 
		{
			printf("Hata: %d. satır komutla başlamıyor veya yanlış biçimde \n", is->line);
		}
	}
	if(dur_komutu_kontrol_sayaci == 0)
	{
		printf("Uyarı-program sonu: komut doysanızda (dur:) komutu bulunmadığı için boş soya çıktısı verilmiştir \n");
	}		
	/* IS için hafızayı boşalt ve çıktı dosyasını kapat*/
	close(dosya_fd);
	jettison_inputstruct(is);
	return 0;
}
//BUTUNE YAZ
DynamicCharArray* butune_yaz(IS is,DynamicCharArray* str)
{
	if ((is->NF) % 2 == 1) 
	{
        int cift_sayisi = ((is->NF) - 1) / 2; // yaz: komutu 5 a 3c 7 f gibi olacağı için çift oalrak değerlendiriliyor. ilk eleman adet ikinci karakter olacak
		
        for (int siracift = 0; siracift < cift_sayisi; siracift++) 
		{
            char* adet_str = is->fields[(siracift * 2) + 1];  //adet bilgileri 1 3 5 7 9.. indekslerinde yakalanır
            char* karakter = is->fields[(siracift * 2) + 2]; // karakterler 2 4 6 8 10.. indekslerindedir
            int yazma_adedi = strtol(adet_str, NULL, 10);/* -------------------------------------------------------------------------------------------------------------------------------------------------------------------
			adet_str yi int e çevirir, eğer çeviremezse 0 değeri atar. Bu sayede yaz: komutunda ilk eleman ve ondan sonra gelen eleman adet belirteçlerinin int olduğu garantilenir*/


            // İlk elemanın bir tam sayı olup olmadığını kontrol et 
            if (yazma_adedi == 0) 
			{
                printf("Uyarı100: satır %d alan %d komut içeriği hatalı\n", is->line, (siracift * 2) + 1);
                break;
            }

            // İkinci elemanın karakter, \b veya yeni satır karakteri olup olmadığını kontrol et
            if (isalpha(*karakter) == 0 ) 
			{
				if(strcmp(karakter,"\\b") == 0) // \b ise geçerlidir
				{}
				else if(strcmp(karakter,"\\n") == 0) // \n ise geçerlidir
				{}
				else
				{
					 printf("Uyarı200: satır %d alan %d komut içeriği hatalı\n", is->line, (siracift * 2) + 2);
					break;
				}
            }

            // İkinci elemanın bir sayı karakteri olmamasını kontrol et
            if (isdigit(*karakter)) 
			{
                printf("Uyarı300: satır %d alan %d komut içeriği hatalı\n", is->line, (siracift * 2) + 2);
                break;
            } 
/* ------------------------------------------------- KONTROLLER BİTTİ   ------------------------------------------------- */
            // geçici oalrak str belleğine alacağız, dinamik dizimizi kullanabiliriz burada
            if ( strcmp(karakter,"\\b") == 0) 
			{
                for (int s = 0; s < yazma_adedi; s++) 
				{
					karakterEkle(str, ' ');
                }
            }
            else if ( strcmp(karakter,"\\n") == 0) 
			{
                for (int s = 0; s < yazma_adedi; s++) 
				{
					karakterEkle(str,'\n');
                }
            } 			
			else 
			{
                for (int s = 0; s < yazma_adedi; s++) 
				{
					karakterEkle(str,*karakter);
                }
            }
        }
    } 
	else 
	{
        printf("Uyarı999: satır %d hatalı\n", is->line);
    }
	return str;
}
//BUTUNDEN SIL
DynamicCharArray* butunden_sil(IS is,DynamicCharArray* str)
{
	if ((is->NF) % 2 == 1) 
	{
        int cift_sayisi = ((is->NF) - 1) / 2; // sil: komutu 5 a  gibi olacağı için çift oalrak değerlendiriliyor. ilk eleman adet ikincisi karakter olacak ve çift sayımız 1 olabilir
		if(cift_sayisi == 1)
		{
            char* adet_str = is->fields[1];  //adet bilgilsi sil: komutu için 1. indekstir
			char* karakter = is->fields[2]; // karakter 2. indekstir
            int silme_adedi = strtol(adet_str, NULL, 10);			
             // İlk elemanın bir tam sayı olup olmadığını kontrol et 
            if (silme_adedi == 0) 
			{
                printf("Uyarı20: satır %d alan %d komut içeriği hatalı\n", is->line, 1);
                return str;
            }

            // İkinci elemanın karakter, \b veya yeni satır karakteri olup olmadığını kontrol et
            if (isalpha(*karakter) == 0 ) 
			{
				if(strcmp(karakter,"\\b") == 0) // \b ise geçerlidir
				{}
				else if(strcmp(karakter,"\\n") == 0) // \n ise geçerlidir
				{}
				else
				{
					printf("Uyarı21: satır %d alan %d komut içeriği hatalı\n", is->line, 2);
					return str;
				}
            }

            // İkinci elemanın bir sayı karakteri olmamasını kontrol et
            if (isdigit(*karakter)) 
			{
                printf("Uyarı22: satır %d alan %d komut içeriği hatalı\n", is->line, 2);
                return str;
            } 
/* ------------------------------------------------- KONTROLLER BİTTİ   ------------------------------------------------- */
            //str belleğinden sileceğiz, dinamik dizimizi kullanabiliriz burada
            if ( strcmp(karakter,"\\b") == 0 ) 
			{
                for (int s = 0; 0 < silme_adedi; silme_adedi--) 
				{
					karakterSil(str,' ');
					if(str->imlec_indeks == 0)
					{
						break;
					}
                }
            }
            else if ( strcmp(karakter,"\\n") == 0) 
			{
                for (int s = 0; s < silme_adedi; silme_adedi--) 
				{
					karakterSil(str, '\n');
					if(str->imlec_indeks == 0)
					{
						break;
					}
                }
            } 			
			else 
			{ 
                for (int s = 0; s < silme_adedi; silme_adedi--) 
				{	
					karakterSil(str, *karakter);
					if(str->imlec_indeks == 0)
					{
						break;
					}
                }
            }
        }
		else
		{
			printf("Uyarı50: satır no=>%d hatalı\n", is->line);
		}
    } 
	else 
	{
        printf("Uyarı50: satır no=>%d hatalı\n", is->line);
    }
	return str;
}
			
void dur_kmt(DynamicCharArray* str, int dosya_fd) 
{	
	for (int indeks = 0; indeks < str->size; indeks++) 
	{
		if (write(dosya_fd,&(str->data[indeks]), sizeof(char)) == -1) 
		{
			perror("Dosyaya yazma hatası\n");
			exit(EXIT_FAILURE);
		}
    }
}
DynamicCharArray* sona_gotur(DynamicCharArray* str)
{
	str->imlec_indeks = str->size;
	return str;
}



