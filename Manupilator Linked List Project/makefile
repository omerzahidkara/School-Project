all: derle bagla calistir
derle:
	g++ -c -I "./include" ./src/TekYonluBagliListeDugumu.cpp -o ./lib/TekYonluBagliListeDugumu.o
	g++ -c -I "./include" ./src/TekYonluBagliListe.cpp -o ./lib/TekYonluBagliListe.o
	g++ -c -I "./include" ./src/AnaListeDugum.cpp -o ./lib/AnaListeDugum.o
	g++ -c -I "./include" ./src/AnaListe.cpp -o ./lib/AnaListe.o					
	g++ -c -I "./include" ./src/test.cpp -o ./lib/test.o	
bagla:
	g++ ./lib/TekYonluBagliListeDugumu.o ./lib/TekYonluBagliListe.o ./lib/AnaListeDugum.o ./lib/AnaListe.o ./lib/test.o -o ./bin/program
calistir:
	./bin/program