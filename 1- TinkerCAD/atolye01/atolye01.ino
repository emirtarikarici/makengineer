const int LED_1 = 13; //Led 1 13. pine bağlı
const int LED_2 = 12;
const int LED_3 = 11;
const int button1 = 4;
const int button2 = 3;
const int button3 = 2;
const int buzzer = 9;

int button_state1 = 0; // butona basılıp basılmadığı
int button_state2 = 0;
int button_state3 = 0;

int button_press = 0; // hangi butona basıldığını tutma

void setup() {

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
  
}

void loop(){

  button_state1 = digitalRead(button1);
  button_state2 = digitalRead(button2);
  button_state3 = digitalRead(button3);
  
  if (!button_state1 && button_state2 && button_state3) //0 1 1
      button_press = 1;
  else if (button_state1 && !button_state2 && button_state3) // 1 0 1 
      button_press = 2;
  else if (button_state1 && button_state2 && !button_state3) //1 1 0 
      button_press = 3;
  else button_press = 0;
    
    scanButtons();
}

void scanButtons() {
  
  switch (button_press) {
    
    case 1:
    digitalWrite(LED_1,HIGH); //led 1i 1 yapar
    tone(buzzer,200,400); //buzzer, kaç Hz, ne kadar çalsın
    delay(200); // gecikme
    digitalWrite(LED_1,HIGH);
    tone(buzzer,400,400);
    delay(200);
    digitalWrite(LED_1,HIGH);
    tone(buzzer,600,400);
    delay(200);
    digitalWrite(LED_1,LOW);
    break;
      
    case 2:
    digitalWrite(LED_2,HIGH); //led 1i 1 yapar
    tone(buzzer,200,400); //buzzer, kaç Hz, ne kadar çalsın
    delay(200); // gecikme
    digitalWrite(LED_2,HIGH);
    tone(buzzer,400,400);
    delay(200);
    digitalWrite(LED_2,HIGH);
    tone(buzzer,800,400);
    delay(200);
    digitalWrite(LED_2,LOW);
    break;
      
    case 3:
    digitalWrite(LED_3,HIGH); //led 1i 1 yapar
    tone(buzzer,400,400); //buzzer, kaç Hz, ne kadar çalsın
    delay(200); // gecikme
    digitalWrite(LED_3,HIGH);
    tone(buzzer,600,400);
    delay(200);
    digitalWrite(LED_3,HIGH);
    tone(buzzer,800,400);
    delay(200);
    digitalWrite(LED_3,LOW);
    break;
    
    default:
    return;
    
  }
}
