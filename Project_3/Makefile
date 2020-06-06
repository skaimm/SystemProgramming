# kullanilan derleyici
CC   = gcc

OBJ=150101028.o
# derleyici flagleri
CFLAGS = -c -ansi -pedantic-errors
#source dosyasi
SOURCES= 150101028.c
#executable dosya
BIN  = 150101028
#silmek icin flagler
RM = rm -f

all: obj

derle:
	$(CC) $(CFLAGS) $(SOURCES)
	
obj: derle
	$(CC) $(OBJ) -o $(BIN)

size: derle
	./$(BIN) A
vals: derle
	./$(BIN) -v A

#vals programının diger ozelleklerini gerceklestirmek icin
vals1: derle
	./$(BIN) -v -t A
vals2: derle
	./$(BIN) -v -d A
vals3: derle
	./$(BIN) -v -r A
vals4: derle
	./$(BIN) -v out A

leak: derle
	valgrind --leak-check=yes ./$(BIN) A 
	valgrind --leak-check=yes ./$(BIN) -v A

clean: 
	${RM} $(OBJ) $(BIN) 
