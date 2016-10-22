#ifndef IOPINS_H
#define IOPINS_H
  // pin configurations for the different inputs/outpus

  // MAXIM pin configuraitons
  const int W_DATA_PIN = 12;
  const int W_CS_PIN = 11;
  const int W_CLOCK_PIN = 10;

  const int G_DATA_PIN = 5;
  const int G_CS_PIN = 4;
  const int G_CLOCK_PIN = 3;

  const int NUM_MAXIMS_PER_COLOUR = 1;

  // turn indicator pins
  const int PLAYER_G_INDICATOR_PIN = 0;     //Change to actual pin on arduino
  const int PLAYER_W_INDICATOR_PIN = 1;   //Change to actual pin on arduino

  // toggle/feature button
  const int START_RESET_BUTTON = 4;
  const int AI_BUTTON_PIN = 3;

  // column buttons
  const int COLUMN_BUTTON_PINS[] = {1, 2, 3, 4, 5, 6, 7};

#endif
