const int SPEED_BUTTON_PIN = 1;
const int PATTERN_BUTTON_PIN = 2;
const int LED_PINS[4] = {3, 4, 5, 6};

int speedIndex = 0;
int sequencerSpeed[3] = {500, 1000, 2000};
int sequenceIndex = 2;
int patternIndex = 0;
int sequencerData[4][4][4] =                          // Max 4 different patterns per sequence
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
  Serial.begin(9600);

  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  pinMode(PATTERN_BUTTON_PIN, INPUT);
  pinMode(SPEED_BUTTON_PIN, INPUT);
}

void loop() {
  if (digitalRead(SPEED_BUTTON_PIN == HIGH)) {
    changeSpeed();
  }

  if (digitalRead(PATTERN_BUTTON_PIN == HIGH)) {
    changeSequence();
  }

  sequencer();

  delay(sequencerSpeed[speedIndex]);
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

