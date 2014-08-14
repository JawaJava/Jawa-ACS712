float temps, adcVolt, cal_value, temp_amp=0.0;
unsigned long calTime=0, time_cal=600;
boolean on_calibrasi=false;

void setup(){
  Serial.begin(9600);
  Serial.println("Running System");
  Serial.print("Time Set :");
  Serial.println(time_cal);
}
 
void loop(){
   get_data();
   delay(500);
}

void get_data(){
  temps     = analogRead(A0) * (5.0 / 1023.0); //convert ke tegangan dari ADC
  adcVolt   = abs(temps - 2.50); //mengambil selisih tegangan pada zero point
  adcVolt  /= 0.185; //Arus dalam A
  adcVolt  *= 1000; //merubah Arus A ke mA
   
  //proses kalibrasi
  calTime++; 
  if(calTime < time_cal){ 
    Serial.print("Kalibrasi Time:");
    Serial.println(calTime);
    temp_amp += adcVolt;
    on_calibrasi = true;
  }else if(on_calibrasi == true){ 
    cal_value = temp_amp/time_cal;
    on_calibrasi = false;
  }
  
  if(on_calibrasi == false){ 
    adcVolt -= cal_value;
    adcVolt = abs(adcVolt);
    Serial.print("Pada mA :");
    Serial.print(adcVolt);
    Serial.println(" mA"); 
    adcVolt /= 1000;
    Serial.print("Pada A :");
    Serial.print(adcVolt);
    Serial.println(" A");
  }
}
