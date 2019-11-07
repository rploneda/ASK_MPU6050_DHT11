#include <VirtualWire.h> //libreria transmisor
#include "I2Cdev.h"     //Libreria para MPU
#include "MPU6050.h"    //Libreria para MPU
#include "Wire.h"       //Libreria para MPU
#include <DHT.h>        //Libreria para DHT11

MPU6050 sensor;   //MPU
int ax, ay, az;   //Valores del acelerometro
//entradas para el sensor DHT11
#define DHTPIN 3
// Dependiendo del tipo de sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Inicializamos el sensor DHT11

void setup()
{

      
    Serial.begin(9600);  // Iniciando puerto serial
    Serial.println("Setup");
    
    Wire.begin();         //Iniciando I2C
    sensor.initialize();  //Iniciando el sensor
    
    // Comenzamos el sensor DHT
    dht.begin();
    
    // Se inicializa el RF
    vw_setup(2000); // velocidad: Bits per segundo
    vw_set_tx_pin(2); //Pin 2 como salida para el RF transmisor
}

void loop()
{
  //---------------DHT11-------------
      // Leemos la humedad relativa
      float h = dht.readHumidity();
  //---------------MPU6050-----------
      // Leer las aceleraciones 
      sensor.getAcceleration(&ax, &ay, &az);
      int datoAx= ax;
      int datoAy= ay;
      int datoAz= az;

  //---------------Transmisor-----------
      char buf[VW_MAX_MESSAGE_LEN]; // Trama para enviar
      String str="";
      str="I" + String(h) + ", " + String(datoAx)+ ", " + String(datoAy) + ", " + String(datoAz) + "F"; //Enviamos HumedadR y valores del acelerometro    
                  
    //Trama
      str.toCharArray(buf,sizeof(buf));   //creamos el string en array
      vw_send((uint8_t *)buf, strlen(buf)); //ennviamos el array
      vw_wait_tx(); //Esperamos hasta que el mensaje se envie
      Serial.println("Enviada");
      delay(200);
}
