#include "interface.h"

int main()
{
	char name[MAX] = "", password[MAX] = "";
	int acctype = 0;
	char **file, ***data;
	data = new char**[10];

	login(name, password, acctype);
	_getch();
	return 0;
}
