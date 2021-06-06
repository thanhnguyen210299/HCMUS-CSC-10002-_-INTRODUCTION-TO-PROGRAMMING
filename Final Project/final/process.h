#pragma warning(disable: 4996)
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include "console.h"
#include <stdlib.h>


#define UPLEFT 218
#define UPRIGHT 191
#define VERTICAL 179
#define HORIZONTAL 196
#define DOWNLEFT 192
#define DOWNRIGHT 217
#define MIDDLEUP 194
#define MIDDLEDOWN 193

#define MAX 50
#define max 200

struct point
{
	int x;
	int y;
};



void DrawRectangle(point upleft, point downright);
void gotoxy(int column, int line);
int loadcsv(char **&file, char ***&data, char *fileName, int column);
int savecsv(char ***data, char *fileName, int column, int row);
int addNewClass();
int viewClassList();
int viewClassStudent();
int addNewCourse();
int editCourse();
int removeCourse();
int  viewCourseList();