#ifndef radix_hpp
#define radix_hpp

#include "queue.hpp"
//Radix sort nesnesi dizi verisini kucukten buyuge siralamak icin kullanilcaktir.
// Algoritma olarak bucket sort kullandigi icin queue veri yapisi adina queue sinifi icermektedir.

class radix{
	private:	
		int *sayilar;
		int boyut;
		queue **kuyruklar;
		int maxBasamak;
		int power(int e);
		int maxBasamakSayisi();
		int basamakSay(int);
		int *queueAndakiBoyut();
	public:
		radix(int*sayilar, int boyut);
		int *sort();
		~radix();
};
#endif
