#include "functions.h"

/*
	1. new profile
	2. print all profiles
	3. sort
	4. search
	5. [thong ke] statistic
	6. exit
*/

void main_menu();
void sub_menu(int slt);
void add_std_menu();

void sort_menu();
void search_menu();
void stat_menu();
void exit_menu();

void main_menu()
{
	int slt = 0;
	init(&L);
	std_inp();
	
	while(true)
	{
		clrscr();
		p_nl_u("Phan mem quan ly sinh vien.");
		hl(27);
//		p_nl("0. Thu nghiem.");
		p_nl("1. Tao moi ho so sinh vien.");
		p_nl("2. Liet ke tat ca ho so.");
		p_nl("3. Sap xep ho so.");
		p_nl("4. Tim kiem ho so.");
		p_nl("5. Thong ke ho so.");
		p_nl("6. Thoat.");
		hl(27);
		slt_p(&slt, 0, 6);
		sub_menu(slt);
	}
}

void sub_menu(int slt)
{
	clrscr();
	
	switch(slt)
	{
		case 1:
			add_std_menu();
		break;

		case 2:
			list_all(&L);
		break;
		
		case 3:
			sort_menu();
		break;
		
		case 4:
			search_menu();
		break;
		
		case 5:
			stat_menu();
		break;
		
		case 6:
			exit_menu();
		break;
		
		case 0:
			test();
		break;
	}
	//getch();
	//paktc();
}

void add_std_menu()
{
	p_nl_u("Chuc nang them moi ho so sinh vien.");
	hl(30);
	p_nl("Vi du mau.");
	ssd(&sastu);
	student *s = (student*)malloc(sizeof(student));
	
	edof(s, 1);
	edof(s, 2);
	edof(s, 3);
	r_dob(s);
	edof(s, 4);
	
	add_std(&L, s);
	
	sne_std(s);
}

void sort_menu()
{
	int st, sk; //sort type
	while(true)
	{
		clrscr();
		
		p_nl_u("Chuc nang sap xep.");
		hl(25);
		p_nl("Cac cach sap xep: ");
		p_nl("0. Quay lai.");
		p_nl("1. Sap xep noi bot.");
		p_nl("2. Sap xep chon.");
		p_nl("3. Sap xep chen.");
		p_nl("4. Sap xep nhanh.");
		hl(25);
		slt_p(&st, 0, 4);
		if(st == 0)
		{
			return;
		}
		
		hl(25);
		p_nl("Cac tieu chi co the duoc dung de sap xep: ");
		p_nl("0. Quay lai.");
		p_nl("1. Ma sinh vien.");
		p_nl("2. Ho va ten.");
		p_nl("3. Ngay sinh.");
		p_nl("4. Diem trung binh.");
		hl(25);
		slt_p(&sk, 0, 4);
		
		if(sk == 0)
		{
			continue;
		}
		
		break;
	}
	
	if(!is_sorted(&L, sk))
	{
		sort_std(&L, st, sk);
	}
	list_all(&L);
}

void search_menu()
{
	char key[50], *stsd, *u_key; //(student to string)'ed
	list srsL; //search result list
	init(&srsL);
	int slt, f_slt; //selection, field selection
	node *tr = L.first;
	
	do
	{
		clrscr();
		p_nl_u("Chuc nang tim kiem ho so.");
		hl(25);
		p_nl("0. Quay lai.");
		p_nl("1. Tim mot tu khoa chinh xac trong mot truong.");
		p_nl("2. Tim mot tu khoa trong mot truong.");
		p_nl("3. Tim mot tu khoa trong tat ca cac truong.");
		hl(25);
		
		slt_p(&slt, 0, 3);
		
		if(slt == 0)
		{
			return;
		}
		
		hl(25);
		p("Nhap tu khoa tim kiem: "); r_str(key, 50);
		u_key = upper(key);
		
		switch(slt)
		{
			case 1:
			case 2:
				ssfs(&f_slt);
				if(f_slt == 0)
				{
					continue;
				}
				
				while(tr != NULL)
				{
					if(filting(u_key, slt, f_slt, tr->s))
					{
						add_std(&srsL, tr->s);
					}
					tr = tr->next;
				}
				list_all(&srsL);
			break;
			
			case 3:
				while(tr != NULL)
				{
					sts(tr->s, &stsd);
					stsd = upper(stsd);
					if(strstr(stsd, u_key))
					{
						add_std(&srsL, tr->s);
					}
					free(stsd);
//					stsd = NULL;
					tr = tr->next;
				}
				list_all(&srsL);
			break;
		}
		
		break;
	}
	while(true);
}

void stat_menu()
{
	c_list cL;
	init_c(&cL);
	calc_c(&cL, &L);
	show_stats(&cL);
}

void exit_menu()
{
	p_nl_u("Luu lai thay doi truoc khi thoat.");
	hl(25);
	p_nl("Ban co muon thoat va luu lai thay doi?");
	p_nl("0. Quay lai.");
	p_nl("1. Thoat va luu thay doi.");
	p_nl("2. Thoat nhung khong luu thay doi.");
	hl(25);
	
	int e_slt; //exit selection
	slt_p(&e_slt, 0, 2);
	
	
	switch(e_slt)
	{
		case 0:
			return;
		break;
		
		case 1:
			std_out();
		case 2:
			exit(0);
		break;
	}
}
