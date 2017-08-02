
#define MOTEURAP 9
#define MOTEURAM 8
#define MOTEURBP 7
#define MOTEURBM 6
#define MOTEURAPWM 10
#define MOTEURBPWM 5
#define VITESSEMAXRANGE 255
#define VITESSEMAX 100

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MOTEURAP, OUTPUT);
  pinMode(MOTEURAM, OUTPUT);
  pinMode(MOTEURBP, OUTPUT);
  pinMode(MOTEURBM, OUTPUT);
  pinMode(MOTEURAPWM, OUTPUT);
  pinMode(MOTEURBPWM, OUTPUT);
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
  analogWrite(MOTEURBPWM,speed);
}

void reculerMoteurB() {
  digitalWrite(MOTEURBP,LOW);
  digitalWrite(MOTEURBM,HIGH);
}


void loop()
{
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
    
  
  
  
  // put your main code here, to run repeatedly:

}


