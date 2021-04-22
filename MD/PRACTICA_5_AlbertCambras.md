## PRACTICA 5: Buses de comunicación

En esta práctica hemos conocido los fundamentos de los buses i2C.
En este caso tenemos un código el cual nos permite ver si se ha establecido correctamente la conexión con el dispositivo que usa una comunicación i2C con nuestra placa ESP-32.

``` cs
#include <Arduino.h>

#include <Wire.h> 
 
void setup(){

  Wire.begin();
 
  Serial.begin(9600);
  while (!Serial);             // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");

}
```

Incluimos la librería Wire.h para poder usar las funciones que usaremos más tarde.

```cs

void loop()
{
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;

  for(address = 1; address < 127; address++ ){

  // The i2c_scanner 
  // the Write.endTransmisstion to see if
  // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
 
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println("  !");
 
      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknown error at address 0x");
       if (address<16)
        Serial.print("0");
        Serial.println(address,HEX);
    }    
}
  
if (nDevices == 0)
  Serial.println("No I2C devices found\n");

else
  Serial.println("done\n");
  delay(5000);           // wait 5 seconds for next scan
}
```

En este caso toda la parte de comunicación se desarrolla en el void loop().
Primero declaramos algunas variables que nos van a servir para mostrar por pantalla si se ha establecido correctamente la conexión.
Imrpimimos por pantalla que se está escaneando.
A partir de ahora hacemos un recorrido por todas las direcciones que tiene la placa, es decir de 1 a 127.
A partir de la función **Wire.beginTransmission(address);** inicializamos la transmisión con la dirección "adress".
La función "error = Wire.endTransmission();" nos devuelve un byte que hace referencia al estado de esta transmisión. Nos basaremos en este para decirle por pantalla al usuario si ha habido algún error con la conexión o si se ha establecido correctamente.

En el caso que nos devuelva 0 entonces sabemos que hace referencia a que no se ha acabado la transmisión y por lo tanto se ha establecido correctamente.
Lo siguiente es mostrar por que dirección se está estableciendo la transmisión de datos en hexadecimal y suma no a la variable ndevices.
Una vez ha enviado por pantalla  la dirección, sale del bucle y entra en el else ya que ahora ndevices vale 1 y nos muestra un "done" y espera 5 segundos a volver a escanear.

En el caso que nos devuelva un número diferente de 0 sería el caso de error. En este programa se contempla la posibilidad de tener el error 4 que es error desconocido.
Una vez entra aquí, la variable nDevices no varía y entraría en el if de después del void loop en el cuál mostrartía por pantalla que no se ha encontrado una interfície i2C.
 



