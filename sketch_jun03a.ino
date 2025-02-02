//________________________________________________________________________________HELLO____________________________________________________________________________________________________//
int current_cabin_state = 1; //cabin state

//_______________________//
int b1 = 28;
int b2 = 29; 
int b3 = 30;
//_______________________//
int moto1= d2;
int moto2= d3;
//_______________________//
int U1=22, U2=24, U3=26;
int D1=23, D2=25, D3=27;
//_______________________//
int l1 = 6;
int l2 = 5;
int l3 = 4;
int signal1 = A9;
int signal2 = A10;
int signal3 = A11;
//______________________//
int O1 = A12;
int O2 = A13;
int O3 = A14;
//_____________________//


void setup() {


   pinMode(b1, INPUT);   //b1
   pinMode(b2, INPUT);   //b2
   pinMode(b3, INPUT);   //b3

//_________________________________//

   pinMode(moto1, OUTPUT);  // for H-bridge
   pinMode(moto2, OUTPUT);  // for H-bridge
//_________________________________//
   pinMode(U1, INPUT);   
   pinMode(U2, INPUT);   
   pinMode(U3, INPUT);   
 
   pinMode(D1, INPUT);   
   pinMode(D2, INPUT);   
   pinMode(D3, INPUT);   
//________________________________//
   pinMode(l1,INPUT);
   pinMode(l2,INPUT);
   pinMode(l3,INPUT);
   pinMode(signal1,OUTPUT);
   pinMode(signal2,OUTPUT);
   pinMode(signal3,OUTPUT);
//_______________________________//

   pinMode(O1,INPUT);
   pinMode(O2,INPUT);
   pinMode(O3,INPUT);
}



void loop()
{
  door_sensors();
  outter_buttons_movement();
  limit_switch();

  door_sensors();
  inside_buttons_movement();
  limit_switch();
}









//__________________________________________________________________________//

void inside_buttons_movement() {

int current = current_cabin_state;
int desired = current;         //temporary until user presses a button 


//read desired floor from inner button 

int button1= digitalRead(b1);    //for floor 1
int button2= digitalRead(b2);    //for floor 2
int button3= digitalRead(b3);    //for floor 3



if ( button1==HIGH )
{
   desired=1; 
}
else if( button2 == HIGH)
{
   desired=2
}
else if( button3 == HIGH)
{
   desired=3
}


                   
while (desired != current) 
{
   if (desired > current)    // going up
   {
      digitalWrite(moto1,HIGH);
      digitalWrite(moto2,LOW);
      delay(3000);             // assumption that it takes three seconds between any two floors
      
      current+=1;
   }
   else if (desired < current)  // for going down 
   {
       digitalWrite(moto1,LOW);
       digitalWrite(moto2,HIGH);
       delay(3000);           // assumption that it takes three seconds between any two floors
       
       current-=1;
   }
}
   digitalWrite(moto1,LOW);
   digitalWrite(moto2,LOW);
   
   current_cabin_state=current;
}
//__________________________________________________________________________________________




void outter_buttons_movement(){

int current = current_cabin_state;
int desired = current;         //temporary until user presses a button 


//read desired floor from outter button 

int up1= digitalRead(U1);              //for floor 1
int do1= digitalRead(D1);//not used

int up2= digitalRead(U2);              //for floor 2
int do2= digitalRead(D2);

int up3= digitalRead(U3);//not used    //for floor 3
int do3= digitalRead(D3);


if ( up1==HIGH )
{
   desired=1; 
}
else if( up2 == HIGH || do2==HIGH)
{
   desired=2;
}
else if( do3 == HIGH)
{
   desired=3;
}

                   
while (desired != current) 
{
   if (desired > current)    // going up
   {
      digitalWrite(moto1,HIGH);
      digitalWrite(moto2,LOW);
      delay(3000);             // assumption that it takes three seconds between any two floors
      
      current+=1;
   }
   else if (desired < current)  // for going down 
   {
       digitalWrite(moto1,LOW);
       digitalWrite(moto2,HIGH);
       delay(3000);           // assumption that it takes three seconds between any two floors
       
       current-=1;   
   }
} 
     digitalWrite(moto1,LOW);
     digitalWrite(moto2, LOW);
     current_cabin_state=current;
  
}



void limit_switch(){
   
   int l1_state= digitalRead(l1);
   int l2_state= digitalRead(l2);
   int l3_state= digitalRead(l3);
 
   if(l1_state==HIGH) 
   {
      digitalWrite(signal1,HIGH);
   }
    else{
      digitalWrite(signal1,LOW);
    } 
    
    if(l2_state==HIGH) 
    {
      digitalWrite(signal2,HIGH);
    } 
    else
    {
      digitalWrite(signal2,LOW);
    } 

    
     if(l3_state==HIGH) 
     {
      digitalWrite(signal3,HIGH);
     } 
     else
     {
      digitalWrite(signal3,LOW);
     } 

  }


void door_sensors()
{
  
  int O1_state= digitalRead(O1);
  int O2_state= digitalRead(O2);
  int O3_state= digitalRead(O3);
  
  while(O1_state==LOW || O2_state==LOW || O3_state==LOW)   // if door not closed turn off motor  
  { 
   digitalWrite(moto1,LOW) ;
   digitalWrite(moto2,LOW) ;
  }
  
}
