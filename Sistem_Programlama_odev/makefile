all: derle bagla calistir

derle: 
	gcc -I ./include/ -o ./lib/fields.o -c ./src/fields.c
	gcc -I ./include/ -o ./lib/jval.o -c ./src/jval.c
	gcc -I ./include/ -o ./lib/dllist.o -c ./src/dllist.c
	gcc -I ./include/ -o ./lib/jrb.o -c ./src/jrb.c
			
bagla:
	gcc -I ./include/ -o ./bin/Program ./lib/jval.o ./lib/dllist.o ./lib/jrb.o ./lib/fields.o ./src/main.c
		
calistir:
	@echo "Program çalıştırıldı ve girdi - çıktı dosyası içeriği okundu:"
	./bin/Program ./bin/girdi.dat ./bin/çıktı.dat
	
	cat ./bin/girdi.dat 
	
	cat ./bin/çıktı.dat  
