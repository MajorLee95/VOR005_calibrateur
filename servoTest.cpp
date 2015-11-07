#include "servoTest.h"

servoTest::servoTest(byte pin)
    {
      _pin=pin;
      
      _carteAda = Adafruit_PWMServoDriver(0x40);
       
    }
    
    
bool servoTest::getType()
  {
    return _type;    
    }
    
int servoTest::getMilieu()
  {
    return _milieu;    
    }

int servoTest::getMin()
  {
    return _min;    
    }
    
    
int servoTest::getMax()
  {
    return _max;    
    }
    
    
bool servoTest::isMin()
  {
   
  return(_enCours==_min);
   } 
bool servoTest::isMax()
  {
   
  return(_enCours==_max);
   } 

void servoTest::setType(bool type)
  {
   
    _type=type;
    if (type)
      {
    _min=1000;   //1000
    _max=2000; //2000
    _milieu=1500;
    _vitesse=300;
   _enCours=_milieu+1;
  _objectif=_milieu; 
   _myServo.attach(_pin);
              
        }
        
       else
       
       {
   _min=300;
   _max=400;
   _milieu=350;
   _vitesse=100;
   _enCours=_milieu+1;
  _objectif=_milieu;    
    Serial.println("hehe");
   _carteAda.begin();
    _carteAda.setPWMFreq(50); 
    
         
         }

    
    }
    
  void servoTest::setPotence()
  {
    
  
    _min=800;
    _max=2200;
    _milieu=1500;
    _vitesse=300;
   _enCours=_milieu+1;
  _objectif=_milieu;
  _myServo.attach(_pin); 
        
              
        }  
    
 void servoTest::setEnCours(int val)
 {  
   if (_enCours!=val)
        { _enCours=val;
         if (_type==false)
              {
              _carteAda.setPWM(0, 0, val);
              }
              else
              {
               // Serial.println(val);
                _myServo.writeMicroseconds(val);
               
                }
                
         }
   
   }
 
 
 void servoTest::setObjectif(int val)
  {
    

    _objectif=val;
    
 
    
    } 
 
 
 void servoTest::appliqueObjectif()

{
   float pas(0);
   
   pas=(float)_vitesse*0.1;
  
 /* Serial.print("obj= ");
  Serial.println(_objectif);
  Serial.print("en cours =");
  Serial.println(_enCours);
  */
    if (_objectif>_enCours)
      {
        
        if (pas>(_objectif-_enCours))
            {
              
              setEnCours(_objectif);
           }
         else
           {
            
             setEnCours(_enCours+pas);
            }
            
       }
     else if (_objectif<_enCours)
        {
         
        
        if (pas>(_enCours-_objectif))
            {
              
              setEnCours(_objectif);
             
           }
         else
           {
        
             setEnCours(_enCours-pas);
             
             
          
             }
        
        }
        
   }
