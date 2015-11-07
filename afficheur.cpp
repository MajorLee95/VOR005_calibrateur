#include "afficheur.h"

/*

P : 0x98
O :0x01
T : 0xF0
A: 0x88
R : 0xFA
d:0xC2
f:0xB8
U : 0xC1
I: 0xCF
M :0x89

N
S : 0xA4
b : 0xF0
E : 0xB0
L : 0XF1
w: 0xE3





*/






afficheur::afficheur(byte adresse)
    {
    _adresse=adresse; 
    _affichageEnCours[0]=0; 
    _numSeq=0; 
    _numMax =0;
      
    }
    
    
    
void afficheur::refreshAfficheur()
{
 // Serial.print("numSeq ");
  //Serial.println(_numSeq);
  
  if (_numMax==0) 
    {
      return;
      }
  
  
  _numSeq=_numSeq+1;
  if (_numSeq>_numMax)
    {
      _numSeq=-1;
      envoi(0xFF);
     }
    else
    
     {
       envoi(_affichageEnCours[_numSeq]);
      }
  }

void afficheur::envoi(byte data)
{
  //Serial.println(_adresse,HEX);
  Wire.beginTransmission(_adresse);
  //Serial.println(data,HEX);
  Wire.write(data);
  //Serial.println("ta");
  int a=Wire.endTransmission(); 
  //Serial.println(a)  ;
  
  
  }

void afficheur::affiche(byte toto)

{
  switch (toto)
    {
    case 0: // affiche rien
        _affichageEnCours[0]=0xFF;
       Serial.println("Rien"); 
        _numMax =0;       
        break;
        
    case 1: // affiche USB 
        _affichageEnCours[0]=0xC1;//
        _affichageEnCours[1]=0xA4;//
        _affichageEnCours[2]=0xF0;//
        
       Serial.println("USB"); 
         
        _numMax =2;       
        break;
  
    case 2: // affiche SWEEP 
        _affichageEnCours[0]=0xA4;//
        _affichageEnCours[1]=0xE3;
        _affichageEnCours[2]=0xB0;
        _affichageEnCours[3]=0xB0;
        _affichageEnCours[4]=0x98;
        
       Serial.println("SWEEP"); 
        
        _numMax =4;       
        break;
     
     case 3: 
        _affichageEnCours[0]=0xC2;
        _affichageEnCours[1]=0x81;
        _affichageEnCours[2]=0x8E;
        _affichageEnCours[3]=0xC0;
        _affichageEnCours[4]=0xDE;
        _numMax=4;
       Serial.println("POtAr"); 
               
        break; 
     
     
     case 4: // affiche Milieu 
  
        _affichageEnCours[0]=0x89;
        _affichageEnCours[1]=0xCF;//
        _affichageEnCours[2]=0xF1;//
        _affichageEnCours[3]=0xCF;
        _affichageEnCours[4]=0xB0;//
        _affichageEnCours[5]=0xC1;//
       Serial.println("MILIEU"); 
        
        _numMax =5;       
        break;    
      
       
        
        
        
      
      
      

        case 5: // affiche A Adafruit 
        _affichageEnCours[0]=0x88;
        _affichageEnCours[1]=0xC2;
        _affichageEnCours[2]=0x88;
        _affichageEnCours[3]=0xB8;
        _affichageEnCours[4]=0xFA;
        _affichageEnCours[5]=0xC1;
        _affichageEnCours[6]=0xCF;
        _affichageEnCours[7]=0xF0;


    //test de chaque segment de led    
//        _affichageEnCours[0]=0xFD;//
//        _affichageEnCours[1]=0xFB;
//        _affichageEnCours[2]=0xF7;
//        _affichageEnCours[3]=0xEF;
//        _affichageEnCours[4]=0xDF;
//        _affichageEnCours[5]=0xBF;
//        _affichageEnCours[6]=0xFE;
//        _affichageEnCours[7]=0xFE;
        
        
        
        
        
       Serial.println("ADAFRUIT"); 
        
        _numMax =7;       
        break;   
      
      
      case 6: // affiche classique 
        _affichageEnCours[0]=0xF1;//
        _affichageEnCours[1]=0x88;
        _affichageEnCours[2]=0xF1;
        _affichageEnCours[3]=0x88;
        _affichageEnCours[4]=0xF1;
        _affichageEnCours[5]=0x88;
        _affichageEnCours[6]=0xF1;
        _affichageEnCours[7]=0x88;
        _affichageEnCours[8]=0xF1;
       Serial.println("CLASSIQUE"); 
        
        _numMax =8;
           
        break;  
      
      
      
    }  
     _numSeq=0;
   // Serial.println(_affichageEnCours[0]);
     envoi(_affichageEnCours[0]);
    
  
  }