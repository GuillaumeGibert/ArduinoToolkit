const int _portBaud = 9600; // baud rate of the serial port
const float _fps = 1.0; // frame rate to send data
unsigned long samplingTimestamp = 0; 

const unsigned int nbSamples = 10; //  number of samples to compute mean and std
unsigned long sampleTimestamps[nbSamples]; // array containing the timestamps
unsigned int sampleIndex = 0; // current sample index

void setup() 
{
	// initializes the serial port
	Serial.begin(_portBaud);

}


void loop() 
{
	// initializes the timer
	unsigned long startTime = micros();
	
	// estimates sampling duration
	unsigned long samplingDuration = startTime - samplingTimestamp;
	samplingTimestamp = startTime;
	
	//Serial.println(samplingDuration);
	if (sampleIndex < nbSamples)
	{
		sampleTimestamps[sampleIndex] = samplingDuration;
		sampleIndex++;
	}
	
	if (sampleIndex == nbSamples)
	{
		// average
		double timestampAverage = 0;
		for (int l_sample=0; l_sample < nbSamples; l_sample++)
		{
			timestampAverage += (double)sampleTimestamps[l_sample]/nbSamples;
		}
		Serial.print("average= ");
		Serial.println(timestampAverage); // print the timestamp average
		
		// variance
		double timestampVariance = 0;
		for (int l_sample=0; l_sample < nbSamples; l_sample++)
		{
      timestampVariance += pow((double)(sampleTimestamps[l_sample]-timestampAverage), 2.0)/nbSamples;
		}
		Serial.print("variance= ");
		Serial.println(timestampVariance); // print the timestamp average
    Serial.print("std= ");
    Serial.println(sqrt(timestampVariance)); // print the timestamp average
		
		sampleIndex = 0;
	}
	
	//reads data once on pin A0
	analogRead(0);

	// estimates the loop duration and waits before starting a new loop
	unsigned long currentTime = micros(); // in microseconds
	unsigned long elapsedTime = currentTime - startTime; // in microseconds
	unsigned long waitingTime = 1000000/_fps - elapsedTime; // in microseconds

	if (waitingTime < 16384) //(see https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/)
		delayMicroseconds(waitingTime); // in microseconds
	else
		delay(waitingTime / 1000); // in milliseconds 
	
}
