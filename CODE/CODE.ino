
#include <LiquidCrystal.h>

//first calibrate on powering up the module 
//a poscal function to calculate avg values of x , y , z and print them on serial
//turn on the LED on pin13 and turn it off after the calibration is completed


//in loop continually read the data and calculate total accerelation vector 
//call stepdetect function
//print total number of steps on monitor
//if step occurs flash led 3 times
char ch;
int Contrast=200 ;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int xpin=A2;
int ypin=A3;
int zpin=A4;
int intwo[2]={0};
int j=0;
int powerpin=A0;
int gnd=A1;

//float threshhold=80.0;
float threshhold=30;

float xval[100]={0};
float yval[100]={0};
float zval[100]={0};
float xavg;
  float yavg;
  float zavg;
  int k;
int steps,flag=0;
void setup()
{
Serial.begin(9600);
//Serial.println("LCD test with PWM contrast adjustment"); 
pinMode(13,OUTPUT);
analogWrite(6,Contrast);
lcd.begin(16, 2);
// set up the LCD's number of columns and rows: lcd.begin(16, 2);
// Print a message to the LCD.
//lcd.print("AKASH!!!M");
//lcd.setCursor(0, 1);
//lcd.print("AKASH!!!M");
pinMode(powerpin,OUTPUT);
pinMode(gnd,OUTPUT);
digitalWrite(powerpin,HIGH);
digitalWrite(gnd,LOW);
pinMode(13,OUTPUT);
//calibrate();
//lcd.setCursor(0, 0);
//lcd.print("AKASH!!!M");
}




void loop()
{
  digitalWrite(13,LOW); delay(1000); digitalWrite(13,HIGH);
// set the cursor to column 0, line 1
// (note: line 1 is the second row, since counting begins with 0): lcd.setCursor(0, 1);
// print the number of seconds since reset: lcd.print(millis()/1000);
//lcd.setCursor(0, 1);
float dist=steps*0.762;
lcd.setCursor(0, 1);
lcd.print("Steps : ");
  lcd.print(steps);
  lcd.setCursor(0, 0);
lcd.print("Distance");
  lcd.print(dist);
  lcd.print(" m");
  
  
 //lcd.print(millis()/1000);
/*void serialEvent() {
if (Serial.available()) {
ch= Serial.read();
if(ch=='A' && Contrast<255) {
Contrast=Contrast+1; }
if(ch=='B' && Contrast>0) {
Contrast=Contrast-1; }
if(ch=='N') {
analogWrite(9,28836); }
if(ch=='F') {
analogWrite(9,0); }
analogWrite(6,Contrast); Serial.println("Current contrast");
Serial.println(Contrast);
}*/
  int acc=0;
  
  float totvect[100]={0};
float totave[100]={0};
 //float sum1,sum2,sum3=0;
  float xaccl[100]={0};
   float yaccl[100]={0};
    float zaccl[100]={0};
   // float x,y,z;
   
  
for (int i=0;i<100;i++)
{
xaccl[i]=float(analogRead(xpin));
delay(1);


//delay(100);
//x=sum1/100.0;

//Serial.println(xavg);


yaccl[i]=float(analogRead(ypin));
delay(1);

//sum2=yaccl[i]+sum2;

//y=sum2/100.0;

//Serial.println(yavg);
//delay(100);

zaccl[i]=float(analogRead(zpin));
delay(1);

//sum3=zaccl[i]+sum3;
//z=sum3/100;

 
 totvect[i] = sqrt(((xaccl[i])* (xaccl[i]))+ ((yaccl[i])*(yaccl[i])) + ((zval[i])*(zval[i])));
 totave[i] = (totvect[i] - totvect[i-1]) ;
 //acc=acc+totave[i];
 //Serial.println(totave[i]);
 //delay(200);

//cal steps 
if (totave[i]>threshhold && flag==0)
{
  steps=steps+1;
  flag=1;
  if(intwo[0]==40)
  {  //delay(100);
    //lcd.clear();
 // lcd.setCursor(0, 1);
// lcd.print(steps);
  intwo[1]=0;
  intwo[0]=0;
  }
  intwo[0]++;
  intwo[1]++;
 
}
 else if (totave[i] > threshhold && flag==1)
{
  if(intwo[0]==40)
  {
    //delay(100);
    //lcd.clear();
    //lcd.setCursor(0, 1);
  //lcd.print(steps);
  intwo[1]=0;
  intwo[0]=0;
  }
intwo[0]++;
 
}
  if (totave[i] <threshhold  && flag==1)
  {flag=0;}
  Serial.println('\n');
  Serial.print("steps=");
  Serial.println(steps);
  Serial.println("Distance covered");
  Serial.println(intwo[1]*0.762);
  //Serial.println(steps*0.762);
  //lcd.print("Steps ");
 //lcd.setCursor(0, 1);
 // lcd.print("Steps ");
//lcd.print(steps*.0762);
}


//float tim=acc/100;
//Serial.println(tim);
 delay(50);
// stepcal(totave);

 
}
void serialEvent() {
if (Serial.available()) {
ch= Serial.read();
if(ch=='A' && Contrast<255) {
Contrast=Contrast+1; }
if(ch=='B' && Contrast>0) {
Contrast=Contrast-1; }
if(ch=='N') {
analogWrite(9,28836); }
if(ch=='F') {
analogWrite(9,0); }
analogWrite(6,Contrast); Serial.println("Current contrast");
Serial.println(Contrast);
}
}
/*void stepcal(float arr[100])
{   


// int threshhold=80; 
 float jack=0;
//delay(100)
//Serial.println(xavg);
for (int i=0;i<100;i++)
{
jack=jack+arr[i];


}
float m=jack/100;

//Serial.println(yavg);
//delay(100);


 //detect pushups or count  for number of dumbles
 
 //crossing the threshold and 
 
 //cross 20 in down and 80 in up 
 
 /*add one to counter and set a flag high to indicate it is above a threshhold value 

if a flag is high and threshhold is crossed :do nothing }
if signal falls below threshhold set flag to -1 indicating it is blow threshhold


if (m>threshhold && flag==0)
{
  steps=steps+1;
  flag=1;
  Serial.println('\n');
  Serial.print("steps=");
  Serial.println(steps);
}

else if (m > threshhold && flag==1)
{
//do nothing 
}
  if (m <threshhold  && flag==1)
  {flag=0;}
  Serial.println('\n');
  Serial.print("steps=");
  Serial.println(steps);
}  */
  
  

//calculate total accerelation vector







void calibrate()

{

  digitalWrite(13,HIGH);
  
  float sum=0;
  float sum1=0;
  float sum2=0;
for (int i=0;i<100;i++)
{
xval[i]=float(analogRead(xpin));

sum=xval[i]+sum;
}
delay(100);
xavg=sum/100.0;

Serial.println(xavg);

for (int j=0;j<100;j++)
{
xval[j]=float(analogRead(xpin));

sum1=xval[j]+sum1;
}
yavg=sum1/100.0;

Serial.println(yavg);
delay(100);
for (int i=0;i<100;i++)
{
zval[i]=float(analogRead(zpin));

sum2=zval[i]+sum2;
}
zavg=sum2/100.0;
delay(100);
Serial.println(zavg);
//threshold=sqrt(((xavg)* (xavg))+ ((yavg)*(yavg)) + ((zavg)*(zavg)));
digitalWrite(13,LOW);

}


  
//counting the pushups

