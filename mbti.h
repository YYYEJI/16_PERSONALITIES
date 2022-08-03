#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct st_test{
    char testername[20];
    int answer[4][8];
    int mbti_type;
};
struct st_question{
    int type; // 1~4
    char* common;
    char* q1;
    char* q2;
};
struct st_testset{
    int qcount;
    struct st_question* qlist;
};

int getMenu();
void ready(char* filename, struct st_question q[]);
void run(struct st_test* who, struct st_question q[], int num);
void eval(struct st_test* who);
void result(struct st_test* who);
void graph(int e, int s, int t, int j);
char* mbtiname(int n, int y, int mon, int d, int h, int m, int s);
void text_result();
int file_line();
int sum_e = 0, sum_s = 0, sum_t = 0, sum_j = 0;
int year, month, day, hour, min, sec;

int file_line(){
    int cnt = 0;
    char line[100];
    FILE* file;
    file = fopen("sheet.txt","r");
    while(!feof(file)){
        fgets(line, 100, file);
        cnt++;        
    }
    fclose(file);
    return cnt;
}



int getMenu(){
    int menu;
    printf("1.새 검사 2.검사 결과 3.그래프로 보기 4.결과 목록 0. 종료\n");
    printf("입력 > ");
    scanf("%d", &menu); 

    return menu;
}

void ready(char* filename, struct st_question q[]){
   	FILE* file;
	file = fopen(filename, "r");
	int qcount = 32;
	char line[200];
	for(int i=0; i<qcount; i++){
        fgets(line, 200, file);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1] = '\0';

        fgets(line, 200, file);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1] = '\0';
		q[i].common = (char*) malloc(sizeof(char)*(strlen(line)+1));
		strcpy(q[i].common, line);

		fgets(line, 200, file);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1] = '\0';
		q[i].q1 = (char*) malloc(sizeof(char)*(strlen(line)+1));
		strcpy(q[i].q1, line);

		fgets(line, 200, file);
		if(line[strlen(line)-1]=='\n')
			line[strlen(line)-1] = '\0';
		q[i].q2 = (char*) malloc(sizeof(char)*(strlen(line)+1));
		strcpy(q[i].q2, line);
	}
	fclose(file); 
}

void run(struct st_test* who, struct st_question q[], int num){
    FILE* file;
    file = fopen("sheet.txt","a");
    char name[10];
    printf("Test begins.\n");
    printf("Input your name > ");
    scanf("%s", name);
    // if(num!=1) fprintf(file, "\n%d. %s - ", num , name);
    fprintf(file, "%d. %s - ", num , name);
    num++;
    printf("Your answer is..\n\n");
    sum_e = 0, sum_s = 0, sum_t = 0, sum_j = 0;
    for(int i=0;i<32;i++){
        int row = i%4;
        int col = i/4;
        who->answer[row][col] = rand()%6;
        // printf("\n%d. %s\n",i+1, q[i].common);
        // printf("\n[5] 문장1 : %s\n", q[i].q1);
        // // printf("<4>\n");
        // // printf("<3>\n");
        // // printf("<2>\n");
        // // printf("<1>\n");
        // printf("[0] 문장2 : %s\n", q[i].q2);
        // printf("Enter 0~5 >> ");
        // scanf("%d", &(who->answer[row][col]));
        int num = who->answer[row][col];
        if(who->answer[row][col] < 0 || who->answer[row][col] > 5){
            printf("잘못 입력하셨습니다.\n\n");
            i--;
        }
        if(row==0&&who->answer[row][col] >= 0 && who->answer[row][col] <= 5) sum_e += num;
        if(row==1&&who->answer[row][col] >= 0 && who->answer[row][col] <= 5) sum_s += num;
        if(row==2&&who->answer[row][col] >= 0 && who->answer[row][col] <= 5) sum_t += num;
        if(row==3&&who->answer[row][col] >= 0 && who->answer[row][col] <= 5) sum_j += num;
        //printf("%2d", who->answer[row][col]);
       
    }
    time_t t = time(NULL);
    struct tm* time_info = localtime(&t);
    year = time_info->tm_year + 1900;    //연도에는 1900 더해줌
    month = time_info->tm_mon + 1;    // 월에는 1 더해줌
    day = time_info->tm_mday;
    hour = time_info->tm_hour;
    min = time_info->tm_min;
    sec = time_info->tm_sec;

    // printf("\n검사 시간 : %d/%d/%d \n검사 날짜 : %d:%d:%d\n\n", year, month, day, hour, min, sec);

    printf("\nTest ended.\n\n");
    fclose(file);

}

void graph(int e, int s, int t, int j){
    printf("\nMBTI GRAPH");
    // printf("\n%d", sum_e);
    printf("\n[ E ] ");
    for(int i = 0; i<40-sum_e; i++)  printf("-");
    printf("*");
    for(int i = 0; i<sum_e; i++)  printf("-");
    printf(" [ I ]");

    // printf("\n%d", sum_s);
    printf("\n[ S ] ");
    for(int i = 0; i<40-sum_s; i++)  printf("-");
    printf("*");
    for(int i = 0; i<sum_s; i++)  printf("-");
    printf(" [ N ]");
    
    // printf("\n%d", sum_t);
    printf("\n[ T ] ");
    for(int i = 0; i<40-sum_t; i++)  printf("-");
    printf("*");
    for(int i = 0; i<sum_t; i++)  printf("-");
    printf(" [ F ]");

    // printf("\n%d", sum_j);
    printf("\n[ J ] ");
    for(int i = 0; i<40-sum_j; i++)  printf("-");
    printf("*");
    for(int i = 0; i<sum_j; i++)  printf("-");
    printf(" [ P ]\n\n");
}

void eval(struct st_test* who){
    int count[4]={0};
    int type=0;
    for(int i=0;i<32;i++){
        int row = i%4;
        int col = i/4;
        count[row] += who->answer[row][col];
    }
    for(int i=0; i<4; i++) 
        if(count[i]>=20)
            type +=  1<<i;
    printf("\nType : %d\n", type);
    who->mbti_type = type;
}
void result(struct st_test* who){
    char type[10];
    char line[100];
    char mbti_name[10];

    strcpy(mbti_name, mbtiname(who->mbti_type, year, month, day, hour, min, sec));
    strcpy(type, mbti_name);
    strcat(type, ".txt");
    FILE* file = fopen(type, "r");
    printf("You are < %s >.\n", mbti_name);
    while(!feof(file)){
        fgets(line, 100, file);
        printf("%s", line);
    }
    printf("\n\n");
}
char* mbtiname(int n, int y, int mon, int d, int h, int m, int s){
    FILE* file;
    file = fopen("sheet.txt", "a");
    char* name = (char*)malloc(sizeof(char)*5);
    if(n & (1<<3)) name[0]='E'; else name[0]='I'; 
    if(n & (1<<2)) name[1]='S'; else name[1]='N'; 
    if(n & (1<<1)) name[2]='T'; else name[2]='F'; 
    if(n & (1<<0)) name[3]='J'; else name[3]='P'; 
    name[4] = '\0';
  

    fprintf(file, "%s ", name);
    fprintf(file,"[%d-%d-%d %d:%d:%d]\n", year, month, day, hour, min, sec);
    fclose(file);  
    return name;

}
void text_result(){
    FILE* file;
    char line[100];

    file = fopen("sheet.txt","r");
    while(!feof(file)){
        if(fgets(line, 100, file)==NULL) break;
        printf("%s", line);
    }
    fclose(file);
    printf("\n");
}