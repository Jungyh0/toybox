#include <stdio.h>
#include <windows.h>
#include <conio.h>

void initialize_log() {
    FILE *log_file = fopen("game_log.txt", "w");  // "w" ���� ���� ���� (���� ����)
    if (log_file != NULL) {
        fclose(log_file);  // ������ �ݱ⸸ �ϸ� ���� ���� ������ ������
    } else {
        printf("�α� ������ �� �� �����ϴ�!\n");
    }
}

void log_to_file(const char *log_message) {
    FILE *log_file = fopen("game_log.txt", "a");  // "a" ���� ������ ���� �߰�
    if (log_file != NULL) {
        fprintf(log_file, "%s\n", log_message);  // �α� �޽����� ���Ͽ� ���
        fclose(log_file);  // ������ �ݱ�
    } else {
        printf("�α� ������ �� �� �����ϴ�!\n");
    }
}

void save_game(int g_round, User *user) {
    FILE *file = fopen("save_file.txt", "w");

    fprintf(file, "%d\n", g_round); // ���� ���� ����
    fprintf(file, "%d\n", user->num_pokemons); // ���� ���ϸ� ���� ����

    // ���ϸ� ���� ����
    for (int i = 0; i < user->num_pokemons; i++) {
        poketmon *p = &user->poketmon_list[i];

        // ���ϸ� �⺻ ���� ����
        fprintf(file, "%s %d %d %d %d %d %f %d %d %d %c %d %d %d\n",
                p->name, p->type, p->hp, p->attack_power, p->defense, 
                p->level, p->status, p->number, p->evol_level, p->speed, 
                p->imege, p->color_number, p->exp, p->max_exp);

        // ��ũ�� ���� ����
        fprintf(file, "%d %d %d %d\n", p->rank_up[0], p->rank_up[1], p->rank_up[2], p->rank_up[3]);

        // ��� ��� ����
        fprintf(file, "%d\n", p->skill_filled);
        for (int j = 0; j < p->skill_filled; j++) {
            fprintf(file, "%s %d %d %d %d %d\n",
                    p->skill_list[j].skill_name, p->skill_list[j].power, 
                    p->skill_list[j].type, p->skill_list[j].accuracy, 
                    p->skill_list[j].priority, p->skill_list[j].skill_number);
        }

        // ��� �� �ִ� ��� ��� ����
        for (int j = 0; j < 20; j++) {
            fprintf(file, "%d ", p->learn_skill[j]);
        }
        fprintf(file, "\n");

        for (int j = 0; j < 20; j++) {
            fprintf(file, "%d ", p->learn_skill_level[j]);
        }
        fprintf(file, "\n");

        // �⺻ ��� ����
        fprintf(file, "%d %d\n", p->base_skill[0], p->base_skill[1]);

        // ���ϸ� ��ȭ ���� ���� (�����͸� ������� �ʰ� ��ȣ ����)
        if (p->evolution_poketmon != NULL) {
            fprintf(file, "%d\n", p->evolution_poketmon->number);
        } else {
            fprintf(file, "-1\n");
        }
    }

    fclose(file);
}

void load_game(int *g_round, User *user, poketmon poketmon_all_list[]) {
    FILE *file = fopen("save_file.txt", "r");

    fscanf(file, "%d", g_round); // ����� ���� �ҷ�����
    fscanf(file, "%d", &user->num_pokemons); // ���ϸ� ���� �ҷ�����

    // ���ϸ� ���� �ҷ�����
    for (int i = 0; i < user->num_pokemons; i++) {
        poketmon *p = &user->poketmon_list[i];

        // ���ϸ� �⺻ ���� �ҷ�����
        fscanf(file, "%s %d %d %d %d %d %f %d %d %d %c %d %d %d",
               p->name, &p->type, &p->hp, &p->attack_power, &p->defense, 
               &p->level, &p->status, &p->number, &p->evol_level, &p->speed, 
               &p->imege, &p->color_number, &p->exp, &p->max_exp);

        // ��ũ�� ���� �ҷ�����
        fscanf(file, "%d %d %d %d", &p->rank_up[0], &p->rank_up[1], &p->rank_up[2], &p->rank_up[3]);

        // ��� ��� �ҷ�����
        fscanf(file, "%d", &p->skill_filled);
        for (int j = 0; j < p->skill_filled; j++) {
            fscanf(file, "%s %d %d %d %d %d",
                   p->skill_list[j].skill_name, &p->skill_list[j].power, 
                   &p->skill_list[j].type, &p->skill_list[j].accuracy, 
                   &p->skill_list[j].priority, &p->skill_list[j].skill_number);
        }

        // ��� �� �ִ� ��� ��� �ҷ�����
        for (int j = 0; j < 20; j++) {
            fscanf(file, "%d", &p->learn_skill[j]);
        }

        for (int j = 0; j < 20; j++) {
            fscanf(file, "%d", &p->learn_skill_level[j]);
        }

        // �⺻ ��� �ҷ�����
        fscanf(file, "%d %d", &p->base_skill[0], &p->base_skill[1]);

        // ���ϸ� ��ȭ ���� �ҷ�����
        int evolution_num;
        fscanf(file, "%d", &evolution_num);
        if (evolution_num != -1) {
            p->evolution_poketmon = &poketmon_all_list[evolution_num - 1]; // ���� ����Ʈ���� ����
        } else {
            p->evolution_poketmon = NULL;
        }
    }

    fclose(file);
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

void clear_line(int y) {
    gotoxy(1, y);
    for (int i = 2; i < 150; i++) {
        printf(" ");
    }
}

void log_masage(char *s){
	gotoxy(35,3);
	printf("%s", s);
}

void clear_input_buffer() {
    while (_kbhit()) _getch();
}

void block_input_for_ms(int milliseconds) {
    clear_input_buffer();
    Sleep(milliseconds);
}

void make_input_buffer(){
	while (1) { 
        int ch = _getch();
        if (ch == 32 || ch == 13) break;
    }
}
