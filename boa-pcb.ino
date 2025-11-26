int bstart = D3;
int bhit = D4;
int bstand = D5;
int breset = D6;

int lplayer = D10;
int ldealer = D9;
int lturn = D8;
int lresult = D7;

int playertotal, dealertotal = 0;

int draw() {
  return random(1, 11);
}

void blinkScore(int led, int value) {
  int longs = value / 5;
  int shorts = value % 5;

  for (int i = 0; i < longs; i++) {
    digitalWrite(led, HIGH);
    delay(350);
    digitalWrite(led, LOW);
    delay(350);
  }

  for (int i = 0; i < shorts; i++) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
  }
}

void setup() {
  pinMode(bstart, INPUT_PULLUP);
  pinMode(bhit, INPUT_PULLUP);
  pinMode(bstand, INPUT_PULLUP);
  pinMode(breset, INPUT_PULLUP);

  pinMode(lplayer, OUTPUT);
  pinMode(ldealer, OUTPUT);
  pinMode(lturn, OUTPUT);
  pinMode(lresult, OUTPUT);

  randomSeed(analogRead(A10));
}

void loop() {

  if (!digitalRead(bstart)) {
    digitalWrite(lresult, LOW);

    playertotal = draw() + draw();
    dealertotal = draw();

    do {
      
      blinkScore(lplayer, playertotal);
      blinkScore(ldealer, playertotal);

      digitalWrite(lturn, HIGH);

    } while (digitalRead(bhit) && digitalRead(bstand))



    while (score < 21) {

      if (!digitalRead(bhit)) {
        playertotal += draw();
        blinkScore(lplayer, playertotal);
      }
      else if (!digitalRead(bstand)) {
        playertotal += draw();
        blinkScore(lplayer, playertotal);
        break;
      }
    
    }
    


    digitalWrite(lturn, LOW);


    while (dealertotal < 17)
    {
      dealertotal += draw();
    }

    //            win conds
    // you get 21 and dealer doesn't
    // you get more than the dealer but less than 21
    // dealer busts
    

    while (true) {

      if (playertotal > 21 || (dealertotal > playertotal && dealertotal <= 21) ) {
        digitalWrite(lresult, HIGH);    // plr lose
      }
      else if (   (playertotal == 21 && dealertotal !=21) ||
                  (playertotal > dealertotal) ||              // plr win
                  dealertotal > 21) { 
        
        digitalWrite(lresult, HIGH);
        delay(50);
        digitalWrite(lresult, LOW);
        delay(50);
      }
      else if (playertotal == dealertotal) { // draw

        digitalWrite(lresult, HIGH);
        delay(250);
        digitalWrite(lresult, LOW);
        delay(250);
      }



      if (!digitalRead(breset)) {
        playertotal, dealertotal = 0;
        digitalWrite(lturn, LOW);
        digitalWrite(lresult, LOW);
        return;

      }



    }
    
  
    
  }  
}



















