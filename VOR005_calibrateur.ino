#include <SCoop.h>
#include <Wire.h>
#include "bouton.h"
#include "afficheur.h"
#include "servoTest.h"
#include "potar.h"
#include <Adafruit_PWMServoDriver.h>
#include <Servo.h>

bouton boutonP(4);
afficheur affichage(0x20);
byte etatCalibrateur (3); //1= PC 2=Sweep 3=potar 4=Milieu
unsigned long temp;
potar lePotar(0);
servoTest leServo(5); 
servoTest potence(9);


defineTimerRun(rafraichirAffichage,800) //ne pas mettre ce timer a une valeur trop faible pour éviter le rebond lors de l'apuui bouton (ne pas compter des apuis multiple pour un seul appuie voulu)   
        {  
         //Serial.println("affichagePP");
          affichage.refreshAfficheur();
         
          }

defineTimerRun(surveilleBouton,40) //ne pas mettre ce timer a une valeur trop faible pour éviter le rebond lors de l'apuui bouton (ne pas compter des apuis multiple pour un seul appuie voulu)   
        {  
         //Serial.println("bouton");
          boutonP.refreshBouton();
         
          }

defineTimerRun(surveilleServo,100) //conserver 100 ou modifier le "*0.1" dans méthode appliqueobjectif du Servo
        {  
         //Serial.println("Servo");
         leServo.appliqueObjectif();
         potence.appliqueObjectif();

         
          }


defineTimerRun(surveillePotar,80)
  {
   // Serial.println("potar");
    lePotar.refresh();
             
    
    }


defineTimerRun(reflechi,40)
  {
    
    //Serial.println("reflechi");
      if (boutonP.hasBeenLongClicked())
        { 
          
          unsigned long dateChangeServo(millis());
          
          if (leServo.getType())
              {
                leServo.setType(false);
                affichage.affiche(AFFICHEADAFRUIT);
                Serial.println("servo de type Adafruit");
                
                }
           else
             {
               leServo.setType(true);
               affichage.affiche(AFFICHECLASSIQUE);
               Serial.println("servo de type Classique");
               }
          //sleep( 3000);
          
          while (millis()<dateChangeServo+3000)
          {
            
            }
                 
          affichage.affiche(etatCalibrateur);
          boutonP.acquit();
          }
    
    switch (etatCalibrateur)
        {
        
          
          
          
          case 1:
             if (boutonP.hasBeenClicked())
            {
              boutonP.acquit();
              etatCalibrateur=2;
              affichage.affiche(AFFICHESWEEP);
              leServo.setObjectif(leServo.getMin());
              
                            
              }
                 
             break;     
                  
        case 2:
             if (leServo.isMin())
            {
              
              etatCalibrateur=20;
              leServo.setObjectif(leServo.getMax());
                                         
              }
              
              if (boutonP.hasBeenClicked())
            {
              boutonP.acquit();
              etatCalibrateur=3;
              affichage.affiche(AFFICHEPOTAR);
              }
                 
             break;
    
    case 20:
             if (leServo.isMax())
            {
              
              etatCalibrateur=2;
              leServo.setObjectif(leServo.getMin());
                                         
              }
               
               if (boutonP.hasBeenClicked())
            {
              boutonP.acquit();
              etatCalibrateur=3;
              affichage.affiche(AFFICHEPOTAR);
              }
               
               
                 
             break;
    
    
             
            
        case 3:
          int temp;
          int potarVal;
          potarVal=lePotar.getValue();
          //Serial.print("lepotar : ");
          //Serial.println(potarVal);
          
          if (leServo.getType())
          
            {
              temp=map(potarVal,0,1023,300,3000);
            }
          else
            {
             temp=map(potarVal,0,1023,100,1000);
              }
              
           //Serial.print ("OBJECTIF=  ");
           //Serial.println(temp);   
           leServo.setObjectif(temp);
          if (boutonP.hasBeenClicked())
            {
              boutonP.acquit();
              etatCalibrateur=4;
              affichage.affiche(AFFICHEMILIEU);
              leServo.setObjectif(leServo.getMilieu());
              
              }
          
          
          
          break;
    
      case 4:
           
           leServo.setObjectif(leServo.getMilieu());
           if (boutonP.hasBeenClicked())
            {
              boutonP.acquit();
              etatCalibrateur=1;
              affichage.affiche(AFFICHEUSB);
                            
              }
           
           
           
           
           break;
           
      case 8:
        
        break;
        
        
        
      }

    
    
    
    }


          
void setup() 
   {     
     Serial.begin(57600);
     potence.setPotence(); 
     leServo.setType(true); 
     Wire.begin();
    
    Serial.println("hello");
    mySCoop.start();
   temp=millis();
   //etatCalibrateur=3; fait dans l'init de la variable
   affichage.affiche(AFFICHEPOTAR);
   
     
     }
         
         
 void loop ()
 
   {
     mySCoop.sleep(100);
    
//    if (boutonP.hasBeenClicked()==true)
//      {
//        Serial.println("clic ");
//        boutonP.acquit();
//        
//        }
//   if (boutonP.hasBeenDoubleClicked()==true)
//      {
//        Serial.println("DoubleClic ");
//        boutonP.acquit();
//        
//        }    
//        
//    if (boutonP.hasBeenLongClicked()==true)
//      {
//        Serial.println("Long Clic ");
//        boutonP.acquit();
//        
//        }  
    
    
    if (millis()>2000+temp)
         {
         
         //Serial.print("valeur potar : ");
         //Serial.println(lePotar.getValue());
         temp=millis();
         
         //Serial.print("Etat : ");
    //Serial.println(etatCalibrateur);
         }
         
     }

