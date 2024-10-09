#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

int32_t is_ascii(char str[]){
    int32_t k = 1;
    for(int i = 0; i<strlen(str); i++){
        if(str[i]>127||str[i]<0){
            k = 0;
        }
    }
    return k;
}

int32_t capitalize_ascii(char str[]){
    int32_t counter = 0;
    for(int i = 0; i< strlen(str); i++){
        if(str[i]>=97&&str[i]<=122){
            str[i] = str[i]-32;
            counter++;
        }
    }
    return counter;
}

int32_t width_from_start_byte(char start_byte){
    if(start_byte<128&&start_byte>0){
        return 1;
    }
    if((start_byte&0b11100000)==0b11000000){
        return 2;
    }
    if((start_byte&0b11110000)==0b11100000){
        return 3;
    }
    if((start_byte&0b11111000)==0b11110000){
        return 4;
    }
    return -1;
}

int32_t utf8_strlen(char str[]){
    int a=0;
    int i=0;
    while(i<strlen(str)){
        if(str[i]==-1){
            return -1;
        }
        i+=width_from_start_byte(str[i]);
        a++;
    }
    return a;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi){
    int32_t c = 0;
    int i = 0;
    while (i<cpi){
        if(utf8_strlen(str)==-1){
            return -1;
        }
        c += width_from_start_byte(str[c]);
        i++;
    }
    return c;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[]){
    if(cpi_end<cpi_start||cpi_end<0||cpi_start<0){
        return;
    }
    int32_t bi_start = codepoint_index_to_byte_index(str,cpi_start);
    int32_t bi_end = codepoint_index_to_byte_index(str,cpi_end-1)+width_from_start_byte(str[codepoint_index_to_byte_index(str,cpi_end-1)])-1;
    for(int i=0;i<bi_end-bi_start+1;i++){
        result[i]=str[i+bi_start];
    }
    result[bi_end-bi_start+1]= 0;
}
int convert_to_decimal(char k){
    if(width_from_start_byte(k)==1){
        return k&0b11111111;
    }else if(width_from_start_byte(k)==2){
        return k&0b00011111;
    }else if(width_from_start_byte(k)==3){
        return k&0b00001111;
    }else if(width_from_start_byte(k)==4){
        return k&0b00000111;
    }
    return  k&0b00111111;
}
int32_t codepoint_at(char str[], int32_t cpi){
    int a = codepoint_index_to_byte_index(str,cpi);
    int b = width_from_start_byte(str[a]);
    int c = 0;
    for (int i = 0; i<b; i++){
        int k = convert_to_decimal(str[a+i]);
        c+= convert_to_decimal(str[a+i])*pow(64, b-1-i);
    }
    return c;
}

char is_animal_emoji_at(char str[], int32_t cpi){
    int a = codepoint_at(str,cpi);
    if(a>127999&&a<128064){
        return 1;
    }else if (a>129407&&a<129455){
        return 1;
    }
    return 0;
}

int main(){
    //printf("%d",is_ascii("😸"));
    //printf("%d",is_ascii("a?b"));
    //char str[] = "a?😸b";
    //int reg = capitalize_ascii(str);
    //printf("%d",reg);
    //puts(str);
    char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 },   é is start byte + 1 cont. byte
    printf("Width: %d bytes\n", width_from_start_byte(s[1])); // start byte 0xC3 indicates 2-byte sequence
    printf("Width: %d bytes\n", width_from_start_byte(s[2]));
    char str[] = "Joséph";
    int32_t a = utf8_strlen(str);
    printf("Length of string Joséph is %d\n", a);  // 6 codepoints, (even though 7 bytes)
    int32_t idx = 3;
    printf("Codepoint index 4 is byte index %d\n", codepoint_index_to_byte_index("Joséph", idx));
    char result[17];
    utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result);
    printf("nSubstring: %s ", result); // these emoji are 4 bytes long
    printf("Codepoint at %d in %s is %d\n", idx, str, codepoint_at(str, idx));
    
}
