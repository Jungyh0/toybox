#include "include_info.h"
#include "API.c"

void mainprt(){
	system("title poketmonster");
	SetColor(12);
	printf("===================================================\n");
	SetColor(15);
	char *poketmon[5] = {
        " ooooo   ooo  o   o ooo  ooooo  o   o  ooo  o   o",
        " o    o o   o o  o  o      o    oo oo o   o oo  o",
        " ooooo  o   o ooo   ooo    o    o o o o   o o o o",
        " o      o   o o  o  o      o    o   o o   o o  oo",
        " o       ooo  o   o ooo    o    o   o  ooo  o   o"
    };

    for (int i = 0; i < 5; i++) {
        printf("%s\n", poketmon[i]);
    }
    SetColor(12);
    printf("===================================================");
	SetColor(15);
	gotoxy(40, 8); printf("새 게임");
	gotoxy(40, 10); printf("이어 하기");
	gotoxy(40, 12); printf("게임  종료");
}

void prt_select_poketball_ui(){
	for (int i = 10; i >= 3; i --){
		gotoxy(33, i);
		printf("|"); 
	}
	gotoxy(34, 2);	printf("------------------");
	SetColor(11);
	gotoxy(36, 3);	printf(">");
	SetColor(15);
	gotoxy(37, 3);	printf("몬스터 볼 x ");
	gotoxy(37, 5);	printf("슈퍼 볼 x ");
	gotoxy(37, 7);	printf("하이퍼 볼 x ");
	gotoxy(37, 9);	printf("마스터 볼 x ");
	gotoxy(32, 11);	printf("--------------------");
}

void show_my_poketmon_ui(int number){
	switch(number){
		case 0:
			SetColor(15);
			gotoxy(2,3);
			printf(" -----------------------");
			gotoxy(2,4);
			printf("|");
			gotoxy(2,5);
			printf("|");
									gotoxy(26,4);
									printf("|");
									gotoxy(26,5);
									printf("|");
									gotoxy(2,6);
			printf(" -----------------------");
			
			SetColor(8);
			gotoxy(2,8);
			printf(" -----------------------");
			gotoxy(2,9);
			printf("|");
			gotoxy(2,10);
			printf("|");
			
			gotoxy(30,1);
			printf(" -----------------------");
			gotoxy(30,2);
			printf("|");
			gotoxy(30,3);
			printf("|");
			
			gotoxy(30,6);
			printf(" -----------------------");
			gotoxy(30,7);
			printf("|");
			gotoxy(30,8);
			printf("|");
			
			gotoxy(30,11);
			printf(" -----------------------");
			gotoxy(30,12);
			printf("|");
			gotoxy(30,13);
			printf("|");
			break;
		case 1:
			SetColor(8);
			gotoxy(2,3);
			printf(" -----------------------");
			gotoxy(2,4);
			printf("|");
			gotoxy(2,5);
			printf("|");
			
			SetColor(15);
			gotoxy(2,8);
			printf(" -----------------------");
			gotoxy(2,9);
			printf("|");
			gotoxy(2,10);
			printf("|");
									gotoxy(26,9);
									printf("|");
									gotoxy(26,10);
									printf("|");
									gotoxy(2,11);
			printf(" -----------------------");
			
			SetColor(8);
			gotoxy(30,1);
			printf(" -----------------------");
			gotoxy(30,2);
			printf("|");
			gotoxy(30,3);
			printf("|");
			
			gotoxy(30,6);
			printf(" -----------------------");
			gotoxy(30,7);
			printf("|");
			gotoxy(30,8);
			printf("|");
			
			gotoxy(30,11);
			printf(" -----------------------");
			gotoxy(30,12);
			printf("|");
			gotoxy(30,13);
			printf("|");
			break;
		case 2:
			SetColor(8);
			gotoxy(2,3);
			printf(" -----------------------");
			gotoxy(2,4);
			printf("|");
			gotoxy(2,5);
			printf("|");
			
			gotoxy(2,8);
			printf(" -----------------------");
			gotoxy(2,9);
			printf("|");
			gotoxy(2,10);
			printf("|");
			
			SetColor(15);
			gotoxy(30,1);
			printf(" -----------------------");
			gotoxy(30,2);
			printf("|");
			gotoxy(30,3);
			printf("|");
									gotoxy(54,2);
									printf("|");
									gotoxy(54,3);
									printf("|");
									gotoxy(30,4);
			printf(" -----------------------");
			
			SetColor(8);
			gotoxy(30,6);
			printf(" -----------------------");
			gotoxy(30,7);
			printf("|");
			gotoxy(30,8);
			printf("|");
			
			gotoxy(30,11);
			printf(" -----------------------");
			gotoxy(30,12);
			printf("|");
			gotoxy(30,13);
			printf("|");
			break;
		case 3:
			SetColor(8);
			gotoxy(2,3);
			printf(" -----------------------");
			gotoxy(2,4);
			printf("|");
			gotoxy(2,5);
			printf("|");
			
			gotoxy(2,8);
			printf(" -----------------------");
			gotoxy(2,9);
			printf("|");
			gotoxy(2,10);
			printf("|");
			
			gotoxy(30,1);
			printf(" -----------------------");
			gotoxy(30,2);
			printf("|");
			gotoxy(30,3);
			printf("|");
			
			SetColor(15);
			gotoxy(30,6);
			printf(" -----------------------");
			gotoxy(30,7);
			printf("|");
			gotoxy(30,8);
			printf("|");
									gotoxy(54,7);
									printf("|");
									gotoxy(54,8);
									printf("|");
									gotoxy(30,9);
			printf(" -----------------------");
			
			SetColor(8);
			gotoxy(30,11);
			printf(" -----------------------");
			gotoxy(30,12);
			printf("|");
			gotoxy(30,13);
			printf("|");	
			break;
		case 4:
			SetColor(8);
			gotoxy(2,3);
			printf(" -----------------------");
			gotoxy(2,4);
			printf("|");
			gotoxy(2,5);
			printf("|");
			
			gotoxy(2,8);
			printf(" -----------------------");
			gotoxy(2,9);
			printf("|");
			gotoxy(2,10);
			printf("|");
			
			gotoxy(30,1);
			printf(" -----------------------");
			gotoxy(30,2);
			printf("|");
			gotoxy(30,3);
			printf("|");
			
			gotoxy(30,6);
			printf(" -----------------------");
			gotoxy(30,7);
			printf("|");
			gotoxy(30,8);
			printf("|");
			
			SetColor(15);
			gotoxy(30,11);
			printf(" -----------------------");
			gotoxy(30,12);
			printf("|");
			gotoxy(30,13);
			printf("|");
			
									gotoxy(54,12);
									printf("|");
									gotoxy(54,13);
									printf("|");
									gotoxy(30,14);
			printf(" -----------------------");
			break;
	}

	for (int i = 0; i < 60; i ++){
		SetColor(15);
		gotoxy(i,15);
		printf("-");
	}
	
	gotoxy(2, 16);	printf("포켓몬을 선택하세요.");
}

double getY(double x) {
    return (-7.0 / 23.0) * x + (244.0 / 23.0);
}

void prt_ball_throw(int color){
	
	int xy_list[50][50] = {0};
	int index = 0;
    for (int x = 3; x < 25; x++) {
        double y = getY(x);
        int roundedY = (int)y;
        if (xy_list[index][1] != roundedY){
        	xy_list[++index][1] = roundedY;
			xy_list[index][0] = x;
		}
    }
    
    for (int i = 1; i < index; i ++){
    	gotoxy(xy_list[i - 1][0], xy_list[i - 1][1]);
    	printf(" ");
    	gotoxy(xy_list[i][0], xy_list[i][1]);
    	SetColor(color); 
        printf("●"); 
        Sleep(50);
	}
	gotoxy(19, 4);	printf(" ");
	gotoxy(25, 3);	printf(" ");
	gotoxy(25, 1);	printf("●");  
	
	Sleep(300);
	gotoxy(25, 1);	printf(" ");
	gotoxy(25, 3);	printf("●");
}

void clear_select_poketball_ui() {
    for (int i = 10; i >= 3; i--) {
        gotoxy(33, i);
        printf(" "); // 세로 줄 삭제
    }
    gotoxy(34, 2);
    printf("                    "); // 상단 가로줄 삭제
    gotoxy(37, 3);
    printf("                   "); // "몬스터 볼 x" 삭제
    gotoxy(37, 5);
    printf("                   "); // "슈퍼 볼 x" 삭제
    gotoxy(37, 7);
    printf("                   "); // "하이퍼 볼 x" 삭제
    gotoxy(37, 9);
    printf("                   "); // "마스터 볼 x" 삭제
}

