all: derle bagla calistir
derle:
	g++ -c -I "./include" ./src/organizma.cpp -o ./lib/organizma.o
	g++ -c -I "./include" ./src/sistem.cpp -o ./lib/sistem.o
	g++ -c -I "./include" ./src/organ.cpp -o ./lib/organ.o
	g++ -c -I "./include" ./src/queueNode.cpp -o ./lib/queueNode.o
	g++ -c -I "./include" ./src/queue.cpp -o ./lib/queue.o
	g++ -c -I "./include" ./src/radix.cpp -o ./lib/radix.o
	g++ -c -I "./include" ./src/kontrol.cpp -o ./lib/kontrol.o
	g++ -c -I "./include" ./src/doku.cpp -o ./lib/doku.o
	g++ -c -I "./include" ./src/ikiliAramaAgaci.cpp -o ./lib/ikiliAramaAgaci.o
	g++ -c -I "./include" ./src/hucre.cpp -o ./lib/hucre.o						
	g++ -c -I "./include" ./src/test.cpp -o ./lib/test.o	
bagla:
	g++ ./lib/queueNode.o ./lib/queue.o ./lib/radix.o ./lib/hucre.o ./lib/doku.o ./lib/ikiliAramaAgaci.o ./lib/kontrol.o ./lib/organ.o ./lib/sistem.o ./lib/test.o ./lib/organizma.o -o ./bin/program
calistir:
	./bin/program