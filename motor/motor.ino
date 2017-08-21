
#define MOTEURAP 9
#define MOTEURAM 8
#define MOTEURBP 4
#define MOTEURBM 2
#define MOTEURAPWM 10
#define MOTEURBPWM 3
#define VITESSEMAXRANGE 255
#define VITESSEMAX 100

enum direction_e{
  forward_e, 
  backward_e
};

int incomingByte = 0; 
direction_e direction = forward_e;

void forward(short speed) {
   avancerMoteurA();
   avancerMoteurB();
   setSpeedMoteurA(speed);
   setSpeedMoteurB(speed);
}

void backward(short speed) {
   reculerMoteurA();
   reculerMoteurB();
   setSpeedMoteurA(speed);
   setSpeedMoteurB(speed);
}

void turnLeft(short speed) {
  reculerMoteurA();
  avancerMoteurB();
  setSpeedMoteurA(speed);
  setSpeedMoteurB(speed);
}

void turnRight(short speed) {
  avancerMoteurA();
  reculerMoteurB();
  setSpeedMoteurA(speed);
  setSpeedMoteurB(speed);
}

void stopMotors() {
  setSpeedMoteurA(0);
  setSpeedMoteurB(0);
}

void avancerMoteurA() {
  digitalWrite(MOTEURAP,HIGH);
  digitalWrite(MOTEURAM,LOW);
}

void setSpeedMoteurA(short speed) {
  speed=min(max(speed,0),VITESSEMAX);
  speed=speed*VITESSEMAXRANGE/VITESSEMAX;
  analogWrite(MOTEURAPWM,speed);
}

void reculerMoteurA() {
  digitalWrite(MOTEURAP,LOW);
  digitalWrite(MOTEURAM,HIGH);
}

void avancerMoteurB() {
  digitalWrite(MOTEURBP,HIGH);
  digitalWrite(MOTEURBM,LOW);
}

void setSpeedMoteurB(short speed) {
  speed=min(max(speed,0),VITESSEMAX);
  speed=speed*VITESSEMAXRANGE/VITESSEMAX;
  analogWrite(MOTEURBPWM,speed);
}

void reculerMoteurB() {
  digitalWrite(MOTEURBP,LOW);
  digitalWrite(MOTEURBM,HIGH);
}

void serialFlush() {
  if (Serial.available() ) {
    while (Serial.read() != -1){}
    }
  }

  



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MOTEURAP, OUTPUT);
  pinMode(MOTEURAM, OUTPUT);
  pinMode(MOTEURBP, OUTPUT);
  pinMode(MOTEURBM, OUTPUT);
  pinMode(MOTEURAPWM, OUTPUT);
  pinMode(MOTEURBPWM, OUTPUT);

  setSpeedMoteurA(50);  // half of max speed
}


void loop()
{
  /*
  avancerMoteurA();
  setSpeedMoteurA(50);  // half of max speed
  delay(4000);
  setSpeedMoteurA(100);
  delay(4000);
  for(int inc_speed=0 ; inc_speed<=VITESSEMAX ; inc_speed++)
  {  
    Serial.println (inc_speed);
    delay(100);
    setSpeedMoteurA(inc_speed); 
  }
  */
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

  
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    if (incomingByte == 49){
      do {
        serialFlush();
        forward(100);
        delay(100);
      /*if (Serial.available() > 0){*/
        incomingByte = Serial.read();/*
        else {(incomingByte == 0);}*/
      } while (incomingByte == 49);
  
    } else if (incomingByte == 50){
        do {
          serialFlush();
          backward(100);
          delay(100);
       /* (Serial.available() > 0){*/
        incomingByte = Serial.read();
    /*  else{(incomingByte == 0);} */
        } while (incomingByte == 50);
      
    } else if (incomingByte == 51){
      do {
        serialFlush();
        turnRight(30);
        delay(100);
   /*   if (Serial.available() > 0){*/
        incomingByte = Serial.read();
  /*    else {(incomingByte == 0);} */
     } while (incomingByte == 51);
     
    } else if (incomingByte == 52){
      do {
        serialFlush();
        turnLeft(30);
        delay(100);
  /*    if (Serial.available() > 0){*/
        incomingByte = Serial.read();
   /*   else {(incomingByte == 0);}*/
        } while (incomingByte == 52);
      }
    //After action, stop the motors.  
    stopMotors();
    }
  }
  

    
/*    if (direction == forward_e){
      avancerMoteurA();
      direction = backward_e;
    } else {
      reculerMoteurA();
      direction = forward_e;
    }
  }   
}
*/

