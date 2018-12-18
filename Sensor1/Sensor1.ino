#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <EtherCard.h>

#define APIKEY "MZKNYQLA1R30TF0F"

const char website[] PROGMEM = "api.thingspeak.com";

uint8_t Ethernet::buffer[700];//criando vetor de 700 posicoes
byte mymac[]={ 0x74,0x69,0x69,0x2D,0x30,0x31};// criando o mac


Stash stash;

byte session;

//timing variable
int res = 100; // was 0

const int chipSelect = 10;


// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 6

 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);

 
// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0;
float tempC;

 byte termometru[8] = {
    B00100,
    B01010,
    B01010,
    B01110,
    B01110,
    B11111,
    B11111,
    B01110
  
  };

//define o icone do termometro na temperatura minima

 byte termometrumin[8] = {
  0b00100,
  0b01010,
  0b01010,
  0b01010,
  0b01010,
  0b10001,
  0b10001,
  0b01110
};

//define o  icone do termometro na temperatura maxima

 byte termometrumax[8] = {
  0b00100,
  0b01110,
  0b01110,
  0b01110,
  0b01110,
  0b11111,
  0b11111,
  0b01110
};

 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

 
// Inicializa o LCD
LiquidCrystal lcd(7, 8, 5, 4, 3, 2);


//funcao para inicializar a rede
void inicializaRede(){
   byte vers = ether.begin(sizeof Ethernet::buffer,mymac,chipSelect);
   if(vers == 0){
      Serial.println(F("Erro na conexao"));
   }
    if (!ether.dhcpSetup()){
      Serial.println(F("DHCP failed"));
      
    }

    if (!ether.dnsLookup(website))
      Serial.println(F("DNS failed"));
      
    res = 180;
}


//Funcao que inicializa o lcd
void inicializarlcd(){
    lcd.begin(16, 2); 
    lcd.clear();
    lcd.setCursor(0,0);
}



//Funcao para localizar e mostrar o endereco dos sensores 
void identificasensor(){
  sensors.begin();
  
  // Localiza e mostra enderecos dos sensores
  Serial.println(F("Localizando sensores DS18B20..."));
  Serial.print(F("Foram encontrados "));
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(F(" sensores."));
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println(F("Sensores nao encontrados !")); 
     
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print(F("Endereco sensor: "));
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();
}



//Funcao que encontra o endereco do sensor
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print(F("0"));
    Serial.print(deviceAddress[i], HEX);
  }
}

 

//Funcao para mostrar a temperatura do ambiente, a temperatura maxima e a minima
void medesensor(){
  
  // Le a informacao do sensor
  sensors.requestTemperatures();
  tempC = sensors.getTempC(sensor1);
  
  // Atualiza temperaturas minima e maxima
  if (tempC < tempMin)
  {
    tempMin = tempC;
  }
  if (tempC > tempMax)
  {
    tempMax = tempC;
  }
  
  // Mostra dados no serial monitor
  Serial.print(F("Temp C: "));
  Serial.print(tempC);
  Serial.print(F(" Min : "));
  Serial.print(tempMin);
  Serial.print(F(" Max : "));
  Serial.println(tempMax); 

  delay(2000);
}




//Funcao para imprimir os dados na tela do lcd
void mostrandolcd(){


inicializarlcd();
  
  lcd.setCursor(1,0);
  lcd.print(F("Temp.:       "));
  //Simbolo grau
  lcd.write(223);
  lcd.print(F("C"));
  lcd.setCursor(8,0);
  lcd.print(tempC);
  lcd.setCursor(0,1);
  lcd.write(2);
  lcd.print(F(": "));
  lcd.setCursor(3,1);
  lcd.print(tempMin,1);
  lcd.setCursor(8,1);
  lcd.write(3);
  lcd.print(F(": "));
  lcd.setCursor(11,1);
  lcd.print(tempMax,1);


  variaTempC();

   delay(1000); 
}


void variaTempC(){

      //comandos para fazer a temperatura ambiente variar de acordo com a temperatura 
 if((tempC>30) && (tempC<35)){
  
  lcd.setCursor(0,0);
  lcd.write(2);
  
}else if (tempC<=30.0){

  
  lcd.setCursor(0,0);
  lcd.write(4);
  
}else{

  
  lcd.setCursor(0,0);
  lcd.write(3);
  
}
}


 void initialize_ethernet(void){
  for(;;){ // keep trying until you succeed
    //Reinitialize ethernet module
    //pinMode(5, OUTPUT);  // do notknow what this is for, i ve got something elso on pin5
    //Serial.println("Reseting Ethernet...");
    //digitalWrite(5, LOW);
    //delay(1000);
    //digitalWrite(5, HIGH);
    //delay(500);

    // Change 'SS' to your Slave Select pin, if you arn't using the default pin
    if (ether.begin(sizeof Ethernet::buffer, mymac, SS) == 0){
      Serial.println( "Failed to access Ethernet controller");
      continue;
    }

    if (!ether.dhcpSetup()){
      Serial.println("DHCP failed");
      continue;
    }


    if (!ether.dnsLookup(website))
      Serial.println("DNS failed");

  
    //reset init value
    res = 180;
    break;
  }
}


void enviaDados(){
 if (res > 220){
    initialize_ethernet();
  }

  res = res + 1;

  ether.packetLoop(ether.packetReceive());

  //200 res = 10 seconds (50ms each res)
  if (res == 200) {


    //Generate random info
    float demo = random(0,500);
    word one = random(0,500);

    // generate two fake values as payload - by using a separate stash,
    // we can determine the size of the generated message ahead of time
    // field1=(Field 1 Data)&field2=(Field 2 Data)&field3=(Field 3 Data)&field4=(Field 4 Data)&field5=(Field 5 Data)&field6=(Field 6 Data)&field7=(Field 7 Data)&field8=(Field 8 Data)&lat=(Latitude in Decimal Degrees)&long=(Longitude in Decimal Degrees)&elevation=(Elevation in meters)&status=(140 Character Message)
    byte sd = stash.create();
    stash.print("field1=");
    stash.print(String(tempC));
    //stash.print("&field2=");
    //stash.print(one);
    //stash.print("&field3=");
    //stash.print(msje);
    stash.save();

    //Display data to be sent


    // generate the header with payload - note that the stash size is used,
    // and that a "stash descriptor" is passed in as argument using "$H"
    Stash::prepare(PSTR("POST /update HTTP/1.0" "\r\n"
      "Host: $F" "\r\n"
      "Connection: close" "\r\n"
      "X-THINGSPEAKAPIKEY: $F" "\r\n"
      "Content-Type: application/x-www-form-urlencoded" "\r\n"
      "Content-Length: $D" "\r\n"
      "\r\n"
      "$H"),
    website, PSTR(APIKEY), stash.size(), sd);

    // send the packet - this also releases all stash buffers once done
    session = ether.tcpSend();

 // added from: http://jeelabs.net/boards/7/topics/2241
 int freeCount = stash.freeCount();
    if (freeCount <= 3) {   Stash::initMap(56); }
  }

   const char* reply = ether.tcpReply(session);

   if (reply != 0) {
     res = 0;
     Serial.println(F(" >>>REPLY recieved...."));
     Serial.println(reply);
   }
   delay(300);

} 


void setup(void)
{
  Serial.begin(9600);
  lcd.createChar(2,termometru);
  lcd.createChar(4,termometrumin);
  lcd.createChar(3,termometrumax);
    
 //Chamada das funcoes criadas anteriormente

  identificasensor();
  inicializarlcd();
 initialize_ethernet();
}

void loop(){
  //Chamada das funcoes criadas anteriormente

  medesensor();
  variaTempC();
  mostrandolcd();
  enviaDados();
}
