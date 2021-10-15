// C++ code
// Multidimensional sensing techniques
// Assignment 3
// Sabina Bäck

const int MAX_VALUE = 100;
int MAX_VARIANCE = 30000;
int count = 0;
double mean = 0;
double variance = 0;

// select the input pin for ldr
const int sensorPin[] = {A0, A1, A2, A3};

// count length of lists
const int size_pin = sizeof(sensorPin)/sizeof(sensorPin[0]);

// empty arrays for storing sensor values
int sensorValueList[size_pin] = {};
int sensorMatrix[size_pin][MAX_VALUE];

// count length of lists
const int size = sizeof(sensorMatrix[0]) / sizeof(int);

void setup() {
  Serial.begin(9600); 		// sets serial port for communication
  Serial.println("");
  Serial.println("Start:");
}


void loop() {
  Serial.println((String)"Count: " + count);
  // Serial.println("Mean and variance for each sensor separately:");
  
  // looping through number of pins
  for(int i = 0; i < size_pin; i++){
    
    // read values and set to array
    sensorValueList[i] = analogRead(sensorPin[i]); 	

/*    
    // Printing mean and variance for each list separately
    Serial.println(calculateMean(sensorMatrix[i],size));
    Serial.println(calculateVariance(sensorMatrix[i], calculateMean(sensorMatrix[i],size), size));
*/ 
  }

  // updating lists for sensors (window sliding)
  updateData(sensorValueList, count, size_pin);
 
  // calculating combined mean and variance
  mean = calculateMean(sensorValueList, size_pin);
  variance = calculateVariance(sensorValueList, mean, size_pin);

/*
  // printing combined mean and variance
  Serial.println("Combined mean and variance:");
  Serial.println(mean);
  Serial.println(variance); 
*/  
  
  // detecting faulty sensor
  detectError(sensorValueList, variance, mean, size_pin);
  
  // counting for window sliding
  count++;
  if (count > 99){
    count = 0;
  }
  
  delay(1000); 
}


// function for calcutaling mean
double calculateMean(const int* list, const int n){
  float sum = 0;
  for(int i = 0; i < n; i++){
    sum += list[i];
  }
  (double)n;
  return (float)(sum/n); 
}


// function for calculating variance
double calculateVariance(const int* list, double mean, const int n){
  double sum = 0;
  for(int i = 0; i < n; i++){
    sum += (list[i] - mean) * (list[i]-mean);
  }
  return (double)(sum/n);
}


// window sliding technique
void updateData(int* valueList, int count, const int n){
  for ( int i = 0; i < n; i++){
    sensorMatrix[i][count] = valueList[i];
  }
}

                   
// error detection
void detectError(int* valueList, double var, double mean, const int n){
  double sd = sqrt(var);

  if (var > MAX_VARIANCE){
  	for (int i = 0 ; i < n ; i++){               
      if(sd > 0 && (valueList[i] > (mean + sd))){
        Serial.println((String)"Sensor: " + i + ", is too high");
      }
      if (sd > 0 && (valueList[i] < (mean - sd))){
        Serial.println((String)"Sensor: " + i + ", is too low");
      }
    }
  }
}