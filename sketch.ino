enum GameState {
  START_GAME,
  LEVEL_1,
  LEVEL_2,
  GAME_OVER,
  PLAY_AGAIN
};

GameState stateGame = START_GAME;

const int LED_PINS[] = {6,7,8,9};
const int NUM_LEDS = sizeof(LED_PINS) / sizeof(LED_PINS[0]);
int botaoAmarelo = 1;
int botaoAzul = 2;
int botaoVerde = 3;
int botaoVermelho = 4;

void setup() {
  for(int i = 0; i < NUM_LEDS; i++){
    pinMode(LED_PINS[i], OUTPUT);
  }
  randomSeed(analogRead(0));
  pinMode(botaoVerde, INPUT);
  pinMode(botaoAmarelo, INPUT);
  pinMode(botaoAzul, INPUT);
  pinMode(botaoVermelho, INPUT);
  Serial.begin(9600);
}




void piscaled(int tempo, int vezes){
  for(int i = 0; i < vezes; i++){
    for(int j = 0; j < NUM_LEDS; j++){
      digitalWrite(LED_PINS[j], HIGH);
    }
    delay(tempo);
    for(int j = 0; j < NUM_LEDS; j++){
      digitalWrite(LED_PINS[j], LOW);
    }
    delay(tempo);
  }
}

void loop() {
  switch(stateGame){
    case START_GAME:
      int num = iniciar();
      Serial.println(num);
      stateGame = LEVEL_1;
  }
}

int iniciar() {
  int aux = 0;
  bool estadoBotaoVerdeAtual = LOW;
  bool estadoBotaoVerdeAnterior = LOW;

  Serial.println("Está no iniciar");

  // Enquanto o botão vermelho não for pressionado, fique no loop
  while (digitalRead(botaoVermelho) == LOW) {
    Serial.println("Chegou");

    digitalWrite(LED_PINS[aux], HIGH);

    estadoBotaoVerdeAtual = digitalRead(botaoVerde);
    if (estadoBotaoVerdeAtual == HIGH && estadoBotaoVerdeAnterior == LOW) {
      digitalWrite(LED_PINS[aux], LOW);

      aux++;
      if (aux >= NUM_LEDS) {
        aux = 0;
      }

    
      digitalWrite(LED_PINS[aux], HIGH);

      
      delay(300);
    }

    // Atualiza o estado anterior do botão
    estadoBotaoVerdeAnterior = estadoBotaoVerdeAtual;
  }

  return aux;
}
