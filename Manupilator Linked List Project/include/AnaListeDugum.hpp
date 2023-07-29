#ifndef AnaListeDugum_hpp
#define AnaListeDugum_hpp

#include "TekYonluBagliListe.hpp"
class AnaListeDugum
{
	public:
		AnaListeDugum* sonraki;
		TekYonluBagliListe* ustListe;
		TekYonluBagliListe* altListe;
		AnaListeDugum();	
		~AnaListeDugum();
};

#endif