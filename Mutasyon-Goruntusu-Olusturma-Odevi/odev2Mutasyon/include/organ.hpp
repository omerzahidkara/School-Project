#ifndef organ_hpp
#define organ_hpp
#include "ikiliAramaAgaci.hpp"
#include "kontrol.hpp"
#include "doku.hpp"

class organ
{
	public:
		organ();
		void organOlustur(string* agacinSatirlari);
		~organ();		
		ikiliAramaAgaci* organinAgaci;		
};
#endif
