hepsi: derle calistir

derle:
	gcc -I ./include/ -o ./lib/KOLONI.o -c ./src/KOLONI.c
	gcc -I ./include/ -o ./lib/OYUN.o -c ./src/OYUN.c
	gcc -I ./include/ -o ./lib/TAKTIK.o -c ./src/TAKTIK.c
	gcc -I ./include/ -o ./lib/TAKTIKPUSU.o -c ./src/TAKTIKPUSU.c
	gcc -I ./include/ -o ./lib/TAKTIKSABOTAJ.o -c ./src/TAKTIKSABOTAJ.c
	gcc -I ./include/ -o ./lib/TAKTIKTOPLUHUCUM.o -c ./src/TAKTIKTOPLUHUCUM.c
	gcc -I ./include/ -o ./lib/TAKTIKVURKAC.o -c ./src/TAKTIKVURKAC.c
	gcc -I ./include/ -o ./lib/URETIM.o -c ./src/URETIM.c
	gcc -I ./include/ -o ./lib/URETIMAVCITOPLAYICI.o -c ./src/URETIMAVCITOPLAYICI.c
	gcc -I ./include/ -o ./lib/URETIMHAYVANCILIK.o -c ./src/URETIMHAYVANCILIK.c
	gcc -I ./include/ -o ./lib/URETIMTARIM.o -c ./src/URETIMTARIM.c
	gcc -I ./include/ -o ./bin/BeTheLastColony ./lib/KOLONI.o ./lib/OYUN.o ./lib/TAKTIK.o ./lib/TAKTIKPUSU.o ./lib/TAKTIKSABOTAJ.o ./lib/TAKTIKTOPLUHUCUM.o ./lib/TAKTIKVURKAC.o ./lib/URETIM.o ./lib/URETIMAVCITOPLAYICI.o ./lib/URETIMHAYVANCILIK.o ./lib/URETIMTARIM.o ./src/Test.c
	
	
calistir:
	./bin/BeTheLastColony
	