#include <OneWire.h>
#include <SoftwareSerial.h>
#include <DallasTemperature.h>

SoftwareSerial hc06(9,10); // 9 = tx  10 = rx

String cmd=""; //accumule les caractères reçus par le bluetooth

//pour capteur DS18B20
const int ONE_WIRE_BUS = 2;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

String reponseBluetooth; //réponse envoyée quand commande reçu
String valeurRep = "";

void setup()
{
  //Initialize Bluetooth Serial Port
  sensors.begin(); //pour démarrer le capteur OneWire
  sensors.requestTemperatures(); //requête pour 1-Wire
  hc06.begin(9600); //démarrage du hc06 
}

void loop()
{
  int setPoint=10;
  
  sensors.requestTemperatures();//requête pour 1-Wire
  //Read data from HC06
  if(hc06.available()>0) //si quelque chose sur le port série bluetooth
  {
    while(hc06.available()>0) //tant qu'il y a quelque chose sur le port
    {
        cmd+=(char)hc06.read(); //accumule les caractères reçus
    }    
  }

  if(cmd!="") //si la commande n'est pas rien ("")
  {

    if(cmd=="temp") //si la commande est temp, envoie la température en réponse
    {
      double temp;
      temp = sensors.getTempCByIndex(0);
      reponseBluetooth = String(temp);
      valeurRep = "Temperature: " + reponseBluetooth;
      
      hc06.println(valeurRep); //envoie la réponse
    }
    else //si la commande est autre chose que temp
    {
        hc06.write("commande invalide...");
    }
    cmd=""; //reset cmd
  }
  delay(100);
}
