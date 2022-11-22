/* 
Załóżmy, że układ symuluje nam sterownik smart mieszkania, który wykonuje proste
czynnosci jak np. zapalanie swiatła, czy informowanie użytkownika o obecnym stanie. 
Układ taki możemy zastosować w praktyce, np. do wyprowadzeń, gdzie są podpięte diody można 
podłączyć tranzystory a następnie do przekaźników i sterować większą mocą, natomiast
do wejść można podpiąć konntraktony informujące czy okno lub drzwi są otwarte lub zamnięte.
W symulacji uzyjemy przetwornika adc oraz czujnika temp.
Transmisja z komputerem odbywa się poprzez transmisję szeregową UART
*/
void setup()
{
	pinMode(11, OUTPUT);
  	pinMode(12, OUTPUT);
  	pinMode(13, OUTPUT);
  	pinMode(10, INPUT);
    pinMode(9, INPUT);
  	pinMode(8, INPUT);
  	Serial.begin(9600);
}

String odebrane_dane = "";
bool swiatlo_przedpokoj, swiatlo_kuchnia, swiatlo_salon,
  	 drzwi_przedpokoj, 	 okno_kuchnia, 	  okno_salon;

void loop()
{
	if(Serial.available() > 0) //czy arduino odebrało dane
    {
      //jeśli tak to odebrane dane czytamy do końca lini
      
      odebrane_dane = Serial.readStringUntil('\n');
      
      if(odebrane_dane == "zapal swiatlo w kuchni")
      {
        swiatlo_kuchnia = 1;
        digitalWrite(13, HIGH);
      }
      
      if(odebrane_dane == "zgas swiatlo w kuchni")
      {
        swiatlo_kuchnia = 0;
        digitalWrite(13, LOW);
      }
      
      if(odebrane_dane == "zapal swiatlo w przedpokoju")
      {
        swiatlo_przedpokoj = 1;
      	digitalWrite(12, HIGH);
      }
        
      if(odebrane_dane == "zgas swiatlo w przedpokoju")
      {
        swiatlo_przedpokoj = 0;
        digitalWrite(12, LOW);
      }
      
      if(odebrane_dane == "zapal swiatlo w salonie")
      {
        swiatlo_salon = 1;
        digitalWrite(11, HIGH);
      }
      
      if(odebrane_dane == "zgas swiatlo w salonie")
      {
        swiatlo_salon = 0;
        digitalWrite(11, LOW);
      }
      
    }
  
  //sprawdzamy stany na wejsciach 
  if(digitalRead(10) == 1)
    okno_kuchnia = 1;
  	else
      okno_kuchnia = 0;
  
  if(digitalRead(9) == 1)
    drzwi_przedpokoj = 1;
  	else
      drzwi_przedpokoj = 0;
  
  if(digitalRead(8) == 1)
    okno_salon = 1;
  	else
      okno_salon = 0;
  
  //za pomoca iloczynu binarnego sprawdzamy jakie mamy stany i wysylamy informacje do uzytkownika
  if(okno_kuchnia & swiatlo_kuchnia)
    Serial.println("okno w kuchni otwarte, swiatlo zapalone");
  else if(!okno_kuchnia & swiatlo_kuchnia)
    Serial.println("okno w kuchni zakmniete, swiatlo zapalone");
  else if(okno_kuchnia & !swiatlo_kuchnia)
    Serial.println("okno w kuchni otwarte, swiatlo zgaszone");
  else
    Serial.println("okno w kuchni zamkniete, swiatlo zgaszone");
    
  if(drzwi_przedpokoj & swiatlo_przedpokoj)
    Serial.println("drzwi otwarte, swiatlo zapalone");
  else if(!drzwi_przedpokoj & swiatlo_przedpokoj)
    Serial.println("drzwi zakmniete, swiatlo zapalone");
  else if(drzwi_przedpokoj & !swiatlo_przedpokoj)
    Serial.println("drzwi otwarte, swiatlo zgaszone");
  else
    Serial.println("drzwi zamkniete, swiatlo zgaszone");
    
  if(okno_salon & swiatlo_salon)
    Serial.println("okno w salonie otwarte, swiatlo zapalone");
  else if(!okno_kuchnia & swiatlo_kuchnia)
    Serial.println("okno w salonie zakmniete, swiatlo zapalone");
  else if(okno_kuchnia & !swiatlo_kuchnia)
    Serial.println("okno w salonie otwarte, swiatlo zgaszone");
  else
    Serial.println("okno w salonie zamkniete, swiatlo zgaszone"); 
    
    //pomiar temperatury
  float volt;
  float temp;
  int odczyt = analogRead(A0);      //odczytanie wartości z czujnika
  volt = (odczyt * 5.0) / 1024.0;        //przeliczenie odczytanej wartości na napięcie w woltach (dla podłączenia pod 5 V)
  temp = (volt - 0.5) * 100;             //konwersja z napięcia na temperaturę, rozdzielczość czujnika wynosi 10 mV na stopień, dodatkowo należy zastosować offset 500 mV
  Serial.println("Temperatura w celcjuszach w mieszkaniu wynosi: ");     
  Serial.println(temp);
  
}
