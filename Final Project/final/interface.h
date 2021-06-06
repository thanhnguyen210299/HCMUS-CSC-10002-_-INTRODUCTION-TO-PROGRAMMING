#include "process.h"


#define MAUNEN 60
#define MAUCHU 48
#define MAUNEN2  176
#define ESC 27

typedef char str[50];
//?i?u khi?n lên, xu?ng, trái, ph?i, enter.
enum STATUS { UP, DOWN, LEFT, RIGHT, ENTER, esc };
STATUS key(int z);

void draw(int x, int y, int color);

int login(char *name, char *password, int &acctype);
int dashboard(char *name, char *password, int acctype, char ***data, int position, int row);
void printInfo(char *name, char *password, int acctype, char ***data, int position, int row);
void changePass(char *name, char *password, int acctype, char ***data, int position, int row);
int studentMenu(char *name, char *password, int acctype, char ***data, int position, int row);
int lecturerMenu(char *name, char *password, int acctype, char ***data, int position, int row);
int staffMenu(char *name, char *password, int acctype, char ***data, int position, int row);

int control(str thaotac[], int n, char *name, char *password, int acctype, char ***data, int position, int row);

int student_class(char *name, char *password, int acctype, char ***data, int position, int row);
int course(char *name, char *password, int acctype, char ***data, int position, int row);
int attendance(char *name, char *password, int acctype, char ***data, int position, int row);
int schedule(char *name, char *password, int acctype, char ***data, int position, int row);
int scoreboard(char *name, char *password, int acctype, char ***data, int position, int row);
