#include "mbti.h"

int main(){
    struct st_test tester;
    struct st_question qlist[32];
    //질문 준비
    int menu, quit = 0, tested = 0, tcount = 0;
    int sheet_num = 1;

    while(quit == 0){
        // 1.새 검사 2.검사 결과 3.그래프로 보기 4.결과 목록 0. 종료
        menu = getMenu();
        switch(menu){ 
            case(1):
                sheet_num = file_line();
                printf("%d\n", sheet_num);
                ready("qlist.txt", qlist); //질문 진행
                run(&tester, qlist, sheet_num); // parameter : questionlist, answerarray //결과 분석
                break;
            case(2):
                eval(&tester); // parameter : answerarray, return : type //결과 제시
                result(&tester); // parameter : mbtitype
                break;
            case(3):
                graph(sum_e, sum_s, sum_t, sum_j);
                break;
            case(4):
                text_result();
                break;
        }
        if(menu == 0) break;
    }
    return 0;
}