int b_size = 256;

char buffer[256];
char msg[256];
int joy[2];

int l_motor = 3; // 0 index
int r_motor = 6; // 1  index

void decode() {
  int count = 0;
  snprintf(msg,sizeof(msg),"%s","");
  char *pch;
  pch = strtok(buffer,"R");
  while (pch !=NULL) {
    joy[count] = atoi(pch);
    count++;
    pch = strtok(NULL,"R");
  }
}


void setup() {
  pinMode(l_motor,OUTPUT);
  pinMode(r_motor,OUTPUT);
  Serial.begin(115200);
}

void loop() {
  Serial.readBytesUntil('E',buffer,b_size);
  Serial.println(buffer);
  decode();
  String s = String("L : "+String(joy[0])+", R: "+String(joy[1]));
  analogWrite(l_motor,joy[0]);
  analogWrite(r_motor,joy[1]);
  Serial.println(s);
  
  delay(1000);

}
