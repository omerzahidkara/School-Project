#ifndef hucre_hpp
#define hucre_hpp
#include <iostream>
#include <string>
using namespace std;

class hucre
{
	private:
		int satiriSay(string aktifDokuSatiri);
		int*  satiriSirala(string aktifDokuSatiri);
	public:
		hucre();
		~hucre();			
		int hucreVerisiGetir(string dokuSatiri);	
	
};
#endif
