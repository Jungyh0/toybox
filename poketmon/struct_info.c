#define MAX 20
typedef struct skill {
	char skill_name[10];
	int power;
	int type;
	int accuracy;
	int priority;
	int skill_number;
}skill;


typedef struct poketmon{
	char name[10];
	int type;
	int hp;
	int attack_power;
	int defense;
	int level;
	float status;
	int number;
	int evol_level;
	int speed;
	char imege;
	int color_number;
	int exp;
	int max_exp;
	int rank_up[4];
	struct poketmon *evolution_poketmon;
	skill skill_list[4];
	int skill_filled;
	int learn_skill[20];
	int learn_skill_level[20];
	int base_skill[2];
	float rate;
}poketmon;

typedef struct item {
	char name[10];
	int price;
	char effect[200];
}item;

typedef struct bag {
	int money;
	item bac_max[MAX];
	int item_count[MAX]; 
}bag;


typedef struct User {
	poketmon poketmon_list[5];
	int num_pokemons;
	int alive_pokemon; 
}User;

typedef struct poket_ball {
	char name[10];
	float ball_bonus;
	int color_index;
}ball;
