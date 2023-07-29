#ifndef sistem_hpp
#define sistem_hpp
#include "organ.hpp"
#include "kontrol.hpp"
#include "doku.hpp"
#include <string>
#include <iostream>
using namespace std;
class sistem
{
	private:
		void sistemSil();
	public:
		sistem();
		~sistem();
		void sistemOlustur(string* sistemSatiri);
		void sistemYazdir();
		organ** sistemGorevlisi;				
};
#endif
