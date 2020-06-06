#include "150101028.h"

int main(int argc, char *argv[])
{
	// parametre 1 ve 2 olacak şekilde sayı kontrolü yap 
	if(argc==2){
		// gelen parametre tekse o zaman ls komutu isteniyor
		// dosya adı kontrolü yap
		if(!strcmp(argv[1],"-t") || !strcmp(argv[1],"-r") || !strcmp(argv[1],"-d")){ 
			// -t -d -r komutu isteniyor ama eksik yazıldıysa usage göster
			usage();
		}else{ // ls komutu isteniyor
			// dosya adı kontrolü yap
			lscommand(argv[1]);
		}
	}else if(argc==3){
		// 2 parametre varsa ne isteniyor
		if(!strcmp(argv[1],"-t")){ // -t komutu isteniyor
			tcommand(argv[2]);
		}else if(!strcmp(argv[1],"-r")){ // -r komutu isteniyor
			rcommand(argv[2]);
		}else if(!strcmp(argv[1],"-d")){ // -d komutu isteniyor
			dcommand(argv[2]);
		}else{ // -t,-r,-d değilse kayıt isteniyor
			// dosya adı kontrolü yap
			outcommand(argv[1],argv[2]);
		}
	}else{
		// 2'den fazla ve ya 1 den az parametre varsa kullanım göster 
		usage();
	}
    return 1;
}
