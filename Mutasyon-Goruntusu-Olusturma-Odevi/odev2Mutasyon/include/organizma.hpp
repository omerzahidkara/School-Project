#ifndef organizma_hpp
#define organizma_hpp
#include "sistem.hpp"
#include <string>

class organizma
{
	private:
		int sistemSayisi;		
		int sistemSayisiBul();
		void dosyadakiSistemleriOlusturYaz();
		void anaSistemiSil();
		void mutasyonluSistemiSil();
		sistem** organizmaGorevlisi;
		sistem** mutasyonluOrganizmaGorevlisi;
	public:
		organizma();
		~organizma();						
		void mutasyonaUgrat();				
};
#endif
