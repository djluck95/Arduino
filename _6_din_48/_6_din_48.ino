
#include "LedControl.h" // Pin 7 to Data In, 6 to Clk, 5 to LOAD, number of devices is 3 
LedControl lc = LedControl(7, 6, 5, 2);
const int button = 12;
int ok = 1;

void setup() {
  // Initialize the 3 MAX7219 devices
  Serial.begin(9600);
  pinMode(button, INPUT);
  digitalWrite(button, HIGH);

  randomSeed(analogRead(0));

  for (int k = 0; k < 2; k++) {
    lc.shutdown(k, false); // Enable display
    lc.setIntensity(k, 9); // Set brightness level (0 is min, 15 is max)
    lc.clearDisplay(k); // Clear display register
  }
}

//----------------------------------------------------------

int cicle() {
  long long aux = 0, aux2 = 0;
  while (ok) {
    aux = random (99999999);
    aux2 = random (99999999);

    for (int i = 0; i < 8; i++) {
      if (i != 2 && i != 5) {
        if (i == 0 || i == 3 || i == 6)
          lc.setDigit(1, i, aux2 % 10 , (i == 0 || i == 3 || i == 6));
        else if (( aux2 % 10) % 5 != 0)
          lc.setDigit(1, i, ( aux2 % 10) % 5, (i == 0 || i == 3 || i == 6));
        aux2 /= 10;
      }
    }

    for (int i = 0; i < 8; i++) {
      if (i != 2 && i != 5) {
        if (i == 0 || i == 3 || i == 6)
          lc.setDigit(0, i, aux % 10, (i == 0 || i == 3 || i == 6));
        else if (( aux % 10) % 5 != 0)
          lc.setDigit(0, i, (aux % 10) % 5, (i == 0 || i == 3 || i == 6));
        aux /= 10;
      }
    }
    ok = digitalRead(button);
    delay(100);
  }

  return 1;
}
//--------------------------------------------------------
void bingo() {

  int a[10], b[20];

  for (int i = 0; i < 6; i++)
    a[i] = random(0, 49);
  for (int i = 0; i < 6; i++)
    for (int j = i + 1; j < 6; j++)
      if (a[i] == a[j])
      { a[j] = random(0, 49);
        j--;
      }
  int z = 0;
  for (int i = 0; i < 6; i++)
  { Serial.println(a[i]);
    b[z] = a[i] % 10;
    Serial.println(b[z]);
    z++;
    a[i] /= 10;
    if (a[i] == 0)
      b[z] = 11;
    else
      b[z] = a[i] % 10;
    Serial.println(b[z]);
    z++;


  }

  lc.clearDisplay(0);
  lc.clearDisplay(1);


  int ct = 0;

  for (int i = 0; i < 8; i++) {
    if (b[ct] != 11) {
      if (i == 2 || i == 5) delay (500);
      if (!(i == 2 || i == 5)) {
        if (i == 0)
        {
          lc.setDigit(1, i, b[ct], 0), ct++;
          delay(10);
        }
        else
        { lc.setDigit(1, i, b[ct], (i == 0 || i == 3 || i == 6)), ct++;
          delay(10);
        }

      }
    }
    else ct++;
  }

  ct = 6;
  Serial.println("am intrat");
  for (int i = 0; i < 8; i++) {
    Serial.print("->");
    Serial.println(i);
    if (b[ct] != 11)
    { if (i == 0 || i == 2 || i == 5) delay (500);
      if (i != 2 && i != 5 ) {
        Serial.println(b[ct]);
        Serial.println(ct);
        if (b[ct] != 11)
        {
          lc.setDigit(0, i, b[ct], (i == 0 || i == 3 || i == 6));
          ct++;
        }

        delay(10);
      }
    }
    else ct++;
  }
}

void loop() {

  cicle();

  if (ok == 0)
  { delay(100);
    bingo();
    while (ok == 0)
      if (digitalRead(button) == LOW)
        ok = 1;
  }
  delay(200);



}




