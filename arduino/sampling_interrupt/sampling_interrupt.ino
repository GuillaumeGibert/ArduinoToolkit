// VARIABLES TO MODIFY : _fps and _portBaud
// CHOOSE THE SAMPLING FREQUENCY YOU WOULD LIKE
const float _fps = 2000.0; //Hz
// CHOOSE THE BAUD RATE
const int _portBaud = 9600; // baud rate of the serial port

// ADAPT THESE VALUES IF YOU DO NOT USE AN ARDUINO UNO BOARD
const long _arduinoClockFrequency = 16000000; // Crystal oscillator 16 MHz on Arduino UNO
int _prescalerChoicesTimer0[]  = {1, 8, 64, 256, 1024};
int _prescalerChoicesTimer1[]  = {1, 8, 64, 256, 1024};
const int _nbPresalerChoicesTimer0 = 5;
const int _nbPresalerChoicesTimer1 = 5;

// DO NOT MODIFY THESE VARIABLES 
int _registerIndex = 0;
unsigned int _registerRolloverValue = 0;
int _registerPrescaler = 0;
bool _registerSolutionFound = false;
int _prescalerIndex = 0;

unsigned long samplingTimestamp = 0; 

const unsigned int nbSamples = 10; //  number of samples to compute mean and std
unsigned long sampleTimestamps[nbSamples]; // array containing the timestamps
unsigned int sampleIndex = 0; // current sample index

// predivisor: possible values 1, 8, 64, 256, 1024
// Register TCCR#B
// CS#0 -> 1
// CS#1 -> 8
// CS#0 CS#1 -> 64
// CS#2 -> 256
// CS#0 CS#2 -> 1024
// register 0 and 2 are 8 bits -> max value 256
// register 1 is 16 bits -> max value 65535


bool determineRegisterInfosForSampling(int registerIndex, unsigned long int registerMaxValue, int* prescalerChoices, int nbPrescalerChoices)
{
  Serial.println("===========================================");
  Serial.println("Looking for solutions...");
  while (!_registerSolutionFound && _prescalerIndex < nbPrescalerChoices)
  {
    float compareMatchRegister = (float)_arduinoClockFrequency/(prescalerChoices[_prescalerIndex]*_fps)-1;
      
    if (((compareMatchRegister) < registerMaxValue) && (compareMatchRegister-(long int)(compareMatchRegister) == 0.0))
    {
      // a solution was found, register infos are stored
      _registerIndex = registerIndex;
      _registerRolloverValue = compareMatchRegister;
      _registerPrescaler = prescalerChoices[_prescalerIndex];
      _registerSolutionFound = true;

      Serial.println("---> Solution found!");
      Serial.print("Register index: "); Serial.println(_registerIndex);
      Serial.print("Roll over value: "); Serial.println(_registerRolloverValue);
      Serial.print("Prescaler: "); Serial.println(_registerPrescaler);
      Serial.println("===========================================");
    }
    else
    {
      // no solution were found, keep continuing
    }
    _prescalerIndex++;
  }

  return _registerSolutionFound;
}

void setup() 
{
  // initializes the serial port
  Serial.begin(_portBaud);

  // determine the register infos for accurate sampling
  // 1st register is 8 bits
  // bool isFirstRegisterSuccessfull = determineRegisterInfosForSampling(0, pow(2,8), _prescalerChoicesTimer0, _nbPresalerChoicesTimer0);
  // 2nd register is 16 bits (in case no solution were found on 1st register)
  //if (!isFirstRegisterSuccessfull)
  //{ //}
    _prescalerIndex = 0;
    if (!determineRegisterInfosForSampling(1, pow(2,16), _prescalerChoicesTimer1, _nbPresalerChoicesTimer1))
    {
      Serial.println("---> No Solution found!");
      Serial.println("===========================================");
    }
    else
    {
      // stops interrupts
      cli();
    
      // sets timer1 interrupt at _fps Hz
      TCCR1A = 0;// set entire TCCR1A register to 0
      TCCR1B = 0;// same for TCCR1B
      TCNT1  = 0;// initialize counter value to 0
      
      // sets compare match register for _fps hz increments
      OCR1A = _registerRolloverValue;// 
      
      // turns on CTC mode
      TCCR1B |= (1 << WGM12);
      
      switch (_registerPrescaler)
      {
        case 1:
          // set CS10 bits for 1 prescaler
          TCCR1B |= (1 << CS10);
          break;
    
        case 8:
          // set CS10 bits for 8 prescaler
          TCCR1B |= (1 << CS11);
          break;
    
        case 64:
          // set CS10 bits for 64 prescaler
          TCCR1B |= (1 << CS11) | (1 << CS10);
          break;
    
        case 256:
          // set CS10 bits for 256 prescaler
          TCCR1B |= (1 << CS12);
          break;
          
        case 1024:
          // set CS10 and CS12 bits for 1024 prescaler
          TCCR1B |= (1 << CS12) | (1 << CS10);
          break;
      }
      
      // enable timer compare interrupt
      TIMSK1 |= (1 << OCIE1A);
    
      //allow interrupts
      sei();
    }
}

ISR(TIMER1_COMPA_vect)
{  
	//change the 0 to 1 for timer1 and 2 for timer2
	//interrupt commands here
	
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
	
	//reads data once on pin A0
	analogRead(0);
}


void loop() 
{
	if (sampleIndex == nbSamples)
	{
		// average
		double timestampAverage = 0;
		for (int l_sample=0; l_sample < nbSamples; l_sample++)
		{
			timestampAverage += (double)sampleTimestamps[l_sample]/nbSamples;
		}
		Serial.print("average= ");
		Serial.print(timestampAverage); Serial.print("/"); Serial.println(1e6/_fps);// print the timestamp average
		
		// variance
		double timestampVariance = 0;
		for (int l_sample=0; l_sample < nbSamples; l_sample++)
		{
			timestampVariance += pow((double)(sampleTimestamps[l_sample]-timestampAverage), 2.0)/nbSamples;
		}
		Serial.print("variance= ");
		Serial.println(timestampVariance); // print the timestamp average
		
		sampleIndex = 0;
	}
}
