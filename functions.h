#include "structs.h"
#include "misc.h"

#define FILE_NAME "STD_DATA.BIN"

void std_inp(); //input
void std_out(); //output
void slt_p(int *slt, int min, int max);//selection prompt
void test();

void sort_std(list *L, int st, int sk); //sort students
bool cmp_std(student *s1, student *s2, int sk); //compare students
void bb_sort_std(list *L, int sk); //buble sort
void sl_sort_std(list *L, int sk); //selection sort
void ins_sort_std(list *L, int sk); //insertion sort
void q_sort_std(list *L, int left, int right, int sk); //quicksort left, right, sort key

void list_all(list *L); //list all students
void pg_p(list *L, int p); //paging print
void ssd(student *s); //show student data
void sne_std(student *s); //show and edit student
void edof(student *s, int f); //edit one field
void r_dob(student *s); //read date of birth
void edit_std(list *L);

bool filting(char *str, int slt, int f_slt, student *s); //find out if the student is filted by str or not
void ssfs(int *f_slt); //show search fields' selections

void show_stats(c_list *cL);
void c_stats(c_list *cL); //class stats
void strs_stats(c_list *cL); //show students results stats
void valstr(int f, char *str);

FILE *f;
list L;
student sastu = //sample student
{
	"XXXXXXXX",
	"XXXXXXXX",
	"XXXXXXXX",
	{
		6, 6, 1996
	},
	2.50
};

void std_inp()
{
	//if error occurs or there is no file, add none
	f = fopen(FILE_NAME, "rb");
	int n;
	fread(&n, sizeof(int), 1, f);
	
	int i;
	student *s;
	for(i = 0; i < n; ++i)
	{
		s = (student*)malloc(sizeof(student));
		fread(s, sizeof(student), 1, f);
		add_std(&L, s);
	}
	
	fclose(f);
}

void std_out()
{
	//before exit
	//write all to file
	
	if(L.n > 0)
	{
		f = fopen(FILE_NAME, "wb");
		fwrite(&(L.n), sizeof(int), 1, f);
		
		node *n = L.first;
		while(n != NULL)
		{
			fwrite(n->s, sizeof(student), 1, f);
			n = n->next;
		}
		
		fclose(f);
	}
}

void r_dob(student *s)
{
	while(true)
	{
		printf("%-21.21s", "   Ngay sinh: ");
		//p("Ngay sinh: ");
		r_date(&(s->dob));
		
		if(!valda(s->dob))
		{
			hl(25);
			p_nl("Sai dinh dang hoac ngay thang khong hop le.");
			clls(3);
		}
		else
		{
			break;
		}
	}
}

void ssd(student *s) //show student data
{
	hl(25);
	printf("1. %-18.18s", "Ma lop:"); p_nl(s->c_id);
	printf("2. %-18.18s", "Ma sinh vien:"); p_nl(s->s_id);
	printf("3. %-18.18s", "Ho ten:"); p_nl(s->name);
	printf("4. %-18.18s", "Ngay sinh:"); p_nl(dts(s->dob));
	printf("5. %-18.18s", "Diem trung binh:"); printf("%.2f", s->ag); p_nl("");
	hl(25);
}

void sne_std(student *s)
{
	int sl = 0;
	
	do
	{
		clrscr();
		p_nl_u("Thong tin hoc sinh.");
		ssd(s);
		p_nl("Nhap mot so tuong ung voi thong tin ban muon sua.");
		p_nl("Nhap 0 neu ban khong muon sua thong tin.");
		p_nl("Nhap -1 neu ban muon huy/xoa ho so.");
		hl(25);
		slt_p(&sl, -1, 5);
		
		switch(sl)
		{
			case -1:
				rmv_std(&L, s);
				return;
			break;
			
			case 0:
			break;
			
			case 1:
				//p("Nhap ma lop: ");	r_str(s->c_id, CID);
				edof(s, 1);
			break;
			case 2:
				//p("Nhap ma sinh vien: "); r_str(s->s_id, SID);
				edof(s, 2);
			break;
			case 3:
				//p("Nhap ho ten: ");	r_str(s->name, NAME);
				edof(s, 3);
			break;
			case 4:
				r_dob(s);
			break;
			case 5:
				//p("Nhap diem trung binh: "); r_fl(&(s->ag));
				edof(s, 4);
			break;
			default:
				p_nl("Lua chon khong hop le");
		}
		//getch();
	}
	while(sl != 0);
}

void list_all(list *L)
{
	if(L->n == 0)
	{
		clrscr();
		p_nl_u("Danh sach rong.");
		getch();
		return;
	}
	
	int p = 1, slt = 1;
	
	while(slt != 0)
	{
		clrscr();
		p_nl_u("Chuc nang liet ke tat ca ho so.");
		hl(73);
		printf("| %5.5s | %8.8s | %8.8s | %18.18s | %10.10s | %5.5s |\n",
			 "STT", "Ma lop", "MSSV", "Ho va ten", "Ngay sinh", "Diem");
		
		hl(73);
			pg_p(L, p);
		hl(73);
		
		p_nl("0. Quay lai.");
		p_nl("1. Chon STT ho so muon sua.");
		p_nl("2. Chon so trang muon den.");
		
		hl(25);
		
		slt_p(&slt, 0, 2);
		
		
		switch(slt)
		{
			case 0:
				
			break;
			
			case 1:
				edit_std(L);
			break;
			
			case 2:
				while(true)
				{
					printf("Nhap so trang ban muon den: ");
					if(r_int(&p) && p >= 1 && p <= L->n / 10 + 1)
					{
						break;
					}
					else
					{
						printf("So trang phai >= 1 va <= %d.\n", L->n / 10 + 1);
						cll(2);
					}
				}
			break;
		}
		
		
		//clrscr();
		
	}
}

void pg_p(list *L, int p)
{
	int i = 1;
	node *tr = L->first;
	
	while(tr != NULL)
	{
		if(i >= (p - 1)*10 && i < p*10)
		{
			printf("| %5.5d | %8.8s | %8.8s | %18.18s | %10.10s | %5.2f |\n",
				   i, tr->s->c_id, tr->s->s_id, tr->s->name, dts(tr->s->dob), tr->s->ag);
		}
		++i;
		tr = tr->next;
	}
	
	hl(73);
	char res[30];
	sprintf(res, "Trang %d/%d", p, (L->n)/10 + 1);
	printf("| %69.69s |\n", res);
//	hl(60);
}

void edit_std(list *L)
{
	int id, i;
	
	while(true)
	{
		printf("Nhap STT (1 <= STT <= %d): ", L->n); r_int(&id);
		
		if(id > 0 && id <= L->n)
		{
			break;
		}
		else
		{
			hl(18);
			p_nl("STT khong hop le.");
			clls(3);
		}
	}
	
	i = 0;
	node *n = L->first;
	while(n != NULL && i < id - 1)
	{
		n = n->next;
		++i;
	}
	
	sne_std(n->s);
}

void sort_std(list *L, int st, int sk)
{
	//st: sort type
	//sk: sort key
	
	switch(st)
	{
		case 1: //bubble sort
			bb_sort_std(L, sk);
		break;
		
		case 2: //selection sort
			sl_sort_std(L, sk);
		break;	
		
		case 3: //insertion sort
			ins_sort_std(L, sk);
		break;
		
		case 4: //quick sort
			q_sort_std(L, 0, L->n - 1, sk);
		break;
		
		default:
			return;
	}
}

void slt_p(int *slt, int min, int max) //selection prompt
{
	while(true)
	{
		p("Nhap lua chon cua ban: ");
		
		if(r_int(slt) && *slt >= min && *slt <= max)
		{
			break;
		}
		else
		{
			hl(23);
			p("Lua chon khong hop le!");
			clls(2);
			//hl(22);
		}
	}
}

void test()
{	
	p_nl("Mot so chuc nang thu nghiem.");
	hl(25);
	p_nl("0. Quay lai.");
	p_nl("1. Them  1 ho so.");
	p_nl("2. Them 10 ho so.");
	p_nl("3. Doi cho hoc sinh dau tien va cuoi cung.");
	p_nl("4. Lay ra hoc sinh o giua.");
	p_nl("5. .");
	hl(25);
	int slt;
	
	slt_p(&slt, 0, 5);
	student *s;
	switch(slt)
	{
		case 1:
			s = (student*)malloc(sizeof(student));
			(*s) = sastu;
			add_std(&L, s);
		break;
		case 2:
			p("");
			int i = 10;
			while(i)
			{
				s = (student*)malloc(sizeof(student));
				(*s) = sastu;
				add_std(&L, s);
				--i;
			}
		break;
		case 3:
			swap_node(L.first, L.last);
		break;
		
		case 4:
			sne_std(ind(&L, (L.n - 1)/2)->s);
		break;
	}
}

bool cmp_std(student *s1, student *s2, int sk) //compare students
{
	int rs = 0;
	
	switch(sk)
	{
		case 1:
			rs = strcmp(s1->s_id, s2->s_id);
		break;
		
		case 2:
			p("");
			char *n1 = upper(s1->name),
				 *n2 = upper(s2->name);
				 
			char *fn1 = gfn(n1),
				 *fn2 = gfn(n2);
				 
			rs = strcmp(fn1, fn2);
			if(rs == 0)
			{
				rs = strcmp(n1, n2);
				if(rs == 0)
				{
					return cmp_std(s1, s2, 1);
				}
			}
			
			free(n1);
			free(n2);
		break;
		
		case 3:
			if(sada(s1->dob, s2->dob))
			{
				return cmp_std(s1, s2, 1);
			}
			return earl(s1->dob, s2->dob);
		break;
		
		case 4:
			if(s1->ag == s2->ag)
			{
				return cmp_std(s1, s2, 1);
			}
			return (s1->ag < s2->ag);
		break;
	}
	
	return (rs < 0);
}

void bb_sort_std(list *L, int sk)
{
	node *ltf = L->last, //last to first
		 *ltf_p = (L->last)->prev; //last to first previous
	
	while(ltf != NULL)
	{
		ltf_p = ltf->prev;
		while(ltf_p != NULL)
		{
			if(cmp_std(ltf->s, ltf_p->s, sk))
			{
				swap_node(ltf, ltf_p);
			}
			
			ltf_p = ltf_p->prev;
		}
		
		ltf = ltf->prev;
	}
}

void sl_sort_std(list *L, int sk)
{
	node *ftl = L->first, *min, //first to last
		 *ftl_n;
	while(ftl != NULL)
	{
		min = ftl;
		ftl_n = ftl->next;
		while(ftl_n != NULL)
		{
			if(cmp_std(ftl_n->s, min->s, sk))
			{
				min = ftl_n;
			}
			
			ftl_n = ftl_n->next;
		}
		swap_node(ftl, min);
		ftl = ftl->next;
	}
}

void ins_sort_std(list *L, int sk)
{
	node *ftl = L->first,
		 *ftl_p;
	
	while(ftl != NULL)
	{
		ftl_p = ftl;
		while(ftl_p->prev != NULL && cmp_std(ftl_p->s, ftl_p->prev->s, sk))
		{
			swap_node(ftl_p, ftl_p->prev);
			ftl_p = ftl_p->prev;
		}
		
		ftl = ftl->next;
	}
}

void q_sort_std(list *L, int left, int right, int sk) //left, right, sort key
{
	int i = left, j = right,
		mid = left + (right - left) / 2;
	
	node *ftl = ind(L, i), //first to last
		 *ltf = ind(L, j), //last to first
		 *pvt = ind(L, j); //pvt = mid doesn't work?
	
	while(i <= j && ftl != NULL && ltf != NULL)
	{
		while(cmp_std(ftl->s, pvt->s, sk) && ftl != NULL)
		{
			++i;
			ftl = ftl->next;
		}
		while(cmp_std(pvt->s, ltf->s, sk) && ltf != NULL)
		{
			--j;
			ltf = ltf->prev;
		}
		if(i <= j)
		{
			swap_node(ftl, ltf);
			++i;
			ftl = ftl->next;
			--j;
			ltf = ltf->prev;
		}
	}
	
	if(i < right) 	q_sort_std(L, i, right, sk);
	if(left < j) 	q_sort_std(L, left, j, sk);
}

bool filting(char *str, int slt, int f_slt, student *s)
{	
	if(slt == 1)
	{
		switch(f_slt)
		{
			case 1:
				return (strcmp(str, upper(s->s_id)) == 0);
			case 2:
				return (strcmp(str, upper(s->c_id)) == 0);
			case 3:
				return (strcmp(str, upper(s->name)) == 0);
			case 4:
				return (strcmp(str, dts(s->dob)) == 0);
		}
	}
	else if(slt == 2)
	{
		switch(f_slt)
		{
			case 1:
				return (strstr(upper(s->s_id), str) != NULL);
			case 2:
				return (strstr(upper(s->c_id), str) != NULL);
			case 3:
				return (strstr(upper(s->name), str) != NULL);
			case 4:
				return (strstr(dts(s->dob), str) != NULL);
		}
	}
	
	return false;
}

void ssfs(int *f_slt)
{
	hl(25);
	p_nl_u("Cac truong tim kiem:");
	hl(25);
	p_nl("0. Quay lai.");
	p_nl("1. Ma sinh vien.");
	p_nl("2. Ma lop.");
	p_nl("3. Ho va ten.");
	p_nl("4. Ngay thang nam sinh.");
	hl(25);
	slt_p(f_slt, 0, 4);
}

void show_stats(c_list *cL)
{
	p_nl_u("Chuc nang liet ke.");
	hl(25);
	p_nl("0. Quay lai.");
	p_nl("1. Liet ke so hoc sinh theo lop.");
	p_nl("2. Phan loai ket qua hoc tap.");
	hl(25);
	int slt;
	slt_p(&slt, 0, 2);
	
	clrscr();
	switch(slt)
	{
		case 0:
			return;
		break;
		
		case 1:
			c_stats(cL); //class stats
		break;
		
		case 2:
			strs_stats(cL); //study result stats
		break;
	}
	getch();
}

void c_stats(c_list *cL)
{
	hl(30);
	printf("| %10.10s | %13.13s |\n", "Ma lop", "So hoc sinh");
	hl(30);
	c_node *tr = cL->first;
	while(tr != NULL)
	{
		printf("| %10.10s | %13d |\n", tr->c_id, tr->aos);
		tr = tr->next;
	}
	hl(30);
}

void strs_stats(c_list *cL) //show students results stats
{
	hl(70);
	printf("| %6.6s | %9.9s | %9.9s | %9.9s | %9.9s | %9.9s |\n", "", "Xuat sac", "Gioi", "Kha", "TB", "Yeu");
	hl(70);
	printf("| %6.6s |", "Ma lop");
	int i = 5;
	while(i)
	{
		printf(" %3.3s | %3.3s |", "SL", "%");
		--i;
	}
	p_nl("");
	hl(70);
	c_node *cn = cL->first;
	while(cn != NULL)
	{
		printf("| %6.6s | %3d | %3.0f |", cn->c_id, cn->e, cn->e*100.0/cn->aos);
		printf(" %3d | %3.0f |", cn->g, (cn->g*100.0/cn->aos));
		printf(" %3d | %3.0f |", cn->m, cn->m*100.0/cn->aos);
		printf(" %3d | %3.0f |", cn->a, cn->a*100.0/cn->aos);
		printf(" %3d | %3.0f |", cn->f, cn->f*100.0/cn->aos);
		p_nl("");
		cn = cn->next;
	}
	hl(70);
}

void edof(student *s, int f) //edit one field
{
	char fn[25], *p, err[30];
	int sl[4] = {0, 10, 10, 33};
	switch(f)
	{
		case 1:
			strcpy(fn, "   Ma lop: ");
			p = s->c_id;
		break;
		case 2:
			strcpy(fn, "   Ma sinh vien: ");
			p = s->s_id;
		break;
		case 3:
			strcpy(fn, "   Ho ten: ");
			p = s->name;
		break;
		case 4:
			strcpy(fn, "   Diem trung binh: ");
		break;
	}
	
	while(true)
	{
		printf("%-21.21s", fn);
		if(f >= 1 && f <= 3)
		{
			if(!r_str(p, sl[f]))
			{
				strcpy(err, "Loi nhap lieu.");
			}
			else
			{
				break;
			}
		}
		
		if(f == 4)
		{
			if(!r_fl(&(s->ag)) || s->ag < 0 || s->ag > 4)
			{
				strcpy(err, "Diem phai >= 0 va <= 4. ");
			}
			else
			{
				break;
			}
		}
		hl(30);
		printf(err); p_nl("Vui long thu lai.");
		getch();
		cll(); goup();
		cll(); goup();
		cll(); goup();
		cll();
		//hl(30);
	}
	
	if(f >= 1 && f <= 3)
	{
		valstr(f, p);
	}
}

void valstr(int f, char *str)
{
	int i, n = strlen(str);
	switch(f)
	{
		case 1: //class id
		case 2: //student id
			for(i = 0; i < n; ++i)
			{
				str[i] = tu(str[i]);
			}
			
			break;
		case 3: //name
			p("");
			for(i = 0; i < n; ++i)
			{
				str[i] = tl(str[i]);
			}
			
			str[0] = tu(str[0]);
			
			for(i = 1; i < n; ++i)
			{
				if(str[i] == ' ')
				{
					str[++i] = tu(str[i]);
				}
			}
			
	}
}

bool is_sorted(list *L, int sk)
{
	node *tr = L->first;
	
	while(tr != NULL)
	{
		if(tr->next != NULL)
		{
			if(cmp_std(tr->s, tr->next->s, sk))
			{
				return false;
			}
		}
		tr = tr->next;
	}
	return true;
}
