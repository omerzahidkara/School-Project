#ifndef TekYonluBagliListeDugumu_hpp
#define TekYonluBagliListeDugumu_hpp

class TekYonluBagliListeDugumu
{
	public:
		TekYonluBagliListeDugumu* sonraki;
		int veri;
		TekYonluBagliListeDugumu(int veri);	
		~TekYonluBagliListeDugumu();	
};


#endif