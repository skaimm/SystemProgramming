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

ls: derle
	./$(BIN) Folders
lst: derle
	./$(BIN) -t Folders
lsd: derle
	./$(BIN) -d Folders "Yunus Emre Avcı" "02268155348" "Bilgisayar Mühendisliği Öğretim Elemanı"
lsr: derle
	./$(BIN) -r
lsout: derle
	./$(BIN) out.txt Folders

val: derle
	valgrind --leak-check=yes ./$(BIN) Folders 
	valgrind --leak-check=yes ./$(BIN) -t Folders 
	valgrind --leak-check=yes ./$(BIN) -r Folders
	valgrind --leak-check=yes ./$(BIN) -d Folders
	valgrind --leak-check=yes ./$(BIN) out.txt Folders 

clean: 
	${RM} $(OBJ) $(BIN) 
