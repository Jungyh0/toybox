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
#define MAX_ROUND 100

poketmon poketmon_all_list[NUMBER_MAX];
skill all_skill_list[500];
item all_item_list[3];
User my_user;
bag my_bag;

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


void initi_poketmon(poketmon *p, int number, char *name, int type, int hp, int attack_power, int defense, int level, int evol_level, int speed, int color_number, poketmon *e_p, int base_skill[]) {
    char log_message[200];
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
    p->rank_up[0] = 0;
    p->rank_up[1] = 0;
    p->rank_up[2] = 0;
    p->rank_up[3] = 0;
    p->evolution_poketmon = e_p;
    p->skill_filled = 0;
    int idx = 0;
    for (int i = 0; i < 20; i++) {
    p->learn_skill_level[i] = 0;
    p->learn_skill[i] = 0;
	}
	p->base_skill[0] = base_skill[0];
	p->base_skill[1] = base_skill[1];
	
    for (int i = 0; i < MAX_SKILL; i ++){
    	strcpy(p->skill_list[i].skill_name, "----");
    	p->skill_list[i].power = 0;
    	p->skill_list[i].accuracy = 0;
    	p->skill_list[i].priority = 0;
    	p->skill_list[i].type = 0;
	}
    strcpy(p->status, " ");
}

void init_skill(int number, skill *s, char *name, int power, int type, int accu, int priority ){
	s->skill_number = number;
	strcpy(s-> skill_name, name);
	s->power = power;
	s->type = type;
	s->accuracy = accu;
	s-> priority = priority;
}

void init_item(item *tem, char *name, int price, char *effect){
	strcpy(tem->name, name);
	tem->price = price;
	strcpy(tem->effect, effect);
}

void load_all_skill_data(skill all_skill_list[]){ 	
	init_skill(1, &all_skill_list[0], "할퀴기", 40, NORMAL, 100, 0);
	init_skill(2, &all_skill_list[1], "불꽃세례", 40, FIRE, 100, 0);
	init_skill(3, &all_skill_list[2], "분노(p)", 20, NORMAL, 100, 0);
	init_skill(4, &all_skill_list[3], "베어가르기", 70, NORMAL, 100, 0);
	init_skill(5, &all_skill_list[4], "불꽃 엄니", 65, FIRE, 95, 0);
	init_skill(6, &all_skill_list[5], "화염방사", 95, FIRE, 100, 0);
	init_skill(7, &all_skill_list[6], "용의 숨결", 60, DRAGON, 100, 0);
	init_skill(8, &all_skill_list[7], "몸통 박치기", 35, NORMAL, 95, 0);
	init_skill(9, &all_skill_list[8], "덩굴 채찍", 35, GRASS, 100, 0);
	init_skill(10, &all_skill_list[9], "잎날 가르기", 55, GRASS, 95, 0);
	init_skill(11, &all_skill_list[10], "솔라빔(p)", 120, GRASS, 100, 0);
	init_skill(12, &all_skill_list[11], "씨폭탄", 80, GRASS, 100, 0);
	init_skill(13, &all_skill_list[12], "돌진", 90, NORMAL, 85, 0);
	init_skill(14, &all_skill_list[13], "물대포", 40, WATER, 100, 0);
	init_skill(15, &all_skill_list[14], "고속 스핀", 50, NORMAL, 100, 0);
	init_skill(16, &all_skill_list[15], "물기", 60, DARK, 100, 0);
	init_skill(17, &all_skill_list[16], "물의 파동", 60, WATER, 100, 0);
	init_skill(18, &all_skill_list[17], "아쿠아 테일", 90, WATER, 90, 0);
	init_skill(19, &all_skill_list[18], "하이드로 펌프", 110, WATER, 80, 0);
	init_skill(20, &all_skill_list[19], "벌레 먹음", 60, BUG, 100, 0);
	init_skill(21, &all_skill_list[20], "단단해지기", 0, BUG, 100, 0);
	init_skill(22, &all_skill_list[21], "염동력", 50, PSYCHIC, 100, 0);
	init_skill(23, &all_skill_list[22], "환상빔", 65, PSYCHIC, 100, 0);
	init_skill(24, &all_skill_list[23], "에어 슬레시", 75, FLYING, 95, 0);
	init_skill(25, &all_skill_list[24], "벌레의 야단 법석", 90, FLYING, 100, 0);
	init_skill(26, &all_skill_list[25], "베놈 쇼크", 65, POISON, 100, 0);
	init_skill(27, &all_skill_list[26], "승부 굳히기", 60, DARK, 100, 0);
	init_skill(28, &all_skill_list[27], "바늘 미사일", 75, BUG, 90, 0);
	init_skill(29, &all_skill_list[28], "독찌르기", 80, POISON, 100, 0);
	init_skill(30, &all_skill_list[29], "마지막 일침", 80, POISON, 100, 0);
	init_skill(31, &all_skill_list[30], "연속 자르기", 65, BUG, 90, 0);
	init_skill(32, &all_skill_list[31], "바람 일으키기", 40, FLYING, 100, 0);
	init_skill(33, &all_skill_list[32], "전광 석화", 40, NORMAL, 100, 1);
	init_skill(34, &all_skill_list[33], "회오리", 40, DRAGON, 100, 1);
	init_skill(35, &all_skill_list[34], "날개치기", 60, FLYING, 100, 0);
	init_skill(36, &all_skill_list[35], "제비 봔환", 60, FLYING, 100, 0);
	init_skill(37, &all_skill_list[36], "폭풍", 110, FLYING, 70, 0);
	init_skill(38, &all_skill_list[37], "필살앞니", 80, NORMAL, 90, 0);
	init_skill(39, &all_skill_list[38], "깨물어 부수기", 80, DARK, 100, 0);
	init_skill(40, &all_skill_list[39], "기습", 70, DARK, 100, 1);
	init_skill(41, &all_skill_list[40], "분노의 앞니", 0, NORMAL, 90, 0);
	init_skill(42, &all_skill_list[41], "이판사판태클", 90, NORMAL, 100, 0);
	init_skill(43, &all_skill_list[42], "쪼기", 35, FLYING, 100, 0);
	init_skill(44, &all_skill_list[43], "돌진", 90, NORMAL, 80, 0);
	init_skill(45, &all_skill_list[44], "회전 부리", 80, FLYING, 80, 0);
	init_skill(46, &all_skill_list[45], "용해액", 40, POISON, 100, 0);
	init_skill(47, &all_skill_list[46], "애시드봄", 40, POISON, 100, 0);
	init_skill(48, &all_skill_list[47], "오물 폭탄", 90, POISON, 100, 0);
	init_skill(49, &all_skill_list[48], "더스트 슈트", 120, POISON, 90, 0);
	init_skill(50, &all_skill_list[49], "전기 쇼크", 40, ELECTRIC, 100, 0);
	init_skill(51, &all_skill_list[50], "일렉트릭 볼", 60, ELECTRIC, 100, 0);
	init_skill(52, &all_skill_list[51], "스파크", 65, ELECTRIC, 100, 0);
	init_skill(53, &all_skill_list[52], "힘껏 치기", 80, NORMAL, 75, 0);
	init_skill(54, &all_skill_list[53], "방전", 80, ELECTRIC, 100, 0);
	init_skill(55, &all_skill_list[54], "10만볼트", 90, ELECTRIC, 100, 0);
	init_skill(56, &all_skill_list[55], "번개", 110, ELECTRIC, 70, 0);
	init_skill(57, &all_skill_list[56], "사이코 키네시스", 90, PSYCHIC, 100, 0);
}

void init_item_data(item list[]){
	int idx = 0;
	init_item(&list[idx++], "상처약", 200, "200골드를 사용해 포켓몬 1마리의 HP를 20 또는 10% 중 높은 수치만큼 회복한다.");
	init_item(&list[idx++], "좋은 상처약", 500, "500골드를 사용해 포켓몬 1마리의 HP를 50 또는 25% 중 높은 수치만큼 회복한다.");
	init_item(&list[idx], "고급 상처약", 1000, "1000골드를 사용해 포켓몬 1마리의 HP를 200 또는 50% 중 높은 수치만큼 회복한다.");
}

void init_poketmon_data(){
	char log_message[200];
	int base_skill[2] = {0};
	
	base_skill[0] = 7; base_skill[1] = 8; 
    initi_poketmon(&poketmon_all_list[0], 1, "이상해씨", GRASS, 45, 65, 65, 1, 16, 45, 14, &poketmon_all_list[1], base_skill);
    initi_poketmon(&poketmon_all_list[1], 2, "이상해풀", GRASS, 60, 80, 80, 1, 32, 60, 9, &poketmon_all_list[2], base_skill);
    initi_poketmon(&poketmon_all_list[2], 3, "이상해꽃", GRASS, 80, 100, 100, 1, 0, 80, 12, NULL, base_skill);

    base_skill[0] = 0; base_skill[1] = 1;
    initi_poketmon(&poketmon_all_list[3], 4, "파이리", FIRE, 39, 60, 50, 1, 16, 65, 14, &poketmon_all_list[4], base_skill);
    initi_poketmon(&poketmon_all_list[4], 5, "리자드", FIRE, 58, 80, 65, 1, 36, 80, 9, &poketmon_all_list[5], base_skill);
    initi_poketmon(&poketmon_all_list[5], 6, "리자몽", FIRE, 78, 109, 85, 1, 0, 100, 12, NULL, base_skill);
    
    base_skill[0] = 7; base_skill[1] = 13; 
    initi_poketmon(&poketmon_all_list[6], 7, "꼬부기", WATER, 44, 50, 64, 1, 16, 43, 14, &poketmon_all_list[7], base_skill);
    initi_poketmon(&poketmon_all_list[7], 8, "어니부기", WATER, 59, 65, 80, 1, 36, 58, 9, &poketmon_all_list[8], base_skill);
    initi_poketmon(&poketmon_all_list[8], 9, "거북왕", WATER, 79, 85, 105, 1, 0, 78, 12,NULL, base_skill);
    
    base_skill[0] = 7;	base_skill[1] = 19;
    initi_poketmon(&poketmon_all_list[9], 10, "캐터피", BUG, 45, 30, 35, 1, 7, 45, 14, &poketmon_all_list[10], base_skill);
    base_skill[0] = 20;
    initi_poketmon(&poketmon_all_list[10], 11, "단데기", BUG, 50, 20, 55, 1, 10, 30, 9, &poketmon_all_list[11], base_skill);
    initi_poketmon(&poketmon_all_list[11], 12, "버터플", BUG, 60, 45, 50, 1, 0, 70, 12, NULL, base_skill);
    
    base_skill[0] = 19;	base_skill[1] = 7;
    initi_poketmon(&poketmon_all_list[12], 13, "뿔충이", BUG, 40, 35, 30, 1, 7, 50, 14, &poketmon_all_list[13], base_skill);
    base_skill[0] = 20;
    initi_poketmon(&poketmon_all_list[13], 14, "딱충이", BUG, 45, 25, 50, 1, 10, 35, 9, &poketmon_all_list[14], base_skill);
    initi_poketmon(&poketmon_all_list[14], 15, "독침붕", BUG, 65, 80, 40, 1, 0, 75, 12, NULL, base_skill);
    
    base_skill[0] = 7; base_skill[1] = 31;
    initi_poketmon(&poketmon_all_list[15], 16, "구구", FLYING, 40, 45, 40, 1, 18, 56, 14, &poketmon_all_list[16], base_skill);
    initi_poketmon(&poketmon_all_list[16], 17, "피죤", FLYING, 63, 60, 55, 1, 36, 71, 9, &poketmon_all_list[17], base_skill);
    initi_poketmon(&poketmon_all_list[17], 18, "피죤투", FLYING, 83, 80, 75, 1, 0, 101, 12, NULL, base_skill);
    
    base_skill[0] = 7; base_skill[1] = 32;
    initi_poketmon(&poketmon_all_list[18], 19, "꼬렛", NORMAL, 30, 56, 35, 1, 20, 72, 14, &poketmon_all_list[19], base_skill);
    initi_poketmon(&poketmon_all_list[19], 20, "레트라", NORMAL, 55, 81, 60, 1, 0, 97, 9, NULL, base_skill);
    
    base_skill[0] = 42;	base_skill[1] = 7;
    initi_poketmon(&poketmon_all_list[20], 21, "깨비참", NORMAL, 40, 60, 30, 1, 20, 70, 9, &poketmon_all_list[21], base_skill);
    initi_poketmon(&poketmon_all_list[21], 22, "깨비드릴조", NORMAL, 65, 90, 65, 1, 0, 100, 12, NULL, base_skill);
    
    base_skill[0] = 15;	base_skill[1] = 7;
    initi_poketmon(&poketmon_all_list[22], 23, "아보", POISON, 35, 60, 44, 1, 22, 55, 9, &poketmon_all_list[23], base_skill);
    initi_poketmon(&poketmon_all_list[23], 24, "아보크", POISON, 60, 85, 69, 1, 0, 80, 12, NULL, base_skill);
    
    base_skill[0] = 49;	base_skill[1] = 32;
    initi_poketmon(&poketmon_all_list[24], 25, "피카츄", ELECTRIC, 35, 55, 40, 1, 22, 90, 14, &poketmon_all_list[24], base_skill);
    initi_poketmon(&poketmon_all_list[25], 26, "라이츄", ELECTRIC, 60, 90, 55, 1, 0, 110, 6, NULL, base_skill);
    
    initi_poketmon(&poketmon_all_list[26], 27, "모래두지", GROUND, 50, 75, 85, 1, 22, 40, 14, &poketmon_all_list[27], base_skill);
    initi_poketmon(&poketmon_all_list[27], 28, "고지", GROUND, 75, 100, 110, 1, 0, 65, 9, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[28], 29, "니드런♀", POISON, 55, 47, 52, 1, 16, 41, 14, &poketmon_all_list[29], base_skill);
	initi_poketmon(&poketmon_all_list[29], 30, "니드리나", POISON, 70, 62, 67, 1, 32, 56, 9, &poketmon_all_list[30], base_skill);
	initi_poketmon(&poketmon_all_list[30], 31, "니드퀸", POISON, 90, 92, 87, 1, 0, 76, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[31], 32, "니드런♂", POISON, 46, 57, 40, 1, 16, 50, 14, &poketmon_all_list[32], base_skill);
	initi_poketmon(&poketmon_all_list[32], 33, "니드리노", POISON, 61, 72, 57, 1, 32, 65, 9, &poketmon_all_list[33], base_skill);
	initi_poketmon(&poketmon_all_list[33], 34, "니드킹", POISON, 81, 102, 77, 1, 0, 85, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[34], 35, "삐삐", FAIRY, 70, 45, 48, 1, 32, 35, 14, &poketmon_all_list[35], base_skill);
	initi_poketmon(&poketmon_all_list[35], 36, "픽시", FAIRY, 95, 70, 73, 1, 0, 60, 9, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[36], 37, "식스테일", FIRE, 38, 41, 40, 1, 22, 65, 14, &poketmon_all_list[37], base_skill);
	initi_poketmon(&poketmon_all_list[37], 38, "나인테일", FIRE, 73, 76, 75, 1, 0, 100, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[38], 39, "푸린", FAIRY, 115, 45, 20, 1, 32, 20, 14, &poketmon_all_list[39], base_skill);
	initi_poketmon(&poketmon_all_list[39], 40, "푸크린", FAIRY, 140, 70, 45, 1, 0, 45, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[40], 41, "주뱃", POISON, 40, 45, 35, 1, 22, 55, 14, &poketmon_all_list[41], base_skill);
	initi_poketmon(&poketmon_all_list[41], 42, "골뱃", POISON, 75, 80, 70, 1, 0, 90, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[42], 43, "뚜벅쵸", GRASS, 45, 75, 65, 1, 21, 30, 14, &poketmon_all_list[43], base_skill);
	initi_poketmon(&poketmon_all_list[43], 44, "냄새꼬", GRASS, 60, 58, 75, 1, 32, 40, 9, &poketmon_all_list[44], base_skill);
	initi_poketmon(&poketmon_all_list[44], 45, "라플레시아", GRASS, 75, 110, 90, 1, 0, 50, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[45], 46, "파라스", BUG, 35, 70, 55, 1, 24, 25, 14, &poketmon_all_list[46], base_skill);
	initi_poketmon(&poketmon_all_list[46], 47, "파라섹트", BUG, 60, 95, 80, 1, 0, 30, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[47], 48, "콘팡", BUG, 60, 55, 50, 1, 31, 45, 14, &poketmon_all_list[48], base_skill);
	initi_poketmon(&poketmon_all_list[48], 49, "도나리", BUG, 70, 65, 60, 1, 0, 90, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[49], 50, "디그다", GROUND, 10, 55, 25, 1, 26, 95, 14, &poketmon_all_list[50], base_skill);
	initi_poketmon(&poketmon_all_list[50], 51, "닥트리오", GROUND, 35, 100, 50, 1, 0, 120, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[51], 52, "나옹", NORMAL, 40, 45, 35, 1, 28, 90, 14, &poketmon_all_list[52], base_skill);
	initi_poketmon(&poketmon_all_list[52], 53, "페르시온", NORMAL, 65, 70, 60, 1, 0, 115, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[53], 54, "고라파덕", WATER, 50, 52, 48, 1, 33, 55, 14, &poketmon_all_list[54], base_skill);
	initi_poketmon(&poketmon_all_list[54], 55, "골덕", WATER, 80, 82, 78, 1, 0, 85, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[55], 56, "망키", FIGHTING, 40, 80, 35, 1, 28, 70, 14, &poketmon_all_list[56], base_skill);
	initi_poketmon(&poketmon_all_list[56], 57, "성원숭", FIGHTING, 65, 105, 60, 1, 0, 95, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[57], 58, "가디", FIRE, 55, 70, 45, 1, 36, 60, 14, &poketmon_all_list[58], base_skill);
	initi_poketmon(&poketmon_all_list[58], 59, "윈디", FIRE, 90, 110, 80, 1, 0, 95, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[59], 60, "발챙이", WATER, 40, 50, 40, 1, 25, 90, 14, &poketmon_all_list[60], base_skill);
	initi_poketmon(&poketmon_all_list[60], 61, "슈륙챙이", WATER, 65, 65, 65, 1, 36, 70, 9, &poketmon_all_list[61], base_skill);
	initi_poketmon(&poketmon_all_list[61], 62, "강챙이", WATER, 90, 95, 95, 1, 0, 70, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[62], 63, "캐이시", PSYCHIC, 25, 20, 15, 1, 16, 90, 14, &poketmon_all_list[63], base_skill);
    initi_poketmon(&poketmon_all_list[63], 64, "윤겔라", PSYCHIC, 40, 35, 30, 1, 36, 105, 9, &poketmon_all_list[64], base_skill);
    initi_poketmon(&poketmon_all_list[64], 65, "후딘", PSYCHIC, 55, 50, 45, 1, 0, 120, 12, NULL, base_skill);	    
	initi_poketmon(&poketmon_all_list[65], 66, "알통몬", FIGHTING, 70, 80, 50, 1, 28, 70, 14, &poketmon_all_list[66], base_skill);
	initi_poketmon(&poketmon_all_list[66], 67, "근육몬", FIGHTING, 80, 100, 70, 1, 36, 45, 9, &poketmon_all_list[67], base_skill);
	initi_poketmon(&poketmon_all_list[67], 68, "괴력몬", FIGHTING, 90, 130, 80, 1, 0, 55, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[68], 69, "모다피", GRASS, 50, 75, 35, 1, 21, 30, 14, &poketmon_all_list[69], base_skill);
	initi_poketmon(&poketmon_all_list[69], 70, "우츠동", GRASS, 65, 90, 50, 1, 36, 45, 9, &poketmon_all_list[70], base_skill);
	initi_poketmon(&poketmon_all_list[70], 71, "우츠보트", GRASS, 80, 105, 65, 1, 0, 70, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[71], 72, "왕눈해", WATER, 40, 40, 35, 1, 30, 70, 14, &poketmon_all_list[72], base_skill);
	initi_poketmon(&poketmon_all_list[72], 73, "독파리", WATER, 80, 70, 65, 1, 0, 100, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[73], 74, "꼬마돌", ROCK, 40, 80, 100, 1, 25, 20, 14, &poketmon_all_list[74], base_skill);
	initi_poketmon(&poketmon_all_list[74], 75, "데구리", ROCK, 55, 95, 115, 1, 36, 35, 9, &poketmon_all_list[75], base_skill);
	initi_poketmon(&poketmon_all_list[75], 76, "딱구리", ROCK, 80, 120, 130, 1, 0, 45, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[76], 77, "포니타", FIRE, 50, 85, 55, 1, 40, 90, 14, &poketmon_all_list[77], base_skill);
	initi_poketmon(&poketmon_all_list[77], 78, "날쌩마", FIRE, 65, 100, 70, 1, 0, 105, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[78], 79, "야돈", WATER, 90, 65, 65, 1, 37, 15, 14, &poketmon_all_list[79], base_skill);
	initi_poketmon(&poketmon_all_list[79], 80, "야도란", WATER, 95, 75, 110, 1, 0, 30, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[80], 81, "코일", ELECTRIC, 25, 35, 70, 1, 30, 45, 14, &poketmon_all_list[81], base_skill);
	initi_poketmon(&poketmon_all_list[81], 82, "레어코일", ELECTRIC, 50, 60, 95, 1, 0, 70, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[82], 83, "파오리", FLYING, 52, 65, 55, 1, 0, 60, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[83], 84, "두두", NORMAL, 35, 85, 45, 1, 31, 75, 14, &poketmon_all_list[84], base_skill);
	initi_poketmon(&poketmon_all_list[84], 85, "두트리오", NORMAL, 60, 110, 70, 1, 0, 100, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[85], 86, "쥬쥬", WATER, 65, 45, 55, 1, 34, 45, 14, &poketmon_all_list[86], base_skill);
	initi_poketmon(&poketmon_all_list[86], 87, "쥬레곤", WATER, 90, 70, 80, 1, 0, 70, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[87], 88, "질퍽이", POISON, 80, 80, 50, 1, 38, 25, 14, &poketmon_all_list[88], base_skill);
	initi_poketmon(&poketmon_all_list[88], 89, "질뻐기", POISON, 105, 105, 75, 1, 0, 50, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[89], 90, "셀러", WATER, 30, 65, 100, 1, 36, 40, 14, &poketmon_all_list[90], base_skill);
	initi_poketmon(&poketmon_all_list[90], 91, "파르셀", WATER, 50, 95, 180, 1, 0, 70, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[91], 92, "고오스", GHOST, 30, 35, 30, 1, 25, 80, 14, &poketmon_all_list[92], base_skill);
	initi_poketmon(&poketmon_all_list[92], 93, "고우스트", GHOST, 45, 50, 45, 1, 38, 95, 9, &poketmon_all_list[93], base_skill);
	initi_poketmon(&poketmon_all_list[93], 94, "팬텀", GHOST, 60, 65, 60, 1, 0, 110, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[94], 95, "롱스톤", ROCK, 35, 45, 160, 1, 0, 70, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[95], 96, "슬리프", PSYCHIC, 60, 48, 45, 1, 26, 42, 14, &poketmon_all_list[96], base_skill);
	initi_poketmon(&poketmon_all_list[96], 97, "슬리퍼", PSYCHIC, 85, 73, 70, 1, 0, 67, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[97], 98, "크랩", WATER, 30, 105, 90, 1, 28, 50, 14, &poketmon_all_list[98], base_skill);
	initi_poketmon(&poketmon_all_list[98], 99, "킹크랩", WATER, 55, 130, 115, 1, 0, 75, 9, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[99], 100, "찌리리공", ELECTRIC, 40, 30, 50, 1, 30, 100, 14, &poketmon_all_list[100], base_skill);
	initi_poketmon(&poketmon_all_list[100], 101, "붐볼", ELECTRIC, 60, 50, 70, 1, 0, 140, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[101], 102, "아라리", GRASS, 60, 40, 80, 1, 36, 40, 14, &poketmon_all_list[102], base_skill);
	initi_poketmon(&poketmon_all_list[102], 103, "나시", GRASS, 95, 95, 85, 1, 0, 55, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[103], 104, "탕구리", GROUND, 50, 50, 95, 1, 28, 35, 14, &poketmon_all_list[104], base_skill);
	initi_poketmon(&poketmon_all_list[104], 105, "텅구리", GROUND, 60, 80, 110, 1, 0, 45, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[105], 106, "시라소몬", FIGHTING, 50, 120, 53, 1, 0, 87, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[106], 107, "홍수몬", FIGHTING, 50, 105, 79, 1, 0, 76, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[107], 108, "내루미", NORMAL, 90, 55, 75, 1, 0, 30, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[108], 109, "또가스", POISON, 40, 65, 95, 1, 35, 35, 14, &poketmon_all_list[109], base_skill);
	initi_poketmon(&poketmon_all_list[109], 110, "또도가스", POISON, 65, 90, 120, 1, 0, 60, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[110], 111, "뿔카노", GROUND, 80, 85, 95, 1, 42, 25, 9, &poketmon_all_list[111], base_skill);
	initi_poketmon(&poketmon_all_list[111], 112, "코뿌리", GROUND, 105, 130, 120, 1, 0, 40, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[112], 113, "럭키", NORMAL, 250, 5, 5, 1, 0, 50, 9, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[113], 114, "덩구리", GRASS, 65, 55, 115, 1, 0, 60, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[114], 115, "캥카", NORMAL, 105, 95, 80, 1, 0, 90, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[115], 116, "쏘드라", WATER, 30, 40, 70, 1, 32, 60, 14, &poketmon_all_list[116], base_skill);
	initi_poketmon(&poketmon_all_list[116], 117, "시드라", WATER, 55, 65, 95, 1, 0, 85, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[117], 118, "콘치", WATER, 45, 67, 60, 1, 33, 63, 14, &poketmon_all_list[118], base_skill);
	initi_poketmon(&poketmon_all_list[118], 119, "왕콘치", WATER, 80, 92, 65, 1, 0, 68, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[119], 120, "별가사리", WATER, 30, 45, 55, 1, 36, 85, 14, &poketmon_all_list[120], base_skill);
	initi_poketmon(&poketmon_all_list[120], 121, "아쿠스타", WATER, 60, 75, 85, 1, 0, 115, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[121], 122, "마임맨", PSYCHIC, 40, 45, 65, 1, 0, 90, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[122], 123, "스라크", BUG, 70, 110, 80, 1, 0, 105, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[123], 124, "루주라", ICE, 65, 50, 35, 1, 0, 95, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[124], 125, "에레브", ELECTRIC, 65, 83, 57, 1, 0, 105, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[125], 126, "마그마", FIRE, 65, 95, 57, 1, 0, 93, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[126], 127, "쁘사이저", BUG, 65, 125, 100, 1, 0, 85, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[127], 128, "켄타로스", NORMAL, 75, 100, 95, 1, 0, 110, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[128], 129, "잉어킹", WATER, 20, 10, 55, 1, 20, 80, 14, &poketmon_all_list[129], base_skill);
	initi_poketmon(&poketmon_all_list[129], 130, "갸라도스", WATER, 95, 125, 79, 1, 0, 81, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[130], 131, "라프라스", WATER, 130, 85, 80, 1, 0, 60, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[131], 132, "메타몽", NORMAL, 48, 48, 48, 1, 0, 48, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[132], 133, "이브이", NORMAL, 55, 55, 50, 1, 26, 55, 14, &poketmon_all_list[133], base_skill);
	initi_poketmon(&poketmon_all_list[133], 134, "샤미드", WATER, 130, 65, 60, 1, 0, 65, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[134], 135, "쥬피썬더", ELECTRIC, 65, 65, 60, 1, 0, 130, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[135], 136, "부스터", FIRE, 65, 130, 60, 1, 0, 65, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[136], 137, "폴리곤", NORMAL, 65, 60, 70, 1, 0, 40, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[137], 138, "암나이트", ROCK, 35, 40, 100, 1, 40, 35, 14, &poketmon_all_list[138], base_skill);
	initi_poketmon(&poketmon_all_list[138], 139, "암스타", ROCK, 70, 60, 125, 1, 0, 55, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[139], 140, "투구", ROCK, 30, 80, 90, 1, 40, 55, 14, &poketmon_all_list[140], base_skill);
	initi_poketmon(&poketmon_all_list[140], 141, "투구푸스", ROCK, 60, 115, 105, 1, 0, 80, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[141], 142, "프테라", ROCK, 80, 105, 65, 1, 0, 130, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[142], 143, "잠만보", NORMAL, 160, 110, 65, 1, 0, 30, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[143], 144, "프리져", ICE, 90, 85, 100, 1, 0, 85, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[144], 145, "썬더", ELECTRIC, 90, 90, 85, 1, 0, 100, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[145], 146, "파이어", FIRE, 90, 100, 90, 1, 0, 90, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[146], 147, "미뇽", DRAGON, 41, 64, 45, 1, 30, 50, 14, &poketmon_all_list[147], base_skill);
	initi_poketmon(&poketmon_all_list[147], 148, "신뇽", DRAGON, 61, 84, 65, 1, 55, 70, 9, &poketmon_all_list[148], base_skill);
	initi_poketmon(&poketmon_all_list[148], 149, "망나뇽", DRAGON, 91, 134, 95, 1, 0, 80, 12, NULL, base_skill);
	initi_poketmon(&poketmon_all_list[149], 150, "뮤츠", PSYCHIC, 106, 110, 90, 1, 0, 130, 5, NULL, base_skill);
}

void insert_poketmon_skill(){
	set_learn_skill(&poketmon_all_list[0], 0, 12, 9); //이상해씨 
	
	set_learn_skill(&poketmon_all_list[1], 0, 12, 9);// 이상해풀 
	set_learn_skill(&poketmon_all_list[1], 1, 18, 11);
	set_learn_skill(&poketmon_all_list[1], 2, 21, 12);	
	set_learn_skill(&poketmon_all_list[1], 3, 36, 10);
	
	set_learn_skill(&poketmon_all_list[2], 0, 12, 9);// 이상해꽃 
	set_learn_skill(&poketmon_all_list[2], 0, 12, 9);
	set_learn_skill(&poketmon_all_list[2], 1, 18, 11);
	set_learn_skill(&poketmon_all_list[2], 2, 21, 12);	
	set_learn_skill(&poketmon_all_list[2], 3, 36, 10);
	
	set_learn_skill(&poketmon_all_list[3], 0, 12, 6); //파이리
	
	set_learn_skill(&poketmon_all_list[4], 1, 17, 14); //리자드 
	set_learn_skill(&poketmon_all_list[4], 2, 20, 3);
	set_learn_skill(&poketmon_all_list[4], 3, 24, 5);
	
	set_learn_skill(&poketmon_all_list[5], 0, 6, 6);//리자몽 
	set_learn_skill(&poketmon_all_list[5], 1, 17, 14);
	set_learn_skill(&poketmon_all_list[5], 2, 20, 3);
	set_learn_skill(&poketmon_all_list[5], 3, 24, 5);
	
	set_learn_skill(&poketmon_all_list[6], 0, 12, 15);//꼬부기 
	set_learn_skill(&poketmon_all_list[6], 1, 15, 16);
	
	set_learn_skill(&poketmon_all_list[7], 0, 12, 15);//어니부기
	set_learn_skill(&poketmon_all_list[7], 1, 15, 16); 
	set_learn_skill(&poketmon_all_list[7], 1, 24, 17); 
	set_learn_skill(&poketmon_all_list[7], 1, 36, 18); 
	
	set_learn_skill(&poketmon_all_list[8], 0, 12, 15);//거북왕 
	set_learn_skill(&poketmon_all_list[8], 1, 15, 16); 
	set_learn_skill(&poketmon_all_list[8], 1, 24, 17); 
	set_learn_skill(&poketmon_all_list[8], 1, 36, 18); 
	
}
