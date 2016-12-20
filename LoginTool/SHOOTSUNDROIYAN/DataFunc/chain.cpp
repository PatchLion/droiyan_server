#include "stdafx.h"
#include "..\datafunc\common.h"

extern GAMEDATA GameData;
extern CONFIG Config;

extern struct OBJ_INFO_CHAIN Obj_info_chain[MAXPLAYER];
extern struct OBJ_SITE_CHAIN *Obj_site_chain;
extern struct OBJ_CHUM_CHAIN *Obj_chum_chain;
extern struct NOVELITY_SETUP_CHAIN *Novelity_setup_chain;
extern struct NOVELITY_INFO_CHAIN *Novelity_info_chain;
extern struct OBJ_BANK_CHAIN  *Obj_bank_chain;
extern struct SPEAK_CHAIN *Speak_chain;
// 游戏队列部分 链式结构
// 银行取放操作

struct OBJ_BANK_CHAIN *add_bank_chain(BYTE Code1, BYTE Code2, BYTE Index, int Mode, int Number)
{
	struct OBJ_BANK_CHAIN *p;
	p = (struct OBJ_BANK_CHAIN *)malloc(sizeof(struct OBJ_BANK_CHAIN));

	p->Code1  = Code1;
	p->Code2  = Code2;
	p->Index  = Index;
	p->Mode   = Mode;
	p->Number = Number;

	p->next = Obj_bank_chain;

	return p;
}

struct SPEAK_CHAIN *add_speak_chain(char buf[255], int Mode, BOOL Status)
{
	struct SPEAK_CHAIN *p;
	p = (struct SPEAK_CHAIN *)malloc(sizeof(struct SPEAK_CHAIN));

	strcpy(p->buf, buf);
	p->Mode   = Mode;
	p->Status = Status;

	p->next = Speak_chain;

	return p;
}

struct SPEAK_CHAIN *sub_speak_chain(char name[255])
{
	struct SPEAK_CHAIN *p, *q;

	p = search_speak_chain(Speak_chain, name, &q);
	if (p != NULL)
	{ 
		if(q== NULL) 
			Speak_chain = p->next;
		else 
			q->next =p->next;

		p->next = NULL;
		free(p);
	}

	return Speak_chain;
}

struct SPEAK_CHAIN *search_speak_chain(struct SPEAK_CHAIN *h, char name[128], SPEAK_CHAIN **pp)
{
	struct SPEAK_CHAIN *v = h, *u = NULL;


	while (v != NULL)
	{
		if (strcmp(v->buf, name) == 0)
		{
			*pp = u;  return v;
		}
		u = v;
		v = v->next;
	}

	*pp = u; return v;
}

struct OBJ_SITE_CHAIN *add_site_obj(char name[128], int Time, int Danger, int X, int Y, int Mode)
{
	struct OBJ_SITE_CHAIN *p;

	p = (struct OBJ_SITE_CHAIN *)malloc(sizeof(struct OBJ_SITE_CHAIN));

    strcpy(p->Name, name);
	p->Time    = Time;
	p->Danger  = Danger;
	p->X       = X;
	p->Y       = Y;
	p->Mode    = Mode;

	p->next = Obj_site_chain;

	return p;
}

struct OBJ_SITE_CHAIN *sub_site_obj(char name[128])
{
	struct OBJ_SITE_CHAIN *p, *q;

	p = search_site_obj(Obj_site_chain, name, &q);
	if (p != NULL)
	{ 
		if(q== NULL) 
			Obj_site_chain = p->next;
		else 
			q->next =p->next;

		p->next = NULL;
		free(p);
	}

	return Obj_site_chain;
}

struct OBJ_SITE_CHAIN *search_site_obj(struct OBJ_SITE_CHAIN *h, char name[128], OBJ_SITE_CHAIN **pp)
{
	struct OBJ_SITE_CHAIN *v = h, *u = NULL;


	while (v != NULL)
	{
		if (strcmp(v->Name, name) == 0)
		{
			*pp = u;  return v;
		}
		u = v;
		v = v->next;
	}

	*pp = u; return v;
}

struct OBJ_SITE_CHAIN *search_time_obj(struct OBJ_SITE_CHAIN *h, int Time, OBJ_SITE_CHAIN **pp)
{
	struct OBJ_SITE_CHAIN *v = h, *u = NULL;


	while ((v!= NULL))
	{	
		if (v->Time == Time)
		{
			*pp = u; return v;
		}

		u = v;
		v = v->next;
	}

	*pp = u; return v;
}

void create_site_obj()
{
	struct OBJ_SITE_CHAIN *h, *p;

	h = NULL;

	p = (struct OBJ_SITE_CHAIN *)malloc(sizeof(struct OBJ_SITE_CHAIN));
/*
	strcpy(p->Name, "");
	p->Time = 0;
	p->Danger = 0;
	p->X = 0;
	p->Y = 0;
	*/
	p = NULL;
//	p->next = NULL;
	if(h == NULL) Obj_site_chain = p;

}

void create_obj()
{
	int i;

	for (i=0; i<MAXPLAYER; i++)
	{
		Obj_info_chain[i].Code1 = 0xFF;
		Obj_info_chain[i].Code2 = 0xFF;
	}

}

void add_obj(BYTE Code1, BYTE Code2, int X, int Y, int BloodNow, int BloodMax, int mode, char buf1[128], char buf2[128])
{

	int i;

	for (i=0; i<MAXPLAYER; i++)
	{
		if ((Obj_info_chain[i].Code1 == 0xFF) && (Obj_info_chain[i].Code2 == 0xFF))
		{
	
			Obj_info_chain[i].Code1     = Code1;
			Obj_info_chain[i].Code2     = Code2;
			Obj_info_chain[i].X         = X;
			Obj_info_chain[i].Y         = Y;
			Obj_info_chain[i].BloodNow  = BloodNow;
			Obj_info_chain[i].BloodMax  = BloodMax;
			Obj_info_chain[i].Mode      = mode;

			strcpy(Obj_info_chain[i].Name, buf1);
			strcpy(Obj_info_chain[i].Team, buf2);

			return;
		}
	}
}

struct OBJ_CHUM_CHAIN *add_chum_obj(int mode, char Name[128], int Attack)
{
	struct OBJ_CHUM_CHAIN *p;

	p = (struct OBJ_CHUM_CHAIN*)malloc(sizeof(struct OBJ_CHUM_CHAIN));

	p->Mode = mode;
	p->Attack = Attack;
	strcpy(p->Name, Name); 

	p->next = Obj_chum_chain;

	return p;
}

struct OBJ_CHUM_CHAIN *sub_chum_obj(char name[128])
{
	struct OBJ_CHUM_CHAIN *p, *q;

	p = search_chum_obj(Obj_chum_chain, name, &q);
	if (p != NULL)
	{ 
		if(q== NULL) 
			Obj_chum_chain = p->next;
		else 
			q->next =p->next;

		p->next = NULL;
		free(p);
	}

	return Obj_chum_chain;
}

struct OBJ_CHUM_CHAIN *search_chum_obj(struct OBJ_CHUM_CHAIN *h, char Name[128], OBJ_CHUM_CHAIN **pp)
{
	struct OBJ_CHUM_CHAIN *v = h, *u = NULL;

	while (v!=NULL)
	{	
		if (strcmp(v->Name, Name) == 0)
		{
			*pp = u;  return v;
		}
		u = v;
		v = v->next;
	}

	*pp = u; return v;
}

struct NOVELITY_SETUP_CHAIN *add_novelity_setup_obj(char Name[128], int Mode)
{
	struct NOVELITY_SETUP_CHAIN *p;

	p = (struct NOVELITY_SETUP_CHAIN*)malloc(sizeof(struct NOVELITY_SETUP_CHAIN));

	p->Mode  = Mode;
	strcpy(p->Name, Name);

	p->next = Novelity_setup_chain;

	return p;
}

struct NOVELITY_SETUP_CHAIN *sub_novelity_setup_obj(char Name[256])
{
	struct NOVELITY_SETUP_CHAIN *p, *q;

	p = search_novelity_setup_obj(Novelity_setup_chain, Name, &q);
	if (p != NULL)
	{ 
		if(q== NULL) 
			Novelity_setup_chain = p->next;
		else 
			q->next =p->next;

		p->next = NULL;
		free(p);
	}

	return Novelity_setup_chain;
}

struct NOVELITY_SETUP_CHAIN *search_novelity_setup_obj(struct NOVELITY_SETUP_CHAIN *h, char Name[128], NOVELITY_SETUP_CHAIN **pp)
{
	
	struct NOVELITY_SETUP_CHAIN *v = h, *u = NULL;

	while (v!=NULL)
	{	
		if (strcmp(v->Name, Name) == 0)
		{
			*pp = u;  return v;
		}
		u = v;
		v = v->next;
	}

	*pp = u; return v;
}

/*
struct OBJ_INFO_CHAIN *search_space_obj(struct OBJ_INFO_CHAIN *h)
{
	struct OBJ_INFO_CHAIN *v = h, *u = NULL;

//	if ((v != NULL) && (v->next != NULL)) u = v; else if (v->Mode == 0) return v;

	while (v!=NULL)
	{	
	//	if ((v->next == NULL) && (v->Mode == 0))return u;

		if ((abs((u->X - GameData.ME_X)) >= (abs((v->next->X - GameData.ME_X))))  
			&& (abs((u->Y - GameData.ME_Y)) >= (abs((v->next->Y - GameData.ME_Y)))) && (v->next->X != 0) && (v->next->Y != 0) && (u->Mode == 0) && (v->next->Mode == 0)
			&& (((v->next->Code1 != 0x00) && (v->next->Code2 != 0x00)) || ((v->next->Code1 != 0xFF) && (v->next->Code2 != 0xFF))))
		{
			u = v->next;	
		}
		
		v = v->next;
	}

	return u;
}
*/

int search_space_obj()
{
	int i;

	for (i=0;i<MAXPLAYER;i++)
	{	
		;
	}

	return MAXPLAYER;
}

int search_code_obj(BYTE Code1, BYTE Code2)
{
	int i;

	for (i=0; i<MAXPLAYER;i++)
	{
		if ((Obj_info_chain[i].Code1 == Code1) && (Obj_info_chain[i].Code2 == Code2)) return i;
	}

	return MAXPLAYER;
}

void sub_obj(BYTE Code1, BYTE Code2)
{
	int i;

	i = search_code_obj(Code1, Code2);

	if (i != MAXPLAYER)
	{ 
		Obj_info_chain[i].Code1 = 0xFF;
		Obj_info_chain[i].Code2 = 0xFF;
	}
}

void modify_obj(BYTE Code1, BYTE Code2, int X, int Y, int BloodNow, int BloodMax)
{
	int i;

	i = search_code_obj(Code1, Code2);

	if (i != MAXPLAYER)
	{
		Obj_info_chain[i].X = X;
		Obj_info_chain[i].Y = Y;

		if ((BloodNow != 0) && (BloodMax != 0))
		{	
			Obj_info_chain[i].BloodNow = BloodNow;
			Obj_info_chain[i].BloodMax = BloodMax;
		}	
	}
}