#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h> 
#include <malloc.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define EXIT 2
#define BACKOLDPATH "../"
#define SIZE 100
#define ZERO 0
#define OPENFILE "."
#define PLUSYEAR 1900
#define PLUSMONTH 1
#define MALLOCSIZE 1
#define NOFILE "There is no Folder such a same name "

//ls program to list all directory files
void lscommand(char *nameFile)
{
	// DIR
    	DIR *dirFile = NULL;
    	struct dirent *direntFile = NULL;

	// chdir ile istediğimiz dosya adının içine giriyoruz.
	_Bool checkPath = chdir(nameFile);

	if(checkPath)
	{
		// dosya yolu yoksa cıkış yapar.
		printf("%s '%s'",NOFILE,nameFile);
		exit(EXIT);

	}else
	{
		// dosyamızı açıyoruz.
   		 dirFile = opendir(OPENFILE);

		// dosyanın içini dongu ile kontorl ediyoruz.
	    	for (;(direntFile = readdir(dirFile)) != NULL;)
	    	{
			// . ve .. dosyalarını göstermemek için kontrol
			if (direntFile->d_name[ZERO] != '.')
	       		{	
				// dosya içinde birsey varsa adını yazdır				
				printf("%s \n", direntFile->d_name);

				// dosya içinde birsey bulunduysa ve eger oda dosya ise içindekileri gostermek için ls komutu tekrar cağır.	
				if(direntFile->d_type == DT_DIR){

					lscommand(direntFile->d_name);

					// yolu eski haline getiriyoruz.
					chdir(BACKOLDPATH);
				}
	       		}
   		}	
	}

	//dosyayı kapat.
	closedir(dirFile);
}

// oluşturulma tarihine göre sırala
void tcommand(char *nameFile)
{
	// DIR
    	DIR *dirFile = NULL;
    	struct dirent *direntFile = NULL;
	struct stat statsFile;
	// dosya isimlerini,oluşturulma tarhilerini ve indexlerini tutmak için isim,tarih listesi ve index oluştur.
	char *fileNamesList[SIZE];
	char* tempname;
	struct tm dt[SIZE];
	int index =-1;
	int i,j,min;

	// chdir ile istediğimiz dosya adının içine giriyoruz.
	_Bool checkPath = chdir(nameFile);

	if(checkPath)
	{
		// dosya yolu bulunamazsa hata ver cık.
		printf("%s '%s'",NOFILE,nameFile);
		exit(EXIT);
	}else
	{
		// dosyamızı açıyoruz.
   		 dirFile = opendir(OPENFILE);

		// dosyanın içini dongu ile kontorl ediyoruz.
    		for (;(direntFile = readdir(dirFile)) != NULL;)
    		{
			// . ve .. dosyalarını göstermemek için kontrol
			if (direntFile->d_name[ZERO] != '.')
       			{	
				// her dosya için indexi artır	
				index++;
				stat(direntFile->d_name,&statsFile);
				// dosyaların son değiştirilme zamanlarını listele
				dt[index] = *(gmtime(&statsFile.st_mtime));
				// listede isim kadar alan ac ve dosya ismini oraya kopyala.
				fileNamesList[index] = malloc(MALLOCSIZE*(strlen(direntFile->d_name)));	
				strcpy(fileNamesList[index],direntFile->d_name);
       			}
   		}
	
		// tarih ve isim listelerini tarihlerine göre sırala.
		
		for(i=0 ; i<index ; i++)
		{
			min = i;
			for(j = i+1 ; j<=index ; j++){
				
				// tarhileri karşılaştır
				if(dt[j].tm_year < dt[min].tm_year)
				{	
					//j indexinde ki yıl küçük olduğunddan min indexi j olarak değiştir.		
					min = j;

				}else if(dt[j].tm_year == dt[min].tm_year)
				{
					// i ve j indexlerindeki yıllar eşit, ayları karşılaştır
					if(dt[j].tm_mon < dt[min].tm_mon)
					{
						//j indexinde ki ay küçük olduğunddan min indexi j olarak değiştir.
						min = j;
				
					}else if(dt[j].tm_mon == dt[min].tm_mon)
					{
						// i ve j indexlerindeki aylar da eşit, günleri karşılaştır
						if(dt[j].tm_mday < dt[min].tm_mday)
						{
							//j indexinde ki gün küçük olduğunddan min indexi j olarak değiştir.
							min = j;
						
						}else
						{
							// j indexinde ki gün i'dekine eşit veya büyükse devam et
							continue;	
						}			
					}else{
						// j indexinde ki ay zaten büyük devam et
						continue;
						
					}			
				}else{ // j indexinde ki yıl zaten büyük devam et
					continue;
				}
				
				// tarihleri swap et
				struct tm tempdt = dt[min];
				dt[min] = dt[i];
				dt[i] = tempdt;

				// dosya isimlerini swap et
				tempname = fileNamesList[min];
				fileNamesList[min] = fileNamesList[i];
				fileNamesList[i] = tempname;
				
				// memory free
			}
		}

		// dosyaları konsolda göster
		for(i =ZERO ;i<=index;i++)
		{
			printf("%s modified date : %d-%d-%d\n",fileNamesList[i],dt[i].tm_mday,dt[i].tm_mon+PLUSMONTH,dt[i].tm_year+PLUSYEAR);
		}
		// memory free
		for(i = ZERO ;i<=index;i++)
		{
			free(fileNamesList[i]);
		}
		free(tempname);
	}
	
	
	//dosyayı kapat.
    	closedir(dirFile);
}

// dosya içini txt'ye yazdırma
void outcommand(char *txtname ,char *nameFile)
{
	// DIR
    	DIR *dirFile = NULL;
    	struct dirent *direntFile = NULL;
	// bos text icin file ac.
	FILE* txtfile;

	// chdir ile istediğimiz dosya adının içine giriyoruz.
	_Bool checkPath = chdir(nameFile);

	if(checkPath)
	{
		// dosya yolu bulunamazsa hata ver cık.
		printf("%s '%s'",NOFILE,nameFile);
		exit(EXIT);

	}else
	{
		// dosyamızı açıyoruz.
		txtfile =fopen(txtname,"w");
   		dirFile = opendir(OPENFILE);

		// dosyanın içini dongu ile kontorl ediyoruz.
	    	for (; (direntFile = readdir(dirFile)) != NULL;)
	    	{
			// . ve .. dosyalarını göstermemek için kontrol
			if (direntFile->d_name[ZERO] != '.')
	       		{	
				// dosya içinde birsey varsa adını text file icine yazdır				
				fprintf(txtfile,"%s \n", direntFile->d_name);
	       		}
   		}
		
	}

	//dosyaları kapat.	
	fflush(txtfile);
	fclose(txtfile);
	closedir(dirFile);
}

// klasörleri listele ve yolunu göster
void dcommand(char *nameFile)
{
	// DIR
    	DIR *dirFile = NULL;
    	struct dirent *direntFile = NULL;
	
	// chdir ile istediğimiz dosya adının içine giriyoruz.
	_Bool checkPath = chdir(nameFile);

	if(checkPath)
	{
		// dosya yolu bulunamazsa hata ver cık.
		printf("%s '%s'",NOFILE,nameFile);
		exit(EXIT);

	}else
	{
		// dosyamızı açıyoruz.
   		 dirFile = opendir(OPENFILE);
		// dosyanın içini dongu ile kontorl ediyoruz.
    		for (;(direntFile = readdir(dirFile)) != NULL;)
    		{
			if (direntFile->d_name[ZERO] != '.')
       			{	
				// dosya içinde birsey varsa 
				// char yol olustur ve realpath() fonskyionu ile yolu kopyala
				char path[SIZE];
				realpath(direntFile->d_name,path);				
				
				// dosya adını ve yolunu yazdır
				printf("%s path: %s \n", direntFile->d_name,path);
				
				// dosya içinde birsey bulunduysa ve eger oda dosya ise içindekileri gostermek için ls komutu tekrar cağır.	
				if(direntFile->d_type == DT_DIR)
				{
					lscommand(direntFile->d_name);
					// path'i eski haline getiriyoruz.
					chdir(BACKOLDPATH);
				}
       			}
   		}	
	}

	//dosyayı kapat.
    	closedir(dirFile);
}

// tersine göre sırala
void rcommand(char *nameFile)
{
	// DIR
    	DIR *dirFile = NULL;
    	struct dirent *direntFile = NULL;

	// dosya isimlerini ve indexlerini tutmak için liste ve index oluştur.
	char *fileNamesList[SIZE];
	int index =-1;

	// chdir ile istediğimiz dosya adının içine giriyoruz.
	_Bool checkPath = chdir(nameFile);

	if(checkPath)
	{
		// dosya yolu bulunamazsa hata ver cık.
		printf("%s '%s'",NOFILE,nameFile);
		exit(EXIT);
	}else
	{
		// dosyamızı açıyoruz.
   		 dirFile = opendir(OPENFILE);

		// dosyanın içini dongu ile kontorl ediyoruz.
    		for (;(direntFile = readdir(dirFile)) != NULL;)
    		{
			// . ve .. dosyalarını göstermemek için kontrol
			if (direntFile->d_name[ZERO] != '.')
       			{	
				// her dosya için indexi artır	
				index++;

				// listede isim kadar alan ac ve dosya ismini oraya kopyala.
				fileNamesList[index] = malloc(MALLOCSIZE*strlen(direntFile->d_name));		
				strcpy(fileNamesList[index], direntFile->d_name);
       			}
   		}
	
		// listede tutulan isimleri tersten yazdır ve alanı free et.
		for(;index>=ZERO;index--)
		{
			printf("%s\n",fileNamesList[index]);
		}	
	}
	
	// memory free
	for(;index>=ZERO;index--)
	{
		free(fileNamesList[index]);
	}
	//dosyayı kapat.
    	closedir(dirFile);
}

// kullanım gösteren fonskiyon
void usage(){

	printf("Yanlış Kullanım\n");
	printf("./bin klasöradı\n");
	printf("./bin -t klasöradı\n");
	printf("./bin -r klasöradı\n");
	printf("./bin -d klasöradı\n");
	printf("./bin out.txt klasöradı\n");
}
