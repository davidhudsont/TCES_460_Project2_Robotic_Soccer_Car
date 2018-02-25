
String msg = "";
int motorOutputL;
int motorOutputR;
//encoding function 
int joy[2];
void encode(int a1, int a2) {
    msg = "";
    joy[0] = a1;
    joy[1] = a2;
  for (int i =0; i<2; i++) {
    
       msg = String(msg+joy[i]+"R");
   }
   msg = String(msg+"E");

}

String print_joy(int x, int y,int hor, int vert, int sw) {
      String vals = "";
      vals = String("L_MOTOR: "+String(x)+", R_MOTOR: "+String(y)+", HOR: "+String(hor)+", VERT: "+String(vert)+", SW: "+String(sw));
      return vals;
}

int forward = 4;
int reverse = 7;

int l_pwm = 3;
int r_pwm = 6;

int rst = 8;
int button = 9;

void setup() {  

  // put your setup code here, to run once:
  pinMode(forward,OUTPUT);
  pinMode(reverse,OUTPUT);
  pinMode(button,INPUT);
  pinMode(rst,OUTPUT);
  digitalWrite(rst,LOW);
  digitalWrite(button,LOW);
  Serial.begin(115200);
  Serial.println("Setup!!!!!");
}

void loop() {
  int hor = analogRead(A0);
  int vert = analogRead(A1);
  int sw = digitalRead(button);
  int l_motor = 0;
  int r_motor = 0;
  encode(hor,vert);
  if (sw == true) {
    digitalWrite(rst,HIGH);  
  }
  else {
    digitalWrite(rst,LOW);
  }
  //// Forward
  if ( vert > 600) { // Forward
      l_motor = map(vert,600,1023,0,255);
      r_motor = map(vert,600,1023,0,255);
      //l_motor = 255;
      //r_motor = 255;
      digitalWrite(forward,HIGH);
      digitalWrite(reverse,LOW);     
  }
  else if ( hor < 400) { // Left
      l_motor = 0;
      r_motor = map(hor,400,0,0,255);
      digitalWrite(forward,HIGH);
      digitalWrite(reverse,LOW); 
  }
  else if ( hor > 600) { // Right
    //l_motor = 255;
    l_motor = map(hor,600,1023,0,255);
    r_motor = 0;
    digitalWrite(forward,HIGH);
    digitalWrite(reverse,LOW); 
  }
  else if (  vert < 400 ) { // Reverse
    //l_motor = 255;
    //r_motor = 255;
    l_motor = map(vert,400,0,0,255);
    r_motor = map(vert,400,0,0,255);
    digitalWrite(forward,LOW);
    digitalWrite(reverse,HIGH); 
  }
  else {
    l_motor = 0;
    r_motor = 0;
    digitalWrite(forward,HIGH);
    digitalWrite(reverse,LOW); 
  }
  analogWrite(l_pwm,l_motor);
  analogWrite(r_pwm,r_motor);
  Serial.println(print_joy(l_motor,r_motor,hor,vert,sw));
  delay(100);
}

