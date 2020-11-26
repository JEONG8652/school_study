//this code written without lcd.h
//this code non include LCD setting code(like LCD_cmd_write)

#define LINE1 0x80
#define LINE2 0xC0

void LCD_String(char *str){
    char i=0;
    for(i=0;i<16;i++){
        LCD_data_write(str[i]);
    }
}
void int2Str(char *str, int numDigit, int numValue){ //정수를 문자열에 대입하는 함수
    /*
    대입받을 문자열 str
    자릿수 numDigit (단, str의 길이보다 작거나 같아야 한다.)
    문자열로 바꿀 정수 numValue
    */
    int numDiv = 1,i,j;
    for(i=numDigit;i>0;i--){  
        for(j=i; j>1; j--)
            numDiv *= 10;
        str[numDigit - i] = (numValue/numDiv)%10 + '0';
        numDiv = 1;    
    }    
}
void LCD_addStr(char *str1,char *str2,int length_1,int length_2){ //두 개의 문자열을 순차적으로 대입해 합쳐진 문자열을 출력하는 함수
    /*
    첫 번째 문자열 str1
    두 번째 문자열 str2                
    첫 번째 문자열에서 사용할 문자의 수 length_1 (단, str1의 길이보다 작거나 같을 것)
    두 번째 문자열에서 사용할 문자의 수 length_2 (단, str2의 길이보다 작거나 같을 것)
    */ 
    char result[16];
    int i = 0, j = 0;
    for (i=0;i<length_1;i++){ //첫 번째 문자열을 length_1만큼 대입
        result[i] = str1[j];
        j++;
    } 
    j=0;
    for (i;i<length_2+length_1;i++){ //두 번째 문자열을 length_2만큼 대입
        result[i] = str2[j];
        j++;
    }
    if(i<16){
        for(i;i<16;i++){ 
            result[i] = ' '; //만약 문자열의 길이가 16이 되지 않았다면 나머지 공간을 공백기호로 대입
        }
    }
    LCD_String(result); // 합쳐진 문자열을 LCD에 출력
}


void main(){ //사용예시
    //이곳에 lcd setting 코드를 작성하시오
    int count1 = 30;
    int count2 = 130;
    char count_arr[3];
    LCD_cmd_write(LINE1);                       //LCD에 내용이 작성되기전 첫번째 행에 작성 될 건지 결정
    int2Str(count_arr,3,count1);                //count_arr배열에 "030"이 저장됨
    LCD_addStr("count1 = ",count_arr,9,3);      //LCD 첫번째 ROW에 "count1 = 030"이 출력됨
    LCD_cmd_write(LINE2);                       //LCD에 내용이 작성되기전 두번째 행에 작성 될 건지 결정
    int2Str(count_arr,3,count2);                //count_arr배열에 "130"이 저장됨
    LCD_addStr("count2 = ",count_arr,7,3);      //LCD 두번째 ROW에 "count2 130"이 출력됨
}
