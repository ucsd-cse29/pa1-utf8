#include <stdio.h>
#include <stdint.h>
#include <string.h>

int32_t is_ascii(char str[])
{
    for (int i = 0; str[i] != 0; i++)
    {
        if ((unsigned char)str[i] > 0b01111111)
        {
            return 0;
        }
    }

    return 1;
}

int32_t capitalize_ascii(char str[])
{
    int changed_str_num = 0;
    for (int i = 0; str[i] != 0; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = str[i] - 32;
            changed_str_num = changed_str_num + 1;
        }
    }

    return changed_str_num;
}

int32_t width_from_start_byte(char start_byte)
{
    unsigned char byte = (unsigned char)start_byte;

    if ((byte & 0b10000000) == 0) {
        return 1; // ASCII
    }
    else if ((byte & 0b11100000) == 0b11000000) {
        return 2; // 2 byte
    }
    else if ((byte & 0b11110000) == 0b11100000) {
        return 3; // 3 byte
    }
    else if ((byte & 0b11111000) == 0b11110000) {
        return 4; // 4 byte
    }
    return -1; 
}

int32_t utf8_strlen(char str[])
{
    int counter = 0;

    for (int i = 0; str[i] != 0;)
    {
        // not a coutinuation byte
        int width = width_from_start_byte(str[i]);
        if (width == -1)
        {
            return -1;
            
        }
        counter = counter + 1;
        i =  i+ width;
           
    }

    return counter;
}

int32_t codepoint_index_to_byte_index(char str[], int32_t cpi)
{
    int cp_index = 0;
    int byte_index = 0;

    while (str[byte_index] != '\0')
    {
        int width = width_from_start_byte(str[byte_index]);

        if (width == -1)
        {
            return -1;
        }

        else if (cp_index == cpi)
        {
            return byte_index;
        }

        byte_index = width + byte_index;
        cp_index = cp_index + 1;
    }

    return -1;
}

void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[])
{
    int result_index = 0;
    int cp_index = 0;

    if (cpi_start >= cpi_end || cpi_end == 0 )
    {
        result[0] = '\0';
        return;
    }

    else
    {
        int byte_start = codepoint_index_to_byte_index(str, cpi_start);
        int byte_end = codepoint_index_to_byte_index(str, cpi_end);
        printf("%d, %d", byte_start, byte_end);
        for (int i = byte_start; i < byte_end; i++)
        {
            result[result_index] = str[i];
            result_index = result_index + 1;
        }
    }

     result[result_index] = '\0';
}


int32_t codepoint_at(char str[], int32_t cpi)
{

    
    int byte_index = codepoint_index_to_byte_index(str, cpi);
    
    if (byte_index == -1) {
        return -1; 
    }

    
    unsigned char byte = (unsigned char)str[byte_index];

    
    int width = width_from_start_byte(str[byte_index]);
    
    if (width == -1) {
        return -1; 
    }

    // Decode the UTF-8 codepoint based on its width (1 to 4 bytes)
    int codepoint = 0;
    
    if (width == 1) {
        // 1-byte (ASCII) character
        codepoint = byte;
    } 
    else if (width == 2) {
        // 2-byte 
        codepoint = ((byte & 0b00011111) * 64 + (str[byte_index + 1] & 0b00111111));
    } 
    else if (width == 3) {
        // 3-byte 
        codepoint = ((byte & 0b00001111) * 4096 + 
                    (str[byte_index + 1] & 0b00111111) * 64 +
                    (str[byte_index + 2] & 0b00111111));
    } 
    else if (width == 4) {
        // 4-byte 
        codepoint = ((byte & 0b00000111) * 262144 +  
                    (str[byte_index + 1] & 0b00111111) * 4096 +
                    (str[byte_index + 2] & 0b00111111) * 64 + 
                    (str[byte_index + 3] & 0b00111111));
    }

    return codepoint;

}

// question
// Get help from the tutor
char is_animal_emoji_at(char str[], int32_t cpi)
{
    int num = codepoint_at(str, cpi);

    if ((num >= 0x1F400 && num <= 0x1F43F) 
    || (num >= 0x1F980 && num <= 0x1F9AE))
    {
        
        return 1;
    }

    return 0;
}

int main()
{
       
    char buffer[50];
    printf("Enter a UTF-8 encoded string: ");
    fgets(buffer, 50, stdin);

    //valid ascii
    int ascii_valid = is_ascii(buffer);
    printf("Valid ASCII: %s \n", ascii_valid ? "true" : "false");


    //uppercase ascii
    //can't use strcpy because the buffer is not all ascii
    char copy_buffer[50];
    for (int i = 0; buffer[i] != 0; i++){
        if (buffer[i] >= 'a' && buffer[i] <= 'z'){
            copy_buffer[i] = buffer[i] - 32;    
        }

        else{
            copy_buffer[i] = buffer[i];
        }

    }
    
    printf("Uppercased ASCII: %s", copy_buffer);

    int length = 0;
    for (int i = 0; buffer[i] != 0; ){
        int width = width_from_start_byte(buffer[i]);
        length = length + width;
        i = i + width;
    }
    printf("Length in bytes: %d\n", length);
    printf("Number of code points: %d\n", utf8_strlen(buffer));

    //byte per code point
    printf("Bytes per code point: ");
    for (int i = 0; buffer[i] != 0;)
    {
        int width = width_from_start_byte(buffer[i]);
        if (width == -1)
        {
            printf("Error in string.\n");
            return -1;
        }
        printf("%d ", width);
        i = i + width;
    }
    printf("\n");

    //substring
    //careful for the range 
    //get help from the tutor
    char result[50];
    utf8_substring(buffer, 0, 6, result);
    printf("Substring of the first 6 code points: %s\n", result);

    //code point as decimal numbers
    printf("Code points as decimal numbers: ");
    int cp_index = 0;
    for (int i = 0; buffer[i] != 0;)
    {
        int width = width_from_start_byte(buffer[i]);
        if (width == -1)
        {
            printf("Error in string.\n");
            return -1;
        }
        
        printf("%d ", codepoint_at(buffer, cp_index));
        i += width;
        cp_index = cp_index + 1;
    }
    printf("\n");


    //is animal emoji
    // have to use the byte index to print, NOT the CODEPOINT
    printf("Animal emojis: ");
    int cp_index_2 = 0;
    for (int i = 0; buffer[i] != 0;)
    {
        int width = width_from_start_byte(buffer[i]);

        if (width == -1)
        {
            printf("Error in string.\n");
            return -1;
        }
        if (is_animal_emoji_at(buffer, cp_index_2) == 1)
        {
            // Find the byte index of the current codepoint
            int byte_index = codepoint_index_to_byte_index(buffer, cp_index_2);

            // print multiple byte of the emoji
            for (int j = 0; j < width; j++)
            {
                printf("%c", buffer[byte_index + j]);
            }

            
        }
        
        i += width;
        cp_index_2 = cp_index_2 + 1;
    }

    

    return 0;

    // Enter a UTF-8 encoded string: My 🐩’s name is Erdős.
    // Valid ASCII: false
    // Uppercased ASCII: "MY 🐩’S NAME IS ERDőS."
    // Length in bytes: 27
    // Number of code points: 21
    // Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
    // Substring of the first 6 code points: "My 🐩’s"
    // Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
    // Animal emojis: 🐩
}