#ifndef kontrol_hpp
#define kontrol_hpp
#include "ikiliAramaAgaci.hpp"
#include "doku.hpp"
//Ekrana organ yazdirmada organin agac yapisinin dengesini kontrol edecek fonksiyonu barindirir.
//Mutasyon olabilicek agaclarin tespitini yapacak fonksiyonlari barindirir.
class kontrol
{
	public:
		~kontrol();
		kontrol();
		bool dengeOlc(doku* aktifKok);
		int yukseklik(doku* aktifDugum);
		bool mutasyonDurumuOlc(doku* aktifKok);		
};
#endif
