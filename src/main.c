#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

// 회로 로직을 거치는 함수 
void logic(int A, int B, int C, int D, char line1[], char line2[], char line3[]) {
    bool a = !(!A && !C && !(B && D) && !(!B && !D));
    bool b = !(!A && B && (C ^ D));
    bool c = !(!(A) && !(B) && C && !(D));
    bool d = A || (C && !B) || (C && !D) || (!B && !D) || (B && D && !C);
    bool e = (A && B) || (A && C) || (C && !D) || (!B && !D);
    bool f = !(!A && !B && (C || D));
    bool g = A || (B && !C) || (C && !B) || (C && !D);

    // Build each line as a string
    line1[0] = ' '; 
    line1[1] = a ? '_' : ' ';
    line1[2] = ' ';
    line1[3] = '\0';
    line2[0] = f ? '|' : ' ';
    line2[1] = g ? '_' : ' ';
    line2[2] = b ? '|' : ' ';
    line2[3] = '\0';
    line3[0] = e ? '|' : ' ';
    line3[1] = d ? '_' : ' ';
    line3[2] = c ? '|' : ' ';
    line3[3] = '\0';
}


// 받아온 시간 데이터를 한글자씩 분리하여 각각 2진수로 변환( int -> char -> bool )
void sep_hextobin(int hour, int min, int sec) {
    
    char hour_str[4];
    char min_str[4];
    char sec_str[4];
    snprintf(hour_str, sizeof(hour_str), "%02d", hour);
    snprintf(min_str, sizeof(min_str), "%02d", min);
    snprintf(sec_str, sizeof(sec_str), "%02d", sec);
    bool hour1[4], hour2[4], min1[4], min2[4], sec1[4], sec2[4];

    int j = 3;
    for (int i = 0; i < 4; i++, j--) {
        hour1[i] = ((hour_str[0] - '0') >> j) & 1;
        hour2[i] = ((hour_str[1] - '0') >> j) & 1;
        min1[i] = ((min_str[0] - '0') >> j) & 1;
        min2[i] = ((min_str[1] - '0') >> j) & 1;
        sec1[i] = ((sec_str[0] - '0') >> j) & 1;
        sec2[i] = ((sec_str[1] - '0') >> j) & 1;
    }

    char line1[4], line2[4], line3[4];

    for (int i = 0; i < 3; i++) {
        logic(hour1[0], hour1[1], hour1[2], hour1[3], line1, line2, line3);
        printf("%s ", (i == 0 ? line1 : (i == 1 ? line2 : line3)));

        logic(hour2[0], hour2[1], hour2[2], hour2[3], line1, line2, line3);
        printf("%s ", (i == 0 ? line1 : (i == 1 ? line2 : line3)));

        printf("  ");

        logic(min1[0], min1[1], min1[2], min1[3], line1, line2, line3);
        printf("%s ", (i == 0 ? line1 : (i == 1 ? line2 : line3)));

        logic(min2[0], min2[1], min2[2], min2[3], line1, line2, line3);
        printf("%s ", (i == 0 ? line1 : (i == 1 ? line2 : line3)));

        printf("  ");

        logic(sec1[0], sec1[1], sec1[2], sec1[3], line1, line2, line3);
        printf("%s ", (i == 0 ? line1 : (i == 1 ? line2 : line3)));

        logic(sec2[0], sec2[1], sec2[2], sec2[3], line1, line2, line3);
        printf("%s\n", (i == 0 ? line1 : (i == 1 ? line2 : line3)));
    }
}

int main() {
    int hour, min, sec;
    int t_hour = 0; 
    int t_min = 0;
    int t_sec = 0;
    #ifdef _WIN32
        system("cls");   // Windows의 경우 콘솔 지우기
    #else
        system("clear"); // macOS와 Linux의 경우 콘솔 지우기
    #endif
    while(true) {   
        time_t currentTime;
        struct tm *localTime;

        time(&currentTime);
        localTime = localtime(&currentTime);

        hour = localTime->tm_hour;
        min = localTime->tm_min;
        sec = localTime->tm_sec;
        t_sec++;
        if (t_sec >= 60) {
            t_sec -= 60;
            t_min++;
        }
        if (t_min >= 60) {
            t_min -= 60;
            t_hour++;
        }
        printf("Current Time: %02d:%02d:%02d\n", hour, min, sec);
        sep_hextobin(hour, min, sec);
        printf("\n");
        printf("Timer : %02d:%02d:%02d\n", t_hour, t_min, t_sec);
        sep_hextobin(t_hour, t_min, t_sec);
        sleep(1);
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    return 0;
}