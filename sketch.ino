String recebido;
String sequenciaNumerica = "";
long SERIAL_TIMEOUT = 6000;

enum GameState {
  START_GAME,
  PLAY_GAME,
  GAME_OVER
};

GameState stateGame = START_GAME;

const int LED_PINS[] = {6, 7, 8, 9};
const int NUM_LEDS = sizeof(LED_PINS) / sizeof(LED_PINS[0]);
const int botaoAmarelo = 11; 
const int botaoAzul = 2;    
const int botaoVerde = 3;  
const int botaoVermelho = 4; 
const int buzzerPin = 13;

void setup() {
  for (int i = 0; i < NUM_LEDS; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }
  randomSeed(analogRead(0));
  
  pinMode(botaoVerde, INPUT_PULLUP);
  pinMode(botaoAmarelo, INPUT_PULLUP);
  pinMode(botaoAzul, INPUT_PULLUP);
  pinMode(botaoVermelho, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.begin(9600);
}

void piscaled(int vezes) {
  for (int i = 0; i < vezes; i++) {
    for (int j = 0; j < NUM_LEDS; j++) {
      digitalWrite(LED_PINS[j], HIGH);
      tocarSom(j+1);
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
          sequenciaNumerica = ""; 
          delay(1000);
        }
      }
      break;

    case PLAY_GAME:
      recebido = "";
      mostraSequencia(); 
      leBotao();         
      if (stateGame == PLAY_GAME) {
        adicionaNovoElemento();  
      }
      SERIAL_TIMEOUT = 6000;
      break;

    case GAME_OVER:
      for (int i = 0; i < 4; i++) {
        for (int j = 0; j < NUM_LEDS; j++) {
          digitalWrite(LED_PINS[j], HIGH);
        }
        tocarSom(5);
        delay(300);
        for (int j = 0; j < NUM_LEDS; j++) {
          digitalWrite(LED_PINS[j], LOW);
        }
        delay(300);
      }

      Serial.println("GAME OVER!");
      delay(2000); 
      stateGame = START_GAME;
      break;
  }
}

void mostraSequencia() {
  for (int i = 0; i < sequenciaNumerica.length(); i++) {
    int ledIndex = sequenciaNumerica.charAt(i) - '1'; 
    digitalWrite(LED_PINS[ledIndex], HIGH);
    tocarSom(ledIndex+1);
    delay(400);
    digitalWrite(LED_PINS[ledIndex], LOW);
    delay(200);
  }
}

void adicionaNovoElemento() {
  int novoElemento = random(1, NUM_LEDS + 1);
  sequenciaNumerica += String(novoElemento);
}

void leBotao() {
  recebido = "";  
  long startTime = millis();
  int posicaoAtual = 0;

  while (millis() - startTime < SERIAL_TIMEOUT && posicaoAtual < sequenciaNumerica.length()) {
    if (digitalRead(botaoVerde) == LOW) {
      delay(150);  
      if (digitalRead(botaoVerde) == LOW) {
        acendeLed(2);
        tocarSom(3);
        recebido += "3";
        if (!verificaRecebido(posicaoAtual)) {
          stateGame = GAME_OVER; 
          return;
        }
        posicaoAtual++;
      }
    } else if (digitalRead(botaoAmarelo) == LOW) {
      delay(150);  
      if (digitalRead(botaoAmarelo) == LOW) {
        acendeLed(0);
        tocarSom(1);
        recebido += "1";
        if (!verificaRecebido(posicaoAtual)) {
          stateGame = GAME_OVER; 
          return;
        }
        posicaoAtual++;
      }
    } else if (digitalRead(botaoAzul) == LOW) {
      delay(150);  
      if (digitalRead(botaoAzul) == LOW) {
        acendeLed(1);
        tocarSom(2);
        recebido += "2";
        if (!verificaRecebido(posicaoAtual)) {
          stateGame = GAME_OVER; 
          return;
        }
        posicaoAtual++;
      }
    } else if (digitalRead(botaoVermelho) == LOW) {
      delay(150); 
      if (digitalRead(botaoVermelho) == LOW) {
        acendeLed(3);
        tocarSom(4);
        recebido += "4";
        if (!verificaRecebido(posicaoAtual)) {
          stateGame = GAME_OVER; 
          return;
        }
        posicaoAtual++;
      }
    }
  }

 
  if (posicaoAtual == sequenciaNumerica.length()) {
    Serial.println("Acertou a sequência!");
    delay(1000);
  }
}

boolean verificaRecebido(int posicaoAtual) {
  
  if (recebido.charAt(posicaoAtual) == sequenciaNumerica.charAt(posicaoAtual)) {
    return true;  
  } else {
    return false;
  }
}

void acendeLed(int led) {
  digitalWrite(LED_PINS[led], HIGH);
  delay(100);
  digitalWrite(LED_PINS[led], LOW);
}

void tocarSom(int nota) {
  int frequencias[] = {261, 329, 392, 523, 150}; 
  if (nota >= 1 && nota <= 5) {
    tone(buzzerPin, frequencias[nota - 1], 100); 
  }
}
