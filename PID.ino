//PID FUNCTION

double PID_Control(double input){
  unsigned long currentTime=millis();
 unsigned long timeChange=currentTime-lastTime;
 
  if(timeChange>sampleTime){
    double error=Setpoint-input;          //calculating error term
     ITerm +=error*timeChange;        // integral term
    double dInput=(error-lastError)/timeChange;   // differential term

    //computing Output
    double output=Kp*error + Ki*ITerm + Kd*dInput;

    lastTime=currentTime;       //remembering values 
   lastError=error;
   return output;             //have function return the PID output
  }
  }

  
