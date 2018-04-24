#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//structs
typedef struct date
{
	int d, m, y; //year, month, day
} date;

typedef struct student
{
	char c_id[10], //class id
		 s_id[10], //student id
		 name[33]; //full name
	date dob;
	float ag; //average grade, 0 <= ag <= 4
} student;

typedef struct node
{
	student *s;
	struct node *next, *prev;
} node;

typedef struct list
{
	node *first, *last;
	int n;
} list;

typedef struct c_node
{
	char c_id[10];
	int aos, //amount of student
		e, //exellent 3.50 <= x < 4.00
		g, //good 3.0 <= x < 3.5
		m, //marginal 2.00 <= x < 3.0
		a, //average 1.00 <= x < 2.0
		f; //fail 0 <= x < 1.00
	struct c_node *next, *prev;
} c_node;

typedef struct c_list
{
	int taos; //total amount of student
	c_node *first, *last;
} c_list;

bool valda(date d); //validating date
void init(list *L);
student *cr_std(char* c_id, char* s_id, char* name, date dob, float ag);
date *cr_date(int d, int m, int y);
node *cr_node(student *s);
void add_std(list *L, student *s);
void rmv_std(list *L, student *s);
void rmv_f_std(list *L); //remove first student
void rmv_l_std(list *L); //remove last student
void rmv_o_std(list *L); //remove the only student
void swap_node(node *a, node *b);
void nava(char *name);
node *ind(list *L, int i); //index
void sts(student *s, char **rs); //student to string

char *dts(date d); //date to string
char *its(int x); //int to string
bool earl(date d1, date d2); //earlier
bool sada(date d1, date d2);

void init_c(c_list *L);
c_node *c_ex(c_list *cL, char *c_id);
c_node *cr_c(char *c_id);
void cna(c_node *cn, float ag); //check and add
void add_c(c_list *cL, student *s);
void calc_c(c_list *cL, list *L);

//
bool sada(date d1, date d2)
{
	return (d1.d == d2.d && d1.m == d2.m && d1.y == d2.y);
}

bool earl(date d1, date d2)
{	
	if(d1.y > d2.y) return false;
	else if(d1.y < d2.y) return true;
	else
		if(d1.m > d2.m) return false;
		else if(d1.m < d2.m) return true;
		else
			if(d1.d > d2.d) return false;
			else if(d1.d < d2.d) return true;
			else return false;
}

bool valda(date d)
{
	//year > 1900, 1 <= month <= 12, 1 <= day <= 31
	if(d.y < 1990 || d.y > 2018 || d.m < 1 || d.m > 12 || d.d < 1 || d.d > 31)
	{
		return false;
	}
	
	//				1   2   3   4   5   6   7   8   9   10  11  12
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if((d.y % 4 == 0 && d.y % 25 != 0) || d.y % 400 == 0)
	{
		days[1] = 29;
	}
	
	return (d.d <= days[d.m - 1]);
}

student *cr_std(char* c_id, char* s_id, char* name, date dob, float ag)
{
	student *s = (student*)malloc(sizeof(student));
	strcpy(s->c_id, c_id);
	strcpy(s->s_id, s_id);
	strcpy(s->name, name);
	s->dob = dob;
	s->ag = ag;
	
	return s;
}

date *cr_date(int d, int m, int y)
{
	date *dt = (date*)malloc(sizeof(date));
	
	dt->d = d;
	dt->m = m;
	dt->y = y;
	
	return dt;
}

void init(list *L)
{
	L->first = NULL;
	L->last = NULL;
	L->n = 0;
}

node *cr_node(student *s)
{
	node *n = (node*)malloc(sizeof(node));
	n->s = s;
	n->next = NULL;
	n->prev = NULL;
	
	return n;
}

void add_std(list *L, student *s)
{
	++(L->n);
	
	if(L->first== NULL)
	{
		L->first = cr_node(s);
		L->last = L->first;
		return;
	}
	
	L->last->next = cr_node(s);
	L->last->next->prev = L->last;
	L->last = L->last->next;
}

void rmv_o_std(list *L)
{
	if(L->n == 1)
	{
		free(L->first);
		L->first = NULL;
		L->last = NULL;
		L->n = 0;
	}
}

void rmv_f_std(list *L) //remove first student
{
	if(L->n == 1)
	{
		rmv_o_std(L);
		return;
	}

	if(L->n > 0)
	{
		node *n = L->first;
		L->first = n->next;
		L->first->prev = NULL;
		free(n);
		--(L->n);
	}

}

void rmv_l_std(list *L)
{
	if(L->n == 1)
	{
		rmv_o_std(L);
		return;
	}
	
	if(L->n > 0)
	{
		node *n = L->first;
		while(n->next->next != NULL)
		{
			n = n->next;
		}
		
		free(n->next);
		n->next = NULL;
		L->last = n;
		--(L->n);
	}
}

void rmv_std(list *L, student *s)
{	
	if(L->n > 0)
	{
		if((L->first)->s == s)
		{
			rmv_f_std(L);
			return;
		}
		
		if((L->last)->s == s)
		{
			rmv_l_std(L);
			return;
		}
		
		node *n = (L->first);
		while(n != NULL)
		{
			if(n->s == s)
			{
				(n->prev)->next = n->next;
				(n->next)->prev = n->prev;
				
				free(n);
				--(L->n);
				
				return;
			}
			
			n = n->next;
		}
	}
}

int aon(int x) //amount of number
{
	int rs = 0;
	
	while(x != 0)
	{
		x = x / 10;
		++rs;
	}
	
	return rs;
}

char *its(int x) //int to string
{
	int i, n = aon(x);
	
	char *rs = (char*)malloc(sizeof(char) * n);
	
	for(i = 0; i < n; ++i)
	{
		rs[n - i - 1] = (x % 10) + 48;
		x = x / 10;
	}
	
	return rs;
}

char *dts(date d)
{
	char *rs = (char*)malloc(10 * sizeof(char));
	sprintf(rs, "%2.2d/%2.2d/%4.4d", d.d, d.m, d.y);
	
	return rs;
}

void swap_node(node *a, node *b)
{
	student *s = a->s;
	a->s = b->s;
	b->s = s;
}

void nava(char *name)
{
	int i, n = strlen(name);
	
	for(i = 0; i < n; ++i)
	{
		if(name[i] == ' ')
		{
			//if(name[i + 1])
		}
	}
}

node *ind(list *L, int i)
{
	if(i == 0)
	{
		return L->first;
	}
	
	if(i >= L->n - 1)
	{
		return L->last;
	}
	
	node *tr = L->first;
	int j = 0;
	while(j < i)
	{
		tr = tr->next;
		++j;
	}
	
	return tr;
}

void sts(student *s, char **rs)
{
	*rs = (char*)malloc(80*sizeof(char));
	sprintf(*rs, "%s %s %s %s %f", s->c_id, s->s_id, s->name, dts(s->dob), s->ag);
}

void init_c(c_list *cL)
{
	cL->taos = 0;
	cL->first = NULL;
	cL->last = NULL;
}

void cna(c_node *cn, float ag)
{
	if(cn != NULL)
	{
		++(cn->aos);
		
		if(ag >= 3.5) ++(cn->e);
		else if(ag >= 3) ++(cn->g);
		else if(ag >= 2) ++(cn->m);
		else if(ag >= 1) ++(cn->a);
		else ++(cn->f);
	}
}

c_node *c_ex(c_list *cL, char *c_id) //class existed
{
	c_node *tr = cL->first;
	while(tr != NULL)
	{
		if(strcmp(tr->c_id, c_id) == 0)
		{
			return tr;
		}
		
		tr = tr->next;
	}
	
	return NULL;
}

void calc_c(c_list *cL, list *L)
{
	node *tr = L->first;
	
	while(tr != NULL)
	{
		add_c(cL, tr->s);
		tr = tr->next;
	}
}

//int aos, //amount of student
//		e, //exellent 3.50 <= x <= 4.00
//		g, //good 3.0 <= x < 3.5
//		m, //marginal 2.00 <= x < 3.0
//		a, //average 1.00 <= x < 2.0
//		f; //fail 0 <= x < 1.00

c_node *cr_c(char *c_id)
{
	c_node *cn = (c_node*)malloc(sizeof(c_node));
	
	strcpy(cn->c_id, c_id);
	cn->aos = 0; //amount of student
	
	cn->e = 0; //exellent
	cn->g = 0; //good
	cn->m = 0; //marginal
	cn->a = 0; //average
	cn->f = 0; //fail
	
	cn->next = NULL;
	cn->prev = NULL;
	
	return cn;
}

void add_c(c_list *cL, student *s)
{
	++cL->taos;
	
	c_node *cn = c_ex(cL, s->c_id);
	if(cn != NULL)
	{
		cna(cn, s->ag);
	}
	else
	{
		cn = cr_c(s->c_id);
		cna(cn, s->ag);
		
		if(cL->first == NULL)
		{
			cL->first = cn;
			cL->last = cn;
			return;
		}
		
		cn->prev = cL->last;
		cL->last->next = cn;
		cL->last = cn;
	}
}
