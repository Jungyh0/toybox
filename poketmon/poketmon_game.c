#include "ui.c"
void game_main();

void prt_poketmon_info(poketmon *p, poketmon list[], int x);
void prt_hp_bar(poketmon *p, poketmon list[], int x, int y);
void prt_start_text(poketmon *p, poketmon *enemy);
void prt_skill_txt(skill skill_list[]);
void prt_exp_bar(poketmon *p, int plus_exp);
void prt_text(char text[], poketmon *p);
void prt_battle(poketmon *my, poketmon *enmy, poketmon list[]);
void prt_item_ui(int x, int y, char *str, int money);
void prt_evolution(poketmon *p, poketmon *ev_p);
void prt_poketmon_stat(poketmon *p, int x, int y, int color);
void check_pokeballs(int ball_count[]);

void change_skill(skill poketmon_skill_list[], int skill_number, skill s);
void change_poketmon(poketmon *my, int change_poketmon_index);
void check_new_skill(poketmon *p);
int check_priority(skill *skill1, skill *skill2);
void battle_start(poketmon *my_p, poketmon *en_p, skill *s1, int idx, poketmon list[]);
void battle_turn(int skill_idx, poketmon *my, poketmon *enmy, skill *my_s, skill *enmy_s, poketmon poketmon_all_list[]);

void insert_poketmon_skill();
void insert_ball_in_my_bag(ball *ball);
void init_poketmon_data();
void init_item_data(item list[]);
void load_all_skill_data(skill all_skill_list[]);
void set_learn_skill(poketmon *p, int index, int level, int skill_index);
void init_ball(ball *b, char *name, float ball_bonus, int color_index);
void init_ball_data(ball ball_info[]);

void select_my_poketmon(poketmon poketmon_all_list[], User *user, skill all_skill_list[]);
poketmon* select_enemy_poketmon(poketmon poketmon_all_list[], int color_number, skill all_skill_list[]);
skill select_skill(skill skill_list[]);
skill select_enemy_skill(poketmon *enemy, poketmon *my);
int select_item(item ilst[], int gold, int money, int round, int lv, int hp, int max_hp);
int get_enemy_level(int player_level); 
void select_remove_skill(poketmon *p, skill *s);
int select_user_move();
int select_my_poketmon_in_list(poketmon *my, poketmon *enmy);
int select_move_in_poketmon_list();
int select_released_poketmon(int x, int y);
int select_ball();

int calc_attack_damage(poketmon *atk_p, poketmon *def_p, skill *s);
int calc_acc(int acc);
void calc_rank_up(poketmon *p);
int calc_run(poketmon *my_p, poketmon *en_p);
float calc_rate(poketmon *enmy, ball *b);
int* calc_success_rate(float total_rate);
int calc_max_hp(poketmon *p, poketmon list[]);

void poketmon_learn_skill(poketmon *poketmon, skill all_skill_list[], int skill_number);
void evolution(poketmon *p);
void use_healing_pack(item *i, poketmon *p, bag *b, poketmon list[]);
void Rank_up(poketmon *p);
void level_up(poketmon *p);

void set_stat(poketmon *p, int lv, poketmon list[]);
void sort_ppoketmon_list(poketmon list[]);

void initialize_log();
void log_to_file(const char *log_message);

void remove_poketmon(int index, poketmon *my, poketmon *enmy);
void move(int selct_move, poketmon *my, poketmon *enmy, int s_POS);

void success_catch(int success, int color);
void bouns_ball(int bouns);

int battle(poketmon *my, poketmon *enmy, poketmon list[]);

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
{1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 0.5, 1, 1, 1, 1, 0, 0.5, 1},	//애스퍼 
{1, 0.5, 1, 1, 2, 2, 0.5, 0.5, 1, 0.5, 2, 1, 1, 0.5, 2, 0.5, 0.5},	//벌레 
{1, 2, 1, 1, 1, 2, 0.5, 1, 0.5, 2, 1, 2, 1, 1, 1, 0.5, 1},	//바위 
{0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 1},	//고스트 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 0.5, 0},	//드래곤 
{1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 0.5, 1, 0.5},	//악 
{1, 0.5, 0.5, 0.5, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 0.5, 2},	//강철 
{1, 0.5, 1, 1, 1, 1, 2, 0.5, 1, 1, 1, 1, 1, 2, 2, 0.5, 1}		//페어리 
};

poketmon poketmon_all_list[NUMBER_MAX];
skill all_skill_list[500];
int g_round = 1;
item all_item_list[3];
ball ball_list[4];
User my_user;
bag my_bag = {0};
int using_poketmon_index = 0, run_count = 0, skill_index = 0, bag_index = 0;
ball my_ball_list[4];
int ball_count[4] = {0};
int* bouns_and_success;


int main(){
	clear_input_buffer();
	game_main();
}

void game_main(){
		for (int i = 1; i < 5; i ++){
		my_user.poketmon_list[i].level = 0;
	}
	ball_count[0] = 10;
	ball_count[1] = 10;
	ball_count[2] = 10;
	ball_count[3] = 10;
	char log_message[200];
	my_user.alive_pokemon = 0;
	initialize_log();
	init_poketmon_data();
	insert_poketmon_skill();
	load_all_skill_data(all_skill_list);
	snprintf(log_message, sizeof(log_message), "------------------------------\n기술 데이터 초기화 완료");
	log_to_file(log_message);
	
	init_ball_data(my_ball_list);
	snprintf(log_message, sizeof(log_message), "------------------------------\n몬스터볼 리스트 초기화 완료");
	log_to_file(log_message);
	
	init_item_data(all_item_list);
	snprintf(log_message, sizeof(log_message), "------------------------------\n아이템 데이터 초기화 완료");
	log_to_file(log_message);
	CursorView(0);
	my_bag.money = 500;
	srand(time(NULL));
	int POS = 2;
	int hidden = 0;
	mainprt();
	while (1) {
		if (kbhit()){
			int ch = _getch();
			if (ch == 224){
				ch = _getch();
				switch(ch){
					case 72://위 
						if (POS == 0)	POS = 2;
						else POS --;
						break;
					case 80://아래 
						if (POS == 2)	POS = 0;
						else POS ++;
						break;
				}
			}
			else if (ch == 13 || ch == 32){
				break;
			}
			switch(POS){
				case 0:
					gotoxy(39, 8);	printf(" ");
					gotoxy(39, 10);	printf(" ");
					gotoxy(39, 12);	printf(" ");
					SetColor(11);
					gotoxy(39, 8);	printf(">");
					SetColor(15);
					break;
				case 1:
					gotoxy(39, 8);	printf(" ");
					gotoxy(39, 10);	printf(" ");
					gotoxy(39, 12);	printf(" ");
					SetColor(11);
					gotoxy(39, 10);	printf(">");
					SetColor(15);
					break;
				case 2:
					gotoxy(39, 8);	printf(" ");
					gotoxy(39, 10);	printf(" ");
					gotoxy(39, 12);	printf(" ");
					SetColor(11);
					gotoxy(39, 12);	printf(">");
					SetColor(15);
					break;
			}
		}
		Sleep(100);
	}
	if (POS == 1)	return;
	cls;
	if (POS == 0){
		select_my_poketmon(poketmon_all_list, &my_user, all_skill_list);
		POS = 0; 
		set_stat(&my_user.poketmon_list[0], 5, poketmon_all_list);
		snprintf(log_message, sizeof(log_message), "\nselect_my_poketmon으로 선택 후 검사\n%s의 learn_skill_level[0] = %d	learn_skill[0] = %d\n", my_user.poketmon_list[0].name, my_user.poketmon_list[0].learn_skill_level[0], my_user.poketmon_list[0].learn_skill[0]);	log_to_file(log_message);
		my_user.poketmon_list[0].skill_filled = 2;
		my_user.num_pokemons = 1;
		my_user.alive_pokemon ++;
	}
	if (POS == 1){
		load_game(&g_round, &my_user, poketmon_all_list);
		snprintf(log_message, sizeof(log_message), "내 포켓몬의 이름: %s", my_user.poketmon_list[0].name);
		log_to_file(log_message);
	}
	if (POS == 2)	return;
	
	int max_hp = my_user.poketmon_list[using_poketmon_index].hp;
	while(my_user.alive_pokemon > 0 && g_round <= MAX_ROUND){
		poketmon enemy_poketmon;
		int n_hp, n_max_hp, sub_hp; 
		cls;
		gotoxy(0, 0); printf("round: %d", g_round);	
		gotoxy(25, 0); 
		SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
		// 적 포켓몬 셋팅
		if (g_round == MAX_ROUND){
			memcpy(&enemy_poketmon, &poketmon_all_list[149], sizeof(poketmon));
			poketmon_learn_skill(&enemy_poketmon, all_skill_list, 57); 
		} 
		else{
			poketmon *en = select_enemy_poketmon(poketmon_all_list, my_user.poketmon_list[using_poketmon_index].color_number, all_skill_list);
			memcpy(&enemy_poketmon, en, sizeof(poketmon));
		}
		int level_enemy = get_enemy_level(my_user.poketmon_list[using_poketmon_index].level);
		if (my_user.poketmon_list[using_poketmon_index].level < 6 && g_round < 10)	level_enemy = get_enemy_level(3);
		set_stat(&enemy_poketmon, level_enemy, poketmon_all_list);
		prt_battle(&my_user.poketmon_list[using_poketmon_index], &enemy_poketmon, poketmon_all_list);
		
		if (my_user.poketmon_list[using_poketmon_index].hp > 0){
			g_round++;
			if (my_user.poketmon_list[using_poketmon_index].exp >= my_user.poketmon_list[using_poketmon_index].max_exp){
				level_up(&my_user.poketmon_list[using_poketmon_index]);
			}
			int get_gold = 100 * g_round / log(3);  
			int item_idx = select_item(all_item_list, get_gold, my_bag.money, g_round, my_user.poketmon_list[using_poketmon_index].level, my_user.poketmon_list[using_poketmon_index].hp, max_hp);
			int idx = 0;
			switch (item_idx) {	
				case 0:
					if (g_round < 15)	idx = 0;
					if (g_round >= 15 && g_round < 30)	idx = 1;
					if (g_round >= 36)	idx = 2;
					use_healing_pack(&all_item_list[idx],  &my_user.poketmon_list[using_poketmon_index], &my_bag, poketmon_all_list);
					break;
				case 1:
					clear_line(12);	clear_line(13);
					gotoxy(2,12);	printf("%d골드를 얻었다!!", get_gold);
					my_bag.money += get_gold;	
					make_input_buffer();
					break;
				case 2:
					n_hp = my_user.poketmon_list[using_poketmon_index].hp;
					n_max_hp = calc_max_hp(&my_user.poketmon_list[using_poketmon_index],poketmon_all_list);
					sub_hp = n_max_hp - n_hp;
					Rank_up(&my_user.poketmon_list[using_poketmon_index]);
					my_user.poketmon_list[using_poketmon_index].hp -= sub_hp;
					break;
				case 3: 
					if (hidden == 2){
						hidden = 0;
						snprintf(log_message, sizeof(log_message), "히든으로 능력치 상승, 체력 회복!");
						log_to_file(log_message);
						clear_line(12);	clear_line(13);
						gotoxy(2,12);	printf("%s의 모든 능력치가 매우 크게 올랐다!!", my_user.poketmon_list[using_poketmon_index].name);
						make_input_buffer();
						for (int i = 0; i < 4; i ++){
							if (my_user.poketmon_list[using_poketmon_index].rank_up[i] < 6)
								my_user.poketmon_list[using_poketmon_index].rank_up[i] += 2;
						}
						my_user.poketmon_list[using_poketmon_index].hp = calc_max_hp(&my_user.poketmon_list[using_poketmon_index], poketmon_all_list);
						calc_rank_up(&my_user.poketmon_list[using_poketmon_index]);
					}
					else
						hidden ++;
					break;
				default:
					break;			
			}
		}
		save_game(g_round, &my_user);
	}
	if (g_round == 51){
		cls;
		gotoxy(1,2);	printf("game clear!!");
		clear_input_buffer();
		game_main();
	}
}

int calc_max_hp(poketmon *p, poketmon list[]){
	char log_message[200];
	
	int max_hp = list[p->number - 1].hp + (p->level - 1) * 2;
	int hp_rank_up = p->rank_up[0];
	if (hp_rank_up > 0){
		for (int i = 0; i < hp_rank_up; i++){
    		max_hp += max_hp / 2;
    		snprintf(log_message, sizeof(log_message), "체력 1랭크 상승!!");
			log_to_file(log_message);
		}
	}
	
	return max_hp;
}

void prt_poketmon_info(poketmon *p, poketmon list[], int x){
	if (x == 0) {	// 내 포켓몬 
		gotoxy(15,8);	printf("%s	Lv. %d", p->name, p->level);
		SetColor(10);
		prt_hp_bar(p, list, 15, 9);
		prt_exp_bar(p, 0);
		SetColor(p->color_number);
		gotoxy(2,10);	printf("%c", p->imege);
		SetColor(15);
		gotoxy(0,11);	printf("--------------------------------");
	}
	if (x == 1) {	//상대 포켓몬 
		clear_line(1);
		gotoxy(4,1);	printf("%s Lv. %d", p->name, p->level);
		prt_hp_bar(p, list, 4, 2);
		SetColor(p->color_number);
		clear_line(3);
		gotoxy(25,3);	printf("%c", p->imege);
		SetColor(15);
	} 
}

void prt_item_ui(int x, int y, char *str, int money){
	char *str1 = str;
	int len = strlen(str1);
	int max_x = 30;
	int line_x = 1, line_y = 12;
	
	SetColor(5);
	gotoxy(5,6);	printf("ㅁ");
	SetColor(11);
	gotoxy(x,y);	printf(">");
	SetColor(6);
	gotoxy(15,6);	printf("ㅁ");
	SetColor(3);
	gotoxy(25,6);	printf("ㅁ");
	SetColor(14);
	gotoxy(25, 1);	printf("$: %d", money);
	SetColor(15);
	gotoxy(24, 10);	printf("건너뛰기");
	for (int i = 0; i < len; i++) {
		if (str1[i] == ' ') {
            line_x++;
            continue;
        }
        gotoxy(line_x, line_y);
        printf("%c", str1[i]);
        line_x++;
        if (line_x >= max_x) {  
            line_x = 0; 
            line_y++; 
        }
    }
}

void prt_hp_bar(poketmon *p, poketmon list[], int x, int y){
	SetColor(15);
	int hp_rank_up = p->rank_up[0];
	int hp = p->hp;
	int number = p->number;
	int hp_color = 10;
	int max_hp = list[number - 1].hp + (p->level - 1) * 2;
	if (hp_rank_up > 0){
		for (int i = 0; i < hp_rank_up; i++){
    		max_hp += max_hp / 2;
		}
	}
	
	float draw_ratio = (float)hp / max_hp;
    int draw = (int)round(draw_ratio * 10);
	
	if (draw <6 && draw > 2)	hp_color = 6;
	else if (draw < 3)	hp_color = 4;
	
	if (x == 15){
		gotoxy(x,y);	
		printf("%d / %d", hp, max_hp);		
	}
	else 
		gotoxy(x,y);
	
	SetColor(hp_color);
	for (int i = 0; i < draw; i ++){
		printf("-");
	}
	SetColor(15);
}

void prt_start_text(poketmon *my, poketmon *enmy){
	char log_message[200];
	clear_line(12);
	clear_line(13);
	gotoxy(2,12);	
	printf("야생의 %s(이)가 나타났다!",enmy->name);
	make_input_buffer();
	clear_line(12);
	
	gotoxy(2,12);
	printf("가랏! %s!", my->name);
	make_input_buffer();
	clear_line(12);
	
	if (my_user.alive_pokemon > 1){
		clear_line(12);
		clear_line(13);
		gotoxy(0,11);	printf("--------------------------------------");
		gotoxy(2,12);
		printf("포켓몬을 교체하시겠습니까?");
		gotoxy(30,12);	printf("|");
		gotoxy(30,13);	printf("|");
		
		SetColor(11); 
		gotoxy(31, 12);	printf(">");	SetColor(15); 
		gotoxy(32, 12);	printf("예");
		gotoxy(32, 13);	printf("아니요");
		int mo = select_released_poketmon(31, 13);
		SetColor(15);
		
		if (mo == 0){
			cls;
			show_my_poketmon_ui(0);
			if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
			
			if (my_user.num_pokemons > 1){
				if (my_user.poketmon_list[1].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
				}
				if (my_user.poketmon_list[2].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
				}
				if (my_user.poketmon_list[3].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
				}
				if (my_user.poketmon_list[4].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
				}
			}
			int test = select_my_poketmon_in_list(my, enmy);
			
			while(my_user.poketmon_list[test].hp == 0){
				test = select_my_poketmon_in_list(my, enmy);
				snprintf(log_message, sizeof(log_message), "%s의 체력이 %d입니다. 다시 선택하세요.", my_user.poketmon_list[test], my_user.poketmon_list[test].hp);
				log_to_file(log_message);
			}
			
			if (test != 27){
				cls;
				gotoxy(0, 0); 
				printf("round: %d", g_round);
				prt_poketmon_info(my, poketmon_all_list, 0);
				prt_poketmon_info(enmy, poketmon_all_list, 1);
				change_poketmon(my, test);
			}
		}
	}
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
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "경험치 상승 적용 실행\n현제 경험치: %d\n상승 경헙치: %d",p->exp, plus_exp);
	log_to_file(log_message);
	int lv = p->level;

	int n = p->level + 1;
	int max_exp =  1.2 * (int)pow((double)n, 3.0) - 15 * (int)pow((double)n, 2.0) + 100 * n - 140;
	p->max_exp = max_exp;
	snprintf(log_message, sizeof(log_message), "\n최대 경험치:  %d\n", p->max_exp);
	log_to_file(log_message);
	clear_line(12);	clear_line(13);
	SetColor(p->color_number);
	gotoxy(2,10);	printf("%c", p->imege);
	SetColor(15);
	gotoxy(11, 10);	printf("exp");
	int exp = p->exp + plus_exp;
	p->exp = exp; 
	float draw_rate = ((float)exp / max_exp) * 10;
	int draw = (int)round(draw_rate);
	snprintf(log_message, sizeof(log_message), "상승후 경험치: %d",p->exp);
	log_to_file(log_message);
	
	snprintf(log_message, sizeof(log_message), "\n 경험치칸 수: %d\n",draw);
	log_to_file(log_message);
	if (draw < 11){
		if (draw < 1 && exp > 0){
			gotoxy(15, 10);	SetColor(3);
			printf("-");
			SetColor(15);
			return;
		}
	
		gotoxy(15, 10);	SetColor(3);
		for (int i = 0; i < draw; i ++){
			printf("-");
		}
	}
	else{
		gotoxy(15, 10);	SetColor(3);
		for (int i = 0; i < 10; i ++){
			printf("-");
		}
	}
	SetColor(15);
}

int select_user_move(poketmon *my_p){
	gotoxy(0,11);	printf("----------------------------------------------------");
	gotoxy(2,12);
	printf("%s(은)는 무엇을 할까??", my_p->name);
	
	gotoxy(30,12);	printf("|");
	gotoxy(30,13);	printf("|");

	SetColor(11);
	gotoxy(32,12);	printf(">"); 
	SetColor(15);
	
	gotoxy(33,12);	printf("싸운다");
	gotoxy(33,13);	printf("포켓몬");
	
	gotoxy(43,12);	printf("볼");
	gotoxy(43,13);	printf("도망간다");
	
	int s_POS = 0;
	
	while(1){
		if (_kbhit()){
			int ch = _getch();
            if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                    case 75: //왼쪽 
                        if (s_POS == 0) s_POS = 1;
                        else if(s_POS == 2) s_POS = 3;
                        else s_POS -= 1;
                        break;
                    case 77: //오른쪽 
                        if (s_POS == 1) s_POS = 0;
                        else if(s_POS == 3) s_POS = 2;
                        else s_POS += 1;
                        break;
                    case 72: //위 
                        if (s_POS == 1) s_POS = 3;
                        else if(s_POS == 0)	s_POS = 2;
                        else s_POS -= 2;
                        break;
                    case 80: //아래 
                        if (s_POS == 3) s_POS = 1;
                        else if(s_POS == 2)	s_POS = 0;
                        else s_POS += 2;
                        break;
                }
            } 
			else if (ch == 13 || ch == 32) { 
                break;
            } 
            switch(s_POS){
            	case 0:
            		gotoxy(32,12);	printf(" ");
					gotoxy(32,13);	printf(" ");	
					gotoxy(42,12);	printf(" ");	
					gotoxy(42,13);	printf(" ");
					gotoxy(32,12);
					SetColor(11);		
					printf(">");
					SetColor(15);
					break;
				case 1:
            		gotoxy(32,12);	printf(" ");
					gotoxy(32,13);	printf(" ");	
					gotoxy(42,12);	printf(" ");	
					gotoxy(42,13);	printf(" ");
					gotoxy(42,12);
					SetColor(11);		
					printf(">");
					SetColor(15);
					break;
				case 2:
            		gotoxy(32,12);	printf(" ");
					gotoxy(32,13);	printf(" ");	
					gotoxy(42,12);	printf(" ");	
					gotoxy(42,13);	printf(" ");
					gotoxy(32,13);
					SetColor(11);		
					printf(">");
					SetColor(15);
					break;
				case 3:
            		gotoxy(32,12);	printf(" ");
					gotoxy(32,13);	printf(" ");	
					gotoxy(42,12);	printf(" ");	
					gotoxy(42,13);	printf(" ");
					gotoxy(42,13);
					SetColor(11);		
					printf(">");
					SetColor(15);
					break;
				default:
					clear_line(12);
					clear_line(13);
					gotoxy(2,12); 
					printf("에러 발생!!");
					make_input_buffer();
					break;
			}
		}
		Sleep(100);
	}
	
	clear_line(11);	gotoxy(0,11);	
	printf("--------------------------------");
	return s_POS;
}

int calc_run(poketmon *my_p, poketmon *en_p){
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "도망치기를 선택!!\n현제 도망시도 횟수: %d", run_count);
    log_to_file(log_message);
    snprintf(log_message, sizeof(log_message), "내 포켓몬의 스피드: %d\n적 포켓몬의 스피드: %d", my_p->speed, en_p->speed);
    log_to_file(log_message);
	float run_rate = (((float)(my_p->speed * 32) / (en_p->speed * 32)) + (30.0 * run_count)) / 256.0 * 100.0;
	srand(time(NULL));
	int random_value = rand() % 100;
	snprintf(log_message, sizeof(log_message), "도망갈 확률: %f", run_rate);
    log_to_file(log_message);
	
	if (run_rate >= random_value || g_round == MAX_ROUND - 1) {
        return 1;
    } else {
        return 0;
    }
    
	return run_rate;
}

void check_pokeballs(int ball_count[]){	
	gotoxy(49, 3);	printf("%d", ball_count[0]);
	gotoxy(47, 5);	printf("%d", ball_count[1]);
	gotoxy(49, 7);	printf("%d", ball_count[2]);
	gotoxy(49, 9);	printf("%d", ball_count[3]);
}

void insert_ball_in_my_bag(ball *b){
	
	//if (strcmp())
	
	
}



void prt_battle(poketmon *my, poketmon *enmy, poketmon list[]){
	char log_message[200];
	int run;
	snprintf(log_message, sizeof(log_message), "prt_battle시작");
    log_to_file(log_message);
	// UI그리기 
	prt_poketmon_info(my, list, 0);
	prt_poketmon_info(enmy, list, 1);
	prt_start_text(my, enmy);
	run = battle(my, enmy, poketmon_all_list);
	
	if (run == 1) {
		poketmon *en = select_enemy_poketmon(poketmon_all_list, my_user.poketmon_list[using_poketmon_index].color_number, all_skill_list);
		memcpy(enmy, en, sizeof(poketmon));	
		int enemy_level = get_enemy_level(my_user.poketmon_list[using_poketmon_index].level);
		set_stat(enmy, enemy_level, poketmon_all_list);

		cls;  // 화면 초기화
		gotoxy(0, 0); 
		printf("round: %d", g_round);
		gotoxy(25, 0); 
		SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
		prt_battle(&my_user.poketmon_list[using_poketmon_index], enmy, poketmon_all_list);
	}
	
	if (my->hp == 0){
		prt_text("은(는) 쓰러졌다", my);
		my_user.alive_pokemon--;
		make_input_buffer();
		clear_line(12);
		gotoxy(2,12);
		
		if (my_user.alive_pokemon <= 0){
			printf("눈앞이 깜깜해졌다....");
			make_input_buffer();
			cls;
			clear_input_buffer();
			game_main();	
		} 
		else{
			cls;
			show_my_poketmon_ui(0);
			prt_poketmon_stat(my, 2, 5, 15);
			
			if (my_user.num_pokemons > 1){
				if (my_user.poketmon_list[1].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
				}
				if (my_user.poketmon_list[2].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
				}
				if (my_user.poketmon_list[3].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
				}
				if (my_user.poketmon_list[4].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
				}
			}
			
			int test = select_my_poketmon_in_list(my, enmy);
			
			if(my_user.poketmon_list[test].hp <= 0){
				while(my_user.poketmon_list[test].hp <= 0){
					test = select_my_poketmon_in_list(my, enmy);
				}
			}
			
			
			poketmon change_poketmon = my_user.poketmon_list[test];
			my_user.poketmon_list[test] = *my;
			*my = change_poketmon;
			    
			cls;
			gotoxy(0, 0); 
			printf("round: %d", g_round);
			prt_poketmon_info(my, poketmon_all_list, 0);
			prt_poketmon_info(enmy, poketmon_all_list, 1);
			
			clear_line(12);
			gotoxy(2, 12); printf("가랏 %s!!", my->name);
			make_input_buffer();
			battle(my, enmy, poketmon_all_list);	
			
		}
		
	}
	else if (enmy->hp == 0){
		prt_text("은(는) 쓰러졌다", enmy);
		Sleep(100);
		clear_line(3);
		make_input_buffer();
		float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
		int up_exp = (int)round(up_exp_rate);
		clear_line(12);
		gotoxy(2,12);
		printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
		make_input_buffer(); 
		prt_exp_bar(my, up_exp);
		make_input_buffer();
	}
	
	run = 0;
}

int battle(poketmon *my, poketmon *enmy, poketmon list[]){
	char log_message[200];
	float total_rate;
	int run = 0;
	while(my->hp > 0 && enmy->hp > 0){
		clear_line(12);	clear_line(13);
		int user_select = select_user_move(my);
		
		if (user_select == 0){
			prt_skill_txt(my->skill_list);

			skill my_use_skill = select_skill(my->skill_list);
			if (strcmp(my_use_skill.skill_name, "돌아가기") == 0){
				 continue; 
			}
		
			snprintf(log_message, sizeof(log_message), "내 포켓몬의 기술이 선택되었습니다.");
    		log_to_file(log_message);
			skill enemy_use_skill = select_enemy_skill(enmy, my);
			snprintf(log_message, sizeof(log_message), "적 포켓몬의 기술이 선택되었습니다.");
    		log_to_file(log_message);
			skill use_skill_list[2] = {};
			use_skill_list[0] = my_use_skill;
			use_skill_list[1] = enemy_use_skill;
			int skill_idx = check_priority(&use_skill_list[0],&use_skill_list[1]);
			snprintf(log_message, sizeof(log_message), "우선도 계산 완료");
    		log_to_file(log_message);
			// 데미지 계산, 적용 
			float match = type_matchup[use_skill_list[0].type][my_user.poketmon_list[using_poketmon_index].type];
			snprintf(log_message, sizeof(log_message), "상성 계산 완료");
			log_to_file(log_message);
			battle_turn(skill_idx, my, enmy, &use_skill_list[0], &use_skill_list[1], list);
		}
		
		else if (user_select == 1){
			prt_select_poketball_ui();
			check_pokeballs(ball_count);
			int ball_index = select_ball();
			
			if (ball_index == 27){
				cls;
				gotoxy(0, 0); 
				printf("round: %d", g_round);
				prt_poketmon_info(my, list, 0);
				prt_poketmon_info(enmy, list, 1);
				continue;
			}
			else if (ball_index == 0){
				if (ball_count[0] > 0){
					ball_count[0] --;
					clear_select_poketball_ui();
					gotoxy(36, 3);	printf(" "); 
					prt_ball_throw(my_ball_list[0].color_index);
					snprintf(log_message, sizeof(log_message), "--------------------------------\nball_index가 0일 때 몬스터볼 확인");
					log_to_file(log_message);
					snprintf(log_message, sizeof(log_message), "my_ball_list[0].name: %s, my_ball_list[0].bonus: %f", my_ball_list[0].name, my_ball_list[0].ball_bonus);
					log_to_file(log_message);
					total_rate = calc_rate(enmy, &my_ball_list[0]);
					bouns_and_success = calc_success_rate(total_rate);
					bouns_ball(bouns_and_success[0]);
					Sleep(500);
					success_catch(bouns_and_success[1], enmy->color_number);
					SetColor(15);
					
					
					if (bouns_and_success[1] == 1){
						clear_line(12);
						clear_line(13);	gotoxy(2,12);
						printf("신난다! 야생의 %s를 잡았다!!", enmy->name);	make_input_buffer();
						if (my_user.num_pokemons < 5){
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
							my_user.num_pokemons ++;
							make_input_buffer();
							break;
						}
						
						if (my_user.num_pokemons >= 5){
							clear_line(12);	gotoxy(2, 12);
							printf("지닌 포켓몬이 가득 찼습니다.");
							gotoxy(2, 13);	printf("대신해 포켓몬을 놓아주시겠습니까??");
							SetColor(11);
							gotoxy(40, 12);	printf(">");
							SetColor(15);
							gotoxy(41, 12);	printf("예");
							gotoxy(41, 13);	printf("아니요");
							int mo = select_released_poketmon(40, 13);
							SetColor(15);
							
							if (mo == 0){
								cls;
								show_my_poketmon_ui(0);
								if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
								
								if (my_user.num_pokemons > 1){
									if (my_user.poketmon_list[1].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
									}
									if (my_user.poketmon_list[2].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
									}
									if (my_user.poketmon_list[3].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
									}
									if (my_user.poketmon_list[4].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
									}
								}
								int test = select_my_poketmon_in_list(my, enmy);
								gotoxy(2, 16);	printf("%s(을)를 정말 놓아주겠습니까?", my_user.poketmon_list[test].name);
								SetColor(11);
								gotoxy(49, 16);	printf(">");
								SetColor(15);
								gotoxy(50, 16);	printf("예");
								gotoxy(50, 17);	printf("아니요");	
								mo = select_released_poketmon(49, 17);
								if (mo == 0){
									clear_line(16);
									clear_line(17);
									clear_line(18);
									remove_poketmon(test, my, enmy);
									gotoxy(2, 16);	printf("바이바이 %s!!", my_user.poketmon_list[test].name);
									make_input_buffer();
									memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
									cls;
									prt_poketmon_info(my, poketmon_all_list, 0);
								}	
							}
							
							
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							clear_line(13);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							make_input_buffer();	
							break;
						}
					}	
					else{
						clear_line(12);	clear_line(13);
						gotoxy(2, 12);	printf("앗! 볼에서 나와버렸다!");
						make_input_buffer(); 	
						skill enemy_use_skill = select_enemy_skill(enmy, my);
						snprintf(log_message, sizeof(log_message), "적 포켓몬의 기술이 선택되었습니다.");
		    			log_to_file(log_message);
		    			
		    			float match = type_matchup[enemy_use_skill.type][my->type];
		    			snprintf(log_message, sizeof(log_message), "상성 계산 완료");
						log_to_file(log_message);
					
						battle_start(enmy, my, &enemy_use_skill, 1, poketmon_all_list);
						snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enemy_use_skill.skill_name, my->name);
		    			log_to_file(log_message);
					}
				}
				else{
			        clear_select_poketball_ui();
			        gotoxy(36, 3);	printf(" "); 
			        clear_line(12);
			        clear_line(13);
			        gotoxy(2, 12);	printf("몬스터 볼이 부족합니다!!");
			        make_input_buffer();
				}
			}
			else if (ball_index == 1){
				if (ball_count[1] > 0){
					ball_count[1] --;
					clear_select_poketball_ui();
					gotoxy(36, 5);	printf(" "); 
					prt_ball_throw(my_ball_list[1].color_index);
					snprintf(log_message, sizeof(log_message), "--------------------------------\nball_index가 1 때 몬스터볼 확인");
					log_to_file(log_message);
					snprintf(log_message, sizeof(log_message), "my_ball_list[0].name: %s, my_ball_list[1].bonus: %f", my_ball_list[1].name, my_ball_list[1].ball_bonus);
					log_to_file(log_message);
					total_rate = calc_rate(enmy, &my_ball_list[1]);
					bouns_and_success = calc_success_rate(total_rate);
					bouns_ball(bouns_and_success[0]);
					Sleep(500);
					success_catch(bouns_and_success[1], enmy->color_number);
					SetColor(15);
					
					
					if (bouns_and_success[1] == 1){
						clear_line(12);
						clear_line(13);	gotoxy(2,12);
						printf("신난다! 야생의 %s를 잡았다!!", enmy->name);	make_input_buffer();
						if (my_user.num_pokemons < 5){
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
							my_user.num_pokemons ++;
							make_input_buffer();
							break;
						}
						
						if (my_user.num_pokemons >= 5){
							clear_line(12);	gotoxy(2, 12);
							printf("지닌 포켓몬이 가득 찼습니다.");
							gotoxy(2, 13);	printf("대신해 포켓몬을 놓아주시겠습니까??");
							SetColor(11);
							gotoxy(40, 12);	printf(">");
							SetColor(15);
							gotoxy(41, 12);	printf("예");
							gotoxy(41, 13);	printf("아니요");
							int mo = select_released_poketmon(40, 13);
							SetColor(15);
							
							if (mo == 0){
								cls;
								show_my_poketmon_ui(0);
								if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
								
								if (my_user.num_pokemons > 1){
									if (my_user.poketmon_list[1].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
									}
									if (my_user.poketmon_list[2].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
									}
									if (my_user.poketmon_list[3].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
									}
									if (my_user.poketmon_list[4].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
									}
								}
								int test = select_my_poketmon_in_list(my, enmy);
								gotoxy(2, 16);	printf("%s(을)를 정말 놓아주겠습니까?", my_user.poketmon_list[test].name);
								SetColor(11);
								gotoxy(49, 16);	printf(">");
								SetColor(15);
								gotoxy(50, 16);	printf("예");
								gotoxy(50, 17);	printf("아니요");	
								mo = select_released_poketmon(49, 17);
								if (mo == 0){
									clear_line(16);
									clear_line(17);
									clear_line(18);
									remove_poketmon(test, my, enmy);
									gotoxy(2, 16);	printf("바이바이 %s!!", my_user.poketmon_list[test].name);
									make_input_buffer();
									memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
									cls;
									prt_poketmon_info(my, poketmon_all_list, 0);
								}	
							}
							
							
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							clear_line(13);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							make_input_buffer();	
							break;
						}
					}
					else{
						clear_line(12);	clear_line(13);
						gotoxy(2, 12);	printf("앗! 볼에서 나와버렸다!");
						make_input_buffer(); 	
						skill enemy_use_skill = select_enemy_skill(enmy, my);
						snprintf(log_message, sizeof(log_message), "적 포켓몬의 기술이 선택되었습니다.");
		    			log_to_file(log_message);
		    			
		    			float match = type_matchup[enemy_use_skill.type][my->type];
		    			snprintf(log_message, sizeof(log_message), "상성 계산 완료");
						log_to_file(log_message);
					
						battle_start(enmy, my, &enemy_use_skill, 1, poketmon_all_list);
						snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enemy_use_skill.skill_name, my->name);
		    			log_to_file(log_message);
					}
				}
				else{
			        clear_select_poketball_ui();
			        gotoxy(36, 5);	printf(" "); 
			        clear_line(12);
			        clear_line(13);
			        gotoxy(2, 12);	printf("몬스터 볼이 부족합니다!!");
			        make_input_buffer();
				}
			}
			else if (ball_index == 2){
				if (ball_count[2] > 0){
					ball_count[2] --;
					clear_select_poketball_ui();
					gotoxy(36, 7);	printf(" "); 
					prt_ball_throw(my_ball_list[2].color_index);
					snprintf(log_message, sizeof(log_message), "--------------------------------\nball_index가 2 때 몬스터볼 확인");
					log_to_file(log_message);
					snprintf(log_message, sizeof(log_message), "my_ball_list[0].name: %s, my_ball_list[1].bonus: %f", my_ball_list[2].name, my_ball_list[2].ball_bonus);
					log_to_file(log_message);
					total_rate = calc_rate(enmy, &my_ball_list[1]);
					bouns_and_success = calc_success_rate(total_rate);
					bouns_ball(bouns_and_success[0]);
					Sleep(500);
					success_catch(bouns_and_success[1], enmy->color_number);
					SetColor(15);
					
					
					if (bouns_and_success[1] == 1){
						clear_line(12);
						clear_line(13);	gotoxy(2,12);
						printf("신난다! 야생의 %s를 잡았다!!", enmy->name);	make_input_buffer();
						if (my_user.num_pokemons < 5){
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
							my_user.num_pokemons ++;
							make_input_buffer();
							break;
						}
						
						if (my_user.num_pokemons >= 5){
							clear_line(12);	gotoxy(2, 12);
							printf("지닌 포켓몬이 가득 찼습니다.");
							gotoxy(2, 13);	printf("대신해 포켓몬을 놓아주시겠습니까??");
							SetColor(11);
							gotoxy(40, 12);	printf(">");
							SetColor(15);
							gotoxy(41, 12);	printf("예");
							gotoxy(41, 13);	printf("아니요");
							int mo = select_released_poketmon(40, 13);
							SetColor(15);
							
							if (mo == 0){
								cls;
								show_my_poketmon_ui(0);
								if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
								
								if (my_user.num_pokemons > 1){
									if (my_user.poketmon_list[1].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
									}
									if (my_user.poketmon_list[2].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
									}
									if (my_user.poketmon_list[3].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
									}
									if (my_user.poketmon_list[4].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
									}
								}
								int test = select_my_poketmon_in_list(my, enmy);
								gotoxy(2, 16);	printf("%s(을)를 정말 놓아주겠습니까?", my_user.poketmon_list[test].name);
								SetColor(11);
								gotoxy(49, 16);	printf(">");
								SetColor(15);
								gotoxy(50, 16);	printf("예");
								gotoxy(50, 17);	printf("아니요");	
								mo = select_released_poketmon(49, 17);
								if (mo == 0){
									clear_line(16);
									clear_line(17);
									clear_line(18);
									remove_poketmon(test, my, enmy);
									gotoxy(2, 16);	printf("바이바이 %s!!", my_user.poketmon_list[test].name);
									make_input_buffer();
									memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
									cls;
									prt_poketmon_info(my, poketmon_all_list, 0);
								}	
							}
							
							
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							clear_line(13);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							make_input_buffer();	
							break;
						}
					}
					else{
						clear_line(12);	clear_line(13);
						gotoxy(2, 12);	printf("앗! 볼에서 나와버렸다!");
						make_input_buffer(); 	
						skill enemy_use_skill = select_enemy_skill(enmy, my);
						snprintf(log_message, sizeof(log_message), "적 포켓몬의 기술이 선택되었습니다.");
		    			log_to_file(log_message);
		    			
		    			float match = type_matchup[enemy_use_skill.type][my->type];
		    			snprintf(log_message, sizeof(log_message), "상성 계산 완료");
						log_to_file(log_message);
					
						battle_start(enmy, my, &enemy_use_skill, 1, poketmon_all_list);
						snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enemy_use_skill.skill_name, my->name);
		    			log_to_file(log_message);
					}
				}
				else{
			        clear_select_poketball_ui();
			        gotoxy(36, 7);	printf(" "); 
			        clear_line(12);
			        clear_line(13);
			        gotoxy(2, 12);	printf("몬스터 볼이 부족합니다!!");
			        make_input_buffer();
				}
			}
			else if (ball_index == 3){
				if (ball_count[3] > 0){
					ball_count[3] --;
					clear_select_poketball_ui();
					gotoxy(36, 9);	printf(" "); 
					prt_ball_throw(my_ball_list[3].color_index);
					snprintf(log_message, sizeof(log_message), "--------------------------------\nball_index가 3 때 몬스터볼 확인");
					log_to_file(log_message);
					snprintf(log_message, sizeof(log_message), "my_ball_list[0].name: %s, my_ball_list[1].bonus: %f", my_ball_list[3].name, my_ball_list[3].ball_bonus);
					log_to_file(log_message);
					int total_rate = 255;
					bouns_and_success = calc_success_rate(total_rate);
					bouns_ball(bouns_and_success[0]);
					Sleep(500);
					success_catch(bouns_and_success[1], enmy->color_number);
					SetColor(15);
					
					
					if (bouns_and_success[1] == 1){
						clear_line(12);
						clear_line(13);	gotoxy(2,12);
						printf("신난다! 야생의 %s를 잡았다!!", enmy->name);	make_input_buffer();
						if (my_user.num_pokemons < 5){
							my_user.alive_pokemon ++;
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
							my_user.num_pokemons ++;
							make_input_buffer();
							break;
						}
						
						if (my_user.num_pokemons >= 5){ 
							clear_line(12);	gotoxy(2, 12);
							printf("지닌 포켓몬이 가득 찼습니다.");
							gotoxy(2, 13);	printf("대신해 포켓몬을 놓아주시겠습니까??");
							SetColor(11);
							gotoxy(40, 12);	printf(">");
							SetColor(15);
							gotoxy(41, 12);	printf("예");
							gotoxy(41, 13);	printf("아니요");
							int mo = select_released_poketmon(40, 13);
							SetColor(15);
							
							if (mo == 0){
								cls;
								show_my_poketmon_ui(0);
								if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
								
								if (my_user.num_pokemons > 1){
									if (my_user.poketmon_list[1].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
									}
									if (my_user.poketmon_list[2].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
									}
									if (my_user.poketmon_list[3].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
									}
									if (my_user.poketmon_list[4].level != 0){
										prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
									}
								}
								int test = select_my_poketmon_in_list(my, enmy);
								gotoxy(2, 16);	printf("%s(을)를 정말 놓아주겠습니까?", my_user.poketmon_list[test].name);
								SetColor(11);
								gotoxy(49, 16);	printf(">");
								SetColor(15);
								gotoxy(50, 16);	printf("예");
								gotoxy(50, 17);	printf("아니요");	
								mo = select_released_poketmon(49, 17);
								if (mo == 0){
									clear_line(16);
									clear_line(17);
									clear_line(18);
									remove_poketmon(test, my, enmy);
									gotoxy(2, 16);	printf("바이바이 %s!!", my_user.poketmon_list[test].name);
									my_user.alive_pokemon--;
									make_input_buffer();
									memcpy(&my_user.poketmon_list[test], &poketmon_all_list[enmy->number - 1], sizeof(poketmon));
									memcpy(&my_user.poketmon_list[my_user.num_pokemons], enmy, sizeof(poketmon));
									cls;
									prt_poketmon_info(my, poketmon_all_list, 0);
								}	
							}
							
							
							float up_exp_rate = ((6* pow(enmy->level, 2)) / 5) * 3;
							int up_exp = (int)round(up_exp_rate);
							clear_line(12);
							clear_line(13);
							gotoxy(2,12);
							printf("%s은(는) %d의 경험치를 얻었다.", my->name, up_exp);
							make_input_buffer(); 
							prt_exp_bar(my, up_exp);
							make_input_buffer();	
							break;
						}
					}
				}
				else{
			        clear_select_poketball_ui();
			        gotoxy(36, 9);	printf(" "); 
			        clear_line(12);
			        clear_line(13);
			        gotoxy(2, 12);	printf("몬스터 볼이 부족합니다!!");
			        make_input_buffer();
				}
			}
		}
		
		else if (user_select == 2){
			cls;
			show_my_poketmon_ui(0);
			if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
			
			if (my_user.num_pokemons > 1){
				if (my_user.poketmon_list[1].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
				}
				if (my_user.poketmon_list[2].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
				}
				if (my_user.poketmon_list[3].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
				}
				if (my_user.poketmon_list[4].level > 0){
					prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
				}
			}
			int test = select_my_poketmon_in_list(my, enmy);
			
			if (test != 27){
				clear_line(16); 
				int selct_move = select_move_in_poketmon_list();	
				move(selct_move, my, enmy, test);	
			}
		}
		
		else if(user_select == 3){
			run_count++;
			run = calc_run(my, enmy);
			if (run == 1){
				clear_line(12);
				clear_line(13);
				gotoxy(2,12);	printf("무사히 도망쳤다!!");
				run_count = 0;	g_round++;
				make_input_buffer();
				break;
			}
		
			else if(run == 0){
				clear_line(12);
				clear_line(13);
				gotoxy(2,12);	printf("도망칠 수 없다!!");
				make_input_buffer();
				skill enemy_use_skill = select_enemy_skill(enmy, my);
				snprintf(log_message, sizeof(log_message), "적 포켓몬의 기술이 선택되었습니다.");
    			log_to_file(log_message);
    			
    			float match = type_matchup[enemy_use_skill.type][my->type];
    			snprintf(log_message, sizeof(log_message), "상성 계산 완료");
				log_to_file(log_message);
			
				battle_start(enmy, my, &enemy_use_skill, 1, poketmon_all_list);
				snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enemy_use_skill.skill_name, my->name);
    			log_to_file(log_message);
			} 
		}
	}
	
	return run;
}

void prt_poketmon_stat(poketmon *p, int x, int y, int color){
	if (color == 15){
		gotoxy(x + 2, y);	SetColor(p->color_number);	printf("O");
		SetColor(15);
		prt_hp_bar(p, poketmon_all_list, x + 5, y);
		gotoxy(x + 4, y - 1);	printf("lv. %d", p->level);
		gotoxy(x + 12, y - 1);	printf("%s", p->name);
	}
	else if(color == 8){
		SetColor(8);
		gotoxy(x + 2, y);	printf("O");
		prt_hp_bar(p, poketmon_all_list, x + 5, y);
		SetColor(8);
		gotoxy(x + 4, y - 1);	printf("lv. %d", p->level);
		gotoxy(x + 12, y - 1);	printf("%s", p->name);	
		SetColor(15);
	}
}

void sort_ppoketmon_list(poketmon list[]){
	for (int i = 1; i < 4; i ++){
		if (list[i].level == 0){
			memcpy(&list[i], &list[i + 1], sizeof(poketmon));
			list[i + 1].level = 0;
		}
	}
}

int select_ball(){
	int pos = 0;
	
	while(1){
		if (_kbhit()){
			int ch = _getch();
			if(ch == 27 || ch == 'x' || ch == 'X'){
				return 27;
			}
            else if (ch == 224) { 
                ch = _getch(); 
                switch(ch){
					case 72:
						if (pos == 0)	pos = 3;
						else	pos --;
						break;
					case 80:
						if (pos == 3)	pos = 0;
						else pos ++;
						break;
				}
            } else if (ch == 13 || ch == 32) { 
                break;
            } 
            switch(pos){
            	case 0:
					gotoxy(36, 3);	printf(" ");
					gotoxy(36, 5);	printf(" ");
					gotoxy(36, 7);	printf(" ");
					gotoxy(36, 9);	printf(" ");
					SetColor(11);
					gotoxy(36, 3);	printf(">");
					SetColor(15);
					break;
				case 1:
					gotoxy(36, 3);	printf(" ");
					gotoxy(36, 5);	printf(" ");
					gotoxy(36, 7);	printf(" ");
					gotoxy(36, 9);	printf(" ");
					SetColor(11);
					gotoxy(36, 5);	printf(">");
					SetColor(15);
					break;
				case 2:
					gotoxy(36, 3);	printf(" ");
					gotoxy(36, 5);	printf(" ");
					gotoxy(36, 7);	printf(" ");
					gotoxy(36, 9);	printf(" ");
					SetColor(11);
					gotoxy(36, 7);	printf(">");
					SetColor(15);
					break;
				case 3:
					gotoxy(36, 3);	printf(" ");
					gotoxy(36, 5);	printf(" ");
					gotoxy(36, 7);	printf(" ");
					gotoxy(36, 9);	printf(" ");
					SetColor(11);
					gotoxy(36, 9);	printf(">");
					SetColor(15);
					break;
			}
		}
		Sleep(100);
	}
	
	return pos;
} 

int select_my_poketmon_in_list(poketmon *my, poketmon *enmy){
	char log_message[200];
	int s_POS = 0;
	int mo = 0;
	
	while(1){
		if (_kbhit()){
			int ch = _getch();
			if(ch == 27 || ch == 'x' || ch == 'X'){
				cls;
				gotoxy(0, 0); 
				printf("round: %d", g_round);
				gotoxy(25, 0); 
				SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
				// UI그리기 
				prt_poketmon_info(my, poketmon_all_list, 0);
				prt_poketmon_info(enmy, poketmon_all_list, 1);
				return 27;
			}
            else if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                    case 75: //왼쪽 
                        if (s_POS == 2) s_POS = 0;
                        else if(s_POS == 3) s_POS = 0;
                        else if(s_POS == 4 && my_user.poketmon_list[1].level > 0) s_POS = 1;
                        break;
                    case 77: //오른쪽 
                        if (s_POS == 0 && my_user.poketmon_list[2].level > 0) s_POS = 2;
                        else if(s_POS == 1 && my_user.poketmon_list[4].level > 0) s_POS = 4;
                        break;
                    case 72: //위 
                        if (s_POS == 1) s_POS = 0;
                        else if(s_POS == 3 && my_user.poketmon_list[2].level > 0)	s_POS = 2;
                        else if(s_POS == 4 && my_user.poketmon_list[3].level > 0)	s_POS = 3;
                        break;
                    case 80: //아래 
                        if (s_POS == 0 && my_user.poketmon_list[1].level > 0) s_POS = 1;
                        else if(s_POS == 2 && my_user.poketmon_list[3].level > 0)	s_POS = 3;
                        else if(s_POS == 3 && my_user.poketmon_list[4].level > 0)	s_POS = 4;
                        break;
                }
            } else if (ch == 13 || ch == 32) { 
                break;
            } 
            switch(s_POS){
            	case 0:
            		cls;
					show_my_poketmon_ui(0);
					if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
					if (my_user.poketmon_list[1].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
					if (my_user.poketmon_list[2].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
					if (my_user.poketmon_list[3].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
					if (my_user.poketmon_list[4].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
					break;
				case 1:
					cls;
					show_my_poketmon_ui(1);
					prt_poketmon_stat(my, 2, 5, 8);
					prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 15);
					if (my_user.poketmon_list[2].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
					if (my_user.poketmon_list[3].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
					if (my_user.poketmon_list[4].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
					gotoxy(2, 16);
					break;
				case 2:
					cls;
					show_my_poketmon_ui(2);
					if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 8);
					prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 15);
					if (my_user.poketmon_list[1].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
					if (my_user.poketmon_list[3].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
					if (my_user.poketmon_list[4].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
					gotoxy(2, 16);
					break;
				case 3:
					cls;
					show_my_poketmon_ui(3);
					if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 8);
					prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 15);
					if (my_user.poketmon_list[1].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
					if (my_user.poketmon_list[2].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
					if (my_user.poketmon_list[4].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
					gotoxy(2, 16);
					break;
				case 4:
					cls;
					show_my_poketmon_ui(4);
					if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 8);
					prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 15);
					if (my_user.poketmon_list[1].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
					if (my_user.poketmon_list[2].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
					if (my_user.poketmon_list[3].level > 0)	prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
					gotoxy(2, 16);
					break;
				default:
					clear_line(12);
					clear_line(13);
					gotoxy(2,12); 
					printf("에러 발생!!");
					make_input_buffer();
					break;
			}
		}
		Sleep(100);
	}
	return s_POS;
}

void move(int selct_move, poketmon *my, poketmon *enmy, int s_POS){
	char log_message[200];
	int mo;
	switch(selct_move){
		case 0:
			if (s_POS == 0){
				clear_line(16);
				clear_line(17);
				clear_line(18);
				gotoxy(2, 16);	printf("이미 전투중인 포켓몬입니다.");
				make_input_buffer();
				clear_line(16);
				gotoxy(2, 16); printf("포켓몬을 선택하세요.");
				int test = select_my_poketmon_in_list(my, enmy);
				
				if (test != 27){
					clear_line(16); 
					int selct_move = select_move_in_poketmon_list();	
					move(selct_move, my, enmy, test);	
				}
			}
			
			else if(my_user.poketmon_list[s_POS].hp <= 0){
				while (my_user.poketmon_list[s_POS].hp <= 0){
					cls;
					show_my_poketmon_ui(0);
					if (my->level > 0)	prt_poketmon_stat(my, 2, 5, 15);
					
					if (my_user.num_pokemons > 1){
						if (my_user.poketmon_list[1].level > 0){
							prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
						}
						if (my_user.poketmon_list[2].level > 0){
							prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
						}
						if (my_user.poketmon_list[3].level > 0){
							prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
						}
						if (my_user.poketmon_list[4].level > 0){
							prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
						}
					}
					clear_line(16);
					clear_line(17);
					clear_line(18);
					gotoxy(2, 16);	printf("전투에 나갈 수 없는 포켓몬입니다!");
					make_input_buffer();
					clear_line(16);	gotoxy(2, 16);	printf("포켓몬을 선택하세요.");
					s_POS = select_my_poketmon_in_list(my, enmy);
					
					snprintf(log_message, sizeof(log_message), "선택된 포켓몬 s_POS: %d, HP: %d\n", s_POS, my_user.poketmon_list[s_POS].hp);
    				log_to_file(log_message);
				}
			}
			
			cls;
			gotoxy(0, 0); 
			printf("round: %d", g_round);
			prt_poketmon_info(my, poketmon_all_list, 0);
			prt_poketmon_info(enmy, poketmon_all_list, 1);
			change_poketmon(my, s_POS);
			skill enemy_use_skill = select_enemy_skill(enmy, my);
			snprintf(log_message, sizeof(log_message), "적 포켓몬의 기술이 선택되었습니다.");
	    	log_to_file(log_message);
	    			
	    	float match = type_matchup[enemy_use_skill.type][my->type];
	    	snprintf(log_message, sizeof(log_message), "상성 계산 완료");
			log_to_file(log_message);
				
			battle_start(enmy, my, &enemy_use_skill, 1, poketmon_all_list);
			snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enemy_use_skill.skill_name, my->name);
	    	log_to_file(log_message);	
			
			break;
		case 1:
			clear_line(16); 
			gotoxy(47, 16);	printf("|");
			gotoxy(47, 17);	printf("|");
			gotoxy(48, 18);	printf("--------");
			if (s_POS == 0){
				clear_line(16);
				clear_line(17);
				clear_line(18);
				gotoxy(2, 16);
				printf("전투중인 포켓몬은 놓아줄 수 없습니다.");
				make_input_buffer();
				clear_line(16);
				gotoxy(2, 16); printf("포켓몬을 선택하세요.");
				int test = select_my_poketmon_in_list(my, enmy);
				if (test == 27){
					cls;
					gotoxy(0, 0); 
					printf("round: %d", g_round);
					gotoxy(25, 0); 
					SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
					// UI그리기 
					prt_poketmon_info(my, poketmon_all_list, 0);
					prt_poketmon_info(enmy, poketmon_all_list, 1);
				}
			} 
			else{
				gotoxy(2, 16);	printf("%s(을)를 정말 놓아주겠습니까?", my_user.poketmon_list[s_POS].name);
				SetColor(11);
				gotoxy(49, 16);	printf(">");
				SetColor(15);
				gotoxy(50, 16);	printf("예");
				gotoxy(50, 17);	printf("아니요");	
				mo = select_released_poketmon(49, 17);
				if (mo == 0){
					clear_line(16);
					clear_line(17);
					clear_line(18);
					remove_poketmon(s_POS, my, enmy);
					gotoxy(2, 16);	printf("바이바이 %s!!", my_user.poketmon_list[s_POS].name);
					sort_ppoketmon_list(my_user.poketmon_list);
					make_input_buffer();
					cls;
					show_my_poketmon_ui(0);
					prt_poketmon_stat(my, 2, 5, 15);
					
					if (my_user.num_pokemons > 1){
						if (my_user.poketmon_list[1].level != 0){
							prt_poketmon_stat(&my_user.poketmon_list[1], 2, 10, 8);
						}
						if (my_user.poketmon_list[2].level != 0){
							prt_poketmon_stat(&my_user.poketmon_list[2], 30, 3, 8);
						}
						if (my_user.poketmon_list[3].level != 0){
							prt_poketmon_stat(&my_user.poketmon_list[3], 30, 8, 8);
						}
						if (my_user.poketmon_list[4].level != 0){
							prt_poketmon_stat(&my_user.poketmon_list[4], 30, 13, 8);
						}
					}
					int test = select_my_poketmon_in_list(my, enmy);
					
					if (test == 27){
						cls;
						gotoxy(0, 0); 
						printf("round: %d", g_round);
						gotoxy(25, 0); 
						SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
						// UI그리기 
						prt_poketmon_info(my, poketmon_all_list, 0);
						prt_poketmon_info(enmy, poketmon_all_list, 1);
					}
				}
				else if (mo == 1){
					clear_line(16);
					clear_line(17);
					gotoxy(2, 16); printf("포켓몬을 선택하세요.");
					int test = select_my_poketmon_in_list(my, enmy);
					if (test == 27){
						cls;
						gotoxy(0, 0); 
						printf("round: %d", g_round);
						gotoxy(25, 0); 
						SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
						// UI그리기 
						prt_poketmon_info(my, poketmon_all_list, 0);
						prt_poketmon_info(enmy, poketmon_all_list, 1);
					}
				}
			}
			break;
		case 2:
			clear_line(16);
			clear_line(17);
			gotoxy(2, 16); printf("포켓몬을 선택하세요.");
			int test = select_my_poketmon_in_list(my, enmy);
			if (test == 27){
				cls;
				gotoxy(0, 0); 
				printf("round: %d", g_round);
				gotoxy(25, 0); 
				SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
				// UI그리기 
				prt_poketmon_info(my, poketmon_all_list, 0);
				prt_poketmon_info(enmy, poketmon_all_list, 1);
			}
			break;
	}
}

void remove_poketmon(int index, poketmon *my, poketmon *enmy){
	if (index == 0){
		clear_line(16);
		gotoxy(2, 16);
		printf("전투중인 포켓몬은 놓아줄 수 없습니다.");
		make_input_buffer();
		clear_line(16);
		clear_line(17);
		int test = select_my_poketmon_in_list(my, enmy);
		if(test == 27){
			cls;
			gotoxy(0, 0); 
			printf("round: %d", g_round);
			gotoxy(25, 0); 
			SetColor(14);	printf("$: %d", my_bag.money);	SetColor(15);
			// UI그리기 
			prt_poketmon_info(my, poketmon_all_list, 0);
			prt_poketmon_info(enmy, poketmon_all_list, 1);
		}
	}
	else{
		my_user.poketmon_list[index].level = 0;
		my_user.num_pokemons --;	
	}
} 

int select_poket_ball(){
	
}

int select_released_poketmon(int x, int y){
	int pos = 0;
	
	while(1){
		if (_kbhit()){
			int ch;
			ch = _getch();
			if (ch == 224){
				ch = _getch();
				
				switch(ch){
					case 72:
						if (pos == 0)	pos ++;
						else if(pos == 1)	pos --;
						break;
					case 80:
						if (pos == 1)	pos --;
						else if(pos == 0)	pos ++;
						break;
				}
			}
			else if (ch == 13 || ch == 32)
				break;
				
			switch(pos){
			case 0:
				gotoxy(x, y);	printf(" ");
				gotoxy(x, y - 1);	printf(" ");
				SetColor(11);
				gotoxy(x, y - 1);	printf(">");
				SetColor(15);
				break;
			case 1:
				gotoxy(x, y);	printf(" ");
				gotoxy(x, y - 1);	printf(" ");
				SetColor(11);
				gotoxy(x, y);	printf(">");
				SetColor(11);
				break;
			}
		}
		Sleep(100);
	}
	return pos;
} 

void change_poketmon(poketmon *my, int change_poketmon_index) {
    gotoxy(2, 12); printf("돌아와 %s!!", my->name);
    block_input_for_ms(500);
    gotoxy(2,10); printf(" ");
    gotoxy(10,8); printf("                                                         ");
	gotoxy(10,9); printf("                                                         ");
	gotoxy(10,10); printf("                                                        ");
	
	for (int i = 0; i < 4; i ++){
		my->rank_up[i] = 0;
	}
	int hp = my->hp;
	set_stat(my, my->level, poketmon_all_list);
	my->hp = hp;
    // 포켓몬 교체 
    poketmon change_poketmon = my_user.poketmon_list[change_poketmon_index];
    my_user.poketmon_list[change_poketmon_index] = *my;
    *my = change_poketmon;

    clear_line(12);
    for (int i = 0; i < 4; i ++){
		my->rank_up[i] = 0;
	}
    gotoxy(2, 12); printf("가랏 %s!!", my->name);
    block_input_for_ms(500);
    Sleep(500); 
	clear_input_buffer();
	
    prt_poketmon_info(my, poketmon_all_list, 0);
}


int select_move_in_poketmon_list(){
	SetColor(11);
	gotoxy(4,16);	printf(">");
	SetColor(15);
	gotoxy(5, 16);	printf("교체한다");
	gotoxy(20, 16);	printf("놓아준다");
	gotoxy(35, 16);	printf("그만 둔다");
	
	int Pos = 0;
	
	while (1){
		if(_kbhit()){
			int ch = _getch();
			
			if (ch == 224){
				ch = _getch();
				switch(ch){
					case 75:	//왼쪽 
						if (Pos == 0)	Pos = 2;
						else Pos --;
						break;
					case 77:	//오른쪽
						if (Pos == 2)	Pos = 0;
						else Pos ++;
						break; 
				}
			}
			else if (ch == 13 || ch == 32){
				break;
			}
				
			switch (Pos){
				case 0:
					gotoxy(4,16);	printf(" ");
					gotoxy(19,16);	printf(" ");
					gotoxy(34,16);	printf(" ");
					SetColor(11);
					gotoxy(4,16);	printf(">");
					SetColor(15);
					break;
				case 1:
					gotoxy(4,16);	printf(" ");
					gotoxy(19,16);	printf(" ");
					gotoxy(34,16);	printf(" ");
					SetColor(11);
					gotoxy(19,16);	printf(">");
					SetColor(15);
					break;
				case 2:
					gotoxy(4,16);	printf(" ");
					gotoxy(19,16);	printf(" ");
					gotoxy(34,16);	printf(" ");
					SetColor(11);
					gotoxy(34,16);	printf(">");
					SetColor(15);
					break;
			}			
		}
		Sleep(100);
	}
	
	return Pos;
} 

void calc_rank_up(poketmon *p){
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "\n랭크업 배열의 값들을 검사하고 랭크업을 시작합니다!!");
	log_to_file(log_message);
	snprintf(log_message, sizeof(log_message), "현제 능력치:\n hp: %d\nat: %d\ndef: %d\nspped: %d", p->hp, p->attack_power, p->defense, p->speed);
	log_to_file(log_message);
	set_stat(p, p->level, poketmon_all_list);
	snprintf(log_message, sizeof(log_message), "\n검사한 포켓몬 랭크업 배열\nhp: %d\natk: %d\ndef: %d\nspeed: %d\n", p->rank_up[0], p->rank_up[1], p->rank_up[2], p->rank_up[3]);
	log_to_file(log_message);
	
	if (p->rank_up[0] > 0){
		p->hp = calc_max_hp(p, poketmon_all_list);
	}
	if (p->rank_up[1] > 0){
		for (int i = p->rank_up[1]; i > 0; i --){
			p->attack_power += p->attack_power / 2;
			snprintf(log_message, sizeof(log_message), "공격력 1랭크 상승!!");
			log_to_file(log_message);
		}
	}
	if (p->rank_up[2] > 0){
		for (int i = p->rank_up[2]; i > 0; i --){
			p->defense += p->defense / 2;
			snprintf(log_message, sizeof(log_message), "방여력 1랭크 상승!!");
			log_to_file(log_message);
		}
	}
	if (p->rank_up[3] > 0){
		for (int i = p->rank_up[3]; i > 0; i --){
		p->speed += p->speed / 2;
			snprintf(log_message, sizeof(log_message), "스피드 1랭크 상승!!");
			log_to_file(log_message);
		}
	}
	snprintf(log_message, sizeof(log_message), "랭크업 후 능력치:\n hp: %d\nat: %d\ndef: %d\nspped: %d", p->hp, p->attack_power, p->defense, p->speed);
	log_to_file(log_message);
}

void level_up(poketmon *p){
	char log_message[200];
	p->exp = 0;
	clear_line(12);
	clear_line(13);
	gotoxy(2,12);	printf("%s(이)가 레벨업했다!!", p->name);
	make_input_buffer();
	int n_hp = p->hp;
	int max_hp = calc_max_hp(p, poketmon_all_list);
	int sub_hp = max_hp - n_hp;
	set_stat(p, p->level, poketmon_all_list);
	calc_rank_up(p);
	int new_max_hp = calc_max_hp(p, poketmon_all_list);
	p->hp = new_max_hp - sub_hp;
	p->level += 1;	
	prt_poketmon_info(p, poketmon_all_list, 0);
	check_new_skill(p);
	if (p->level == p->evol_level) {
        prt_evolution(p, p->evolution_poketmon);
        evolution(p);
    }
    snprintf(log_message, sizeof(log_message), "\n%s의 능력치\nhp: %d / %d\natk: %d\ndef: %d\nspeed: %d\n", p->name, p->hp, new_max_hp, p->attack_power, p->defense, p->speed);
	log_to_file(log_message);
	make_input_buffer();
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

int select_item(item ilst[], int gold, int money, int round, int lv, int hp, int max_hp){
	cls;
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "아이템 선택 실행");
	log_to_file(log_message);
	int my_money = money;
	int get_gold = gold;
	gotoxy(10,1);	printf("-아이템 선택-");
	gotoxy(13,2);	printf("상처약");
	gotoxy(5,6);	printf("-");
	gotoxy(15,6);	printf("-");
	gotoxy(25,6);	printf("-");
	gotoxy(25, 1);	printf("$: -");
	gotoxy(24, 10);	printf("건너뛰기");
	gotoxy(0,11);	printf("--------------------------------");
	Sleep(500);
	
	if (round < 20)
		prt_item_ui(4,6,ilst[0].effect, money);
	else if (round > 20 && round < 50)
		prt_item_ui(4,6,ilst[1].effect, money);
	else if (round >= 50)
		prt_item_ui(4,6,ilst[2].effect, money);
	int i_POS = 0;
	while(1){
		if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                    case 75: //왼쪽 
                        if (i_POS == 0) i_POS = 2;
                        else if(i_POS == 1)	i_POS = 0;
                        else if(i_POS == 2)	i_POS = 1;
                        break;
                    case 77: //오른쪽 
                        if (i_POS == 2) i_POS = 0;
                        else if(i_POS == 1)	i_POS = 2;
                        else if(i_POS == 0)	i_POS = 1;
                        break;
                    case 72: //위 
                        if (i_POS == 3) i_POS = 0;
                        else if(i_POS == 4)	i_POS = 1;
                        else if(i_POS == 5)	i_POS = 2;
                        break;
                    case 80: //아래 
                        if (i_POS == 0) i_POS = 3;
                        else if(i_POS == 1)	i_POS = 4;
                        else if(i_POS == 2)	i_POS = 5;
                        break;
                }
            } else if (ch == 13 || ch == 32) { 
                break;
            }

            switch (i_POS) {
                case 0:
                	clear_line(2);
                	gotoxy(14,6);	printf(" ");
                	gotoxy(24,6);	printf(" ");
                	gotoxy(23,10);	printf(" ");
                	clear_line(12);	clear_line(13);
                	gotoxy(13,2);	printf("상처약");
                	if (lv < 20)
                    	prt_item_ui(4,6," 200골드를 사용해 포켓몬 1마리의 HP를 20 또는 10% 중 높은 수치만큼 회복한다.", money);
                    else if (lv >= 20 && lv < 36)
                    	prt_item_ui(4,6," 500골드를 사용해 포켓몬 1마리의 HP를 50 또는 25% 중 높은 수치만큼 회복한다.", money);
                    else if (lv >= 36)
                    	prt_item_ui(4,6," 1000골드를 사용해 포켓몬 1마리의 HP를 200 또는 50% 중 높은 수치만큼 회복한다.", money);
                    break;
                case 1:
                	clear_line(2);
                	gotoxy(4,6);	printf(" ");
                	gotoxy(24,6);	printf(" ");
                	gotoxy(23,10);	printf(" ");
                	clear_line(12);	clear_line(13);
                    prt_item_ui(14,6,"골드 획득", money);
                    gotoxy(13,2);	printf("골드 획득");
                    SetColor(14);
					gotoxy(12,12); printf("(%d골드)", get_gold);
					SetColor(15);
                    break;
                case 2:
                	clear_line(2);
                	gotoxy(4,6);	printf(" ");
                	gotoxy(14,6);	printf(" ");
                	gotoxy(23,10);	printf(" ");
					clear_line(12);	clear_line(13);
                    prt_item_ui(24,6,"포켓몬의 스텟중 1가지를 무작위로 골라 10% 상승시킨다.", money);
                    gotoxy(13,2);	printf("스텟 증가");
                    break;
                case 3: case 4: case 5:
                	clear_line(2);
                	gotoxy(4,6);	printf(" ");
                	gotoxy(14,6);	printf(" ");
                	gotoxy(24,6);	printf(" ");
					clear_line(12);	clear_line(13);
					gotoxy(13,2);	printf("건너뛰기");
                    prt_item_ui(23,10,"선택하지 않고 넘어감", money);
                    break;
            }
        }
        Sleep(100);
	}
	if (i_POS == 0){
		snprintf(log_message, sizeof(log_message), "상처약 선택");
		log_to_file(log_message);
		if (lv < 20){
			
			if (money < 200){
				clear_line(12);
				clear_line(13);
				gotoxy(2,12);	printf("%d골드가 부족합니다! ",money);
				make_input_buffer();
			}
		}
		
		else if (lv >= 20 && lv < 36){
			clear_line(12);
			clear_line(13);
			if (money < 500){
				clear_line(12);
				clear_line(13);
				gotoxy(2,12);	printf("%d골드가 부족합니다! ",money);
				make_input_buffer();
			}
		}
		
		else if (lv >= 36){
			clear_line(12);
			clear_line(13);
			if (money < 1000){
				clear_line(12);
				clear_line(13);
				gotoxy(2,12);	printf("%d골드가 부족합니다! ",money);
				make_input_buffer();
			}
		}
	
        else if (hp == max_hp){
		clear_line(12);
		clear_line(13);
		gotoxy(2,12);	printf("사용해도 효과가 없다! ");
		make_input_buffer();
		}
		else	return i_POS;
	}
		
		else if (i_POS == 1){
			snprintf(log_message, sizeof(log_message), "골드 선택");
			log_to_file(log_message);
			return i_POS;
		}
		
		else if (i_POS == 2){
			snprintf(log_message, sizeof(log_message), "능력치 상승 선택");
			log_to_file(log_message);
			return i_POS;
		}
		else {
			snprintf(log_message, sizeof(log_message), "건너뛰기 선택");
			log_to_file(log_message);
			return i_POS;
		}
}

void use_healing_pack(item *i, poketmon *p, bag *b, poketmon list[]){
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "상처약 사용 실행");
    log_to_file(log_message);
	int number = p->number;
	int hp_rank_up = p->rank_up[0];
	int price = i->price;
	int max_hp = list[number - 1].hp + (p->level - 1) * 2;
	int heal_hp = 0;
	if (hp_rank_up > 0){
		for (int i = 0; i < hp_rank_up; i++){
    		max_hp += max_hp / 2;
		}
	}
	
	b->money -= price;
	snprintf(log_message, sizeof(log_message), "골드 지불 완료");
    log_to_file(log_message);
	
	if (strcmp(i->name, "상처약") == 0){
		snprintf(log_message, sizeof(log_message), "상처약 선정");
   		log_to_file(log_message);
		 int ex = max_hp * (10 / 100);
		 if (ex < 30){
		 	heal_hp = 20;
		 	p->hp += heal_hp;
		 	if (p->hp > max_hp)	p->hp = max_hp;
		 }
		 else{
		 	heal_hp = ex;
		 	p->hp += heal_hp;
		 	if (p->hp > max_hp)	p->hp = max_hp;
		 }
	}
	
	else if (strcmp(i->name, "좋은 상처약") == 0){
		snprintf(log_message, sizeof(log_message), "좋은 상처약 선정");
   		log_to_file(log_message);
		 int ex = max_hp * (25 / 100);
		 if (ex < 60){
		 	heal_hp = 50;
		 	p->hp += heal_hp;
		 	if (p->hp > max_hp)	p->hp = max_hp;
		 }
		 else{
		 	heal_hp = ex;
		 	p->hp += ex;
		 	if (p->hp > max_hp)	p->hp = max_hp;
		 }
	}
	
	else if (strcmp(i->name, "고급 상처약") == 0){
		snprintf(log_message, sizeof(log_message), "고급 상처약 선정");
   		log_to_file(log_message);
		 int ex = max_hp * (50 / 100);
		 if (ex < 200){
		 	heal_hp = 200;
		 	p->hp += heal_hp;
		 	if (p->hp > max_hp)	p->hp = max_hp;
		 }
		 else{
		 	heal_hp = ex;
		 	p->hp += ex;
		 	if (p->hp > max_hp)	p->hp = max_hp;
		 }
	}
	
	clear_line(12);
	clear_line(13);
	gotoxy(2,12);	printf("%s(은)는 %d의 체력을 회복했다!", p->name, heal_hp);
	make_input_buffer();
}

void Rank_up(poketmon *p){
	char log_message[200]; 
	snprintf(log_message, sizeof(log_message), "랭크업 실행");
   	log_to_file(log_message);
	int rand_num = 4;
	int rank_up_idx = 0;
	int n_hp = p->hp;
	int hp = p->rank_up[0], 
		at = p->rank_up[1], 
		de = p->rank_up[2], 
		sp = p->rank_up[3];
	if (hp == 6 && at == 6 && de == 6 && sp == 6){
		clear_line(12);	clear_line(13);
		gotoxy(2,12);	printf("이미 능력치가 최대치입니다!!");	make_input_buffer();
		snprintf(log_message, sizeof(log_message), "능력치가 이미 최대로 실행하지 않습니다!!");
   		log_to_file(log_message);
	}
	
	else{
		while (1) {
        rank_up_idx = rand() % rand_num;
        if (p->rank_up[rank_up_idx] >= 6)
            continue;
        break;
    	}
		switch (rank_up_idx) {
        	case 0: // 체력
        	    p->rank_up[0] ++;
        	    clear_line(12); clear_line(13);
        	    gotoxy(2, 12); printf("%s의 체력이 크게 올랐다!!", p->name); make_input_buffer();
        	    break;
        	    
        	case 1: // 공격력
        	    p->rank_up[1] ++;
        	    clear_line(12); clear_line(13);
        	    gotoxy(2, 12); printf("%s의 공격력이 크게 올랐다!!", p->name); make_input_buffer();
        	    break;
	
	        case 2: // 방어력
    	        p->rank_up[2] ++;
    	        clear_line(12); clear_line(13);
    	        gotoxy(2, 12); printf("%s의 방어력이 크게 올랐다!!", p->name); make_input_buffer();
    	        break;
	
	        case 3: // 스피드
	            p->rank_up[3] ++;
	            clear_line(12); clear_line(13);
	            gotoxy(2, 12); printf("%s의 스피드가 크게 올랐다!!", p->name); make_input_buffer();
	            break;
	
	        default:
	            break;
    	}
		calc_rank_up(p)	;	
	}
}	


int get_enemy_level(int player_level) {
    
    int min_level = player_level - 2;
    int max_level = player_level + 2;
    
    int enemy_level = rand() % (max_level - min_level + 1) + min_level;
    
    return enemy_level;
}

void set_enemy_skills(poketmon *p, skill all_list[]){
	int len = sizeof(all_list) / sizeof(all_list[0]) * 4; 		
	int idx = rand() % 6;
	
	for (int i = 0; i < 4; i ++){
		if (strcmp(p->skill_list[i].skill_name, all_list[idx].skill_name) != 0)
			p->skill_list[i] = all_list[idx];
		else{
			int idx = rand() % 6;
		}
	}
}


skill select_skill(skill skill_list[]){
	char log_message[200]; 
	
	switch(skill_index){
		case 0:
			SetColor(11);
			gotoxy(1,12);	printf(">");
			SetColor(15);
			break;
		case 1:
			SetColor(11);
			gotoxy(21,12);	printf(">");
			SetColor(15);
			break;
		case 2:
			SetColor(11);
			gotoxy(1,13);	printf(">");
			SetColor(15);
			break;
		case 3:
			SetColor(11);
			gotoxy(21,13);	printf(">");
			SetColor(15);
			break;
	}

	int able_skill[4];
	skill esc;
	strcpy(esc.skill_name, "돌아가기");
	
	for (int i = 0; i < 4; i ++){
		if (strcmp(skill_list[i].skill_name, "----") == 0){
			able_skill[i] = 0;
		}
		else 
			able_skill[i] = 1;
	} 
	
	while(1){
		if (_kbhit()){
			int ch = _getch();
            if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                    case 75: //왼쪽 
                        if (skill_index == 0 && able_skill[1] == 1) skill_index = 1;
                        else if(skill_index == 2 && able_skill[3] == 1) skill_index = 3;
                        else if(skill_index == 1 && able_skill[0] == 1) skill_index = 0;
                        else if(skill_index == 3 && able_skill[2] == 1) skill_index = 2;
                        break;
                    case 77: //오른쪽 
                        if (skill_index == 0 && able_skill[1] == 1) skill_index = 1;
                        else if(skill_index == 2 && able_skill[3] == 1) skill_index = 3;
                        else if(skill_index == 1 && able_skill[0] == 1) skill_index = 0;
                        else if(skill_index == 3 && able_skill[2] == 1) skill_index = 2;
                        break;
                    case 72: //위 
                        if (skill_index == 1 && able_skill[3] == 1) skill_index = 3;
                        else if(skill_index == 0 && able_skill[2] == 1) skill_index = 2;
                        else if(skill_index == 2 && able_skill[0] == 1) skill_index = 0;
                        else if(skill_index == 3 && able_skill[1] == 1) skill_index = 1;
                        break;
                    case 80: //아래 
                        if (skill_index == 1 && able_skill[3] == 1) skill_index = 3;
                        else if(skill_index == 0 && able_skill[2] == 1) skill_index = 2;
                        else if(skill_index == 2 && able_skill[0] == 1) skill_index = 0;
                        else if(skill_index == 3 && able_skill[1] == 1) skill_index = 1;
                        break;
                }
            } else if(ch == 27 || ch == 'x' || ch == 'X'){
            	snprintf(log_message, sizeof(log_message), "skill  선택창에서 esc를 누름!",skill_list[skill_index].skill_name);
    			log_to_file(log_message);
            	return esc; 
			} 
			else if (ch == 13 || ch == 32) { 
            	if (strcmp(skill_list[skill_index].skill_name, "----") != 0)
                	break;
                else 
                	continue;
            } 
            switch(skill_index){
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
				default:
					clear_line(12);
					clear_line(13);
					gotoxy(2,12); 
					printf("에러 발생!!");
					make_input_buffer();
					break;
			}
		}
		Sleep(100);
	}
	gotoxy(1, 12); printf(" ");
	clear_line(13);
	clear_line(12);
	gotoxy(2,12);
	snprintf(log_message, sizeof(log_message), "%s가 선택됐습니다.",skill_list[skill_index].skill_name);
    log_to_file(log_message);
	return skill_list[skill_index];
}

void poketmon_learn_skill(poketmon *p, skill all_skill_list[], int skill_number){
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "\n%s의 skillfilled: %d",p->name, p->skill_filled);
	log_to_file(log_message);
	for (int i = 0; i < MAX_SKILL; i ++){
		if (strcmp(p->skill_list[i].skill_name, "----") == 0){
			p->skill_list[i] = all_skill_list[skill_number - 1];
			p->skill_filled ++;
			snprintf(log_message, sizeof(log_message), "\npoketmon_learn_skill에서 실행\n기술을 배운 후 skill_filled ++ 실행!!\nskillfilled: %d",p->skill_filled);
			log_to_file(log_message);
			break;
		}
	}
}

void set_learn_skill(poketmon *p, int index, int level, int skill_index) {
	p->learn_skill_level[index] = level;
	p->learn_skill[index] = skill_index;
}

void select_my_poketmon(poketmon poketmon_all_list[], User *user, skill all_skill_list[]) {
	char log_message[200];
    cls;
    my_user.num_pokemons ++;
    int POS = 0;
    SetColor(14);
    printf("---------select poketmon------------\n\n\n\n\n\n");
    printf("------------------------------------");
    SetColor(11);
    gotoxy(2, 2); printf(">");
    SetColor(10);
    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
    SetColor(10);
    gotoxy(3,4);	printf("%s" , "풀타입");
    SetColor(15);
    gotoxy(10,4);	printf("%s" , "몸통 박치기");
    gotoxy(22,4);	printf("%s" , "덩굴 채찍");
    SetColor(12);
    gotoxy(14, 2); printf("%s", poketmon_all_list[3].name);
    SetColor(9);
    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);
	SetColor(15);
    while (1) {
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                    case 75: 
                        if (POS == 0) POS = 2;
                        else if (POS == 1)	POS = 0;
                        else if (POS == 2)	POS = 1;
                        break;
                    case 77: 
                        if (POS == 2) POS = 0;
                        else if (POS == 1)	POS = 2;
                        else if (POS == 0)	POS = 1;
                        break;
                }
            } else if (ch == 13 || ch == 32) { 
                break;
            }

            switch (POS) {
                case 0:
                	for (int i = 4; i < 50; i ++){
                		gotoxy(i,4);	printf(" ");
					} 
                    gotoxy(13, 2); printf(" ");
                    gotoxy(22, 2); printf(" ");
                    SetColor(11);
                    gotoxy(2, 2); printf(">");
                    SetColor(10);
                    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
                    SetColor(10);
                    gotoxy(3,4);	printf("%s" , "풀타입");
                    SetColor(15);
    				gotoxy(10,4);	printf("%s" , "몸통 박치기");
    				gotoxy(22,4);	printf("%s" , "덩굴 채찍");
    				SetColor(12);
                    gotoxy(14, 2); printf("%s", poketmon_all_list[3].name);
                    SetColor(9);
                    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);
                    SetColor(15);
                    break;
                case 1:
                	for (int i = 4; i < 50; i ++){
                		gotoxy(i,4);	printf(" ");
					} 
                    gotoxy(2, 2); printf(" ");
                    gotoxy(22, 2); printf(" ");
                    SetColor(11);
                    gotoxy(13, 2); printf(">");
                    SetColor(10);
                    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
                    SetColor(12);
                    gotoxy(3,4);	printf("%s" , "불타입");
                    SetColor(15);
    				gotoxy(10,4);	printf("%s" , "할퀴기");
    				gotoxy(22,4);	printf("%s" , "불꽃 세례");
    				SetColor(12);
                    gotoxy(14, 2); printf("%s", poketmon_all_list[3].name);
                    SetColor(9);
                    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);
                    SetColor(15);
                    break;
                case 2:
                	for (int i = 1; i < 50; i ++){
                		gotoxy(i,4);	printf(" ");
					} 
                    gotoxy(13, 2); printf(" ");
                    gotoxy(2, 2); printf(" ");
                    SetColor(11);
                    gotoxy(22, 2); printf(">");
                    SetColor(10);
                    gotoxy(3, 2); printf("%s", poketmon_all_list[0].name);
                    SetColor(9);
                    gotoxy(3,4);	printf("%s" , "물타입");
                    SetColor(15);
    				gotoxy(10,4);	printf("%s" , "몸통 박치기");
    				gotoxy(22,4);	printf("%s" , "물대포");
    				SetColor(12);
                    gotoxy(14, 2); printf("%s", poketmon_all_list[3].name);
                    SetColor(9);
                    gotoxy(23, 2); printf("%s", poketmon_all_list[6].name);
                    SetColor(15);
                    break;
            }
        }
        Sleep(100); 
    }
    if (POS == 0) {
    	snprintf(log_message, sizeof(log_message), "%s가 선택되었습니다!!", poketmon_all_list[0]);	log_to_file(log_message);
    	snprintf(log_message, sizeof(log_message), "\n%s의기본 기술 인덱스: %d, %d", poketmon_all_list[3].name, poketmon_all_list[3].base_skill[0], poketmon_all_list[3].base_skill[1]);	log_to_file(log_message);
    	memcpy(&user->poketmon_list[0], &poketmon_all_list[0], sizeof(poketmon));
		poketmon_learn_skill(&user->poketmon_list[0], all_skill_list, user->poketmon_list[0].base_skill[0] + 1);
		gotoxy(1,7);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, user->poketmon_list[0].skill_list[0].skill_name);
		poketmon_learn_skill(&user->poketmon_list[0], all_skill_list, user->poketmon_list[0].base_skill[1] + 1);
		gotoxy(1,8);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, user->poketmon_list[0].skill_list[1].skill_name);
	}
	
    else if (POS == 1){
    	snprintf(log_message, sizeof(log_message), "\n%s가 선택되었습니다!!", poketmon_all_list[3].name);	log_to_file(log_message);
    	snprintf(log_message, sizeof(log_message), "\n%s의기본 기술 인덱스: %d, %d", poketmon_all_list[3].name, poketmon_all_list[3].base_skill[0], poketmon_all_list[3].base_skill[1]);	log_to_file(log_message);
    	snprintf(log_message, sizeof(log_message), "\n%s의learn_skill[0] = {%d, %d}", poketmon_all_list[3].name, poketmon_all_list[3].learn_skill_level[0], poketmon_all_list[3].learn_skill[0]);	log_to_file(log_message);
		memcpy(&user->poketmon_list[0], &poketmon_all_list[3], sizeof(poketmon));
    	poketmon_learn_skill(&user->poketmon_list[0], all_skill_list, user->poketmon_list[0].base_skill[0] + 1);
		gotoxy(1,7);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, user->poketmon_list[0].skill_list[0].skill_name);
		poketmon_learn_skill(&user->poketmon_list[0], all_skill_list, user->poketmon_list[0].base_skill[1] + 1);
		gotoxy(1,8);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, user->poketmon_list[0].skill_list[1].skill_name);
		snprintf(log_message, sizeof(log_message), "\n유저 리스트로 이동 후 검사\n%s의learn_skill[0] = {%d, %d}", user->poketmon_list[0].name, user->poketmon_list[0].learn_skill_level[0], user->poketmon_list[0].learn_skill[0]);	log_to_file(log_message);
	}
    else if (POS == 2) {
    	snprintf(log_message, sizeof(log_message), "%s가 선택되었습니다!!", poketmon_all_list[6]);	log_to_file(log_message);
    	snprintf(log_message, sizeof(log_message), "\n%s의기본 기술 인덱스: %d, %d", poketmon_all_list[3].name, poketmon_all_list[3].base_skill[0], poketmon_all_list[3].base_skill[1]);	log_to_file(log_message);
    	memcpy(&user->poketmon_list[0], &poketmon_all_list[6], sizeof(poketmon));
    	poketmon_learn_skill(&user->poketmon_list[0], all_skill_list, user->poketmon_list[0].base_skill[0] + 1);
		gotoxy(1,7);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, user->poketmon_list[0].skill_list[0].skill_name);
		poketmon_learn_skill(&user->poketmon_list[0], all_skill_list, user->poketmon_list[0].base_skill[1] + 1);
		gotoxy(1,8);	printf("%s(이)가 %s(을)를 배웠다!", user->poketmon_list[0].name, user->poketmon_list[0].skill_list[1].skill_name);
	}
    POS = 0;
    make_input_buffer();
	cls; 
    snprintf(log_message, sizeof(log_message), "%s가 유저의 리스트로 이동",user->poketmon_list[0]);
    log_to_file(log_message);
}



poketmon* select_enemy_poketmon(poketmon poketmon_all_list[], int color_number, skill all_skill_list[]){
	char log_message[200];
	poketmon enemy_candi_list[151];
	int ran_num = 0;
	poketmon* enemy_poketmon = (poketmon*)malloc(sizeof(poketmon));
	
	for (int i = 0 ; i < 151; i ++){
		if (poketmon_all_list[i].color_number == color_number){
			enemy_candi_list[ran_num++] = poketmon_all_list[i];
		}
	}		
	int idx = rand() % ran_num;
	snprintf(log_message, sizeof(log_message), "%s가 적 포켓몬으로 셋팅되었습니다.",enemy_candi_list[idx]);
    log_to_file(log_message);
	int skill_idx1 = rand() % 56;
	int skill_idx2 = rand() % 56;
	while (skill_idx2 == skill_idx1)	skill_idx2 = rand() % 56;
	int skill_idx3 = rand() % 56;
	while (skill_idx3 == skill_idx2 || skill_idx3 == skill_idx1)	skill_idx3 = rand() % 56;
	int skill_idx4 = rand() % 56;
	while (skill_idx4 == skill_idx2 || skill_idx4 == skill_idx1 || skill_idx4 == skill_idx3)	skill_idx4 = rand() % 56;
	
	poketmon_learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx1 + 1);
	snprintf(log_message, sizeof(log_message), "%s가 적의 1번째 기술로 등록됐습니다.", all_skill_list[skill_idx1]);
    log_to_file(log_message);
	poketmon_learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx2 + 1);
	snprintf(log_message, sizeof(log_message), "%s가 적의 2번째 기술로 등록됐습니다.", all_skill_list[skill_idx2]);
    log_to_file(log_message);
	poketmon_learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx3 + 1);
	snprintf(log_message, sizeof(log_message), "%s가 적의 3번째 기술로 등록됐습니다.", all_skill_list[skill_idx3]);
    log_to_file(log_message);
	poketmon_learn_skill(&enemy_candi_list[idx], all_skill_list, skill_idx4 + 1);
	snprintf(log_message, sizeof(log_message), "%s가 적의 4번째 기술로 등록됐습니다.", all_skill_list[skill_idx4]);
    log_to_file(log_message);
	
	*enemy_poketmon = enemy_candi_list[idx];
	
	return 	enemy_poketmon;
}

void set_stat(poketmon *p, int lv, poketmon list[]){
	char log_message[200];
	int grow;
	snprintf(log_message, sizeof(log_message), "스텟 조정이 실행됐습니다!! .");
    log_to_file(log_message);
	int level = p->level;
	int base_hp = list[p->number - 1].hp;
	int base_attack_power = list[p->number - 1].attack_power;
	int base_defense = list[p->number - 1].defense;
	int base_speed = list[p->number - 1].speed;
	//레벨업했을 와 랭크업하기 전을 나누기 위한 비교 
	if (lv > level) grow = lv - level;
	else	grow = level;

	p->level = lv;
	p->hp = base_hp + (lv - 1) * 2;
	p->speed = base_speed + (int)(grow * log(lv)); 
    p->attack_power = base_attack_power + (int)(grow * log(lv)) * 2; 
    p->defense = base_defense + (int)(grow * log(lv));
}

void evolution(poketmon *p){
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "\n-----------------evolution함수 시작---------------------", p->name, p->evolution_poketmon->name);
	log_to_file(log_message);
	snprintf(log_message, sizeof(log_message), "\n%s가 %s(으)로 진회를 시작합니다!!\n", p->name, p->evolution_poketmon->name);
	log_to_file(log_message);
	
	poketmon evolution_poketmon;
	memcpy(&evolution_poketmon, p->evolution_poketmon, sizeof(poketmon));
	char poketmon_name[10]; 
	strcpy(poketmon_name, p->name);
	int lv = p->level;
	int evol_level = evolution_poketmon.evol_level;
	skill temp_skills[MAX_SKILL];
    memcpy(temp_skills, p->skill_list, sizeof(temp_skills));
    
    int rank_up[4];
	memcpy(rank_up, p->rank_up, sizeof(rank_up));
    
    memcpy(p, &evolution_poketmon, sizeof(poketmon));
    
    memcpy(p->skill_list, temp_skills, sizeof(temp_skills));
    memcpy(p->rank_up, rank_up, sizeof(rank_up));
    p->level = lv;
    p->evol_level = evol_level;
    set_stat(p, p->level, poketmon_all_list);
    calc_rank_up(p);
    
    snprintf(log_message, sizeof(log_message), "%s가 %s(으)로 진화했습니다!", poketmon_name, evolution_poketmon.name);
    log_to_file(log_message);
}

void prt_evolution(poketmon *p, poketmon *ev_p){
	cls;
	int idx = 5, time = 500;
	SetColor(p->color_number);
	gotoxy (15,6);	printf("%c", p->imege);
	SetColor(15);
	gotoxy (0,11);	printf("--------------------------------");
	gotoxy (2, 12);	printf("오잉..?! %s의 모습이....??", p->name);
	block_input_for_ms(3000);
	Sleep(3000);
	while (idx != 0){
		SetColor(ev_p->color_number);
		gotoxy (15,6);	printf("%c", p->imege);
		Sleep(time);
		SetColor(p->color_number);
		gotoxy (15,6);	printf("%c", p->imege);
		Sleep(time);
		idx --;
		time -= 100;
	}
	SetColor(ev_p->color_number);
	gotoxy (15,6);	printf("%c", p->imege);

	clear_line(12);	
	SetColor(15);
	gotoxy (2, 12);	printf("축하합니다! %s는 %s(으)로 진화했습니다!", p->name, ev_p->name);
	clear_input_buffer();
}

void check_new_skill(poketmon *p){
	char log_message[200];
	snprintf(log_message, sizeof(log_message), "\n레벨업후 새로운 기술을 습득할 레벨이 되었는지 체크합니다.");
	log_to_file(log_message);
	int lv = p->level;
	for (int i = 0; i < 20; i ++){
		if (p->learn_skill_level[i] == lv){
			snprintf(log_message, sizeof(log_message), "\n새로운 기술을 배울 수 있는 레벨입니다!!\nskillfilled: %d", p->skill_filled);
			log_to_file(log_message);
			snprintf(log_message, sizeof(log_message), "\np->learn_skill_level[i]: %d	p->learn_skill[i]: %d", p->learn_skill_level[i], p->learn_skill[i]);
			log_to_file(log_message);
			int idx = p->learn_skill[i];
			if (p->skill_filled < 4){
				poketmon_learn_skill(p, all_skill_list, ++idx);
				clear_line(12);	clear_line(13);	
				gotoxy(2, 12);	printf("%s는 %s를 배웠다!!", p->name, all_skill_list[idx].skill_name);
			}
			else{
				select_remove_skill(p, &all_skill_list[idx]);
			}	
			break;
		}
	}
	return;
}

void select_remove_skill(poketmon *p, skill *s){
	clear_line(12);	clear_line(13);
	gotoxy(2,12);	printf("%s는 %s를 배우고싶다...", p->name, s->skill_name);	make_input_buffer();
	clear_line(12);	clear_line(13);
	gotoxy(2,12);	printf("그러나 기술 4개를 알고 있으므로더 이상 배울 수 없다!!");	make_input_buffer();
	clear_line(12);	clear_line(13);
	gotoxy(2,12);	printf("%s대신 다른 기술을 잊게 하겠습니까??", s->skill_name);
	Sleep(100);
	int check_POS = 0;
	gotoxy(32,11);	printf("---------------------");
	gotoxy(44, 12);	printf("|");	gotoxy(44, 13);	printf("|");
    gotoxy(45, 12);	printf(">");
	gotoxy(46, 12);	printf("예");
	gotoxy(46, 13);	printf("아니오");
	while(1){
		if (_kbhit()) {
            int ch = _getch();
            if (ch == 224) { 
                ch = _getch(); 
                switch (ch) {
                   case 72: //위 
                        if (check_POS == 0) check_POS = 1;
                        else if(check_POS == 1)	check_POS = 0;
                        break;
                    case 80: //아래 
                        if (check_POS == 1) check_POS = 0;
                        else if(check_POS == 0)	check_POS = 1;
                        break;
                }
            } else if (ch == 13 || ch == 32) { 
                break;
            }

            switch (check_POS) {
                case 0:
                	gotoxy(45, 12);	printf(" ");
                	gotoxy(45, 13);	printf(" ");
                	gotoxy(45, 12);	printf(">");
					gotoxy(46, 12);	printf("예");
					gotoxy(46, 13);	printf("아니오");
                    break;
                case 1:
                	gotoxy(45, 12);	printf(" ");
                	gotoxy(45, 13);	printf(" ");
                	gotoxy(45, 13);	printf(">");
					gotoxy(46, 12);	printf("예");
					gotoxy(46, 13);	printf("아니오");
                    break;
            }
        }
        Sleep(100);
	}
	if (check_POS == 0){
		clear_line(11);	clear_line(12);	clear_line(13);
		gotoxy(0, 11);	printf("--------------------------------");
		gotoxy(2, 12);	printf("어느 기술을 잊게 하겠습니까??");
		make_input_buffer();
		prt_skill_txt(p->skill_list);
		skill remove_skill = select_skill(all_skill_list);
		change_skill(p->skill_list, remove_skill.skill_number, *s);
		clear_line(12);	clear_line(13);
		gotoxy(2, 12);	printf("%s는 %s를 잊고 %s를 배웠다!!!", p->name, remove_skill.skill_name, s->skill_name);
	}
	else if (check_POS == 1){
		clear_line(11);	clear_line(12);	clear_line(13);
		gotoxy(0,11);	printf("--------------------------------");
		gotoxy(2,12);	printf("%s는 %s를 배우지 않았다!!", p->name, s->skill_name);
	}
	return;
}

void change_skill(skill poketmon_skill_list[], int skill_number, skill s){
	int search_number = skill_number;
	for (int i = 0; i < 4; i ++){
		if (poketmon_skill_list[i].skill_number == search_number){
			poketmon_skill_list[i] = s;
			break;
		}
	}
}

void battle_start(poketmon *at_p, poketmon *de_p, skill *s1, int idx, poketmon list[]){
	char log_message[200]; 
	clear_line(12);
	float match = type_matchup[s1->type][de_p->type];
	int acc_rate = calc_acc(s1->accuracy);
	gotoxy(2,12);	printf("%s의 %s!!",at_p->name, s1->skill_name);	Sleep(100);
	if (acc_rate == 0){
		gotoxy(2,12);	printf("%s에게는 맞지 않았다!!",de_p->name); 	make_input_buffer();
		snprintf(log_message, sizeof(log_message), "%s의 공격이 빗나갔습니다.", at_p->name);
    	log_to_file(log_message); 
	}
	else{
		snprintf(log_message, sizeof(log_message), "%s의 공격 시작", at_p->name);
    	log_to_file(log_message);
		if (match == 0){
			clear_line(12);
			gotoxy(2,12);	printf("%s에게는 효과가 없는 것 같다....", de_p->name);	make_input_buffer();
		}
		else{
			if (de_p->hp <= 0){
				de_p->hp = 0;
			}
			else{
				float damg = calc_attack_damage(at_p, de_p, s1) * match;
				int r_damg = (int)round(damg);
				de_p->hp -= r_damg;
				
				if (de_p->hp < 0)	de_p->hp = 0;
		
				if (idx == 0){
					for (int i = 2; i < 25; i ++){
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
				make_input_buffer();
				clear_line(12);
				gotoxy(2,12);
				if (match == 0.5){
					printf("효과가 별로인 것 같다...");
					make_input_buffer();
				}
				if (match == 2){
					printf("효과가 굉장했다!");
					make_input_buffer();
				}	
			}
		}
		snprintf(log_message, sizeof(log_message), "\n%s의 체력이 %d남았습니다.",de_p->name, de_p->hp);
	    log_to_file(log_message);	
	}
}

int calc_attack_damage(poketmon *atk_p, poketmon *def_p, skill *s){
	char log_message[200];
	int attack_p = atk_p->attack_power;
	int attack_s = s->power;
	int defence = def_p->defense;
	int acc = s->accuracy;
	int level = atk_p->level;
	int my_p = 0;
	
	if (atk_p->type == s->type)	attack_s = attack_s * 1.5;
	
	int damage = (((level * 2 / 5) + 2) * attack_s * attack_p / 15) / defence; 
	snprintf(log_message, sizeof(log_message), "\n%s의 데미지 계산완료: %d",atk_p->name, damage);
    log_to_file(log_message);
	return damage;
}

int calc_acc(int acc){
	int acc_ration = 0;
	acc_ration = rand() % 100;
	
	if (acc >= acc_ration){
		return 1;
	} 
	else return 0;
}

float calc_rate(poketmon *enmy, ball *b){
	char log_message[200];
	
	snprintf(log_message, sizeof(log_message), "-----------------------------------------------\ncalc_rate실행");
	log_to_file(log_message);
	
	int enmy_max_hp = calc_max_hp(enmy, poketmon_all_list);
	int enmy_now_hp = enmy->hp;
	float ball_bonus = b->ball_bonus;
	float rate = enmy->rate;
	float status_bonus = enmy->status;
	float total_rate = (((3.0 * (float)enmy_max_hp - 2.0 * (float)enmy_now_hp) * rate * ball_bonus) / (3.0 * (float)enmy_max_hp)) * status_bonus;
	
	snprintf(log_message, sizeof(log_message), "적 체력: %d / %d\n%s의 볼 보너스: %f\n%s의 포획률: %f\n총 포획률: %f",enmy_now_hp, enmy_max_hp, b->name, ball_bonus, enmy->name, rate, total_rate);
	log_to_file(log_message);
	
	return total_rate;
} 

void success_catch(int success, int color){
	
	if (success == 1){
		gotoxy(25, 3);	printf(" ");
		SetColor(8);
		gotoxy(25, 3);	printf("●");	
	}
	
	else{
		gotoxy(25, 3);	printf(" ");
		SetColor(color);
		gotoxy(25, 3);	printf("O");	
	}
}

void bouns_ball(int bouns){
	if (bouns >= 1){
		Sleep(100);
		gotoxy(25, 3);	printf(" ");
		gotoxy(24, 3);	printf("●");
	
		Sleep(100);
		gotoxy(24, 3);	printf(" ");
		gotoxy(25, 3);	printf("●");	
	}
	
	if (bouns >= 2){
		Sleep(500);
		gotoxy(25, 3);	printf(" ");
		gotoxy(26, 3);	printf("●");
		
		Sleep(100);
		gotoxy(26, 3);	printf(" ");
		gotoxy(25, 3);	printf("●");	
	}
	
	if (bouns == 3){
		Sleep(500);
		gotoxy(26, 3);	printf(" ");
		gotoxy(25, 3);	printf("●");
		
		Sleep(100);
		gotoxy(25, 3);	printf(" ");
		gotoxy(24, 3);	printf("●");
		
		Sleep(100);
		gotoxy(24, 3);	printf(" ");
		gotoxy(25, 3);	printf("●");
	}
}

int* calc_success_rate(float total_rate){
	char log_message[200];
    int success = 1, bouns = 0;
    static int answer[2];
    float num[3] = {0};
    float b;

    if (total_rate < 255) {
        b = 65535 * pow(total_rate / 255.0, 1.0 / 4.0);
        for (int i = 0; i < 3; i++) {
            int random = (rand() << 15) | rand();
            random = random % 65535;
            num[i] = (float) random;
        }
        for (int i = 0; i < 3; i++) {
            if (b >= num[i]) { 
                bouns++;
            } else {
                success = 0;
            }
        }
        if (bouns > 3) bouns = 3;
    }
    answer[0] = bouns;
    answer[1] = success;

	snprintf(log_message, sizeof(log_message), "---------------------------------\ncalc_success_rate시작");
	log_to_file(log_message);
	
	snprintf(log_message, sizeof(log_message), "%d번 흔들리고 ", bouns);
	log_to_file(log_message);
	
	if (success == 1){
		snprintf(log_message, sizeof(log_message), "포획 성공\n");
		log_to_file(log_message);
	}
	
	else if (success == 0){
		snprintf(log_message, sizeof(log_message), "포획 실패 \n");
		log_to_file(log_message);
	}
    return answer;
}

void battle_turn(int skill_idx, poketmon *my, poketmon *enmy, skill *my_s, skill *enmy_s, poketmon poketmon_all_list[]){
	char log_message[200];
	if (skill_idx == 0){
		battle_start(my, enmy, my_s, 0, poketmon_all_list);
    	snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", my->name, my_s->skill_name, enmy->name);
    	log_to_file(log_message);
		if (enmy->hp > 0){
			battle_start(enmy, my, enmy_s, 1, poketmon_all_list);
			snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enmy_s->skill_name, my->name);
    		log_to_file(log_message);
		}			
	}
	else if (skill_idx == 1){
		battle_start(enmy, my, enmy_s, 1, poketmon_all_list);
		snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enmy_s->skill_name, my->name);
    	log_to_file(log_message);
		if (my->hp > 0){
			battle_start(my, enmy, my_s, 0, poketmon_all_list);	
			snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", my->name, my_s->skill_name, enmy->name);
    		log_to_file(log_message);
		}
	}
	else{
		int speed1 = my->speed;
		int speed2 = enmy->speed;
		if (speed1 > speed2){
			battle_start(my, enmy, my_s, 0, poketmon_all_list);
			if (enmy->hp > 0){
				battle_start(enmy, my, enmy_s, 1, poketmon_all_list);
				snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enmy_s->skill_name, my->name);
    			log_to_file(log_message);
    		}
		}	
		else{
			battle_start(enmy, my, enmy_s, 1, poketmon_all_list);
			snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", enmy->name, enmy_s->skill_name, my->name);
    		log_to_file(log_message);
			if (my->hp > 0){
				battle_start(my, enmy, my_s, 0, poketmon_all_list);	
				snprintf(log_message, sizeof(log_message), "%s의 %s로 %s에게 공격을 시작합니다!", my->name, my_s->skill_name, enmy->name);
    			log_to_file(log_message);
			}
		}
	}
}

void initi_poketmon(poketmon *p, int number, char *name, int type, int hp, int attack_power, int defense, int level, int evol_level, int speed, int color_number, poketmon *e_p, int base_skill[], float rate) {
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
    p->rate = rate;
    p->exp = 0;
    p->status = 1.0;
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

void init_ball(ball *b, char *name, float ball_bonus, int color_index){
	strcpy(b->name, name);
	b->ball_bonus = ball_bonus;
	b->color_index = color_index;
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
	init_item(&list[idx++], "고급 상처약", 1000, "1000골드를 사용해 포켓몬 1마리의 HP를 200 또는 50% 중 높은 수치만큼 회복한다.");	
}

void init_ball_data(ball ball_info[]){
	int idx = 0;
	init_ball(&ball_info[idx ++], "몬스터볼", 1, 4);
	init_ball(&ball_info[idx ++], "수퍼볼", 1.5, 9);
	init_ball(&ball_info[idx ++], "하이퍼볼", 2, 14);
	init_ball(&ball_info[idx ++], "마스터볼", 100, 13);
}

void init_poketmon_data(){
	char log_message[200];
	int base_skill[2] = {0};
	
	base_skill[0] = 7; base_skill[1] = 8; 
    initi_poketmon(&poketmon_all_list[0], 1, "이상해씨", GRASS, 45, 65, 65, 1, 16, 45, 14, &poketmon_all_list[1], base_skill, 45);
    initi_poketmon(&poketmon_all_list[1], 2, "이상해풀", GRASS, 60, 80, 80, 1, 32, 60, 9, &poketmon_all_list[2], base_skill, 45);
    initi_poketmon(&poketmon_all_list[2], 3, "이상해꽃", GRASS, 80, 100, 100, 1, 0, 80, 12, NULL, base_skill, 45);

    base_skill[0] = 0; base_skill[1] = 1;
    initi_poketmon(&poketmon_all_list[3], 4, "파이리", FIRE, 39, 60, 50, 1, 16, 65, 14, &poketmon_all_list[4], base_skill, 45);
    initi_poketmon(&poketmon_all_list[4], 5, "리자드", FIRE, 58, 80, 65, 1, 36, 80, 9, &poketmon_all_list[5], base_skill, 45);
    initi_poketmon(&poketmon_all_list[5], 6, "리자몽", FIRE, 78, 109, 85, 1, 0, 100, 12, NULL, base_skill, 45);
    
    base_skill[0] = 7; base_skill[1] = 13; 
    initi_poketmon(&poketmon_all_list[6], 7, "꼬부기", WATER, 44, 50, 64, 1, 16, 43, 14, &poketmon_all_list[7], base_skill, 45);
    initi_poketmon(&poketmon_all_list[7], 8, "어니부기", WATER, 59, 65, 80, 1, 36, 58, 9, &poketmon_all_list[8], base_skill, 45);
    initi_poketmon(&poketmon_all_list[8], 9, "거북왕", WATER, 79, 85, 105, 1, 0, 78, 12,NULL, base_skill, 45);
    
    base_skill[0] = 7;	base_skill[1] = 19;
    initi_poketmon(&poketmon_all_list[9], 10, "캐터피", BUG, 45, 30, 35, 1, 7, 45, 14, &poketmon_all_list[10], base_skill, 255);
    base_skill[0] = 20;
    initi_poketmon(&poketmon_all_list[10], 11, "단데기", BUG, 50, 20, 55, 1, 10, 30, 9, &poketmon_all_list[11], base_skill, 120);
    initi_poketmon(&poketmon_all_list[11], 12, "버터플", BUG, 60, 45, 50, 1, 0, 70, 12, NULL, base_skill, 45);
    
    base_skill[0] = 19;	base_skill[1] = 7;
    initi_poketmon(&poketmon_all_list[12], 13, "뿔충이", BUG, 40, 35, 30, 1, 7, 50, 14, &poketmon_all_list[13], base_skill, 255);
    base_skill[0] = 20;
    initi_poketmon(&poketmon_all_list[13], 14, "딱충이", BUG, 45, 25, 50, 1, 10, 35, 9, &poketmon_all_list[14], base_skill, 120);
    initi_poketmon(&poketmon_all_list[14], 15, "독침붕", BUG, 65, 80, 40, 1, 0, 75, 12, NULL, base_skill, 45);
    
    base_skill[0] = 7; base_skill[1] = 31;
    initi_poketmon(&poketmon_all_list[15], 16, "구구", FLYING, 40, 45, 40, 1, 18, 56, 14, &poketmon_all_list[16], base_skill, 255);
    initi_poketmon(&poketmon_all_list[16], 17, "피죤", FLYING, 63, 60, 55, 1, 36, 71, 9, &poketmon_all_list[17], base_skill, 120);
    initi_poketmon(&poketmon_all_list[17], 18, "피죤투", FLYING, 83, 80, 75, 1, 0, 101, 12, NULL, base_skill, 45);
    
    base_skill[0] = 7; base_skill[1] = 32;
    initi_poketmon(&poketmon_all_list[18], 19, "꼬렛", NORMAL, 30, 56, 35, 1, 20, 72, 14, &poketmon_all_list[19], base_skill, 255);
    initi_poketmon(&poketmon_all_list[19], 20, "레트라", NORMAL, 55, 81, 60, 1, 0, 97, 9, NULL, base_skill, 127);
    
    base_skill[0] = 42;	base_skill[1] = 7;
    initi_poketmon(&poketmon_all_list[20], 21, "깨비참", NORMAL, 40, 60, 30, 1, 20, 70, 9, &poketmon_all_list[21], base_skill, 255);
    initi_poketmon(&poketmon_all_list[21], 22, "깨비드릴조", NORMAL, 65, 90, 65, 1, 0, 100, 12, NULL, base_skill, 90);
    
    base_skill[0] = 15;	base_skill[1] = 7;
    initi_poketmon(&poketmon_all_list[22], 23, "아보", POISON, 35, 60, 44, 1, 22, 55, 9, &poketmon_all_list[23], base_skill, 255);
    initi_poketmon(&poketmon_all_list[23], 24, "아보크", POISON, 60, 85, 69, 1, 0, 80, 12, NULL, base_skill, 90);
    
    base_skill[0] = 49;	base_skill[1] = 32;
    initi_poketmon(&poketmon_all_list[24], 25, "피카츄", ELECTRIC, 35, 55, 40, 1, 22, 90, 14, &poketmon_all_list[24], base_skill, 190);
    initi_poketmon(&poketmon_all_list[25], 26, "라이츄", ELECTRIC, 60, 90, 55, 1, 0, 110, 6, NULL, base_skill, 75);
    
    initi_poketmon(&poketmon_all_list[26], 27, "모래두지", GROUND, 50, 75, 85, 1, 22, 40, 14, &poketmon_all_list[27], base_skill, 255);
    initi_poketmon(&poketmon_all_list[27], 28, "고지", GROUND, 75, 100, 110, 1, 0, 65, 9, NULL, base_skill, 90);
	initi_poketmon(&poketmon_all_list[28], 29, "니드런♀", POISON, 55, 47, 52, 1, 16, 41, 14, &poketmon_all_list[29], base_skill, 235);
	initi_poketmon(&poketmon_all_list[29], 30, "니드리나", POISON, 70, 62, 67, 1, 32, 56, 9, &poketmon_all_list[30], base_skill, 120);
	initi_poketmon(&poketmon_all_list[30], 31, "니드퀸", POISON, 90, 92, 87, 1, 0, 76, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[31], 32, "니드런♂", POISON, 46, 57, 40, 1, 16, 50, 14, &poketmon_all_list[32], base_skill, 235);
	initi_poketmon(&poketmon_all_list[32], 33, "니드리노", POISON, 61, 72, 57, 1, 32, 65, 9, &poketmon_all_list[33], base_skill, 120);
	initi_poketmon(&poketmon_all_list[33], 34, "니드킹", POISON, 81, 102, 77, 1, 0, 85, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[34], 35, "삐삐", FAIRY, 70, 45, 48, 1, 32, 35, 14, &poketmon_all_list[35], base_skill, 150);
	initi_poketmon(&poketmon_all_list[35], 36, "픽시", FAIRY, 95, 70, 73, 1, 0, 60, 9, NULL, base_skill, 25);
	initi_poketmon(&poketmon_all_list[36], 37, "식스테일", FIRE, 38, 41, 40, 1, 22, 65, 14, &poketmon_all_list[37], base_skill, 190);
	initi_poketmon(&poketmon_all_list[37], 38, "나인테일", FIRE, 73, 76, 75, 1, 0, 100, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[38], 39, "푸린", FAIRY, 115, 45, 20, 1, 32, 20, 14, &poketmon_all_list[39], base_skill, 170);
	initi_poketmon(&poketmon_all_list[39], 40, "푸크린", FAIRY, 140, 70, 45, 1, 0, 45, 12, NULL, base_skill, 50);
	initi_poketmon(&poketmon_all_list[40], 41, "주뱃", POISON, 40, 45, 35, 1, 22, 55, 14, &poketmon_all_list[41], base_skill, 255);
	initi_poketmon(&poketmon_all_list[41], 42, "골뱃", POISON, 75, 80, 70, 1, 0, 90, 12, NULL, base_skill, 90);
	initi_poketmon(&poketmon_all_list[42], 43, "뚜벅쵸", GRASS, 45, 75, 65, 1, 21, 30, 14, &poketmon_all_list[43], base_skill, 255);
	initi_poketmon(&poketmon_all_list[43], 44, "냄새꼬", GRASS, 60, 58, 75, 1, 32, 40, 9, &poketmon_all_list[44], base_skill, 120);
	initi_poketmon(&poketmon_all_list[44], 45, "라플레시아", GRASS, 75, 110, 90, 1, 0, 50, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[45], 46, "파라스", BUG, 35, 70, 55, 1, 24, 25, 14, &poketmon_all_list[46], base_skill, 190);
	initi_poketmon(&poketmon_all_list[46], 47, "파라섹트", BUG, 60, 95, 80, 1, 0, 30, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[47], 48, "콘팡", BUG, 60, 55, 50, 1, 31, 45, 14, &poketmon_all_list[48], base_skill, 190);
	initi_poketmon(&poketmon_all_list[48], 49, "도나리", BUG, 70, 65, 60, 1, 0, 90, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[49], 50, "디그다", GROUND, 10, 55, 25, 1, 26, 95, 14, &poketmon_all_list[50], base_skill, 255);
	initi_poketmon(&poketmon_all_list[50], 51, "닥트리오", GROUND, 35, 100, 50, 1, 0, 120, 12, NULL, base_skill, 50);
	initi_poketmon(&poketmon_all_list[51], 52, "나옹", NORMAL, 40, 45, 35, 1, 28, 90, 14, &poketmon_all_list[52], base_skill, 255);
	initi_poketmon(&poketmon_all_list[52], 53, "페르시온", NORMAL, 65, 70, 60, 1, 0, 115, 12, NULL, base_skill, 90);
	initi_poketmon(&poketmon_all_list[53], 54, "고라파덕", WATER, 50, 52, 48, 1, 33, 55, 14, &poketmon_all_list[54], base_skill, 190);
	initi_poketmon(&poketmon_all_list[54], 55, "골덕", WATER, 80, 82, 78, 1, 0, 85, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[55], 56, "망키", FIGHTING, 40, 80, 35, 1, 28, 70, 14, &poketmon_all_list[56], base_skill, 190);
	initi_poketmon(&poketmon_all_list[56], 57, "성원숭", FIGHTING, 65, 105, 60, 1, 0, 95, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[57], 58, "가디", FIRE, 55, 70, 45, 1, 36, 60, 14, &poketmon_all_list[58], base_skill, 190);
	initi_poketmon(&poketmon_all_list[58], 59, "윈디", FIRE, 90, 110, 80, 1, 0, 95, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[59], 60, "발챙이", WATER, 40, 50, 40, 1, 25, 90, 14, &poketmon_all_list[60], base_skill, 255);
	initi_poketmon(&poketmon_all_list[60], 61, "슈륙챙이", WATER, 65, 65, 65, 1, 36, 70, 9, &poketmon_all_list[61], base_skill, 120);
	initi_poketmon(&poketmon_all_list[61], 62, "강챙이", WATER, 90, 95, 95, 1, 0, 70, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[62], 63, "캐이시", PSYCHIC, 25, 20, 15, 1, 16, 90, 14, &poketmon_all_list[63], base_skill, 200);
    initi_poketmon(&poketmon_all_list[63], 64, "윤겔라", PSYCHIC, 40, 35, 30, 1, 36, 105, 9, &poketmon_all_list[64], base_skill, 100);
    initi_poketmon(&poketmon_all_list[64], 65, "후딘", PSYCHIC, 55, 50, 45, 1, 0, 120, 12, NULL, base_skill, 50);	    
	initi_poketmon(&poketmon_all_list[65], 66, "알통몬", FIGHTING, 70, 80, 50, 1, 28, 70, 14, &poketmon_all_list[66], base_skill, 180);
	initi_poketmon(&poketmon_all_list[66], 67, "근육몬", FIGHTING, 80, 100, 70, 1, 36, 45, 9, &poketmon_all_list[67], base_skill, 90);
	initi_poketmon(&poketmon_all_list[67], 68, "괴력몬", FIGHTING, 90, 130, 80, 1, 0, 55, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[68], 69, "모다피", GRASS, 50, 75, 35, 1, 21, 30, 14, &poketmon_all_list[69], base_skill, 255);
	initi_poketmon(&poketmon_all_list[69], 70, "우츠동", GRASS, 65, 90, 50, 1, 36, 45, 9, &poketmon_all_list[70], base_skill, 120);
	initi_poketmon(&poketmon_all_list[70], 71, "우츠보트", GRASS, 80, 105, 65, 1, 0, 70, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[71], 72, "왕눈해", WATER, 40, 40, 35, 1, 30, 70, 14, &poketmon_all_list[72], base_skill, 190);
	initi_poketmon(&poketmon_all_list[72], 73, "독파리", WATER, 80, 70, 65, 1, 0, 100, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[73], 74, "꼬마돌", ROCK, 40, 80, 100, 1, 25, 20, 14, &poketmon_all_list[74], base_skill, 255);
	initi_poketmon(&poketmon_all_list[74], 75, "데구리", ROCK, 55, 95, 115, 1, 36, 35, 9, &poketmon_all_list[75], base_skill, 120);
	initi_poketmon(&poketmon_all_list[75], 76, "딱구리", ROCK, 80, 120, 130, 1, 0, 45, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[76], 77, "포니타", FIRE, 50, 85, 55, 1, 40, 90, 14, &poketmon_all_list[77], base_skill, 190);
	initi_poketmon(&poketmon_all_list[77], 78, "날쌩마", FIRE, 65, 100, 70, 1, 0, 105, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[78], 79, "야돈", WATER, 90, 65, 65, 1, 37, 15, 14, &poketmon_all_list[79], base_skill, 190);
	initi_poketmon(&poketmon_all_list[79], 80, "야도란", WATER, 95, 75, 110, 1, 0, 30, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[80], 81, "코일", ELECTRIC, 25, 35, 70, 1, 30, 45, 14, &poketmon_all_list[81], base_skill, 190);
	initi_poketmon(&poketmon_all_list[81], 82, "레어코일", ELECTRIC, 50, 60, 95, 1, 0, 70, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[82], 83, "파오리", FLYING, 52, 65, 55, 1, 0, 60, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[83], 84, "두두", NORMAL, 35, 85, 45, 1, 31, 75, 14, &poketmon_all_list[84], base_skill, 190);
	initi_poketmon(&poketmon_all_list[84], 85, "두트리오", NORMAL, 60, 110, 70, 1, 0, 100, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[85], 86, "쥬쥬", WATER, 65, 45, 55, 1, 34, 45, 14, &poketmon_all_list[86], base_skill, 190);
	initi_poketmon(&poketmon_all_list[86], 87, "쥬레곤", WATER, 90, 70, 80, 1, 0, 70, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[87], 88, "질퍽이", POISON, 80, 80, 50, 1, 38, 25, 14, &poketmon_all_list[88], base_skill, 190);
	initi_poketmon(&poketmon_all_list[88], 89, "질뻐기", POISON, 105, 105, 75, 1, 0, 50, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[89], 90, "셀러", WATER, 30, 65, 100, 1, 36, 40, 14, &poketmon_all_list[90], base_skill, 190);
	initi_poketmon(&poketmon_all_list[90], 91, "파르셀", WATER, 50, 95, 180, 1, 0, 70, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[91], 92, "고오스", GHOST, 30, 35, 30, 1, 25, 80, 14, &poketmon_all_list[92], base_skill, 190);
	initi_poketmon(&poketmon_all_list[92], 93, "고우스트", GHOST, 45, 50, 45, 1, 38, 95, 9, &poketmon_all_list[93], base_skill, 90);
	initi_poketmon(&poketmon_all_list[93], 94, "팬텀", GHOST, 60, 65, 60, 1, 0, 110, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[94], 95, "롱스톤", ROCK, 35, 45, 160, 1, 0, 70, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[95], 96, "슬리프", PSYCHIC, 60, 48, 45, 1, 26, 42, 14, &poketmon_all_list[96], base_skill, 190);
	initi_poketmon(&poketmon_all_list[96], 97, "슬리퍼", PSYCHIC, 85, 73, 70, 1, 0, 67, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[97], 98, "크랩", WATER, 30, 105, 90, 1, 28, 50, 14, &poketmon_all_list[98], base_skill, 225);
	initi_poketmon(&poketmon_all_list[98], 99, "킹크랩", WATER, 55, 130, 115, 1, 0, 75, 9, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[99], 100, "찌리리공", ELECTRIC, 40, 30, 50, 1, 30, 100, 14, &poketmon_all_list[100], base_skill, 190);
	initi_poketmon(&poketmon_all_list[100], 101, "붐볼", ELECTRIC, 60, 50, 70, 1, 0, 140, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[101], 102, "아라리", GRASS, 60, 40, 80, 1, 36, 40, 14, &poketmon_all_list[102], base_skill, 90);
	initi_poketmon(&poketmon_all_list[102], 103, "나시", GRASS, 95, 95, 85, 1, 0, 55, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[103], 104, "탕구리", GROUND, 50, 50, 95, 1, 28, 35, 14, &poketmon_all_list[104], base_skill, 190);
	initi_poketmon(&poketmon_all_list[104], 105, "텅구리", GROUND, 60, 80, 110, 1, 0, 45, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[105], 106, "시라소몬", FIGHTING, 50, 120, 53, 1, 0, 87, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[106], 107, "홍수몬", FIGHTING, 50, 105, 79, 1, 0, 76, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[107], 108, "내루미", NORMAL, 90, 55, 75, 1, 0, 30, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[108], 109, "또가스", POISON, 40, 65, 95, 1, 35, 35, 14, &poketmon_all_list[109], base_skill, 190);
	initi_poketmon(&poketmon_all_list[109], 110, "또도가스", POISON, 65, 90, 120, 1, 0, 60, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[110], 111, "뿔카노", GROUND, 80, 85, 95, 1, 42, 25, 9, &poketmon_all_list[111], base_skill, 120);
	initi_poketmon(&poketmon_all_list[111], 112, "코뿌리", GROUND, 105, 130, 120, 1, 0, 40, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[112], 113, "럭키", NORMAL, 250, 5, 5, 1, 0, 50, 9, NULL, base_skill, 30);
	initi_poketmon(&poketmon_all_list[113], 114, "덩쿠리", GRASS, 65, 55, 115, 1, 0, 60, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[114], 115, "캥카", NORMAL, 105, 95, 80, 1, 0, 90, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[115], 116, "쏘드라", WATER, 30, 40, 70, 1, 32, 60, 14, &poketmon_all_list[116], base_skill, 225);
	initi_poketmon(&poketmon_all_list[116], 117, "시드라", WATER, 55, 65, 95, 1, 0, 85, 12, NULL, base_skill, 75);
	initi_poketmon(&poketmon_all_list[117], 118, "콘치", WATER, 45, 67, 60, 1, 33, 63, 14, &poketmon_all_list[118], base_skill, 225);
	initi_poketmon(&poketmon_all_list[118], 119, "왕콘치", WATER, 80, 92, 65, 1, 0, 68, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[119], 120, "별가사리", WATER, 30, 45, 55, 1, 36, 85, 14, &poketmon_all_list[120], base_skill, 225);
	initi_poketmon(&poketmon_all_list[120], 121, "아쿠스타", WATER, 60, 75, 85, 1, 0, 115, 12, NULL, base_skill, 60);
	initi_poketmon(&poketmon_all_list[121], 122, "마임맨", PSYCHIC, 40, 45, 65, 1, 0, 90, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[122], 123, "스라크", BUG, 70, 110, 80, 1, 0, 105, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[123], 124, "루주라", ICE, 65, 50, 35, 1, 0, 95, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[124], 125, "에레브", ELECTRIC, 65, 83, 57, 1, 0, 105, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[125], 126, "마그마", FIRE, 65, 95, 57, 1, 0, 93, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[126], 127, "쁘사이저", BUG, 65, 125, 100, 1, 0, 85, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[127], 128, "켄타로스", NORMAL, 75, 100, 95, 1, 0, 110, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[128], 129, "잉어킹", WATER, 20, 10, 55, 1, 20, 80, 14, &poketmon_all_list[129], base_skill, 255);
	initi_poketmon(&poketmon_all_list[129], 130, "갸라도스", WATER, 95, 125, 79, 1, 0, 81, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[130], 131, "라프라스", WATER, 130, 85, 80, 1, 0, 60, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[131], 132, "메타몽", NORMAL, 48, 48, 48, 1, 0, 48, 12, NULL, base_skill, 35);
	initi_poketmon(&poketmon_all_list[132], 133, "이브이", NORMAL, 55, 55, 50, 1, 26, 55, 14, &poketmon_all_list[133], base_skill, 45);
	initi_poketmon(&poketmon_all_list[133], 134, "샤미드", WATER, 130, 65, 60, 1, 0, 65, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[134], 135, "쥬피썬더", ELECTRIC, 65, 65, 60, 1, 0, 130, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[135], 136, "부스터", FIRE, 65, 130, 60, 1, 0, 65, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[136], 137, "폴리곤", NORMAL, 65, 60, 70, 1, 0, 40, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[137], 138, "암나이트", ROCK, 35, 40, 100, 1, 40, 35, 14, &poketmon_all_list[138], base_skill, 45);
	initi_poketmon(&poketmon_all_list[138], 139, "암스타", ROCK, 70, 60, 125, 1, 0, 55, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[139], 140, "투구", ROCK, 30, 80, 90, 1, 40, 55, 14, &poketmon_all_list[140], base_skill, 45);
	initi_poketmon(&poketmon_all_list[140], 141, "투구푸스", ROCK, 60, 115, 105, 1, 0, 80, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[141], 142, "프테라", ROCK, 80, 105, 65, 1, 0, 130, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[142], 143, "잠만보", NORMAL, 160, 110, 65, 1, 0, 30, 12, NULL, base_skill, 25);
	initi_poketmon(&poketmon_all_list[143], 144, "프리져", ICE, 90, 85, 100, 1, 0, 85, 12, NULL, base_skill, 3);
	initi_poketmon(&poketmon_all_list[144], 145, "썬더", ELECTRIC, 90, 90, 85, 1, 0, 100, 12, NULL, base_skill, 3);
	initi_poketmon(&poketmon_all_list[145], 146, "파이어", FIRE, 90, 100, 90, 1, 0, 90, 12, NULL, base_skill, 3);
	initi_poketmon(&poketmon_all_list[146], 147, "미뇽", DRAGON, 41, 64, 45, 1, 30, 50, 14, &poketmon_all_list[147], base_skill, 45);
	initi_poketmon(&poketmon_all_list[147], 148, "신뇽", DRAGON, 61, 84, 65, 1, 55, 70, 9, &poketmon_all_list[148], base_skill, 45);
	initi_poketmon(&poketmon_all_list[148], 149, "망나뇽", DRAGON, 91, 134, 95, 1, 0, 80, 12, NULL, base_skill, 45);
	initi_poketmon(&poketmon_all_list[149], 150, "뮤츠", PSYCHIC, 106, 110, 90, 1, 0, 130, 5, NULL, base_skill, 3);
	initi_poketmon(&poketmon_all_list[150], 151, "뮤", PSYCHIC, 100, 100, 100, 1, 0, 100, 5, NULL, base_skill, 45);
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

