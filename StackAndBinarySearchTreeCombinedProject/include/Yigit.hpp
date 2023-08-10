#ifndef Yigit_hpp
#define Yigit_hpp
#include "YigitDugum.hpp"

class Yigit
{
	private:
		YigitDugum* top;
	public:
		Yigit();
		~Yigit();
		int veriSayisi;
		void Push(int veri);
		void Pop();
		int Peek();
};

#endif