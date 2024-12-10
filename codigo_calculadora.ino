#include <Keypad.h>
#include <LiquidCrystal.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','+'},
  {'4','5','6','-'},
  {'7','8','9','*'},
  {'C','0','=','/'}
};

byte rowPins[ROWS] = {10, 11, 12, 13};
byte colPins[COLS] = {A0, A1, A2, A3};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

LiquidCrystal lcd(7, 8, 9, 4, 5, 6);

String currentNumber = "";
long firstNumber = 0;
long secondNumber = 0;
char operation = 0;
boolean calculationDone = false;

void setup() {
  lcd.begin(16, 2);
  lcd.print("Calculadora");
  delay(1000);
  lcd.clear();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key >= '0' && key <= '9') {
      if (calculationDone) {
        lcd.clear();
        currentNumber = "";
        calculationDone = false;
      }
      currentNumber += key;
      lcd.print(key);
    } else if (key == '+' || key == '-' || key == '*' || key == '/') {
      if (currentNumber != "") {
        firstNumber = currentNumber.toInt();
        currentNumber = "";
        operation = key;
        lcd.setCursor(15, 0);
        lcd.print(operation);
        lcd.setCursor(0, 1);
      }
    } else if (key == '=') {
      if (currentNumber != "") {
        secondNumber = currentNumber.toInt();
        long result = 0;
        switch (operation) {
          case '+':
            result = firstNumber + secondNumber;
            break;
          case '-':
            result = firstNumber - secondNumber;
            break;
          case '*':
            result = firstNumber * secondNumber;
            break;
          case '/':
            if (secondNumber != 0) {
              result = firstNumber / secondNumber;
            } else {
              lcd.clear();
              lcd.print("Erro: Div por 0");
              delay(2000);
              lcd.clear();
              return;
            }
            break;
        }
        lcd.clear();
        lcd.print(result);
        currentNumber = String(result);
        calculationDone = true;
      }
    } else if (key == 'C') {
      lcd.clear();
      currentNumber = "";
      firstNumber = 0;
      secondNumber = 0;
      operation = 0;
      calculationDone = false;
    }
  }
}
