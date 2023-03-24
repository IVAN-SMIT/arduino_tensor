#include <HX711.h>

#include "HX711.h"                                            // подключаем библиотеку для работы с тензодатчиком

#define DT  4                              // Указываем номер вывода, к которому подключен вывод DT  датчика
#define SCK 2                                    // Указываем номер вывода, к которому подключен вывод SCK датчика

HX711 scale;                                                  // создаём объект scale

float calibration_factor = -14.15;                            // вводим калибровочный коэффициент
float units;
int ounces;                                                  // задаём переменную для измерений в граммах
int ounces1;
int ounces2;
int ounces3;                                                 // задаём переменную для измерений в унциях

void setup() {
    Serial.begin(9600);                                         // инициируем работу последовательного порта на скорости 9600 бод
    scale.begin(DT, SCK);                                       // инициируем работу с датчиком
    scale.set_scale();                                          // выполняем измерение значения без калибровочного коэффициента
    scale.tare();                                               // сбрасываем значения веса на датчике в 0
    //scale.set_scale(calibration_factor);                        // устанавливаем калибровочный коэффициент
}

void loop() {
    Serial.print("Reading: ");                                  // выводим текст в монитор последовательного порта
    units = scale.get_units()/10000;
    units=(int)units;

    if(units>1){ounces3=ounces2;
        ounces2=ounces1;                                      // усредняем показания, разделив сумму значений на 10
        ounces1=units;}
    if(units<-1){ounces3=ounces2;
        ounces2=ounces1;                                      // усредняем показания, разделив сумму значений на 10
        ounces1=units;}

    ounces=(ounces2+ounces1+units)/3;                                  // переводим вес из унций в граммы
    Serial.print(ounces);                                       // выводим в монитор последовательного порта вес в граммах
    Serial.println(" grams");                                   // выводим текст в монитор последовательного порта
}
