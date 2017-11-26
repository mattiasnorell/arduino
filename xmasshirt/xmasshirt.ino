const int SPEED_BUTTON_PIN = 1;
const int PATTERN_BUTTON_PIN = 2;
const int LED_PINS[4] = {3, 4, 5, 6};

bool isSpeedButtonPressed = false;
bool isPatternButtonPressed = false;

int speedIndex = 0;
int sequencerSpeed[6] = {500, 1000, 2000, 3000, 5000, 10000};
int sequenceIndex = 0;
int patternIndex = 0;
int sequencerData[8][4][12] =                          // Due to memory/stability issues max 8 sequences, 4 different patterns per sequence and 16 leds per pattern
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }, {
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 1, 0}
  }, {
    {1, 0, 0, 1},
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {0, 1, 1, 0}
  }, {
    {1, 1, 0, 1},
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 1}
  }
};

void setup() {
  int ledCount = sizeof(LED_PINS) / sizeof(int);

  for (int i = 0; i < ledCount; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  pinMode(PATTERN_BUTTON_PIN, INPUT);
  pinMode(SPEED_BUTTON_PIN, INPUT);
}

void loop() {
 

  readButtonInput();

  if(!isSpeedButtonPressed || !isPatternButtonPressed){
    sequencer();
  }

  delay(sequencerSpeed[speedIndex]);
}

void readButtonInput(){
   if (digitalRead(SPEED_BUTTON_PIN == HIGH) && !isSpeedButtonPressed) {
    isSpeedButtonPressed = true;
    changeSpeed();
  }else if(digitalRead(SPEED_BUTTON_PIN == LOW) && isSpeedButtonPressed){
    isSpeedButtonPressed = false;
  }

  if (digitalRead(PATTERN_BUTTON_PIN == HIGH) && !isPatternButtonPressed) {
    isPatternButtonPressed = true;
    changeSequence();
  }else if(digitalRead(PATTERN_BUTTON_PIN == LOW) && isPatternButtonPressed){
    isPatternButtonPressed = false;
  }
}

void changeSpeed() {
  speedIndex++;

  if (speedIndex >= sizeof(sequencerSpeed)) {
    speedIndex = 0;
  }
}

void changeSequence() {
  patternIndex = 0;
  sequenceIndex++;

  if (sequenceIndex >= sizeof(sequencerData)) {
    sequenceIndex = 0;
  }
}

void sequencer() {

  // SEQUENCE     sequencerData[sequenceIndex]
  // PATTERN      sequencerData[sequenceIndex][patternIndex]
  // LED          sequencerData[sequenceIndex][patternIndex][i]

  int arraySize = sizeof(sequencerData[sequenceIndex]) / sizeof(sequencerData[sequenceIndex][patternIndex]);

  for (int i = 0; i < arraySize; i++) {
    setLedState(i, sequencerData[sequenceIndex][patternIndex][i]);
  }

  patternIndex++;

  if (patternIndex >= arraySize) {
    patternIndex = 0;
  }
}

void setLedState(int pin, int state) {
  if (state == 1) {
    digitalWrite(pin, HIGH);
  } else {
    digitalWrite(pin, LOW);
  }
}

