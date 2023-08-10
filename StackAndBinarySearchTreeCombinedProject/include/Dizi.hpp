#ifndef Dizi_Hpp
#define Dizi_Hpp

class Dizi
{
	private:
		int* diziCekirdek;
		int diziBoyutu;
		int elemanSayisi;
	public:
		Dizi();
		~Dizi();
		int ekle(int deger);
		bool bosMu();
		bool doluMu();
		void genislet();
		void sonElemanSil();
		int diziElemanlariToplami();
		void guncelle(int indeks,int deger);
		int getirSon();
		int getirIndeksle(int indeks);
		int* diziGetir();
};


#endif