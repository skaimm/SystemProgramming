#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAXSIZE 1024	//path icin max uzunluk
#define EXIT 2
#define BACKOLDPATH "../"
#define SIZE 100
#define ZERO 0
#define OPENFILE "."
#define PLUSYEAR 1900
#define PLUSMONTH 1
#define MALLOCSIZE 1
#define NOFILE "There is no Folder such a same name "


//kac process oldugunu hesaplamak için

int processes = 2; // ilk ve son process

int calcSize(char *nameFile,FILE *txtFile,char *path){

	// DIR
    	DIR *dirFile = NULL;
    	struct dirent *direntFile = NULL;
	struct stat statsFile;

	// toplam boyut,gelen ve alınan boyutlar ve pid oluştur
	int size = 0,sended=0,received=0;

	pid_t pid = getpid();
	pid_t checkpid;
	
	// dosyaya düzenli yazdırılması için path parametresi verdik.
	//eğer ki ana processte path' e ekleme yapma
	if(strcmp(nameFile,path) != 0)
	{
		strcat(path,"/");
		strcat(path,nameFile);
	}

	// chdir ile istediğimiz dosya adının içine giriyoruz.
	_Bool checkPath = chdir(nameFile);

	if(checkPath)
	{
		// dosya yolu bulunamazsa hata ver cık.
		printf("%s '%s'",NOFILE,nameFile);
		exit(EXIT);
	}
	
	
	// dosyamızı açıyoruz.
   	dirFile = opendir(OPENFILE);

	// dosyanın içini dongu ile kontorl ediyoruz.
    	for (;(direntFile = readdir(dirFile)) != NULL;)
    	{
		// . ve .. dosyalarını göstermemek için kontrol
		if (direntFile->d_name[ZERO] != '.')
       		{	
			//eğer klasör ise içine girmek için özyinemeli olarak tekrar fonksiyonu çağır
			
			if(direntFile->d_type == DT_DIR){
				processes++;
				int signals[2];
				pipe(signals);
				pid_t childpid;
				childpid=fork();
				
			
				if(childpid==0)
				{
					/*child process^ten parent process'e kalsör boyutunu aktarmak yapılan pipe işlemi için
			 		https://stackoverflow.com/questions/49581349/how-to-get-return-value-from-child-process-to-parent 
					sitesinden uyarlanarak yapıldı
					close(signals[0]);*/
					// fonnk tekrar çağır
					sended += calcSize(direntFile->d_name,txtFile,path);
					write(signals[1],&sended,sizeof(sended));
					close(signals[1]);

					//dosyaları kapat ve child'İ sonlandır
					closedir(dirFile);
					fclose(txtFile);
					exit(0);
					

				}else if(childpid<0)
				{
					//child process oluşamadı hatası
					printf("ERROR : Child Process cannot created.");
			
				}else
				{	
					
					//fprintf(txtFile,"%d %s %d \n", childpid,nameFil,size);
					/*child process^ten parent process'e kalsör boyutunu aktarmak yapılan pipe işlemi için
			 		https://stackoverflow.com/questions/49581349/how-to-get-return-value-from-child-process-to-parent 
					sitesinden uyarlanarak yapıldı*/

					close(signals[1]);
				
					// parent process'in devam etmesi için cocuk processlerin tamamlanmasını bekle
					int status;
					waitpid(childpid,&status,0);

					read(signals[0],&received,sizeof(received));
					size +=received;
					close(signals[0]);

					// dosya içinde birsey varsa adını text file icine yazdır

				}
			}else
			{
				// klasör değilse boyutlarını bul ve genel boyutla topla
				// sembolik kısayolsa boyutu 0 al 				
				if(direntFile->d_type == DT_LNK){
						
						fprintf(txtFile,"%d\t\t%s\t\n", pid,"symbolic link");
				}else{
					stat(direntFile->d_name,&statsFile);
					size += statsFile.st_size;
				}
			}
			
       		}
   	}
	fprintf(txtFile,"%d\t%d\t%s\n", pid,size,path);
	
	//dosyaları kapat.	
	closedir(dirFile);
	fclose(txtFile);
	return size;
}

void readFromFile(){

	//A klsöründe olduğumuz için bir geri gel
	chdir(BACKOLDPATH);
	
	printf("PID\tSIZE\tPATH\n");
	//dosyadan okuma
	FILE* txtFile2= fopen("150101028abc2.txt","r");
	char buffer[MAXSIZE];
	char* list[SIZE];
	
	int i=0,j;
	for(;fgets(buffer, MAXSIZE, txtFile2)!=NULL;i++) {
		int c = 0;
		list[i] = malloc(1*strlen(buffer));
		strcat(list[i],buffer);
		for(j=0;j<i;j++){
			if(!strcmp(list[j],buffer)){

				c++;
				break;
			}
		}
		if(c==0)
			printf("%s",buffer);
	}

	//process sayısını yazdır.
	printf("Number of process : %d\n",processes);
}

void runVals(char *argv1,char *argv2){
	
	// ikinci programda çalıştırılmak istenen komut için char oluşturuyoruz.
	char command[100];
	
	// program adını yazıyoruz char boyunu ayarlıyoruz.
	sprintf(command, "%s", "./vals ");
	
	// 1. argumantı komuta ekle
	strcat(command,argv1);

	// 2. varsa onuda ekle,yoksa devam et
	if(strcmp(argv2," ") !=0){
		
		strcat(command," ");
		strcat(command,argv2);
	}

	// cocuk process oluştur ve orda programı istenilen komuta göre çalıştır.
	pid_t pid = fork();

	if(pid == 0)
	{
		// cocuk process oluştu programı sistemde run et.
		printf("\nResults From Vals Program :\n\n");
		system(command);
		
	}else
	{
		// process'i sonlandır.
		kill(-pid, SIGTERM);
        	sleep(1);
        	kill(-pid, SIGKILL);
		
		// Sonlandığına dair konsola yazdır.
		printf("\nVals Program has been terminated.\n\n");	
	}
}

// kullanım gösteren fonskiyon
void usage(){

	printf("Yanlış Kullanım\n");
	printf("./bin klasöradı\n");
	printf("./bin -v klasöradı\n");
}
