#include "150101028.h"


void usage(){
	printf("%s \n",USAGE);
}
void usage_add(){
	printf("%s \n",USAGE_ADD);
}
void usage_update(){
	printf("%s\n",USAGE_UPD);
}
void usage_delete(){
	printf("%s \n",USAGE_DEL);
}
void usage_search(){
	printf("%s \n",USAGE_LET);	
	printf("%s \n",USAGE_PHO);
}
void usage_user(){
	printf("%s \n",USAGE_USER);
}
void addToFile(char *arg1 , char *arg2 , char *arg3){
	FILE *fp;
	gid++;
	fp = fopen(FILENAME,FILE_APPEND);
	fprintf(fp,"%d %s %s %s\n",gid,arg1,arg2,arg3);
	printf("%d %s %s %s\n",gid,arg1,arg2,arg3);
	printf("%s \n",SUCCESS_ADD);
	fclose(fp);
}

void deleteFromFile(Person *sp,int did){
	int line_no=ZERO,delete_line=ZERO,i;
	char filename[LENGTH] = FILENAME;	
	FILE *fp1,*fp2;

	for(i=ZERO;i<entries;i++){
		if(sp[i].id == did){
			delete_line=i+ONE;
		}
	}
	fp1 = fopen(filename,FILE_READ);
	rewind(fp1);
	fp2 = fopen(TEMPFILE,FILE_WRITE);
	while(fgets(buff,SIZE,fp1)!=NULL){
	line_no++;
		if(line_no!=delete_line){
			fputs(buff,fp2);						
		}
	}
	fclose(fp1);
	remove(filename);
	rename(TEMPFILE,FILENAME);
	fclose(fp2);
}
void updateInfo(){
	printf("%s",INFO_UPD);
}

void searchByLetter(Person *sp,char *arg){
	int counter =ZERO,line=ZERO,space=ZERO,gets=ZERO,alpha=ZERO;	
	char ch;
	FILE *fp = fopen(FILENAME,FILE_READ);
	printf("%s \n",INFO_USER);
	ch = getc(fp);
	while(ch!=EOF){
		if(ch == *arg && space==ONE && gets==ZERO && alpha==ZERO){
			printf("%d %s ",sp[line].id,sp[line].name);
			printf("%s %s\n",sp[line].phone,sp[line].department);
			counter++;
			gets++;
		}
		if(isalpha(ch)){
				alpha++;
		}
		if(ch== CTRL_S){
			space++;
		}
		if(ch == CTRL_N){
			line++;
			gets=ZERO;
			space=ZERO;
			alpha=ZERO;
		}
		ch=getc(fp);
	}
	if(counter==ZERO){
		printf("%s %s\n",INFO_FIL,arg);					
	}
}
void searchByDigits(Person *sp,char *arg){
	int counter=ZERO,i;
	for(i=ZERO;i<entries;i++){
		if(sp[i].phone[TEN]==arg[THREE] && sp[i].phone[NINE]==arg[TWO]  && 	                 	sp[i].phone[EIGTH]==arg[ONE]  && sp[i].phone[SEVEN]==arg[ZERO]){
			printf("%d %s ",sp[i].id,sp[i].name);
			printf("%s %s\n",sp[i].phone,sp[i].department);
			counter++;
			break;
		}
	}
	if(counter==ZERO){
		printf("%s %s\n",INFO_PHO,arg);					
	}
}

void showList(Person *sp){
	int i;
	FILE *fp = fopen(ALLUSERS,FILE_WRITE);
	printf("%s\n",INFO_USER);
	for(i=ZERO; i< entries;i++){
		fprintf(fp,"%d %s %s %s\n",sp[i].id,sp[i].name,sp[i].phone,sp[i].department);
		printf("%d %s %s %s",sp[i].id,sp[i].name,sp[i].phone,sp[i].department);
	}
}

int main(int argc,char *argv[]){
	int i,counter=ZERO;
	FILE *fp = fopen(FILENAME,FILE_READ);
	Person *ptrS = NULL;
	ptrS = malloc(sizeof(Person)*entries);
	if(ptrS==NULL){
		printf("%s\n",ERROR_MALLOC);	
	}

	if(fp==NULL)
	{
		printf("%s \n",ERROR_FILE);
		exit(ONE);
	}
	
	while(fgets(buff,SIZE,fp)!=NULL){
		char *pch = strtok(buff,CTRL_S2);
		int counter2=ZERO;
		int counter3=ZERO;
		int tempid;
		char *tempname = malloc(LENGTH*sizeof(char));
		char *tempphone = malloc(LENGTH*sizeof(char));
		char *tempdep = malloc(LENGTH*sizeof(char));
		while(pch !=NULL)
		{
			if(counter2==ZERO){
				tempid = atoi(pch);
			}else{				
				int com = pch[ZERO];
				if(counter3==ZERO){
					if(com == ASCIICODE){
						strcat(tempphone,pch);
						counter3++;
					}else{
						strcat(tempname,pch);
						strcat(tempname,CTRL_S2);	
					}
				}else{
					strcat(tempdep,pch);
					strcat(tempdep,CTRL_S2);	
				}
			}
			pch = strtok(NULL,CTRL_S2);
			counter2++;
		}
		if(entries <= counter){
			entries++;
			ptrS = realloc(ptrS,(entries)*sizeof(Person));
		}
		gid=tempid;
		ptrS[counter].id = tempid;
		ptrS[counter].name = tempname;
		ptrS[counter].phone = tempphone;
		ptrS[counter].department = tempdep;
		counter++;
		free(pch);
	}
	fclose(fp);
	if(argc < TWO || argc > SIX){
		usage_add();
		usage_update();
		usage_delete();
		usage_user();
		usage_search();
	}else{
		if (!strcmp(argv[ONE],ADMIN) && argc>TWO){
			if(!strcmp(argv[TWO],UPDATE)){
				if(argc == SIX){
					updateInfo();
				}else{
					usage_update();
				}
			}else if(!strcmp(argv[TWO],ADD)){
				if(argc == SIX){
						addToFile(argv[THREE],argv[FOUR],argv[FIVE]);
				}else{
					usage_add();
				}
			}else if(!strcmp(argv[TWO],DELETE)){
				if(argc == FOUR){
					deleteFromFile(ptrS,atoi(argv[THREE]));
				}else{
					usage_delete();
				}
			}else{
				usage_add();
				usage_update();
				usage_delete();
			}
		}else if(!strcmp(argv[ONE],USER) && argc>TWO){
			int counter=ZERO;
			if(!strcmp(argv[TWO],FILTER) && argc==FOUR){
				if(strlen(argv[THREE])==ONE){					
					searchByLetter(ptrS,argv[THREE]);
				}else if(strlen(argv[THREE])==FOUR){
					searchByDigits(ptrS,argv[THREE]);
				}else{
					usage_search();
				}
			}else{
				usage_user();
				usage_search();
			}
		}else if(!strcmp(argv[ONE],USER) && argc==TWO){
			showList(ptrS);
		}else{
			usage_add();
			usage_update();
			usage_delete();
			usage_user();
			usage_search();
		}	
	}

	free(ptrS);
}
