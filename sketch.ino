enum GameState {
  START_GAME,
  LEVEL_1,
  LEVEL_2,
  GAME_OVER,
  PLAY_AGAIN
};

GameState stateGame = START_GAME;

const int LED_PINS[] = {6, 7, 8, 9};
const int NUM_LEDS = sizeof(LED_PINS) / sizeof(LED_PINS[0]);
const int botaoAmarelo = 1; 
const int botaoAzul = 2;    
const int botaoVerde = 3;  
const int botaoVermelho = 4; 

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  randomSeed(analogRead(0));
  
  // Configurando os botões como INPUT_PULLUP
  pinMode(botaoVerde, INPUT_PULLUP);
  pinMode(botaoAmarelo, INPUT_PULLUP);
  pinMode(botaoAzul, INPUT_PULLUP);
  pinMode(botaoVermelho, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void piscaled(int tempo, int vezes) {
  for (int i = 0; i < vezes; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(LED_PINS[j], HIGH);
      delay(200);
      digitalWrite(LED_PINS[j], LOW);
    }
  }
}

void loop() {
  switch (stateGame) {
    case START_GAME:
      
      if (digitalRead(botaoVerde) == LOW || digitalRead(botaoVermelho) == LOW || 
          digitalRead(botaoAzul) == LOW || digitalRead(botaoAmarelo) == LOW) {
        delay(50); 
        if (digitalRead(botaoVerde) == LOW || digitalRead(botaoVermelho) == LOW || 
            digitalRead(botaoAzul) == LOW || digitalRead(botaoAmarelo) == LOW) {
          piscaled(200, 5);
          delay(1000);
        }
      }
      break;

    
  }
}
