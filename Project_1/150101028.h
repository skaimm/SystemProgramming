#ifndef sametkocabas
#define sametkocabas
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#define SIZE 1024
#define LENGTH 100
#define ADMIN "-a"
#define USER "-u"
#define ADD "add"
#define DELETE "delete"
#define UPDATE "update"
#define FILTER "filter"
#define FILE_WRITE "w"
#define FILE_READ "r"
#define FILE_APPEND "a"
#define FILENAME "person.txt"
#define TEMPFILE "person2.txt"
#define ALLUSERS "allusers.txt"
#define CTRL_N '\n'
#define CTRL_S ' '
#define CTRL_S2 " "
#define USAGE "Usage: ./$(BIN) <typeOfUser> <command> <string> <string> <string>"
#define USAGE_ADD "Usage: ./$(BIN) -a add <name> <phone> <department>"
#define USAGE_DEL "Usage: ./$(BIN) -a delete <id>"
#define USAGE_UPD "Usage: ./$(BIN) -a update <id> <type> <newInfo>"
#define USAGE_PHO "Usage: ./$(BIN) -u filter <phone>"
#define USAGE_LET "Usage: ./$(BIN) -u filter <letter>"
#define USAGE_USER "Usage: ./$(BIN) -u"
#define INFO_USER "NAME	PHONE	DEPARTMENT"
#define INFO_UPD "This Command is currently under Maintenance.."
#define INFO_FIL "There is no person start with"
#define INFO_PHO "There is no last numbers of phone are"
#define ERROR_MALLOC "Error:Unable to allocate required memory"
#define ERROR_FILE "Error : cannot open the Person.txt"
#define SUCCESS_ADD "Phone Number had been Saved Successfully"
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define SEVEN 7
#define EIGTH 8
#define NINE 9
#define TEN 10
#define ASCIICODE 48

int entries = TWO;
int gid =ZERO;
char buff[SIZE];

typedef struct {
	int id;
	char *name;
	char *phone;
	char *department;
}Person;

void usage();
void usage_add();
void usage_update();
void usage_delete();
void usage_search();
void usage_user();
void addToFile(char *arg1 , char *arg2 , char *arg3);
void deleteFromFile(Person *sp,int did);
void updateInfo();
void searchByLetter(Person *sp,char *arg);
void searchByDigits(Person *sp,char *arg);
void showList(Person *sp);

#endif
