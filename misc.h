#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define NWWS 80 //normal width size
#define NWHS 26 //normal height size

#define TOP 2187
#define BOT 8888

#define TLC 201 //top left char
#define TRC 187 //top right char
#define BLC 200 //bottom left char
#define BRC 188 //bottom right char
#define HFC 186 //horizontal frame char
#define VFC 205 //vertical frame char

void p(char *str);
void p_int(int i);
void p_fl(float fl);
void p_nl(char *str);
void hl(); //horizontal line
bool r_int(int *i); //read int
bool r_str(char *str, int n); //read string
bool r_fl(float *f); //read float
void clrscr();
void cll(); //clear line
void paktc(); //press any key to continue
void ssp(char *str, int w);
char *upper(char *str);
bool il(char c); //is lowercase
bool iu(char c); //is uppercase
char tl(char c); //to lowercase
char tu(char c); //to uppercase

bool cian(char c); //character is a number
bool r_date(date *d);

void gotoXY(int x, int y);
void getXY(int *x, int *y);
void goup();
void clls(int i);

char *gfn(char *name); //get first name

void psc(int c); //print special character
void polortrm(int left, int mid, int right); //print one left one right the rest middle
void ptobd(int slt); //print top or bottom border
void pofrmdl(); //print one framed line
void frmng(); //framing
void sccrs(bool flag); //set console cursor
void scrup(); //scroll up!

void clrscr()
{
	system("cls || clear");
}

void p(char *str)
{
	printf("%s", str);
}

void p_nl(char *str)
{
	printf("%s\n", str);
}

bool r_int(int *i)
{
	char str[10];
	int j;
	
	if(r_str(str, 10))
	{
		for(j = 0; j < strlen(str); ++j)
		{
			if(!cian(str[j]) && str[j] != '\0' && str[j] != '-')
			{
				return false;
			}
		}
		sscanf(str, "%d", i);
		return true;
	}
	
	return false;
}

bool r_str(char *str, int n)
{
	fflush(stdin);
	
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
	
	if(strlen(str) == 0 || strlen(str) > n - 1)
	{
		return false;
	}
	
	return true;
}

void hl(int l) //length
{
	while(l)
	{
		p("=");
		--l;
	}
	p_nl("");
}

bool r_fl(float *f)
{
	char str[10];
	int j;
	
	if(r_str(str, 10))
	{
		for(j = 0; j < strlen(str); ++j)
		{
			if(!cian(str[j]) && str[j] != '\0' && str[j] != '.')
			{
				return false;
			}
		}
		sscanf(str, "%f", f);
		return true;
	}
	
	return false;
}

void paktc()
{
	hl(25);
	p_nl("Bam phim bat ki de tiep tuc.");
	hl(25);
	getch();
}

void ssp(char *str, int w)
{
	int i, l = strlen(str);
	
	if(l > w)
	{
		for(i = 0; i < w - 3; ++i)
		{
			printf("%c", str[i]);
		}
		printf("...");
	}
	else
	{
		printf("%s", str);
		for(i = 0; i < w - l; ++i)
		{
			printf(" ");
		}
	}
}

bool iu(char c) //is uppercase
{
	return (c >= 65 && c <= 90); 
}

bool il(char c) //is lowercase
{
	return (c >= 97 && c <= 122);
}

char tu(char c)
{
	if(il(c))
	{
		return (c - 32);
	}
	return c;
}

char tl(char c)
{
	if(iu(c))
	{
		return (c + 32);
	}
	return c;
}

void p_nl_u(char *str)
{
	int i, n = strlen(str);
	for(i = 0; i < n; ++i)
	{
		if(il(str[i]))
		{
			printf("%c", str[i] - 32);
		}
		else
		{
			printf("%c", str[i]);
		}
	}
	printf("\n");
}

char *upper(char *str)
{
	int i = 0, n = strlen(str);
	char *rs = (char*)calloc(n + 1,sizeof(char));
	
	for(i = 0; i < n; ++i)
	{
		if(il(str[i]))
		{
			rs[i] = str[i] - 32;
		}
		else
		{
			rs[i] = str[i];
		}
	}
	
	return rs;
}

bool cian(char c)
{
	return (c >= '0' && c <= '9');
}

bool r_date(date *d)
{
	char str[50];
	int i;
	if(r_str(str, 50))
	{
		for(i = 0; i < strlen(str); ++i)
		{
			if(!cian(str[i]) && str[i] != '/')
			{
				return false;
			}
		}
		sscanf(str, "%d/%d/%d", &(d->d), &(d->m), &(d->y));
		return true;
	}
	
	return false;
	//scanf("%d/%d/%d", &(d->d), &(d->m), &(d->y));
}

void cll()
{
	p("\r");
	int i = 79;
	while(i)
	{
		p(" ");
		--i;
	}
	p("\r");
}

void gotoXY(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void getXY(int *x, int *y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD rs;
	rs.X = -1;
	rs.Y = -1;
	
	if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		rs = csbi.dwCursorPosition;
	}
	
	*x = rs.X;
	*y = rs.Y;
}

void goup()
{
	int x, y;
	getXY(&x, &y);
	gotoXY(x, y - 1);
}

void clls(int i) //clear lines
{
	getch();
	while(i)
	{
		cll();
		goup();
		--i;
	}
	cll();
}

char *gfn(char *name)
{
	int n = strlen(name);
	char *i = name;
	while(n)
	{
		if(name[n] == ' ')
		{
			i = &(name[n + 1]);
			break;
		}
		--n;
	}
	
	return i;
}

void psc(int c) //print special character
{
	printf("%c", c);
}

void ptobd(int slt) //print top or bottom border
{
	int c1, c2; //corner 1, corner 2
	if(slt == TOP)
	{
		c1 = TLC;
		c2 = TRC;
	}
	else if(slt == BOT)
	{
		c1 = BLC;
		c2 = BRC;
	}
	polortrm(c1, VFC, c2);
}

void pofrmdl() //print one framed line
{
	polortrm(HFC, ' ', HFC);
}

void polortrm(int left, int mid, int right) //print one left one right the rest mid
{
	psc(left);
	int i = NWWS - 2;
	while(i)
	{
		psc(mid);
		--i;
	}
	psc(right);
}

void frmng()
{
	char *cmd = calloc(15, sizeof(char));
	sprintf(cmd, "mode %d, %d", NWWS, NWHS);
	system(cmd);
	ptobd(TOP);
	int i = NWHS - 3;
	while(i)
	{
		pofrmdl();
		--i;
	}
	ptobd(BOT);
	gotoXY(1, 1);
	p("PHAN MEM QUAN LY SINH VIEN");
//	psc(TLC);
	sccrs(false);
	
	
	scrup();
}

void sccrs(bool flag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	GetConsoleCursorInfo(out, &cci);
	cci.bVisible = flag;
	SetConsoleCursorInfo(out, &cci);
}

void scrup() //scroll up!
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(out, &csbi);
	
	SMALL_RECT sre;
	sre = csbi.srWindow;
	sre.Top = sre.Top - NWHS;
	sre.Bottom = sre.Bottom - NWHS;
	SetConsoleWindowInfo(out, true, &sre);
}
