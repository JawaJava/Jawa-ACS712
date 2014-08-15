double temp_amp=0.0; //gunakan tipe data double pada penampung penjumlahan arus sensor
float temps, adcVolt, cal_value;
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
  /*
    bagian if(calTime < time_cal) merupakan seleksi waktu. Digunakan sebagai 
    pembatas satu kali kalibrasi, hal ini sangat di anjurkan untuk mengurangi 
    kelebihan muatan pada var calTime dan temp_amp dimana jika tidak di batasi 
    akan melakukan penambahan berulang-ulang.
  */
  if(calTime < time_cal){ 
    calTime++; 
    Serial.print("Kalibrasi Time:");
    Serial.println(calTime);
    temp_amp += adcVolt; //penjumlahan arus output sensor
    on_calibrasi = true;
  }else if(on_calibrasi == true){
    cal_value = temp_amp/time_cal; //pembagian nilai keseluruhan dengan waktu
    on_calibrasi = false;
  }

  if(on_calibrasi == false){
    adcVolt -= cal_value;
    adcVolt = abs(adcVolt);
    Serial.println("Dalam");
    Serial.print(" mA :");
    Serial.println(adcVolt);
    adcVolt /= 1000;
    Serial.print(" A :");
    Serial.println(adcVolt);
    Serial.println(" ");
  }
}
