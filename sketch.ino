String recebido;
String sequenciaNumerica = "";
const long SERIAL_TIMEOUT = 10000;

enum GameState {
  START_GAME,
  PLAY_GAME,
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
  
  pinMode(botaoVerde, INPUT_PULLUP);
  pinMode(botaoAmarelo, INPUT_PULLUP);
  pinMode(botaoAzul, INPUT_PULLUP);
  pinMode(botaoVermelho, INPUT_PULLUP);
  
  Serial.begin(9600);
}

void piscaled(int vezes) {
  for (int i = 0; i < vezes; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(LED_PINS[j], HIGH);
      delay(150);
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
          piscaled(4);
          stateGame = PLAY_GAME;
          delay(1000);
        }
      }
      break;
    case PLAY_GAME:
      geraSequencia(400, 2);
      leBotao();
      break;

  }
}


void geraSequencia (int tempo, int sequencia){
  int ordemLeds[sequencia];

  for (int i = 0; i < sequencia; i++){
    ordemLeds[i] = random(1, NUM_LEDS + 1);
  }

  sequenciaNumerica = "";

  for (int j = 0; j < sequencia; j++){
    int ledIndex = ordemLeds[j] - 1;
    
    digitalWrite(LED_PINS[ledIndex], HIGH);
    delay(tempo);
    digitalWrite(LED_PINS[ledIndex], LOW);
    delay(tempo);
    sequenciaNumerica += String(ordemLeds[j]);
  }
  Serial.println(sequenciaNumerica);
  delay(5000);
}

void leBotao(){
  
  long startTime = millis();
  while (millis() - startTime < SERIAL_TIMEOUT){
    if (digitalRead(botaoVerde) == LOW) {
      delay(50); 
      if (digitalRead(botaoVerde) == LOW) {
        recebido += "1";  
         
      }
    }
    else if (digitalRead(botaoAmarelo) == LOW) {
      delay(50); 
      if (digitalRead(botaoAmarelo) == LOW) {
        recebido += "2";  
        
      }
    }
    else if (digitalRead(botaoAzul) == LOW) {
      delay(50); 
      if (digitalRead(botaoAzul) == LOW) {
        recebido += "3";  
        
      }
    }
    else if (digitalRead(botaoVermelho) == LOW) {
      delay(50); // debounce
      if (digitalRead(botaoVermelho) == LOW) {
        recebido += "4";  
      }
    }
    if (millis() - startTime >= SERIAL_TIMEOUT) {
      break;
    }
  }

  Serial.println(recebido);
}
