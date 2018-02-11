

String msg = "";
int motorOutputL;
int motorOutputR;
//encoding function 
float joy[2];
void encode(int a1, int a2) {
    joy[0] = a1;
    joy[1] = a2;
  for (int i =0; i<2; i++) {
    
       msg = String(msg+joy[i]+"R");
   }
   msg = String(msg+"E");

}

void setup() {  

  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
 // pinMode(2, OUTPUT);
 // pinMode(3, OUTPUT);
  pinMode(A4,OUTPUT);
  pinMode(A5,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  int a0 = analogRead(A0);
  int Forward_Backwards = analogRead(A1);
  int Left_Right = analogRead(A2);
  //Serial.print(a0);
 // Serial.print(", ");
 Serial.print("Forward_Backwards: ");
 Serial.println(Forward_Backwards);
  Serial.print("Left_Right: ");
  Serial.println(Left_Right);
  //Serial.print(", ");
  //Serial.print(a2);

  //Inputed so we can have a consistent stop and go.
  //values from stick vary -+2 
  if(Forward_Backwards > 1021){
    Forward_Backwards = 1021;
  }else if((Forward_Backwards>=515)&&(Forward_Backwards<=525)){
    Forward_Backwards = 520;
  }else{
    Forward_Backwards = Forward_Backwards;
  }
  if(Left_Right > 1021){
    Left_Right = 1021;
  }else if((Left_Right>=480)&&(Left_Right<=590)){
    Left_Right = 520;
  }else{
    Left_Right = Left_Right;
  }
  if((Forward_Backwards != 520) && (Left_Right != 520)){
    //joystick downleft
     if((Forward_Backwards > 520) && (Left_Right > 520)){
        motorOutputL = 0;  //set to 0,0 since there is no motor controller. Will change with motor controller
        motorOutputR = 0;
        encode(motorOutputL,motorOutputR);
        Serial.println("downleft");
     }//joystick upright
     else if((Forward_Backwards < 520) && (Left_Right < 520)){
        motorOutputL = 200; //using mapping later with motor controller
        motorOutputR = 255;
        encode(motorOutputL,motorOutputR);
        Serial.println("upright");
     }//joystick downright
     else if((Forward_Backwards > 520) && (Left_Right < 520)){
        motorOutputL = 0;
        motorOutputR = 0;
        encode(motorOutputL,motorOutputR);
        Serial.println("downright");
     }//joystick upleft
     else if((Forward_Backwards > 520) && (Left_Right < 520)){
        motorOutputL = 255;
        motorOutputR = 200;
        encode(motorOutputL,motorOutputR);
        Serial.println("upleft");
     }
  }else if((Forward_Backwards < 520) && (Left_Right ==520)){//forward
        motorOutputL = 255;
        motorOutputR = 255;
        encode(motorOutputL,motorOutputR);
        Serial.println("forward");
     }else if((Forward_Backwards > 520) && (Left_Right ==520)){//backwards
        motorOutputL = 0;
        motorOutputR = 0;
        encode(motorOutputL,motorOutputR);
        Serial.println("backwards");
     }else if((Forward_Backwards == 520) && (Left_Right < 520)){//left
        motorOutputL = 255;
        motorOutputR = 150;
        encode(motorOutputL,motorOutputR);
        Serial.println("right");
     }else if((Forward_Backwards == 520) && (Left_Right > 520)){//right
        motorOutputL = 150;
        motorOutputR = 255;
        encode(motorOutputL,motorOutputR);
        Serial.println("left");
     }else{
      motorOutputL = 0;
      motorOutputR = 0;
      encode(motorOutputL,motorOutputR);
      Serial.println("stop");
  }
  //maps a1 to analog ouput for pin 4
  /*int motorOutputL = map(Forward_Backwards,0,1021,0,255);
  int motorOutputR = map(Forward_Backwards,0,1021,0,255);
  encode(motorOutputL,motorOutputR);
  
  Serial.print("motorOutputLeft: ");
  Serial.println(Forward_Backwards);
  Serial.print("motorOutputRight: ");
  Serial.println(motorOutputR);
  //Serial.println(a1);
 analogWrite(A4,motorOutputL);
 analogWrite(A5,motorOutputR);*/
  delay(10);
}

