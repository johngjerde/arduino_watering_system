/* Analog Input */
int Humid_Sensor_1 = A0; 
int Humid_Sensor_2 = A1; 
int Humid_Sensor_3 = A2; 
int Humid_Sensor_4 = A3; 
int Humid_Sensor_5 = A4; 
int Humid_Sensor_6 = A5; 

/* Digital Input */
int Float_Switch = 10; 

/* Digital Output */
int Relay_Sensor = 2; 
int Relay_Pump = 3; 
int Relay_Valve_1 = 4; 
int Relay_Valve_2 = 5; 
int Relay_Valve_3 = 6; 
int Relay_Valve_4 = 7; 
int Relay_Valve_5 = 8; 
int Relay_Valve_6 = 9; 

/* Variables */
float moisture_1 = 0; 
float moisture_2 = 0; 
float moisture_3 = 0; 
float moisture_4 = 0; 
float moisture_5 = 0; 
float moisture_6 = 0; 

unsigned long previousMillis_Check = 0; 
unsigned long previousMillis_Water = 0; 
unsigned long currentMillis = 0; 

/* Constants */
float Moisture_Min = 36.01; 
long Interval_Check = 300000; 
long Interval_Water = 5400000; 
int Time_To_Water = 10000; 
const int numReadings = 5; 
float readings1[numReadings]; 

/* the readings from the analog input */
float readings2[numReadings]; 
float readings3[numReadings]; 
float readings4[numReadings]; 
float readings5[numReadings]; 
float readings6[numReadings]; 
int readIndex = 0; 

/* The index of the current reading */
float total1 = 0; 

/* the running total */
float total2 = 0; 
float total3 = 0; 
float total4 = 0; 
float total5 = 0; 
float total6 = 0; 

void setup(){ 
  Serial.begin(9600); 
  Serial.println("reset"); 
  pinMode (Float_Switch, INPUT); 
  pinMode (Relay_Sensor, OUTPUT); 
  pinMode (Relay_Pump, OUTPUT); 
  pinMode (Relay_Valve_1, OUTPUT); 
  pinMode (Relay_Valve_2, OUTPUT); 
  pinMode (Relay_Valve_3, OUTPUT); 
  pinMode (Relay_Valve_4, OUTPUT); 
  pinMode (Relay_Valve_5, OUTPUT); 
  pinMode (Relay_Valve_6, OUTPUT); 
  
  for(int thisReading1 = 0; thisReading1 < numReadings; thisReading1++){ 
    readings1[thisReading1] = 0; 
  }
   
  for(int thisReading2 = 0; thisReading2 < numReadings; thisReading2++){ 
    readings2[thisReading2] = 0; 
  } 
  
  for(int thisReading3 = 0; thisReading3 < numReadings; thisReading3++){ 
    readings3[thisReading3] = 0; 
  } 
  
  for(int thisReading4 = 0; thisReading4 < numReadings; thisReading4++){ 
    readings4[thisReading4] = 0; 
  } 
  
  for(int thisReading5 = 0; thisReading5 < numReadings; thisReading5++){ 
    readings5[thisReading5] = 0; 
  } 
  
  for(int thisReading6 = 0; thisReading6 < numReadings; thisReading6++){ 
    readings6[thisReading6] = 0; 
  } 
  
  digitalWrite (Relay_Pump, HIGH); 
  digitalWrite (Relay_Valve_1, HIGH); 
  delay(2000); 
  digitalWrite (Relay_Valve_1, LOW); 
  delay(1000); digitalWrite (Relay_Valve_2, HIGH); 
  delay(2000); digitalWrite (Relay_Valve_2, LOW); 
  delay(1000); digitalWrite (Relay_Valve_3, HIGH); 
  delay(2000); digitalWrite (Relay_Valve_3, LOW); 
  delay(1000); digitalWrite (Relay_Valve_4, HIGH); 
  delay(2000); digitalWrite (Relay_Valve_4, LOW); 
  delay(1000); digitalWrite (Relay_Valve_5, HIGH); 
  delay(2000); 
  digitalWrite (Relay_Valve_5, LOW); 
  delay(1000); 
  digitalWrite (Relay_Valve_6, HIGH); 
  delay(2000); 
  digitalWrite (Relay_Valve_6, LOW); 
  delay(1000); 
  digitalWrite (Relay_Pump, LOW); 
} 
    
void loop(){ 
  currentMillis = millis(); 
  
  if(currentMillis - previousMillis_Check >= Interval_Check){ 
    previousMillis_Check = currentMillis; 
    Serial.print("Index: "); 
    Serial.println(readIndex); 
    total1 = total1 - readings1[readIndex]; 
    total2 = total2 - readings2[readIndex]; 
    total3 = total3 - readings3[readIndex]; 
    total4 = total4 - readings4[readIndex]; 
    total5 = total5 - readings5[readIndex]; 
    total6 = total6 - readings6[readIndex]; 
    
    /* Power to the sensors to read moisture */
    digitalWrite (Relay_Sensor, HIGH); 
    delay(2000); 
    
    /* READ AND STORE VALUES */
    readings1[readIndex] = (3.6396322297 * exp(0.0029152931 * (analogRead(Humid_Sensor_1)))); 
    readings2[readIndex] = (3.6396322297 * exp(0.0029152931 * (analogRead(Humid_Sensor_2)))); 
    readings3[readIndex] = (3.6396322297 * exp(0.0029152931 * (analogRead(Humid_Sensor_3)))); 
    readings4[readIndex] = (3.6396322297 * exp(0.0029152931 * (analogRead(Humid_Sensor_4)))); 
    readings5[readIndex] = (3.6396322297 * exp(0.0029152931 * (analogRead(Humid_Sensor_5)))); 
    readings6[readIndex] = (3.6396322297 * exp(0.0029152931 * (analogRead(Humid_Sensor_6)))); 
    
    digitalWrite (Relay_Sensor, LOW); 
    total1 = total1 + readings1[readIndex]; 
    total2 = total2 + readings2[readIndex]; 
    total3 = total3 + readings3[readIndex]; 
    total4 = total4 + readings4[readIndex]; 
    total5 = total5 + readings5[readIndex]; 
    total6 = total6 + readings6[readIndex]; 
    
    Serial.print("Moisture Sensor 1 Value: "); 
    Serial.println(readings1[readIndex]); 
    Serial.print("Moisture Sensor 2 Value: "); 
    Serial.println(readings2[readIndex]); 
    Serial.print("Moisture Sensor 3 Value: "); 
    Serial.println(readings3[readIndex]); 
    Serial.print("Moisture Sensor 4 Value: "); 
    Serial.println(readings4[readIndex]); 
    Serial.print("Moisture Sensor 5 Value: "); 
    Serial.println(readings5[readIndex]); 
    Serial.print("Moisture Sensor 6 Value: "); 
    Serial.println(readings6[readIndex]); 
    readIndex = readIndex + 1; 
    
    if (readIndex >= numReadings) { 
      readIndex = 0; 
    } 
    
    moisture_1 = total1 / numReadings; 
    moisture_2 = total2 / numReadings; 
    moisture_3 = total3 / numReadings; 
    moisture_4 = total4 / numReadings; 
    moisture_5 = total5 / numReadings; 
    moisture_6 = total6 / numReadings; 
    
    Serial.print("Moisture 1 Output Value: "); 
    Serial.println(moisture_1); 
    Serial.print("Moisture 2 Output Value: "); 
    Serial.println(moisture_2); 
    Serial.print("Moisture 3 Output Value: "); 
    Serial.println(moisture_3); 
    Serial.print("Moisture 4 Output Value: "); 
    Serial.println(moisture_4); 
    Serial.print("Moisture 5 Output Value: "); 
    Serial.println(moisture_5); 
    Serial.print("Moisture 6 Output Value: "); 
    Serial.println(moisture_6); 
    Serial.println(" "); 
  } 
  
  if (currentMillis - previousMillis_Water >= Interval_Water) { 
    previousMillis_Water = currentMillis; 
    
    /* Sensor & valve 1 */ 
    if ((moisture_1 <= Moisture_Min) && (digitalRead(Float_Switch) == HIGH)) { 
      digitalWrite (Relay_Pump, HIGH); 
      digitalWrite (Relay_Valve_1, HIGH); 
      delay(Time_To_Water); 
      digitalWrite (Relay_Valve_1, LOW); 
      delay(1000); 
    } 
    
    /* Sensor & valve 2 */ 
    if ((moisture_2 <= Moisture_Min) && (digitalRead(Float_Switch) == HIGH)) { 
      digitalWrite (Relay_Pump, HIGH); 
      digitalWrite (Relay_Valve_2, HIGH); 
      delay(Time_To_Water); 
      digitalWrite (Relay_Valve_2, LOW); 
      delay(1000); 
    } 
    
    /* Sensor & valve 3 */ 
    if ((moisture_3 <= Moisture_Min) && (digitalRead(Float_Switch) == HIGH)) { 
      digitalWrite (Relay_Pump, HIGH); 
      digitalWrite (Relay_Valve_3, HIGH); 
      delay(Time_To_Water); 
      digitalWrite (Relay_Valve_3, LOW); 
      delay(1000); 
    } 
    
    /* Sensor & valve 4 */ 
    if ((moisture_4 <= Moisture_Min) && (digitalRead(Float_Switch) == HIGH)) { 
      digitalWrite (Relay_Pump, HIGH); 
      digitalWrite (Relay_Valve_4, HIGH); 
      delay(Time_To_Water); 
      digitalWrite (Relay_Valve_4, LOW); 
      delay(1000); 
    } 
    
    /* Sensor & valve 5 */ 
    if ((moisture_5 <= Moisture_Min) && (digitalRead(Float_Switch) == HIGH)) { 
      digitalWrite (Relay_Pump, HIGH); 
      digitalWrite (Relay_Valve_5, HIGH); 
      delay(Time_To_Water); 
      digitalWrite (Relay_Valve_5, LOW); 
      delay(1000); 
    } 
    
    /* Sensor & valve 6 */ 
    if ((moisture_6 <= Moisture_Min) && (digitalRead(Float_Switch) == HIGH)) { 
      digitalWrite (Relay_Pump, HIGH); 
      digitalWrite (Relay_Valve_6, HIGH); 
      delay(Time_To_Water); 
      digitalWrite (Relay_Valve_6, LOW); 
      delay(1000); 
    } 

    digitalWrite (Relay_Pump, LOW); 
    delay(1000); 
  } 
}
