
int horiz = 0;
int vert = 1;

int joy[2] = {150,75};
String msg = "";
void encode() {
   msg = "";
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
  encode();
  // put your main code here, to run repeatedly:
  Serial.println(msg);
  
  delay(1000);
}
