#include <VirtualWire.h>
#include <VirtualWire_Config.h>



void setup()
{
    Serial.begin(9600);  // Debugging only
    //Serial.println("Receptor: setup");
    // Se inicializa el RF
    vw_setup(2000);  // velocidad: Bits per segundo
    vw_set_rx_pin(2);    //Pin 2 como entrada del RF
    vw_rx_start();       // Se inicia como receptor
}

void loop()
{
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    String DatoCadena ="";
    //verificamos si hay un dato valido en el RF
    if (vw_get_message((uint8_t *)buf,&buflen))
    {   
        if((char)buf[0]=='I') //verificamos el inicio de trama
        {
            for (int i = 0; i < buflen; i++)
            {
              DatoCadena.concat((char)buf[i]);
            }
            Serial.println(DatoCadena);
        }
     
    }
    else{
    }
    delay(200);
}
