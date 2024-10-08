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
          delay(1000);
        }
      }
      break;

    case PLAY_GAME:
      recebido = "";
      sequenciaNumerica = "";
      for(int i = 2; i< 1000; i++){
        geraSequencia(400, i);
        i++;
        leBotao();
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

void geraSequencia(int tempo, int sequencia) {
  int ordemLeds[sequencia];

  for (int i = 0; i < sequencia; i++) {
    ordemLeds[i] = random(1, NUM_LEDS + 1);
  }

  sequenciaNumerica = "";

  for (int j = 0; j < sequencia; j++) {
    int ledIndex = ordemLeds[j] - 1;
    
    digitalWrite(LED_PINS[ledIndex], HIGH);
    tocarSom(j+1);
    delay(tempo);
    digitalWrite(LED_PINS[ledIndex], LOW);
    delay(tempo);
    sequenciaNumerica += String(ordemLeds[j]);
  }
}

void leBotao() {
  long startTime = millis();
  while (millis() - startTime < SERIAL_TIMEOUT) {
    if (digitalRead(botaoVerde) == LOW) {
      delay(150);
      if (digitalRead(botaoVerde) == LOW) {
        acendeLed(2);
        tocarSom(3); 
        recebido += "3";
        SERIAL_TIMEOUT += 5000;
        if (verificaRecebido(recebido)) {
          break;
        }
      }
    } else if (digitalRead(botaoAmarelo) == LOW) {
      delay(150);
      if (digitalRead(botaoAmarelo) == LOW) {
        recebido += "1";
        acendeLed(0);
        tocarSom(1); 
        SERIAL_TIMEOUT += 5000;
        if (verificaRecebido(recebido)) {
          break;
        }
      }
    }

    if (digitalRead(botaoAzul) == LOW) {
      delay(150);
      if (digitalRead(botaoAzul) == LOW) {
        
        acendeLed(1);
        tocarSom(2);
        recebido += "2";
        SERIAL_TIMEOUT += 5000;
        if (verificaRecebido(recebido)) {
          break;
        }
      }
    } else if (digitalRead(botaoVermelho) == LOW) {
      delay(150);
      if (digitalRead(botaoVermelho) == LOW) {
        acendeLed(3);
        tocarSom(4);
        recebido += "4"; 
        SERIAL_TIMEOUT += 5000;
        if (verificaRecebido(recebido)) {
          stateGame = START_GAME;
          break;
        }
      }
    }
    if (millis() - startTime >= SERIAL_TIMEOUT) {
      break;
    }
  }
}

boolean verificaRecebido(String recebido) {
  if (recebido.equals(sequenciaNumerica)) {
    return true;
  } else {
    for (int i = 0; i < recebido.length(); i++) {
      if (recebido.charAt(i) != sequenciaNumerica.charAt(i)) {
        stateGame = GAME_OVER;
        return true;
      }
    }
    return false;
  }
}

void acendeLed(int led) {
  Serial.println(led);
  digitalWrite(LED_PINS[led], HIGH);
  Serial.println("AQUI");
  delay(100);
  digitalWrite(LED_PINS[led], LOW);
}

void tocarSom(int nota) {
  int frequencias[] = {261, 329, 392, 523, 150}; 
  if (nota >= 1 && nota <= 5) {
    tone(buzzerPin, frequencias[nota - 1], 100); 
  }
}
