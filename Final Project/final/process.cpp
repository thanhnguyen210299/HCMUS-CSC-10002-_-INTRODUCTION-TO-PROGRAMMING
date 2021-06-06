
#include "process.h"

void gotoxy(int column, int line)
{
	COORD coordinate;
	coordinate.X = column;
	coordinate.Y = line;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

//V? hình ch? nh?t
void DrawRectangle(point upleft, point downright)
{
	gotoxy(upleft.x, upleft.y);
	printf("%c", UPLEFT);
	gotoxy(downright.x, upleft.y);
	printf("%c", UPRIGHT);
	gotoxy(downright.x, downright.y);
	printf("%c", DOWNRIGHT);
	gotoxy(upleft.x, downright.y);
	printf("%c", DOWNLEFT);
	for (int i = upleft.x + 1; i < downright.x; i++)
	{
		gotoxy(i, upleft.y);
		printf("%c", HORIZONTAL);
		gotoxy(i, downright.y);
		printf("%c", HORIZONTAL);
	}
	for (int i = upleft.y + 1; i < downright.y; i++)
	{
		gotoxy(upleft.x, i);
		printf("%c", VERTICAL);
		gotoxy(downright.x, i);
		printf("%c", VERTICAL);
	}

}

int loadcsv(char **&file, char ***&data, char *fileName, int column)
{
	//char **file;	//save info of rows of csv file
	//char ***data;	//save info of cells, data in this array will be copied into structs

	FILE *ptr = fopen(fileName, "r");

	if (ptr == NULL)
	{
		printf("Can't open input file!\n");
		_getch();
		return -1;
	}

	int m = 0;
	char ch = fgetc(ptr);
	while (ch != EOF)
	{
		if (ch == '\n')
			m++;
		ch = fgetc(ptr);
	}


	fseek(ptr, 0, SEEK_SET);

	int n = column;	//m: row, n: column; 

	data = new char**[m];
	file = new char*[m];

	if (data == NULL || file == NULL)
	{
		printf("Not enough memory!\n");
		return 0;
	}
	//load file csv to an array

	//load the first line of csv file (Class,17APCS1,)
	file[0] = new char[max];
	//fgets(file[0], max, ptr);
	data[0] = new char*[2];
	fgets(file[0], max, ptr);

	if (file[0] == NULL || data[0] == NULL)
	{
		printf("Not enough memory!\n");
		return 0;
	}

	char *temp = strtok(file[0], ",\n");
	int j = 0;

	while (temp != NULL && j < 2)
	{
		data[0][j] = temp;
		temp = strtok(NULL, ",\n");
		j++;
	}
	//load the rest of the csv file
	for (int i = 1; i < m; i++)/////////////////////moi sua tu i=0 sang i=1
	{
		file[i] = new char[max];
		//fgets(file[i], max, ptr);
		data[i] = new char*[n];
		fgets(file[i], max, ptr);

		if (file[i] == NULL || data[i] == NULL)
		{
			printf("Not enough memory!\n");
			return 0;
		}

		char *temp = strtok(file[i], ",\n");
		int j = 0;

		while (temp != NULL && j < n)
		{
			data[i][j] = temp;
			temp = strtok(NULL, ",\n");
			j++;
		}

	}

	fclose(ptr);
	return m;

	_getch();
}

int savecsv(char ***data, char *fileName, int column, int row)
{
	//save to another csv file
	int m = row, n = column;

	FILE *output = fopen(fileName, "w");
	if (!output)
	{
		printf("Can't open output file!\n");
		_getch();
		return -1;
	}

	//save the first line of csv file
	fprintf(output, "%s,", data[0][0]);
	fprintf(output, "%s,\n", data[0][1]);

	//save the rest of csv file
	for (int i = 1; i < m; i++)
	{
		fprintf(output, "%s", data[i][0]);
		for (int j = 1; j < n; j++)
			fprintf(output, ",%s", data[i][j]);
		fprintf(output, "\n");
	}

	fclose(output);
}

int addNewClass()
{
	clrscr();
	system("color 30");
	char fileName[] = "Classes.csv";
	char **file;
	char ***data;

	int column = 3;
	int numberOfClasses = loadcsv(file, data, fileName, column);
	int row = numberOfClasses;
	// Input Name Class
	printf("\nInput New Class: \n");
	char* className = new char[MAX];
	char *filename = new char[MAX];
	gets_s(className, MAX);

	//Find class in Classes.csv
	bool kt = false;
	for (int i = 0; i < numberOfClasses; i++)
		if (strcmp(data[i][1], className) == 0)
		{
			filename = data[i][2];
			kt = true;
			break;
		}
	if (kt)
		printf("\nClass already exists\n");
	else
	{
		//Create a new file
		char *tmp = new char[MAX];
		className = strupr(className);
		strcpy(tmp, className);
		strcat(tmp, ".csv");
		FILE  *input = fopen(tmp, "w");////////////////////////////////////////

		fprintf(input, "Class,");
		fprintf(input, "%s,\n", className);
		fprintf(input, "No,ID Student,Password,Student Name,Email,Mobile Phone\n");

		fclose(input);

		//Add new class into data array
		data[row] = new char*[column];
		for (int i = 0; i < column; i++)
		{
			data[row][i] = new char[max];
		}
		data[row][0] = itoa(row, data[row][0], 10);
		data[row][1] = className;
		data[row][2] = tmp;

		//Update Classes.csv file
		FILE *classes = fopen("Classes.csv", "a");////ghi de len file cu luon!
		fprintf(classes, "%s", data[row][0]);
		for (int i = 1; i < column; i++)
			fprintf(classes, ",%s", data[row][i]);
		fprintf(classes, "\n");

		fclose(classes);

		printf("Added successfully!\n");

	}
	_getch();
	return 0;
}

int viewClassList()
{
	clrscr();
	system("color 30");
	int column = 2;
	char **file, ***data;
	char fileName[] = "Classes.csv";
	int row = loadcsv(file, data, fileName, column);

	printf("CLASSES:\n");
	for (int i = 1; i < row; i++)
	{
		for (int j = 0; j < column; j++)
			printf("%s ", data[i][j]);
		printf("\n");
	}
	_getch();
	return 0;
}

int viewClassStudent()
{
	clrscr();
	char fileName[] = "Classes.csv";
	char **file;
	char ***data;

	int column = 3;
	int row = loadcsv(file, data, fileName, column);

	// Input Name Class
	printf("\nEnter name of the class: \n");
	char* className = new char[MAX];
	char *filename = new char[MAX];
	gets_s(className, MAX);

	//Find class in Classes.csv
	bool kt = false;
	for (int i = 0; i < row; i++)
		if (stricmp(data[i][1], className) == 0)
		{
			filename = data[i][2];
			kt = true;
			break;
		}
	if (kt)
	{
		column = 6;
		row = loadcsv(file, data, filename, column);
		printf("Class: %s\n", className);
		for (int i = 1; i < row; i++)
		{
			printf("%s", data[i][0]);
			for (int j = 1; j < column; j++)
				printf(",%s", data[i][j]);
			printf("\n");
		}
	}
	else printf("This class doesn't exist!\n");
	_getch();
	return 0;

}


int addNewCourse()
{
	clrscr();
	system("color 30");
	char fileName[] = "Courses.csv";
	char **file;
	char ***data;

	int column = 11;
	int numberOfCourses = loadcsv(file, data, fileName, column);
	int row = numberOfCourses;
	// Input Name Course
	char *courseCode = new char[MAX], *courseName = new char[MAX], *lecturer = new char[MAX], *academicYear = new char[MAX], *semester = new char[MAX];
	char *startDate = new char[MAX], *endDate = new char[MAX], *beginTime = new char[MAX], *endTime = new char[MAX], *dateInWeek = new char[MAX];
	printf("--------Add a new course: ----------\n");
	scanf_s("%c");
	printf("Course code: ");
	gets_s(courseCode, MAX);
	printf("Academic year: ");
	gets_s(academicYear, MAX);
	printf("Semester (1 or 2 or 3): ");
	gets_s(semester, MAX);
	printf("Course name: ");
	gets_s(courseName, MAX);
	printf("Lecturer username: ");
	gets_s(lecturer, MAX);
	printf("Start at (date): ");
	gets_s(startDate, MAX);
	printf("End at (date): ");
	gets_s(endDate, MAX);
	printf("From (time): ");
	gets_s(beginTime, MAX);
	printf("To (time): ");
	gets_s(endTime, MAX);
	printf("Date of week: ");
	gets_s(dateInWeek, MAX);
	//Find courses in Courses.csv
	bool kt = false;
	for (int i = 0; i < numberOfCourses; i++)
		if (strcmp(data[i][1], courseCode) == 0)
		{
			kt = true;
			break;
		}
	if (kt)
		printf("\nCourse already exists\n");
	else
	{
		char *tmp = new char[MAX];

		//Add new courses into data array
		data[row] = new char*[column];
		for (int i = 0; i < column; i++)
		{
			data[row][i] = new char[max];
		}
		data[row][0] = itoa(row, data[row][0], 10);
		data[row][1] = courseCode;
		data[row][2] = academicYear;
		data[row][3] = semester;
		data[row][4] = courseName;
		data[row][5] = lecturer;
		data[row][6] = startDate;
		data[row][7] = endDate;
		data[row][8] = beginTime;
		data[row][9] = endTime;
		data[row][10] = dateInWeek;

		//Update Coursess.csv file
		FILE *courses = fopen("Courses.csv", "a");////ghi de len file cu 
		fprintf(courses, "%s", data[row][0]);
		for (int i = 1; i < column; i++)
			fprintf(courses, ",%s", data[row][i]);
		fprintf(courses, "\n");
		//file courses ko end bang \n
		fclose(courses);

		printf("Added successfully!\n");

	}

	delete[]courseCode; delete[]academicYear; delete[]semester; delete[]courseName; delete[]lecturer;
	delete[]startDate; delete[]endDate; delete[]beginTime; delete[]endTime; delete[]dateInWeek;
	_getch();
	return 0;
}

int editCourse()
{
	clrscr();
	system("color 30");
	char fileName[] = "Courses.csv";
	char **file;
	char ***data;

	int column = 11;
	int numberOfCourses = loadcsv(file, data, fileName, column);
	int row = numberOfCourses;
	// Input Name Course
	char *courseCode = new char[MAX], *courseName = new char[MAX], *lecturer = new char[MAX], *academicYear = new char[MAX], *semester = new char[MAX];
	char *startDate = new char[MAX], *endDate = new char[MAX], *beginTime = new char[MAX], *endTime = new char[MAX], *dateInWeek = new char[MAX];
	printf("--------Add a new course: ----------\n");
	scanf_s("%c");
	printf("Course code: ");
	gets_s(courseCode, MAX);
	printf("Academic year: ");
	gets_s(academicYear, MAX);
	printf("Semester (1 or 2 or 3): ");
	gets_s(semester, MAX);
	printf("Course name: ");
	gets_s(courseName, MAX);
	printf("Lecturer username: ");
	gets_s(lecturer, MAX);
	printf("Start at (date): ");
	gets_s(startDate, MAX);
	printf("End at (date): ");
	gets_s(endDate, MAX);
	printf("From (time): ");
	gets_s(beginTime, MAX);
	printf("To (time): ");
	gets_s(endTime, MAX);
	printf("Date of week: ");
	gets_s(dateInWeek, MAX);
	//Find class in Courses.csv
	bool kt = false;
	int index = -1;
	for (int i = 0; i < numberOfCourses; i++)
		if (strcmp(data[i][1], courseCode) == 0)
		{
			index = i;
			kt = true;
			break;
		}
	if (!kt)
		printf("\nCourse doesn't exist!\n");
	else
	{
		printf("row %d\n", row);
		FILE *output = fopen("Courses.csv", "w");
		fprintf(output, "No,Course Code,Year,Semester,Course Name,Lecturer,Date Start,Date End,Time Begin,Time End,Day of week\n");
		for (int i = 1; i < row; i++)
		{
			if (i != index)
			{
				fprintf(output, "%s", data[i][0]);

				for (int j = 1; j < column; j++)
					fprintf(output, ",%s", data[i][j]);
				fprintf(output, "\n");
			}
			else
			{
				fprintf(output, "%d", index);
				fprintf(output, ",%s", courseCode);
				fprintf(output, ",%s", academicYear);
				fprintf(output, ",%s", semester);
				fprintf(output, ",%s", lecturer);
				fprintf(output, ",%s", courseName);
				fprintf(output, ",%s", lecturer);
				fprintf(output, ",%s", startDate);
				fprintf(output, ",%s", endDate);
				fprintf(output, ",%s", beginTime);
				fprintf(output, ",%s", endTime);
				fprintf(output, ",%s\n", dateInWeek);


			}
		}
		fclose(output);
		printf("Edited!");
	}
	_getch();
	return 0;
}

int removeCourse()
{

	clrscr();
	system("color 30");
	char fileName[] = "Courses.csv";
	char **file;
	char ***data;

	int column = 11;
	int numberOfCourses = loadcsv(file, data, fileName, column);
	int row = numberOfCourses;
	// Input Name Class
	char *courseCode = new char[MAX];
	printf("----------Remove Course---------\n");
	scanf_s("%c");
	printf("Enter course's code: ");
	gets_s(courseCode, MAX);

	//Find class in Classes.csv
	bool kt = false;
	int index = -1;
	for (int i = 0; i < numberOfCourses; i++)
		if (strcmp(data[i][1], courseCode) == 0)
		{
			kt = true;
			index = i;/////////////////position of the course in courses.csv
			break;
		}
	if (!kt)
		printf("\nCourse does not exist!\n");
	else
	{
		FILE *output = fopen("Courses.csv", "w");
		fprintf(output, "No,Course Code,Year,Semester,Course Name,Lecturer,Date Start,Date End,Time Begin,Time End,Day of week\n");
		for (int i = 1; i < row; i++)
		{
			if (i != index)
			{
				if (i > index)
					fprintf(output, "%d", atoi(data[i][0]) - 1);
				else fprintf(output, "%s", data[i][0]);

				for (int j = 1; j < column; j++)
					fprintf(output, ",%s", data[i][j]);
				fprintf(output, "\n");
			}
		}
		fclose(output);
		printf("Removed!");
	}

	_getch();
	return 0;
}

int  viewCourseList()
{
	clrscr();
	system("color 30");
	char fileName[] = "Courses.csv";
	char **file;
	char ***data;

	int column = 11;
	int numberOfCourses = loadcsv(file, data, fileName, column);
	int row = numberOfCourses;

	for (int i = 1; i < row; i++)
	{
		printf("%s", data[i][0]);
		for (int j = 1; j < column; j++)
			printf(",%s", data[i][j]);
		printf("\n");
	}
	_getch();
	return 0;
}