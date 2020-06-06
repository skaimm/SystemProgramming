#include "150101028odev3.h"

int main(int argc, char *argv[])
{
	// parametre 1 ve 2 olacak şekilde sayı kontrolü yap 
	if(argc==2)
	{	
		// gelen parametre tekse o zaman boyut hesaplanmak isteniyor
		// dosya adı kontrolü yap
		if(!strcmp(argv[1],"-v"))
		{ 
			// -v ile program çalıştırılmak isteniyor ama eksik yazılmış usage göster
			usage();

		}else
		{ 
			 //boyut hesaplanmak isteniyor
			// txt dosyasına yazmak için oluşturuyoruz.
			FILE* txtFile = fopen("150101028.txt","w");
			
			// boyut hesaplayan fonskiyonu çağır
			calcSize(argv[1],txtFile,argv[1]);
			fclose(txtFile);
			
			// yazdığımız texti oku ve consola yazdır
			readFromFile();

			// Dosyaları kapat
		}
	}else if(argc==3 || argc==4)
	{
		// 2 ve ya 3 parametre varsa vals programı çalıştırılmak isteniyor
		if(!strcmp(argv[1],"-v")){ // -v komutu mu kontrol ediliyor
			
			if(argc==4){ 

				// 3 parametre varsa			
				runVals(argv[2],argv[3]);
			
			}else
			{	
				// 2 parametre varsa
				runVals(argv[2]," ");
			}
		}else
		{ 
			// -v değilse yanlış yazılmış
			// kullanım göster
			usage();
		}
	}else
	{
		// 2'den fazla ve ya 1 den az parametre varsa kullanım göster 
		usage();
	}
    return 0;
}
