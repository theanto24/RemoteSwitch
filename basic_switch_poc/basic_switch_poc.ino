
// Constants
enum LedPin : uint8_t
{
  RED_LED = 2,
  GREEN_LED = 3,
  BLUE_LED = 4
};

enum ButtonPin : uint8_t
{
  RED = 8,
  GREEN = 9,
  BLUE = 10
};

class Button
{
public:
  //Constructor
  Button(const uint8_t cPinId) :
    mPinId{cPinId},
    mState{0},
    mPrevState{0},
    mPrevCheckTime{0}
  {
    Init();
  }

  //Destructor
  virtual ~Button(void) = default;

  // Initialize the button
  void Init(void)
  {
    pinMode(mPinId, INPUT);
  }

  // Function to update the button's state
  void Update(void)
  {
    // First Check if enough time has passed before checking the button's state again
    if ((mPrevCheckTime + 100) < millis()){
      // Not enough time has passed.
      return;
    }

    // Enough Time has passed. Check the Pin
    uint8_t cur_state = digitalRead(mPinId);
    if ( mState != cur_state )
    {
      // Button has been pressed. Update State
      mPrevState = mState;
      mState = cur_state;
      mPrevCheckTime = millis();
    }
    else
    {
      mPrevCheckTime = millis();
    }
  }

  uint8_t GetState( void ) const
  {
    return mState;
  }

  uint8_t GetPrevState( void ) const
  {
    return mPrevState;
  }

private:
  uint8_t mPinId;
  
  // Current state
  uint8_t mState;

  // Previous State
  uint8_t mPrevState;

  // Time in ms since last time the button was checked.
  uint32_t mPrevCheckTime;
  
};

class Led
{
public:
  Led(const uint8_t cPinId) :
    mPinId(cPinId),
    mState{0}
  {
    Init();
  }

  void Init(void)
  {
    pinMode(mPinId, OUTPUT);
    digitalWrite(mPinId, mState);
  }
  
  virtual ~Led() = default;
  void ToggleLed(void);

private:
  uint8_t mPinId;
  
  uint8_t mState;
  
};
  

void ResetLedOutputs( void )
{
  digitalWrite(LedPin::RED_LED, LOW);
  digitalWrite(LedPin::GREEN_LED, LOW);
  digitalWrite(LedPin::BLUE_LED, LOW);
};

Button gRedButton(ButtonPin::RED);
Button gGreenButton(ButtonPin::GREEN);
Button gBlueButton(ButtonPin::BLUE);

Led gRedLed(LedPin::RED_LED);
Led gGreenLed(LedPin::GREEN_LED);
Led gBlueLed(LedPin::BLUE_LED);

uint8_t gRedLedState = 0;
uint8_t gGreenLedState = 0;
uint8_t gBlueLedState = 0;

void setup() {
}

void loop() {
  // put your main code here, to run repeatedly:
  //delay(10000);

  // Update button states
  gRedButton.Update();
  gGreenButton.Update();
  gBlueButton.Update();

  // Turn on and off LEDs
  if ( gRedButton.GetPrevState() != gRedButton.GetState() )
  {
    // Button was pressed, toggle LED
    gRedLedState = !gRedLedState;
    digitalWrite(LedPin::RED_LED, gRedLedState);
  }
  
}
