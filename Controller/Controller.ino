

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

void setup() {  

  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Forward_Backwards = analogRead(A0);
  int Left_Right = analogRead(A1);
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
     }//joystick upright
     else if((Forward_Backwards < 520) && (Left_Right < 520)){
        motorOutputL = 200; //using mapping later with motor controller
        motorOutputR = 255;
        encode(motorOutputL,motorOutputR);
     }//joystick downright
     else if((Forward_Backwards > 520) && (Left_Right < 520)){
        motorOutputL = 0;
        motorOutputR = 0;
        encode(motorOutputL,motorOutputR);
     }//joystick upleft
     else if((Forward_Backwards > 520) && (Left_Right < 520)){
        motorOutputL = 255;
        motorOutputR = 200;
        encode(motorOutputL,motorOutputR);
     }
  }else if((Forward_Backwards < 520) && (Left_Right ==520)){//forward
        motorOutputL = 255;
        motorOutputR = 255;
        encode(motorOutputL,motorOutputR);
     }else if((Forward_Backwards > 520) && (Left_Right ==520)){//backwards
        motorOutputL = 0;
        motorOutputR = 0;
        encode(motorOutputL,motorOutputR);
     }else if((Forward_Backwards == 520) && (Left_Right < 520)){//left
        motorOutputL = 255;
        motorOutputR = 150;
        encode(motorOutputL,motorOutputR);
     }else if((Forward_Backwards == 520) && (Left_Right > 520)){//right
        motorOutputL = 150;
        motorOutputR = 255;
        encode(motorOutputL,motorOutputR);
     }else{
      motorOutputL = 0;
      motorOutputR = 0;
      encode(motorOutputL,motorOutputR);
  }
  Serial.print(msg);
  delay(10);
}

