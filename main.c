#include <stdio.h>
#include "pico/stdlib.h"
#include <time.h>
#include "includes/seven_segment.h"
#include <string.h>

#define BUTTON_PIN 16
#define LED_PIN 15

#define DELAY_TIME 300


void out(char morse_code[5]);

char morse_code[5] = "";
char dot = '.';
char dash = '-';

void displayCharacter(char character) {
    // Call the appropriate function to display the character on the seven-segment display
    if (character == '.') {
        seven_segment_show(27);  // Display dot
    } else if (character == '-') {
        seven_segment_show(26);  // Display dash (middle segment)
    } else if (character == 't') {
        seven_segment_show(19);
    } else if (character == 'E') {
        seven_segment_show(4);
    }
}


void out(char morse_code[5]){
    bool error = true;
    if (strcmp(morse_code, ".-") == 0){
        printf("A");
        seven_segment_show(0);
        error = false;
    }
    if (strcmp(morse_code, "-...") == 0){
        printf("B");
        seven_segment_show(1);
        error = false;

    }
        if (strcmp(morse_code, "-.-.") == 0){
        printf("C");
        seven_segment_show(2);
        error = false;

    }
    if (strcmp(morse_code, "-..") == 0){
        printf("D");
        seven_segment_show(3);
        error = false;

}
if (strcmp(morse_code, ".") == 0){
        printf("E");
        seven_segment_show(4);
        error = false;

}
if (strcmp(morse_code, "..-.") == 0){
        printf("F");
        seven_segment_show(5);
        error = false;

}
if (strcmp(morse_code, "--.") == 0){
        printf("G");
        seven_segment_show(6);
        error = false;

}
if (strcmp(morse_code, "....") == 0){
        printf("H");
        seven_segment_show(7);
        error = false;

}
if (strcmp(morse_code, "..") == 0){
        printf("I");
        seven_segment_show(8);
        error = false;

}
if (strcmp(morse_code, ".---") == 0){
        printf("J");
        seven_segment_show(9);
        error = false;

}
if (strcmp(morse_code, "-.-") == 0){
        printf("K");
        seven_segment_show(10);
        error = false;

}
if (strcmp(morse_code, ".-..") == 0){
        printf("L");
        seven_segment_show(11);
        error = false;

}
if (strcmp(morse_code, "--") == 0){
        printf("M");
        seven_segment_show(12);
        error = false;

}
if (strcmp(morse_code, "-.") == 0){
        printf("N");
        seven_segment_show(13);
        error = false;

}
if (strcmp(morse_code, "---") == 0){
        printf("O");
        seven_segment_show(14);
        error = false;

}
if (strcmp(morse_code, ".--.") == 0){
        printf("P");
        seven_segment_show(15);
        error = false;

}
if (strcmp(morse_code, "--.-") == 0){
        printf("Q");
        seven_segment_show(16);
        error = false;

}
if (strcmp(morse_code, ".-.") == 0){
        printf("R");
        seven_segment_show(17);
        error = false;

}
if (strcmp(morse_code, "...") == 0){
        printf("S");
        seven_segment_show(18);
        error = false;

}
if (strcmp(morse_code, "-") == 0){
        printf("T");
        seven_segment_show(19);
        error = false;

}
if (strcmp(morse_code, "..-") == 0){
        printf("U");
        seven_segment_show(20);
        error = false;

}
if (strcmp(morse_code, "...-") == 0){
        printf("V");
        seven_segment_show(21);
        error = false;
}
if (strcmp(morse_code, ".--") == 0){
        printf("W");
        seven_segment_show(22);
        error = false;
}
if (strcmp(morse_code, "-..-") == 0){
        printf("X");
        seven_segment_show(23);
        error = false;
}
if (strcmp(morse_code, "-.--") == 0){
        printf("Y");
        seven_segment_show(24);
        error = false;
}
if (strcmp(morse_code, "--..") == 0){
        printf("Z");
        seven_segment_show(25);
        error = false;
}
if (error){
    printf("Input Not Recognised");
    seven_segment_show(27);
}
}

int main() {
    stdio_init_all();
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    gpio_pull_down(BUTTON_PIN); //pull down the button pin towards ground

    // Initialise the seven segment display.
    seven_segment_init();

    // Turn the seven segment display off when the program starts.
    seven_segment_off();

    uint32_t pressed_start_time = 0;
    bool printed_long_press_message = false;

    // Print welcome message
    printf("Welcome to the program!\n");

    // Display dash and toggle the middle segment
    displayCharacter('-');
    sleep_ms(600);
    seven_segment_show(26);
    sleep_ms(600);
    seven_segment_off();
    double current_time_1;
    double current_time_2;

    while (true) {
        if (gpio_get(BUTTON_PIN)) {
            seven_segment_off();
            double current_time = to_ms_since_boot(get_absolute_time());
            bool a = gpio_get(BUTTON_PIN);
            while(a){
                a = gpio_get(BUTTON_PIN);
                seven_segment_show(26);
            }
            seven_segment_off();
            pressed_start_time = to_ms_since_boot(get_absolute_time());
            double duration = pressed_start_time - current_time;


            current_time_1 = to_ms_since_boot(get_absolute_time());


            if(duration < 250){
                strncat(morse_code, &dot, 1);
                printf("%s \n", morse_code);
            }
            if(duration > 250){
                strncat(morse_code, &dash, 1);
                printf("%s \n", morse_code);
            }
            if (duration > 700) {
                printf("ERROR: Pressed for too long");
                strcpy(morse_code, "");
                seven_segment_show(27);
            }
            // do an if statement if it is greater than 700
            // if it is greater printf ERRP
            // reset otupit
        }


        double current_time_2 = to_ms_since_boot(get_absolute_time());


        double duration_2 = current_time_2 - current_time_1;

        //printf("%lf \n", duration_2);

        if(duration_2 > 700 && morse_code[0] != '\0') {
            out(morse_code);
            strcpy(morse_code, ""); //reset string
        }
        sleep_ms(20);

    }
}