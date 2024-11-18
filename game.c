#include<stdio.h>
#include <windows.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include <math.h>
#include<time.h>
#define cls system("cls")
#define pause system("pause");
#define MAX 20
#define NUMBER_MAX 152 
#define NORMAL 0
#define FIRE 1
#define WATER 2
#define ELECTRIC 3
#define GRASS 4
#define ICE 5
#define FIGHTING 6
#define POISON 7
#define GROUND 8
#define FLYING 9
#define PSYCHIC 10
#define BUG 11
#define ROCK 12
#define GHOST 13
#define DRAGON 14
#define DARK 15
#define STEEL 16
#define FAIRY 17
#define MAX_SKILL 5
#define NUM_TYPES 18 

typedef struct skill {
	char skill_name[10];
	int power;
	int type;
	int pp;
	int accuracy;
	int priority;
}skill;


typedef struct poketmon{
	char name[10];
	int type;
	unsigned int hp;
	int attack_power;
	int defense;
	int level;
	skill skill_list[MAX_SKILL];
	char status[5];
	int number;
	int evol_level;
	int speed;
	char imege;
	int color_number;
	int exp;
}poketmon;

typedef struct item {
	char name[10];
	int price;
	char effect[50];
}item;

typedef struct bag {
	int money;
	item bac_max[MAX];
}bag;

typedef struct User {
	poketmon poketmon_list[6];
	bag my_bag;
	int num_pokemons;
}User;

// 공격하는 쪽, 방어하는 쪽 
float type_matchup[NUM_TYPES][NUM_TYPES] = {
//노말 불 물 전기 풀 얼음 격투 독 땅 비행 애스퍼 벌레 바위 고스트 드래곤 악 강철 페어리 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0.5, 0, 1, 1, 1, 1},	//노말 
{1, 0.5, 0.5, 1, 2, 2, 1, 1, 0.5, 1, 1, 2, 0.5, 1, 1, 1, 2, 1},	//불 
{1, 2, 0.5, 1, 0.5, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1},	//물 
{1, 1, 2, 0.5, 0.5, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0.5, 1, 1, 1},// 전기 
{1, 0.5, 2, 1, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 1, 1},	//풀 
{1, 0.5, 0.5, 1, 2, 0.5, 1, 1, 2, 2, 1, 1, 1, 1, 2, 1, 1, 1},	//얼음 
{2, 1, 1, 1, 1, 2, 1, 0.5, 1, 0.5, 0.5, 0.5, 2, 0, 1, 2, 2, 0.5},	//격투 
{1, 1, 1, 2, 1, 2, 1, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 0, 2},	//독 
{1, 2, 1, 2, 0.5, 1, 1, 2, 1, 0, 1, 0.5, 2, 1, 1, 1, 2, 1},	//땅 
{1, 1, 1, 0.5, 2, 1, 2, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 0.5, 1},	//비행 
{1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 0, 0.5, 1},	//애스퍼 
{1, 0.5, 1, 1, 2, 2, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 2, 0.5, 0.5},	//벌레 
{1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 0.5, 1},	//바위 
{0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 1},	//고스트 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 0},	//드래곤 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 0.5},	//악 
{1, 0.5, 0.5, 0.5, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0.5, 2},	//강철 
{1, 0.5, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 1, 1, 2, 2, 0.5, 1}		//페어리 
};

void gotoxy(int x, int y);
void mainprt();
void battle_prt(poketmon *enemy_poketmon, User *my_user, poketmon list[]);
void prt_hp_bar(poketmon *p, poketmon list[], int x, int y);
void prt_start_text(poketmon *p, poketmon *enemy);
void prt_skill_txt(skill skill_list[]);
void prt_exp_bar(poketmon *p, int plus_exp);
void clear_line(int y);
void prt_text(char text[], poketmon *p);

int check_priority(skill *skill1, skill *skill2);
void battle_start(poketmon *my_p, poketmon *en_p, skill *s1, skill *s2, int idx, poketmon list[]);
void battle_turn(int skill_idx, poketmon *my, poketmon *enmy, skill *my_s, skill *enmy_s, poketmon poketmon_all_list[]);

void SetColor(int color);
void CursorView(char show);

void initi_poketmon(poketmon *p, int number, char *name, int type, unsigned int hp, int attack_power, int defense, int level, int evolve_level, int speed, int color_number);
void init_poketmon_data(poketmon poketmon_all[]);
void init_skill(skill *skill, char *name, int power, int type, int accu, int pp, int priority);
void load_all_skill_data(skill all_skill_list[]);

void select_my_poketmon(poketmon poketmon_all_list[], User *user, skill all_skill_list[]);
poketmon select_enemy_poketmon(poketmon poketmon_all_list[], int color_number, skill all_skill_list[]);
skill select_skill(skill skill_list[]);
skill select_enemy_skill(poketmon *enemy, poketmon *my);
int get_enemy_level(int player_level);

int calc_attack_damage(poketmon *atk_p, poketmon *def_p, skill *s);
void learn_skill(poketmon *poketmon, skill all_skill_list[], int skill_number);
void battle();
void evolution();

void set_stat(poketmon *p, int lv);

int main(){
	poketmon poketmon_all_list[NUMBER_MAX];
	skill all_skill_list[50];
	init_poketmon_data(poketmon_all_list);
	load_all_skill_data(all_skill_list);
	CursorView(0);
	User my_user;
	srand(time(NULL));
	
	int POS = 2;
	mainprt();
	while (1) {
		if (GetAsyncKeyState(VK_LEFT))
			if (POS == 2) POS = 0;
			else if (POS == 0) POS = 1;
			else POS -= 1;
		else if (GetAsyncKeyState(VK_RIGHT))
			if (POS == 2) POS = 0;
			else if (POS == 1) POS = 0;
			else POS += 1;
		else if (GetAsyncKeyState(VK_RETURN))
			break;
		switch (POS) {
			case 0: 
				gotoxy(24, 4);	printf(" ");
				SetColor(11);
				gotoxy(4, 4);	printf(">");
				SetColor(15);
				gotoxy(5, 4); printf("게임  시작");
				gotoxy(25, 4); printf("게임  종료");
				break;
			case 1:
				gotoxy(4, 4);	printf(" ");
				SetColor(11);
				gotoxy(24, 4);	printf(">");
				SetColor(15);
				gotoxy(5, 4); printf("게임  시작");
				gotoxy(25, 4); printf("게임  종료");
				break;
			default: break;
		}
		Sleep(100);
	}
	cls;
	getchar();
	if (POS == 0) select_my_poketmon(poketmon_all_list, &my_user, all_skill_list);
	if (POS == 1) return 0;
	POS = 0; 
	
	// 적 포켓몬 셋팅 
	poketmon enemy_poketmon = select_enemy_poketmon(poketmon_all_list, my_user.poketmon_list[0].color_number, all_skill_list);
	set_stat(&my_user.poketmon_list[0], 5);
	int level_enemy = get_enemy_level(my_user.poketmon_list[0].level);
	set_stat(&enemy_poketmon, level_enemy);
	
	// UI그리기 
	battle_prt(&enemy_poketmon, &my_user, poketmon_all_list); 
	prt_start_text(&my_user.poketmon_list[0], &enemy_poketmon);
	prt_skill_txt(my_user.poketmon_list[0].skill_list);
	
	while(my_user.poketmon_list[0].hp > 0 || enemy_poketmon.hp > 0){ 
		// 기술 선택, 우선도 선정 
		skill my_use_skill = select_skill(my_user.poketmon_list[0].skill_list);
		skill enemy_use_skill = select_enemy_skill(&enemy_poketmon, &my_user.poketmon_list[0]);
		skill use_skill_list[2] = {};
		use_skill_list[0] = my_use_skill;
		use_skill_list[1] = enemy_use_skill;
		int skill_idx = check_priority(&use_skill_list[0],&use_skill_list[1]);
		printf("2번"); 
		// 데미지 계산, 적용 
		float match = type_matchup[use_skill_list[0].type][use_skill_list[1].type];
		battle_turn(skill_idx, &my_user.poketmon_list[0], &enemy_poketmon, &use_skill_list[0], &use_skill_list[1], poketmon_all_list);	
		
		prt_skill_txt(my_user.poketmon_list[0].skill_list);
	}
	if (my_user.poketmon_list[0].hp == 0){
		prt_text("는 쓰러졌다", &my_user.poketmon_list[0]);
	}
}

void mainprt(){
	system("title test");
	gotoxy(5, 4); printf("게임  시작");
	gotoxy(25, 4); printf("게임  종료");
}

void battle_prt(poketmon *enemy_poketmon, User *user, poketmon list[]){
	gotoxy(4,1);	printf("%s Lv. %d", enemy_poketmon->name, enemy_poketmon->level);
	prt_hp_bar(enemy_poketmon, list, 4, 2);
	SetColor(enemy_poketmon->color_number);
	gotoxy(25,3);	printf("o");
	SetColor(15);
	gotoxy(15,8);	printf("%s	Lv. %d", user->poketmon_list[0].name, user->poketmon_list[0].level);
	SetColor(10);
	prt_hp_bar(&user->poketmon_list[0], list, 15, 9);
	prt_exp_bar(&user->poketmon_list[0], 0);
	SetColor(user->poketmon_list[0].color_number);
	gotoxy(2,10);	printf("o");
	SetColor(15);
	gotoxy(0,11);	printf("--------------------------------");
}

void prt_hp_bar(poketmon *p, poketmon list[], int x, int y){
	SetColor(15);
	unsigned int hp = p->hp;
	if (hp <= 0)	hp = 0;
	int number = p->number;
	int hp_color = 10;
	unsigned int max_hp = list[number - 1].hp + (p->level - 1) * 2;
	
	float draw_ratio = (float)hp / max_hp;
    unsigned int draw = (int)round(draw_ratio * 10);
	
	if (draw <6 && draw > 2)	hp_color = 6;
	else if (draw < 3)	hp_color = 4;
	
	gotoxy(x,y);	
	if (hp == 0){
		printf(" ");
		printf("%d / %d", 0, max_hp);	
		return 0;
	}
	else{
		printf("%d / %d", hp, max_hp);	
	
		SetColor(hp_color);
		for (int i = 0; i < draw; i ++){
			printf("-");
		}
		SetColor(15);
	}
}

void prt_start_text(poketmon *p, poketmon *enemy){
	gotoxy(2,12);	
	printf("야생의 %s(이)가 나타났다!",enemy->name);
	getchar();
	clear_line(12);
	
	gotoxy(2,12);
	printf("가랏! %s!", p->name);
	getchar();
	clear_line(12);
}

void prt_text(char text[], poketmon *p){
	if (text == NULL || p == NULL) {
        return;
    }
	clear_line(12);
	clear_line(13);
	gotoxy(2,12);
	printf("%s%s",p->name, text);
}

void prt_exp_bar(poketmon *p, int plus_exp){
	clear_line(10);
	gotoxy(11, 10);	printf("exp");
	int exp = p->exp;
	int draw = (exp + plus_exp) / 10;
	
	gotoxy(15, 10);	SetColor(3);
	for (int i = 0; i < draw; i ++){
		printf("-");
	}
	SetColor(15);
}

void prt_skill_txt(skill skill_list[]){
	clear_line(12);
	clear_line(13);
	gotoxy(3,12);
	printf ("%s", skill_list[0].skill_name);
	gotoxy(23,12);
	printf ("%s", skill_list[1].skill_name);
	gotoxy(3,13);
	printf ("%s", skill_list[2].skill_name);
	gotoxy(23,13);
	printf ("%s", skill_list[3].skill_name);
}


int check_priority(skill *skill1, skill *skill2){
	int num1 = skill1->priority;
	int num2 = skill2->priority;
	
	if (num1 > num2)	return 0;
	else if (num2 > num1)	return 1;
	
	else return 2;
}

skill select_enemy_skill(poketmon *enemy, poketmon *my) {
    int idx = 0;
    float max_damage = 0.0;
    
    for (int i = 0; i < 4; i++) {
        float match = type_matchup[enemy->skill_list[i].type][my->type];
        float r_damage = calc_attack_damage(enemy, my, &enemy->skill_list[i]);
        int total_damage = (int)round(r_damage * match);
        
        if (total_damage > max_damage) {
            max_damage = total_damage;
            idx = i;
        }
    }
    
    return enemy->skill_list[idx];
}

int get_enemy_level(int player_level) {
    
    int min_level = player_level - 2;
    int max_level = player_level + 3;
    
    int enemy_level = rand() % (max_level - min_level + 1) + min_level;
    
    return enemy_level;
}

void set_enemy_skills(poketmon *p, skill all_list[]){
	int len = sizeof(all_list) / sizeof(all_list[0]) * 4; 		
	int idx = rand() % 6;
	
	for (int i = 0; i < 4; i ++){
		if (strcmp(p->skill_list[i].skill_name, all_list[idx].skill_name != 0))
			p->skill_list[i] = all_list[idx];
		else{
			int idx = rand() % 6;
		}
	}
}


skill select_skill(skill skill_list[]){
	SetColor(11);
	gotoxy(1,12);	printf(">");
	SetColor(15);
	int POS = 0;
	
	while(1){
		if (_kbhit()){
			int ch = _getch();
            if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                    case 75: //왼쪽 
                        if (POS == 0) POS = 1;
                        else if(POS == 2) POS = 3;
                        else POS -= 1;
                        break;
                    case 77: //오른쪽 
                        if (POS == 1) POS = 0;
                        else if(POS == 3) POS = 2;
                        else POS += 1;
                        break;
                    case 72: //위 
                        if (POS == 1) POS = 3;
                        else if(POS == 0)	POS = 2;
                        else POS -= 2;
                        break;
                    case 80: //아래 
                        if (POS == 3) POS = 1;
                        else if(POS == 2)	POS = 0;
                        else POS += 2;
                        break;
                }
            } else if (ch == 13) { 
                break;
            }
            switch(POS){
            	case 0:
            		gotoxy(1,12);	printf(" ");
					gotoxy(21,12);	printf(" ");	
					gotoxy(1,13);	printf(" ");	
					gotoxy(21,13);	printf(" ");
					gotoxy(1,12);
					SetColor(11);		
					printf(">");
					SetColor(15);
					break;
				case 1:
            		gotoxy(1,12);	printf(" ");
					gotoxy(21,12);	printf(" ");	
					gotoxy(1,13);	printf(" ");	
					gotoxy(21,13);	printf(" ");
					gotoxy(21,12);	SetColor(11);		
					printf(">");
					SetColor(15);
					break;
				case 2:
            		gotoxy(1,12);	printf(" ");
					gotoxy(21,12);	printf(" ");	
					gotoxy(1,13);	printf(" ");	
					gotoxy(21,13);	printf(" ");
					gotoxy(1,13);	SetColor(11);		
					printf(">");
					SetColor(15);
					break;
				case 3:
            		gotoxy(1,12);	printf(" ");
					gotoxy(21,12);	printf(" ");	
					gotoxy(1,13);	printf(" ");	
					gotoxy(21,13);	printf(" ");
					gotoxy(21,13);
					SetColor(11);		
					printf(">");
					SetColor(15);
					break;
					
			}
		}
		Sleep(100);
	}
	gotoxy(1, 12); printf(" ");
	clear_line(13);
	clear_line(12);
	gotoxy(2,12);
	return skill_list[POS];
}

void clear_line(int y) {
    gotoxy(2, y);
    for (int i = 2; i < 150; i++) {
        printf(" ");
    }
}

void SetColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void gotoxy(int x, int y) {

	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void CursorView(char show)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = show;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}

void initi_poketmon(poketmon *p, int number, char *name, int type, unsigned int hp, int attack_power, int defense, int level, int evol_level, int speed, int color_number) {
    strcpy(p->name, name);
    p->type = type;
    p->hp = hp;
    p->attack_power = attack_power;
    p->defense = defense;
    p->level = level;
    p->evol_level = evol_level;
    p->number = number;
    p->speed = speed;
    p->imege = 'O';
    p->color_number = color_number;
    p->exp = 0;
    for (int i = 0; i < MAX_SKILL; i ++){
    	strcpy(p->skill_list[i].skill_name, "----");
    	p->skill_list[i].power = 0;
    	p->skill_list[i].accuracy = 0;
    	p->skill_list[i].pp = 0;
    	p->skill_list[i].priority = 0;
    	p->skill_list[i].type = 0;
	}
    strcpy(p->status, " ");
}

void init_skill(skill *s, char *name, int power, int type, int accu, int pp, int priority ){
	strcpy(s-> skill_name, name);
	s->power = power;
	s->type = type;
	s->accuracy = accu;
	s->pp = pp;
	s-> priority = priority;
}

void load_all_skill_data(skill all_skill_list[]){
	init_skill(&all_skill_list[0], "물기", 60, DARK, 100, 25, 0);
	init_skill(&all_skill_list[1], "몸통박치기", 40, NORMAL, 100, 35, 0);
	init_skill(&all_skill_list[2], "전광석화", 40, NORMAL, 100, 30, 1);
	init_skill(&all_skill_list[3], "불꽃세례", 40, FIRE, 100, 25, 0);
	init_skill(&all_skill_list[4], "물대포", 40, WATER, 100, 25, 0);
	init_skill(&all_skill_list[5], "잎날가르기", 45, GRASS, 100, 25, 0);
	init_skill(&all_skill_list[6], "화염방사", 90, FIRE, 100, 15, 0);
}

void learn_skill(poketmon *p, skill all_skill_list[], int skill_number){
	for (int i = 0; i < MAX_SKILL; i ++){
		if (strcmp(p->skill_list[i].skill_name, "----") == 0){
			p->skill_list[i] = all_skill_list[skill_number];
			break;
		}
	}
}


void init_poketmon_data(poketmon poketmon_all_list[]){
    initi_poketmon(&poketmon_all_list[0], 1, "이상해씨", GRASS, 45, 65, 65, 1, 16, 45, 14);
    initi_poketmon(&poketmon_all_list[1], 2, "이상해풀", GRASS, 60, 80, 80, 1, 32, 60, 9);
    initi_poketmon(&poketmon_all_list[2], 3, "이상해꽃", GRASS, 80, 100, 100, 1, 0, 80, 12);
    initi_poketmon(&poketmon_all_list[3], 4, "파이리", FIRE, 39, 60, 50, 1, 16, 65, 14);
    initi_poketmon(&poketmon_all_list[4], 5, "리자드", FIRE, 58, 80, 65, 1, 36, 80, 9);
    initi_poketmon(&poketmon_all_list[5], 6, "리자몽", FIRE, 78, 109, 85, 1, 0, 100, 12);
    initi_poketmon(&poketmon_all_list[6], 7, "꼬부기", WATER, 44, 50, 64, 1, 16, 43, 14);
    initi_poketmon(&poketmon_all_list[7], 8, "어니부기", WATER, 59, 65, 80, 1, 36, 58, 9);
    initi_poketmon(&poketmon_all_list[8], 9, "거북왕", WATER, 79, 85, 105, 1, 0, 78, 12);
    initi_poketmon(&poketmon_all_list[9], 10, "캐터피", BUG, 45, 30, 35, 1, 7, 45, 14);
    initi_poketmon(&poketmon_all_list[10], 11, "단데기", BUG, 50, 20, 55, 1, 10, 30, 9);
    initi_poketmon(&poketmon_all_list[11], 12, "버터플", BUG, 60, 45, 50, 1, 0, 70, 12);
    initi_poketmon(&poketmon_all_list[12], 13, "뿔충이", BUG, 40, 35, 30, 1, 7, 50, 14);
    initi_poketmon(&poketmon_all_list[13], 14, "딱충이", BUG, 45, 25, 50, 1, 10, 35, 9);
    initi_poketmon(&poketmon_all_list[14], 15, "독침붕", BUG, 65, 80, 40, 1, 0, 75, 12);
    initi_poketmon(&poketmon_all_list[15], 16, "구구", FLYING, 40, 45, 40, 1, 18, 56, 14);
    initi_poketmon(&poketmon_all_list[16], 17, "피죤", FLYING, 63, 60, 55, 1, 36, 71, 9);
    initi_poketmon(&poketmon_all_list[17], 18, "피죤투", FLYING, 83, 80, 75, 1, 0, 101, 12);
    initi_poketmon(&poketmon_all_list[18], 19, "꼬렛", NORMAL, 30, 56, 35, 1, 20, 72, 9);
    initi_poketmon(&poketmon_all_list[19], 20, "레트라", NORMAL, 55, 81, 60, 1, 0, 97, 12);
    initi_poketmon(&poketmon_all_list[20], 21, "깨비참", NORMAL, 40, 60, 30, 1, 20, 70, 9);
    initi_poketmon(&poketmon_all_list[21], 22, "깨비드릴조", NORMAL, 65, 90, 65, 1, 0, 100, 12);
    initi_poketmon(&poketmon_all_list[22], 23, "아보", POISON, 35, 60, 44, 1, 22, 55, 9);
    initi_poketmon(&poketmon_all_list[23], 24, "아보크", POISON, 60, 85, 69, 1, 0, 80, 12);
    initi_poketmon(&poketmon_all_list[24], 25, "피카츄", ELECTRIC, 35, 55, 40, 1, 22, 90, 14);
    initi_poketmon(&poketmon_all_list[25], 26, "라이츄", ELECTRIC, 60, 90, 55, 1, 0, 110, 6);
    initi_poketmon(&poketmon_all_list[26], 27, "모래두지", GROUND, 50, 75, 85, 1, 22, 40, 9);
    initi_poketmon(&poketmon_all_list[27], 28, "고지", GROUND, 75, 100, 110, 1, 0, 65, 12);
    initi_poketmon(&poketmon_all_list[28], 29, "니드런♀", POISON, 55, 47, 52, 1, 16, 41, 14);
    initi_poketmon(&poketmon_all_list[29], 30, "니드리나", POISON, 70, 62, 67, 1, 32, 56, 9);
    initi_poketmon(&poketmon_all_list[30], 31, "니드퀸", POISON, 90, 92, 87, 1, 0, 76, 12);
    initi_poketmon(&poketmon_all_list[31], 32, "니드런♂", POISON, 46, 57, 40, 1, 16, 50, 14);
    initi_poketmon(&poketmon_all_list[32], 33, "니드리노", POISON, 61, 72, 57, 1, 32, 65, 9);
    initi_poketmon(&poketmon_all_list[33], 34, "니드킹", POISON, 81, 102, 77, 1, 0, 85, 12);
    initi_poketmon(&poketmon_all_list[34], 35, "삐삐", FAIRY, 70, 45, 48, 1, 32, 35, 9);
    initi_poketmon(&poketmon_all_list[35], 36, "픽시", FAIRY, 95, 70, 73, 1, 0, 60, 12);
    initi_poketmon(&poketmon_all_list[36], 37, "식스테일", FIRE, 38, 41, 40, 1, 22, 65, 14);
    initi_poketmon(&poketmon_all_list[37], 38, "나인테일", FIRE, 73, 76, 75, 1, 0, 100, 12);
    initi_poketmon(&poketmon_all_list[38], 39, "푸린", FAIRY, 115, 45, 20, 1, 32, 20, 9);
    initi_poketmon(&poketmon_all_list[39], 40, "푸크린", FAIRY, 140, 70, 45, 1, 0, 45, 12);
    initi_poketmon(&poketmon_all_list[40], 41, "주뱃", POISON, 40, 45, 35, 1, 22, 55, 14);
    initi_poketmon(&poketmon_all_list[41], 42, "골뱃", POISON, 75, 80, 70, 1, 0, 90, 12);
    initi_poketmon(&poketmon_all_list[42], 43, "뚜벅쵸", GRASS, 45, 75, 65, 1, 21, 30, 14);
    initi_poketmon(&poketmon_all_list[43], 44, "냄새꼬", GRASS, 60, 58, 75, 1, 32, 40, 9);
    initi_poketmon(&poketmon_all_list[44], 45, "라플레시아", GRASS, 75, 110, 90, 1, 0, 50, 12);
}

void select_my_poketmon(poketmon poketmon_all_list[], User *user, skill all_skill_list[]) {
    cls;
    int POS = 0;
    printf("---------select poketmon------------\n\n\n\n\n\n");
    printf("------------------------------------");
     SetColor(11);
    gotoxy(2, 2); printf(">");
    SetColor(15);
    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
     gotoxy(3,4);	printf("%s" , "풀타입");
    gotoxy(6,4);	printf("%s" , "잎날 가르기");
    gotoxy(20,4);	printf("%s" , "몸통 박치기");
    gotoxy(13, 2); printf("%s", poketmon_all_list[3].name);
    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);

    while (1) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                    case 75: 
                        if (POS == 0) POS = 2;
                        else POS -= 1;
                        break;
                    case 77: 
                        if (POS == 2) POS = 0;
                        else POS += 1;
                        break;
                }
            } else if (ch == 13) { 
                break;
            }

            switch (POS) {
                case 0:
                	for (int i = 4; i < 50; i ++){
                		gotoxy(i,4);	printf(" ");
					} 
                    gotoxy(12, 2); printf(" ");
                    gotoxy(22, 2); printf(" ");
                    SetColor(11);
                    gotoxy(2, 2); printf(">");
                    SetColor(15);
                    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
                    gotoxy(3,4);	printf("%s" , "풀타입");
                    gotoxy(6,4);	printf("%s" , "잎날 가르기");
                    gotoxy(20,4);	printf("%s" , "몸통 박치기");
                    gotoxy(13, 2); printf("%s", poketmon_all_list[3].name);
                    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);
                    break;
                case 1:
                	for (int i = 4; i < 50; i ++){
                		gotoxy(i,4);	printf(" ");
					} 
                    gotoxy(2, 2); printf(" ");
                    gotoxy(22, 2); printf(" ");
                    SetColor(11);
                    gotoxy(12, 2); printf(">");
                    SetColor(15);
                    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
                    gotoxy(13, 2); printf("%s", poketmon_all_list[3].name);
                    gotoxy(3,4);	printf("%s" , "불타입");
                    gotoxy(6,4);	printf("%s" , "불꽃세례");
                    gotoxy(20,4);	printf("%s" , " 전광 석화");
                    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);
                    break;
                case 2:
                	for (int i = 1; i < 50; i ++){
                		gotoxy(i,4);	printf(" ");
					} 
                    gotoxy(12, 2); printf(" ");
                    gotoxy(2, 2); printf(" ");
                    SetColor(11);
                    gotoxy(22, 2); printf(">");
                    SetColor(15);
                    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
                    gotoxy(13, 2); printf("%s", poketmon_all_list[3].name);
                    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);
                    gotoxy(3,4);	printf("%s" , "물타입");
                    gotoxy(6,4);	printf("%s" , "물대포");
                    gotoxy(20,4);	printf("%s" , "몸통 박치기");
                    break;
            }
        }
        Sleep(100); 
    }

    if (POS == 0) {
    	memcpy(&user->poketmon_list[0], &poketmon_all_list[0], sizeof(poketmon));
		learn_skill(&user->poketmon_list[0], all_skill_list, 5);
		gotoxy(1,7);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, all_skill_list[5].skill_name);
		learn_skill(&user->poketmon_list[0], all_skill_list, 1);
		gotoxy(1,8);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, all_skill_list[1].skill_name);
	}
	
    else if (POS == 1){
    	memcpy(&user->poketmon_list[0], &poketmon_all_list[3], sizeof(poketmon));
    	learn_skill(&user->poketmon_list[0], all_skill_list, 3);
		gotoxy(1,7);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, all_skill_list[6].skill_name);
		learn_skill(&user->poketmon_list[0], all_skill_list, 2);
		gotoxy(1,8);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, all_skill_list[2].skill_name);
	}
    else if (POS == 2) {
    	memcpy(&user->poketmon_list[0], &poketmon_all_list[6], sizeof(poketmon));
    	learn_skill(&user->poketmon_list[0], all_skill_list, 4);
		gotoxy(1,7);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, all_skill_list[4].skill_name);
		learn_skill(&user->poketmon_list[0], all_skill_list, 1);
		gotoxy(1,8);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, all_skill_list[1].skill_name);
	}
    POS = 0;
    getchar();
	cls; 
}



poketmon select_enemy_poketmon(poketmon poketmon_all_list[], int color_number, skill all_skill_list[]){
	
	poketmon enemy_candi_list[45];
	int ran_num = 0;
	
	for (int i = 0 ; i < 45; i ++){
		if (poketmon_all_list[i].color_number == color_number){
			enemy_candi_list[ran_num++] = poketmon_all_list[i];
		}
	}		
	int idx = rand() % ran_num;
		
	int skill_idx1 = rand() % 6;
	int skill_idx2 = rand() % 6;
	while (skill_idx2 == skill_idx1)	skill_idx2 = rand() % 6;
	int skill_idx3 = rand() % 6;
	while (skill_idx3 == skill_idx2 || skill_idx3 == skill_idx1)	skill_idx3 = rand() % 6;
	int skill_idx4 = rand() % 6;
	while (skill_idx4 == skill_idx2 || skill_idx4 == skill_idx1 || skill_idx4 == skill_idx3)	skill_idx4 = rand() % 6;
	
	learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx1);
	learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx2);
	learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx3);
	learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx4);
	
	return 	enemy_candi_list[idx];
}

void set_stat(poketmon *p, int lv){
	int level = p->level;
	unsigned int base_hp = p->hp;
	int grow = lv - level;
	p->level = lv;
	p->hp = base_hp + (lv - 1) * 2;
	p->speed += (int)(grow * log(lv)); 
    p->attack_power += (int)(grow * log(lv)) * 2; 
    p->defense += (int)(grow * log(lv));
}

void battle_start(poketmon *at_p, poketmon *de_p, skill *s1, skill *s2, int idx, poketmon list[]){
	
	clear_line(12);
	float match = type_matchup[s1->type][de_p->type];
	gotoxy(2,12);	printf("%s의 %s!!",at_p->name, s1->skill_name);

	if (match == 0){
		clear_line(12);
		gotoxy(2,12);	printf("%s에게는 효과가 없는 것 같다....", de_p->name);
		return;
	}
	
	else{
		float damg = calc_attack_damage(at_p, de_p, s1) * match;
		int r_damg = (int)round(damg);
		de_p->hp -= r_damg;
		
		if (de_p->hp < 0)	de_p->hp = 0;

		if (idx == 0){
			for (int i = 10; i < 25; i ++){
				gotoxy(i,2);	printf(" ");
			}
			prt_hp_bar(de_p, list, 4, 2);
		}
		else if (idx == 1){
			for (int i = 14; i < 50; i ++){
				gotoxy(i,9);	printf(" ");
			}
			prt_hp_bar(de_p, list, 15, 9);
		}
		getchar();
		clear_line(12);
		gotoxy(2,12);
		if (match == 0.5){
			printf("효과가 별로인 것 같다...");
			getchar();
		}
		if (match == 2){
			printf("효과가 굉장했다!");
			getchar();
		}
	}
}

int calc_attack_damage(poketmon *atk_p, poketmon *def_p, skill *s){
	int attack_p = atk_p->attack_power;
	int attack_s = s->power;
	int defence = def_p->defense;
	int acc = s->accuracy;
	int level = atk_p->level;
	int my_p = 0;
		
	int suc = rand() % 100;
	if (suc > acc)
		return -1;
	
	if (atk_p->type == s->type)	attack_s = attack_s * 1.5;
	
	int damage = (((level * 2 / 5) + 2) * attack_s * attack_p / 30) / defence; 
	return damage;
}

void battle_turn(int skill_idx, poketmon *my, poketmon *enmy, skill *my_s, skill *enmy_s, poketmon poketmon_all_list[]){
	
	if (skill_idx == 0){
		battle_start(my, enmy, my_s, enmy, 0, poketmon_all_list);
		battle_start(enmy, my, enmy_s, my_s, 1, poketmon_all_list);	
	}
	else if (skill_idx == 1){
		battle_start(enmy, my, enmy_s, my_s, 1, poketmon_all_list);
		battle_start(my, enmy, my_s, enmy_s, 0, poketmon_all_list);	
	}
	else{
		int speed1 = my->speed;
		int speed2 = enmy->speed;
		if (speed1 > speed2){
			battle_start(my, enmy, my_s, enmy_s, 0, poketmon_all_list);
			battle_start(enmy, my, enmy_s, my_s, 1, poketmon_all_list);
		}	
		else{
			battle_start(enmy, my, enmy_s, my_s, 1, poketmon_all_list);
			battle_start(my, enmy, my_s, enmy_s, 0, poketmon_all_list);	
		}
	}
	
	if (my->hp <= 0) my->hp = 0;
	if (enmy->hp <= 0) enmy->hp = 0;
}

