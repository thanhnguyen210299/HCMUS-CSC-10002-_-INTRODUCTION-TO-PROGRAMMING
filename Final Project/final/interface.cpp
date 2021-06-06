#include "interface.h"

//Hàm ?i?u khi?n m?i tên và enter.
STATUS key(int z) {
	if (z == 224) {
		char c;
		c = _getch();
		if (c == 72)
			return UP;
		if (c == 80)
			return DOWN;
		if (c == 77)
			return RIGHT;
		if (c == 75)
			return LEFT;
	}
	else if (z == 13)
		return ENTER;
	else if (z == ESC)
		return esc;
}

void draw(int x, int y, int color) {
	point upleft, downright;

	upleft.x = x;
	upleft.y = 13;
	downright.x = y;
	downright.y = 16;

	TextColor(color);
	DrawRectangle(upleft, downright);
}

int login(char *name, char *password, int &acctype)
{
	point upleft[5], downright[5];
	system("color 30");//T?o màu n?n cho giao di?n
	//// boundary
	///////////////////////////////////////////
	upleft[4].x = 40;
	upleft[4].y = 1;
	downright[4].x = 75;
	downright[4].y = 24;
	DrawRectangle(upleft[4], downright[4]);
	////user name
	////////////////////////////////////////////////////
	upleft[0].x = 45;
	upleft[0].y = 6;
	downright[0].x = 70;
	downright[0].y = 8;
	//////////////////////////////////////////////////////////
	////pass
	upleft[1].x = 45;
	upleft[1].y = 10;
	downright[1].x = 70;
	downright[1].y = 12;
	//////////////////////////////////////////////////////////////////////////
	////type of acc
	upleft[2].x = 45;
	upleft[2].y = 17;
	downright[2].x = 70;
	downright[2].y = 19;
	//////////////////////////////////////////
	//// log in
	upleft[3].x = 63;
	upleft[3].y = 21;
	downright[3].x = 72;
	downright[3].y = 23;
	///////////////////////////////////////
	gotoxy(45, 3);
	printf("STUDENT MANAGEMENT SYSTEM");
	gotoxy(45, 5);
	printf("User name");
	gotoxy(45, 9);
	printf("Password");
	gotoxy(45, 13);
	printf("Type of account");
	gotoxy(50, 14);
	printf("1.Student");
	gotoxy(50, 15);
	printf("2.Academic Staff");
	gotoxy(50, 16);
	printf("3.Lecturer");
	gotoxy(64, 22);
	printf(" LOG IN ");
	gotoxy(46, 7);

	/////////////////////////////////////////////
	int n = 4;
	int tt = 0;
	int mau[4];
	for (int i = 0; i < n; i++)
		mau[i] = MAUCHU;
	mau[0] = MAUNEN;
	///////////////////////////////////////////////////

	char **file, ***data;
	int row = 0, position = 0;

	while (1) {
		//v? các hình ch?  nh?t
		for (int i = 0; i < 4; i++) {
			TextColor(mau[i]);
			DrawRectangle(upleft[i], downright[i]);
		}
		//Di chuy?n con tr? ??n ?úng v? trí 
		//S? lý ??ng nh?p ? ?ây (ch?a làm)

		switch (tt) {
		case 0: {gotoxy(46, 7);
			gets_s(name, MAX);
			break; }
		case 1: {gotoxy(46, 11); gets_s(password, MAX); break; }
		case 2: {gotoxy(46, 18); scanf_s("%d", &acctype); break; }
		}

		////////////////////////////////////////////////////////////////
		//open file contain log in information

		if (acctype == 3 || acctype == 2)//staff, lecturer
		{
			char fileName[] = "StaffLecturer_list.csv";
			row = loadcsv(file, data, fileName, 7);

		}
		else if (acctype == 1)//student
		{
			char fileName[] = "Student_list.csv";
			row = loadcsv(file, data, fileName, 7);
		}

		bool check = 0;
		for (int i = 1; i < row; i++)
			if (strcmp(name, data[i][1]) == 0 && strcmp(password, data[i][2]) == 0)
			{
				check = 1;
				if (acctype == 2 || acctype == 3)
				{
					int type = atoi(data[i][6]);
					if (acctype != type) check = 0;
				}
				if (check == 1)
				{
					position = atoi(data[i][0]);
					break;
				}
				position = atoi(data[i][0]);
				//printf("%d\n", position);
			}



		////////////////////////////////////////////////////////////////
		int z = _getch();
		STATUS status = key(z);
		switch (status) {
		case UP: {
			if (tt == 0)
				tt = n - 1;
			else
				tt--;
			break;
		}
		case DOWN: {
			if (tt == n - 1)
				tt = 0;
			else
				tt++;
			break;
		}
		case ENTER:
		{
			if (tt == 3)
			{
				if (check == 1)
				{
					clrscr();
					dashboard(name, password, acctype, data, position, row);
					return 0;
				}
				else
				{
					gotoxy(30, 28);
					printf("Username/password/account type is incorrect! Please log in again!\n");
					Sleep(3000);
					clrscr();
					login(name, password, acctype);
					return tt;
				}

			}
			return tt;
			break;
		}
		}
		//Reset lai mau sau khi da chon lai thao tac de in ra
		for (int i = 0; i < n; i++)
			mau[i] = MAUCHU;
		mau[tt] = MAUNEN;

	}



}

int dashboard(char *name, char *password, int acctype, char ***data, int position, int row)
{
	system("color 30");

	point upleft, downright;
	//V? các hình ch? nh?t
	upleft.x = 39;
	upleft.y = 13;
	downright.x = 50;
	downright.y = 16;
	DrawRectangle(upleft, downright);

	upleft.x = 50;
	upleft.y = 13;
	downright.x = 61;
	downright.y = 16;
	DrawRectangle(upleft, downright);

	upleft.x = 61;
	upleft.y = 13;
	downright.x = 72;
	downright.y = 16;
	DrawRectangle(upleft, downright);

	upleft.x = 72;
	upleft.y = 13;
	downright.x = 83;
	downright.y = 16;
	DrawRectangle(upleft, downright);

	for (int i = 50; i < 83; i = i + 11)
	{
		gotoxy(i, 13);
		printf("%c", MIDDLEUP);
		gotoxy(i, 16);
		printf("%c", MIDDLEDOWN);
	}

	gotoxy(56, 11);
	printf("DASHBOARD");
	gotoxy(43, 14);
	printf("MENU");
	gotoxy(54, 14);
	printf("USER");
	gotoxy(54, 15);
	printf("INFO");
	gotoxy(63, 14);
	printf("CHANGE");
	gotoxy(63, 15);
	printf("PASSWORD");
	gotoxy(77, 14);
	printf("LOG");
	gotoxy(77, 15);
	printf("OUT");

	gotoxy(50, 19);
	printf("<< Press ESC to go back");
	///////////////////////////////////////////////
	int n = 4;
	int tt = 0;
	int mau[4];
	for (int i = 0; i < n; i++)
		mau[i] = MAUCHU;
	mau[0] = MAUNEN;


	while (1) {
		for (int i = 0; i < n; i++) {
			draw(40 + 11 * i, 49 + 11 * i, mau[i]);
		}

		int z = _getch();
		STATUS status = key(z);
		switch (status) {
		case LEFT: {
			if (tt == 0)
				tt = n - 1;
			else
				tt--;
			break;
		}
		case RIGHT: {
			if (tt == n - 1)
				tt = 0;
			else
				tt++;
			break;
		}
		case ENTER: {
			if (tt == 0)
			{
				switch (acctype)
				{
				case 1: { clrscr(); studentMenu(name, password, acctype, data, position, row); return 0; break; }
				case 2: { clrscr(); staffMenu(name, password, acctype, data, position, row); return 0; break; }
				case 3: { clrscr(); lecturerMenu(name, password, acctype, data, position, row); return 0; break; }
				default: { return tt; break; }
				}
			}
			else if (tt == 1)
			{
				clrscr();
				printInfo(name, password, acctype, data, position, row);
				return 0;
			}
			else if (tt == 2)
			{
				clrscr();
				changePass(name, password, acctype, data, position, row);
				_getch();
				return 0;
			}
			else if (tt == 3)
			{
				clrscr();
				login(name, password, acctype);
			}
		}
		case esc:
		{
			clrscr();
			login(name, password, acctype);
			return 0;
		}

		}
		//Reset lai mau sau khi da chon lai thao tac de in ra
		for (int i = 0; i < n; i++)
			mau[i] = MAUCHU;
		mau[tt] = MAUNEN;
	}
}

void printInfo(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	point upleft, downright;
	upleft.x = 38;
	upleft.y = 10;
	downright.x = 80;
	downright.y = 21;

	int po = position + 1;
	system("color 30");
	DrawRectangle(upleft, downright);
	gotoxy(50, 10);
	printf("INFORMATION");
	gotoxy(40, 12);
	printf("Username: %s", data[po][1]);
	gotoxy(40, 13);
	printf("Fullname: %s", data[po][3]);
	gotoxy(40, 14);
	printf("Email: %s", data[po][4]);
	gotoxy(40, 15);
	printf("Mobile Phone: %s", data[po][5]);
	gotoxy(40, 16);
	printf("Type: %d", acctype);
	gotoxy(40, 17);
	printf("Password: %s", data[po][2]);
	if (acctype == 1)
	{
		gotoxy(40, 18);
		printf("Class: %s", data[po][6]);
	}
	gotoxy(45, 20);
	printf("<< Press ESC to go back");

	int key = 0;
	while (key != ESC)
	{
		key = _getch();
		gotoxy(0, 0);
	}
	if (key == ESC)
	{
		clrscr();
		dashboard(name, password, acctype, data, position, row);
	}

}

void changePass(char *name, char *password, int acctype, char ***data, int position, int row)
{
	int po = position + 1;
	clrscr();
	system("color 30");
	point upleft, downright;
	upleft.x = 38;
	upleft.y = 10;
	downright.x = 80;
	downright.y = 18;

	DrawRectangle(upleft, downright);
	gotoxy(50, 10);
	printf("CHANGE PASSWORD");
	gotoxy(40, 12);
	printf("Old password: ");
	gotoxy(40, 13);
	printf("New password: ");
	gotoxy(40, 14);
	printf("Confirm password: ");
	gotoxy(45, 16);
	printf("<< Press ESC to go back");

	char oldpass[MAX], newpass[MAX], confirmation[MAX];
	char tmp[10]; //tmp is for nothing!
	gotoxy(0, 0);
	gets_s(tmp, 9);
	gotoxy(60, 12);
	gets_s(oldpass, MAX);
	gotoxy(60, 13);
	gets_s(newpass, MAX);
	gotoxy(60, 14);
	gets_s(confirmation, MAX);

	if (strcmp(newpass, confirmation) == 0 && strcmp(oldpass, data[po][2]) == 0)
	{
		strcpy(data[po][2], newpass);
		char filename[MAX];

		if (acctype == 1)
		{
			strcpy(filename, "Student_list.csv");
		}
		else strcpy(filename, "StaffLecturer_list.csv");

		FILE *output = fopen(filename, "w");
		if (!output)
		{
			gotoxy(45, 20);
			printf("Can't change password!");
			Sleep(3000);
			clrscr();
			dashboard(name, password, acctype, data, position, row);
			return;
		}
		else
		{
			int column = 7;////////////////////////////////////////////////////////////////////
			savecsv(data, filename, column, row);
			gotoxy(47, 20);
			printf("Changed password successfully!");
			Sleep(3000);
			clrscr();
			dashboard(name, password, acctype, data, position, row);
		}

	}
	else
	{
		gotoxy(47, 20);
		printf("Can't change password!");
		Sleep(3000);
		clrscr();
		dashboard(name, password, acctype, data, position, row);
		return;
	}

	int key = 0;
	while (key != ESC)
	{
		key = _getch();
		gotoxy(0, 0);
	}
	if (key == ESC)
	{
		clrscr();
		dashboard(name, password, acctype, data, position, row);
	}

}


int studentMenu(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	system("color 30");
	point upleft, downright;
	//V? vi?n ngoài
	upleft.x = 30;
	upleft.y = 10;
	downright.x = 94;
	downright.y = 20;
	DrawRectangle(upleft, downright);
	//v? các hình ch? nh?t nh?
	draw(34, 47, MAUCHU);
	draw(48, 61, MAUCHU);
	draw(62, 75, MAUCHU);
	draw(76, 89, MAUCHU);
	/////////////////////////////////
	TextColor(MAUCHU);
	gotoxy(35, 10);
	printf(" STUDENT MENU ");
	gotoxy(37, 14);
	printf("Check-in");
	gotoxy(51, 14);
	printf("View");
	gotoxy(51, 15);
	printf("Check-in");
	gotoxy(65, 14);
	printf("View");
	gotoxy(65, 15);
	printf("Score");
	gotoxy(79, 14);
	printf("Schedule");
	gotoxy(55, 18);
	printf("<< Press ESC to go back");
	///////////////////////////////////////
	int n = 4;
	int tt = 0;
	int back = 0;
	int *mau = new int[n];
	for (int i = 0; i < n; i++)
		mau[i] = MAUCHU;
	mau[0] = MAUNEN;
	while (1) {

		draw(34 + 14 * back, 47 + 14 * back, MAUCHU);//??i màu hcn tr??c
		draw(34 + 14 * tt, 47 + 14 * tt, MAUNEN);	//??i màu hcn hi?n t?i
		back = tt;

		int z = _getch();
		STATUS status = key(z);
		switch (status) {
		case LEFT: {
			if (tt == 0)
				tt = n - 1;
			else
				tt--;
			break;
		}
		case RIGHT: {
			if (tt == n - 1)
				tt = 0;
			else
				tt++;
			break;
		}
					//case ENTER: return tt;
		case esc:
		{
			clrscr();
			dashboard(name, password, acctype, data, position, row);
			return 0;

		}
		}

		//Reset lai mau sau khi da chon lai thao tac de in ra
		mau[tt] = MAUNEN;
	}


}

int lecturerMenu(char *name, char *password, int acctype, char ***data, int position, int row)
{
	system("color 30");
	point upleft, downright;
	//V? vi?n  ngoài
	upleft.x = 30;
	upleft.y = 10;
	downright.x = 90;
	downright.y = 20;
	DrawRectangle(upleft, downright);
	//V? hcn bên trong
	draw(35, 50, MAUCHU);
	draw(52, 67, MAUCHU);
	draw(69, 84, MAUCHU);
	//////////////////////////////////
	TextColor(MAUCHU);
	gotoxy(35, 10);
	printf(" LECTURER MENU ");
	gotoxy(40, 14);
	printf("Import");
	gotoxy(38, 15);
	printf("Scoreboard");
	gotoxy(58, 14);
	printf("Edit");
	gotoxy(58, 15);
	printf("Score");
	gotoxy(75, 14);
	printf("View");
	gotoxy(72, 15);
	printf("Scoreboard");
	gotoxy(51, 18);
	printf("<< Press ESC to go back");
	///////////////////////////////////////
	int n = 3;
	int tt = 0;
	int back = 0;
	int *mau = new int[n];
	for (int i = 0; i < n; i++)
		mau[i] = MAUCHU;
	mau[0] = MAUNEN;
	while (1) {

		draw(35 + 17 * back, 50 + 17 * back, MAUCHU);//??i màu hcn tr??c
		draw(35 + 17 * tt, 50 + 17 * tt, MAUNEN);	//??i màu hcn hi?n t?i
		back = tt;

		int z = _getch();
		STATUS status = key(z);
		switch (status) {
		case LEFT: {
			if (tt == 0)
				tt = n - 1;
			else
				tt--;
			break;
		}
		case RIGHT: {
			if (tt == n - 1)
				tt = 0;
			else
				tt++;
			break;
		}
					//case ENTER: return tt;
		case esc:
		{
			clrscr();
			dashboard(name, password, acctype, data, position, row);
			return 0;

		}
		}
		//Reset lai mau sau khi da chon lai thao tac de in ra
		mau[tt] = MAUNEN;
	}
}

int staffMenu(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	system("color 30");
	point upleft, downright;
	//V? vi?n ngoài
	upleft.x = 15;
	upleft.y = 10;
	downright.x = 109;
	downright.y = 20;
	DrawRectangle(upleft, downright);
	//V? hcn bên trong
	draw(21, 36, MAUCHU);
	draw(38, 53, MAUCHU);
	draw(55, 70, MAUCHU);
	draw(72, 87, MAUCHU);
	draw(89, 104, MAUCHU);
	//////////////////////////////////////////////
	TextColor(MAUCHU);
	gotoxy(21, 10);
	printf(" ACADEMIC STAFF MENU ");
	gotoxy(24, 14);
	printf("Students,");
	gotoxy(25, 15);
	printf("Classes");
	gotoxy(41, 14);
	printf("Courses");
	gotoxy(58, 14);
	printf("Schedule");
	gotoxy(74, 14);
	printf("Attendance");
	gotoxy(77, 15);
	printf("List");
	gotoxy(91, 14);
	printf("Scoreboard");
	gotoxy(50, 18);
	printf("<< Press ESC to go back");
	///////////////////////////////////////
	int n = 5;
	int tt = 0;
	int back = 0;
	int *mau = new int[n];
	for (int i = 0; i < n; i++)
		mau[i] = MAUCHU;
	mau[0] = MAUNEN;
	while (1) {

		draw(21 + 17 * back, 36 + 17 * back, MAUCHU);//??i màu hcn tr??c
		draw(21 + 17 * tt, 36 + 17 * tt, MAUNEN);	//??i màu hcn hi?n t?i
		back = tt;

		int z = _getch();
		STATUS status = key(z);
		switch (status) {
		case LEFT: {
			if (tt == 0)
				tt = n - 1;
			else
				tt--;
			break;
		}
		case RIGHT: {
			if (tt == n - 1)
				tt = 0;
			else
				tt++;
			break;
		}
		case ENTER: {
			if (tt == 0)
			{
				clrscr();
				student_class(name, password, acctype, data, position, row);
			}
			else if (tt == 1)
			{
				clrscr();
				course(name, password, acctype, data, position, row);
			}
			else if (tt == 2)
			{
				clrscr();
				schedule(name, password, acctype, data, position, row);
			}
			else if (tt == 3)
			{
				clrscr();
				attendance(name, password, acctype, data, position, row);
			}
			else if (tt == 4)
			{
				clrscr();
				scoreboard(name, password, acctype, data, position, row);
			}
			else return 0;
		}
		case esc:
		{
			clrscr();
			dashboard(name, password, acctype, data, position, row);
			return 0;

		}
		}
		//Reset lai mau sau khi da chon lai thao tac de in ra
		mau[tt] = MAUNEN;
	}
}


int control(str thaotac[], int n, char *name, char *password, int acctype, char ***data, int position, int row) {
	int tt = 0;
	int *mau = new int[n];
	for (int i = 0; i < n; i++)
		mau[i] = MAUCHU;
	mau[0] = MAUNEN2;
	while (1) {

		for (int i = 0; i < n; i++) {
			TextColor(mau[i]);
			gotoxy(43, 12 + i);
			printf("%s\n", thaotac[i]);
		}

		int z = _getch();
		STATUS status = key(z);
		switch (status) {
		case UP: {
			if (tt == 0)
				tt = n - 1;
			else
				tt--;
			break;
		}
		case DOWN: {
			if (tt == n - 1)
				tt = 0;
			else
				tt++;
			break;
		}
				   //case ENTER: return tt;
		case esc:
		{
			clrscr();
			staffMenu(name, password, acctype, data, position, row);
			return 0;

		}
		case ENTER:
		{
			return tt;
		}
		}
		//Reet lai mau sau khi da chon lai thao tac de in ra
		for (int i = 0; i < n; i++)
			mau[i] = MAUCHU;
		mau[tt] = MAUNEN2;
	}
}


int student_class(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	system("color 30");
	str thaotac[7] = {
		"1. Add a new student to a class",
		"2. Edit an existing student",
		"3. Remove a student",
		"4. Change students from class A to class B",
		"5. Add a new empty class",
		"6. View list of classes",
		"7. View list of students"
	};
	point upleft, downright;
	system("color 30");
	//V? vi?n ngoài
	upleft.x = 40;
	upleft.y = 9;
	downright.x = 90;
	downright.y = 24;
	DrawRectangle(upleft, downright);
	//////////////////////////////////////////////////////////
	gotoxy(43, 9);
	printf(" Student, Class ");

	gotoxy(50, 21);
	TextColor(12);
	printf("<< Press ESC to go back");
	////////////////////////////////////////////////////
	int option = -1;
	do option = control(thaotac, 7, name, password, acctype, data, position, row);
	while (option != 4 && option != 5 && option != 6);
	if (option == 4)
	{
		addNewClass();
	}
	else if (option == 5)
	{
		viewClassList();
	}
	else if (option == 6)
	{
		viewClassStudent();
	}

	clrscr();
	student_class(name, password, acctype, data, position, row);
	return option;

}

int course(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	system("color 30");
	str thaotac[4] = {
		"1. Add a new course",
		"2. Edit an existing course",
		"3. Remove a course",
		"4. View list of courses"
	};
	point upleft, downright;
	system("color 30");

	upleft.x = 40;
	upleft.y = 10;
	downright.x = 90;
	downright.y = 21;
	DrawRectangle(upleft, downright);
	//////////////////////////////////////////////////////
	gotoxy(43, 10);
	printf(" Course ");
	TextColor(12);
	gotoxy(50, 19);
	printf("<< Press ESC to go back");
	//////////////////////////////////////////////////////
	int option = -1;
	do
	{
		option = control(thaotac, 4, name, password, acctype, data, position, row);
	} while (option != 0 && option != 1 && option != 2 && option != 3);
	if (option == 0)
	{
		addNewCourse();
	}
	else if (option == 1)
	{
		editCourse();
	}
	else if (option == 2)
	{
		removeCourse();
	}
	else if (option == 3)
	{
		viewCourseList();
	}

	clrscr();
	course(name, password, acctype, data, position, row);
	return option;
}

int schedule(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	system("color 30");
	str thaotac[5] = {
		"1. Import courses' schedules from a csv file",
		"2. Add a course's schedule",
		"3. Edit a couse's schedule",
		"4. Remove a course's schedule",
		"5. View list of schedules"
	};
	point upleft, downright;
	system("color 30");

	upleft.x = 40;
	upleft.y = 10;
	downright.x = 90;
	downright.y = 21;
	DrawRectangle(upleft, downright);
	//////////////////////////////////
	gotoxy(43, 10);
	printf(" Schedule ");
	TextColor(12);
	gotoxy(50, 19);
	printf("<< Press ESC to go back");
	//////////////////////////////////////////////////////
	return control(thaotac, 5, name, password, acctype, data, position, row);
}

int attendance(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	system("color 30");
	str thaotac[2] = {
		"1. Search and view attendance list of a course",
		"2. Export attendance list to a csv file"
	};
	point upleft, downright;
	system("color 30");

	upleft.x = 40;
	upleft.y = 10;
	downright.x = 90;
	downright.y = 18;
	DrawRectangle(upleft, downright);
	////////////////////////////////////////////////////
	gotoxy(43, 10);
	printf(" Attendance List ");
	TextColor(12);
	gotoxy(50, 16);
	printf("<< Press ESC to go back");
	///////////////////////////////////////////////////////
	return control(thaotac, 2, name, password, acctype, data, position, row);
}

int scoreboard(char *name, char *password, int acctype, char ***data, int position, int row)
{
	clrscr();
	system("color 30");
	point upleft, downright;
	system("color 30");

	upleft.x = 40;
	upleft.y = 10;
	downright.x = 90;
	downright.y = 18;
	DrawRectangle(upleft, downright);
	str thaotac[2] = {
		"1. Search and view scoreboard of a course",
		"2. Export scoreboard to a csv file"
	};
	/////////////////////////////////////////////////////
	gotoxy(43, 10);
	printf(" Scoreboard ");
	TextColor(12);
	gotoxy(50, 16);
	printf("<< Press ESC to go back");
	////////////////////////////////////////////////////////
	return control(thaotac, 2, name, password, acctype, data, position, row);

}

