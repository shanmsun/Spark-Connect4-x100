#ifndef IOPINS_H
#define IOPINS_H
// pin configurations for the different inputs/outpus

// MAXIM pin configuraitons
const int W_DATA_PIN = 8;
const int W_CS_PIN = 10;
const int W_CLOCK_PIN = 9;

const int G_DATA_PIN = 5;
const int G_CS_PIN = 7;
const int G_CLOCK_PIN = 6;

const int NUM_MAXIMS_PER_COLOUR = 1;

// turn indicator pins
const int PLAYER_G_INDICATOR_PIN = 49;     //Change to actual pin on arduino
const int PLAYER_W_INDICATOR_PIN = 53;   //Change to actual pin on arduino

// toggle/feature button
const int START_RESET_BUTTON = 12;
const int AI_BUTTON_PIN = 3;

// column buttons
const int COLUMN_BUTTON_PINS[] = {22, 24, 26, 28, 30, 32, 34};
// const int COLUMN_BUTTON_PINS[] = {17, 19, 21, 23, 25, 27, 29};


#endif
