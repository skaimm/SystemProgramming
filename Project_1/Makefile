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

add: derle
	./$(BIN) -a add "Yunus Emre Avcı" "02268155348" "Bilgisayar Mühendisliği Öğretim Elemanı"
delete: derle
	./$(BIN) -a delete "31"
update: derle
	./$(BIN) -a update "Yunus Emre Avcı" "02268155348" "Bilgisayar Mühendisliği Öğretim Elemanı"
list: derle
	./$(BIN) -u 
letter: derle
	./$(BIN) -u filter "Y"
phone: derle
	./$(BIN) -u filter "5348"
val: derle
	valgrind --leak-check=yes ./$(BIN) -a add "Yunus Emre Avcı" "02268155348" "Bilgisayar Mühendisliği Öğretim Elemanı" 

clean: 
	${RM} $(OBJ) $(BIN) 
