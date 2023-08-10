all: derle bagla calistir

derle:
	g++ -c -I "./include" ./src/Dizi.cpp -o ./lib/Dizi.o
	g++ -c -I "./include" ./src/YigitDugum.cpp -o ./lib/YigitDugum.o
	g++ -c -I "./include" ./src/AgacDugum.cpp -o ./lib/AgacDugum.o
	g++ -c -I "./include" ./src/Agac.cpp -o ./lib/Agac.o	
	g++ -c -I "./include" ./src/Yigit.cpp -o ./lib/Yigit.o
	g++ -c -I "./include" ./src/IslemYonetici.cpp -o ./lib/IslemYonetici.o	
	g++ -c -I "./include" ./src/test.cpp -o ./lib/test.o
bagla:
	g++ ./lib/Dizi.o ./lib/YigitDugum.o ./lib/AgacDugum.o ./lib/Agac.o ./lib/Yigit.o ./lib/IslemYonetici.o ./lib/test.o -o./bin/program
calistir:
	./bin/program