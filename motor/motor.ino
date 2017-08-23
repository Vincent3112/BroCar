
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

void forward(short speedL, short speedR) {
   avancerMoteurA();
   avancerMoteurB();
   setSpeedMoteurA(speedR);
   setSpeedMoteurB(speedL);
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
  Serial.begin(115200);
  pinMode(MOTEURAP, OUTPUT);
  pinMode(MOTEURAM, OUTPUT);
  pinMode(MOTEURBP, OUTPUT);
  pinMode(MOTEURBM, OUTPUT);
  pinMode(MOTEURAPWM, OUTPUT);
  pinMode(MOTEURBPWM, OUTPUT);

  setSpeedMoteurA(50);  // half of max speed
}

const byte numChars = 32;
char receivedChars[numChars];
boolean newData = false;
short leftSpeed = 0;
short rightSpeed= 0;

void showNewData() {
    if (newData == true) {
        Serial.print("Left / Right speeds : ");
        Serial.print(receivedChars[0]);
        Serial.print(receivedChars[1]);
        Serial.print(receivedChars[2]);
        Serial.print(receivedChars[3]);
        Serial.print("    ");
        leftSpeed = ((int)receivedChars[0] - 48) * 10 + ((int)receivedChars[1] - 48);
        rightSpeed = ((int)receivedChars[2] - 48) * 10 + ((int)receivedChars[3] - 48);
        Serial.print(leftSpeed);
        Serial.print(" / ");
        Serial.print(rightSpeed);
        Serial.print(" ;; ");
        Serial.println(receivedChars);
        newData = false;
    }
}

void recvWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    char startMarker = '<';
    char endMarker = '>';
    char rc;
 
    while (Serial.available() > 0 && newData == false) {
        rc = Serial.read();

        if (recvInProgress == true) {
            if (rc != endMarker) {
                receivedChars[ndx] = rc;
                ndx++;
                if (ndx >= numChars) {
                    ndx = numChars - 1;
                }
            }
            else {
                receivedChars[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                ndx = 0;
                newData = true;
            }
        }

        else if (rc == startMarker) {
            recvInProgress = true;
        }
    }
}



void loop()
{
  
  if (1) {
    
    recvWithStartEndMarkers();
    showNewData();
    
    // Motor B is left
    if (leftSpeed == 0 || rightSpeed == 0){
      stopMotors();
    } else {
      forward(leftSpeed, rightSpeed);
    }
    
    delay(10);


  } else {
    
    // OLD CODE //
    
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
          incomingByte = Serial.read();
        } while (incomingByte == 49);
  
      } else if (incomingByte == 50){
          do {
            serialFlush();
            backward(100);
            delay(100);
            incomingByte = Serial.read();
          } while (incomingByte == 50);
          
      } else if (incomingByte == 51){
        do {
          serialFlush();
          turnRight(30);
          delay(100);
          incomingByte = Serial.read();
       } while (incomingByte == 51);
  
      } else if (incomingByte == 52){
        do {
          serialFlush();
          turnLeft(30);
          delay(100);
          incomingByte = Serial.read();
          } while (incomingByte == 52);
      }
<<<<<<< HEAD
      
      stopMotors();
      
    }
  }
=======
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
>>>>>>> wip
}
