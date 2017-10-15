 bool reverse_left= false, reverse_right= false;
 int mod1=0, mod2=0, distanceToStop=10, target; 
 int target_velocity_left = 0;
 int target_velocity_right = 0;
 int global_speed_right = 0;
 int global_speed_left = 0;
 long int runningTime;
 float distance = -1;
#define ECHO 50
#define TRIG 51
#define leftPin1 10
#define leftPin2 11
#define rightPin1 12
#define rightPin2 13
#define LEFT 0
#define RIGHT 1

void setup() {
  Serial1.begin(115200);
  Serial.begin(115200);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);  
  pinMode(leftPin1,OUTPUT);
  pinMode(leftPin2,OUTPUT);

  pinMode(rightPin1,OUTPUT);
  pinMode(rightPin2,OUTPUT);


  digitalWrite(leftPin1, LOW);
  digitalWrite(leftPin2, LOW);

  digitalWrite(rightPin1, HIGH);
  digitalWrite(rightPin2, HIGH);

  attachInterrupt(digitalPinToInterrupt(ECHO), measureDistance, CHANGE);

}



void stop(int side)
{
 if(side == LEFT)
  {
    digitalWrite(leftPin1, HIGH);
    digitalWrite(leftPin2, HIGH);
  }
  else if(side == RIGHT)
  {
    digitalWrite(rightPin1, HIGH);
    digitalWrite(rightPin2, HIGH);
  }
  //delay(100000);
}

void measureDistance() {


  if (digitalRead(ECHO) == 1) runningTime = micros();
  if (digitalRead(ECHO) == 0)
  {
     distance = (float)(micros() - runningTime) / 58.0f;
     Serial.println(distance);
  }


}

String msg = "";
char buf_out[16];


void loop() {
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(15);
  digitalWrite(TRIG, LOW);
  delay(200);


  msg = Serial1.readString();

    if(msg!="")
    {
        msg.toCharArray(buf_out, 16);
        msg = strtok(buf_out, " ");
        if(msg!="")
        {
          distanceToStop = msg.toInt();
        }

        msg = strtok(NULL, " ");
        if(msg!="")
        {
          target = msg.toInt();
        } else
        {
          target=0;
        }
    }

    
  if(distance <= (float)distanceToStop) {
    stop(LEFT);
    stop(RIGHT);
    
  } else
    {
            digitalWrite(leftPin1, LOW);
      digitalWrite(rightPin1, HIGH);
      digitalWrite(leftPin2, HIGH);
      digitalWrite(rightPin2, LOW);
    }
}
