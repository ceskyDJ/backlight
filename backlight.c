/**
 *  Simple program for controlling backlight of the notebook main screen
 *
 *  Make sure you execute following commands to be able to access config files as
 *  a regular user:
 *
 *  sudo su -c 'echo SUBSYSTEM==\"backlight\", RUN+=\"/bin/chmod 0666 /sys/class/backlight/%k/brightness /sys/class/backlight/%k/bl_power\" > /etc/udev/rules.d/99-backlight.rules'
 *  sudo reboot
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POWER_FILE "/sys/class/backlight/intel_backlight/bl_power"
#define POWER_ON 0
#define POWER_OFF 1

#define BRIGHTNESS_FILE "/sys/class/backlight/intel_backlight/brightness"
#define MAX_BRIGHTNESS_FILE "/sys/class/backlight/intel_backlight/max_brightness"
#define BRIGHTNESS_MIN 0
#define BRIGHTNESS_STEP 15

int usage(char *argv[]) {
    printf("Usage: %s <option>\n\n"
           "Options:\n"
           "\t- up:\t increases brightness by 10%%\n"
           "\t- down:\t decreases brightness by 10%%\n"
           "\t- max:\t sets brightness to 100%%\n"
           "\t- min:\t sets brightness to 0%%\n"
           "\t- on:\t turns the screen on\n"
           "\t- off:\t turns the screen off\n\n"
           "2015, Jakub Hladik, www.github.com/jakeh12\n"
           "2020, ceskyDJ, www.github.com/ceskyDJ"
           , argv[0]);
    
    return EXIT_FAILURE;
}

int get_brightness() {
    FILE *brightness_file;
    int brightness_value;
    
    brightness_file = fopen(BRIGHTNESS_FILE, "r");
    fscanf(brightness_file, "%d", &brightness_value);
    fclose(brightness_file);
    
    return brightness_value;
}

int get_max_brightness() {
    FILE *brightness_file;
    int brightness_value;
    
    brightness_file = fopen(MAX_BRIGHTNESS_FILE, "r");
    fscanf(brightness_file, "%d", &brightness_value);
    fclose(brightness_file);
    
    return brightness_value;
}

void set_brightness(int brightness_value) {
    int max_brightness = get_max_brightness();
    
    if (brightness_value > max_brightness) brightness_value = max_brightness;
    if (brightness_value < BRIGHTNESS_MIN) brightness_value = BRIGHTNESS_MIN;
    
    FILE *brightness_file;
    
    brightness_file = fopen(BRIGHTNESS_FILE, "w");
    fprintf(brightness_file, "%d", brightness_value);
    fclose(brightness_file);
}

int get_power() {
    FILE *power_file;
    int power_value;
    
    power_file = fopen(POWER_FILE, "r");
    fscanf(power_file, "%d", &power_value);
    fclose(power_file);
    
    return power_value;
}

void set_power(int power_value) {
    if (power_value > POWER_OFF) power_value = POWER_ON;
    if (power_value < POWER_ON) power_value = POWER_OFF;
    
    FILE *power_file;
    
    power_file = fopen(POWER_FILE, "w");
    fprintf(power_file, "%d", power_value);
    fclose(power_file);
}

int main(int argc, char *argv[]) {
    
    // check if two arguments are passed in
    if (argc != 2) return usage(argv);
    
    // check if config files exist
    FILE *brightness_file;
    FILE *power_file;
    
    power_file = fopen(POWER_FILE, "r+");
    if (power_file == NULL) {
        printf("ERROR: '%s' does not exist/insufficient permissions.\n", POWER_FILE);
        return EXIT_FAILURE;
    }
    
    brightness_file = fopen(BRIGHTNESS_FILE, "r+");
    if (brightness_file == NULL) {
        printf("ERROR: '%s' does not exist/insufficient permissions.\n", BRIGHTNESS_FILE);
        return EXIT_FAILURE;
    }
    
    // everything ok, get current values
    int brightness_value = get_brightness();
    int power_value = get_power();
    
    // process arguments
    if (strcmp(argv[1], "up") == 0) {
        brightness_value += BRIGHTNESS_STEP;
    }
    else if (strcmp(argv[1], "down") == 0) {
        brightness_value -= BRIGHTNESS_STEP;
    }
    else if (strcmp(argv[1], "max") == 0) {
        brightness_value = get_max_brightness();
    }
    else if (strcmp(argv[1], "min") == 0) {
        brightness_value = BRIGHTNESS_MIN;
    }
    else if (strcmp(argv[1], "on") == 0) {
        power_value = POWER_ON;
    }
    else if (strcmp(argv[1], "off") == 0) {
        power_value = POWER_OFF;
    }
    else {
        return usage(argv);
    }
    
    // save new values
    set_brightness(brightness_value);
    set_power(power_value);
    
    return EXIT_SUCCESS;
}
