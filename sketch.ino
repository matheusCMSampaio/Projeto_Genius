String recebido;
String sequenciaNumerica = "";
long SERIAL_TIMEOUT = 6000;

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
      recebido = "";
      sequenciaNumerica = "";
      geraSequencia(400, 2);
      leBotao();
      SERIAL_TIMEOUT = 6000;
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
  
}

void leBotao(){
  long startTime = millis();
  Serial.println(millis());
  while (millis() - startTime < SERIAL_TIMEOUT){

    if (digitalRead(botaoVerde) == LOW) {
      delay(100); 
      if (digitalRead(botaoVerde) == LOW) {
        recebido += "3";
        acendeLed(8);
        //delay(100); 
        SERIAL_TIMEOUT += 5000;
        if(verificaRecebido(recebido)){
          stateGame = START_GAME;
          break;
        }
      }
    }
    else if (digitalRead(botaoAmarelo) == LOW) {
      delay(100); 
      if (digitalRead(botaoAmarelo) == LOW) {
        recebido += "1";  
        acendeLed(6);
        //delay(100); 

        SERIAL_TIMEOUT += 5000;
        if(verificaRecebido(recebido)){
          stateGame = START_GAME;
          break;
        }
      }
    }

    if (digitalRead(botaoAzul) == LOW) {
      delay(100); 
      if (digitalRead(botaoAzul) == LOW) {
        recebido += "2";
        acendeLed(7);  
        //delay(100); 
        SERIAL_TIMEOUT += 5000;
        if(verificaRecebido(recebido)){
          stateGame = START_GAME;
          break;
        }
      }
    }else if (digitalRead(botaoVermelho) == LOW) {
      delay(100); 
      if (digitalRead(botaoVermelho) == LOW) {
        recebido += "4";
        acendeLed(9);
        SERIAL_TIMEOUT += 5000;
        if(verificaRecebido(recebido)){
          stateGame = START_GAME;
          break;
        }
      }
    }
    if (millis() - startTime >= SERIAL_TIMEOUT) {
      break;
    }
    Serial.println("Recebido: "+recebido);
  }
}

boolean verificaRecebido(String recebido){
  if(recebido.equals(sequenciaNumerica)){
    return true;
  }else{
    return false;
  }
}

void acendeLed(int led){
  digitalWrite(LED_PINS[led], HIGH);
  delay(50);
  digitalWrite(LED_PINS[led], LOW);

} 
