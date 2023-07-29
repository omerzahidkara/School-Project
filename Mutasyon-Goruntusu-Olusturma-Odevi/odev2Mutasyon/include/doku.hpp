#ifndef doku_hpp
#define doku_hpp
//Organ nesnesindeki doku yapisi(dugum) doku nesnesi tarafindan saglanacaktir.
class doku
{
	public:
	doku(int ortaHucreVerisi);
	doku* sag;
	doku* sol;
	int ortaHucreVerisi;
};
#endif