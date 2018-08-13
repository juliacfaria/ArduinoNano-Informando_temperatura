 #include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

/*
//Bibliotecas do cartao SD
#include <SPI.h>
#include <SD.h>
*/

//Define o CS do cartao SD como 4
const int chipSelect = 10;


// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 6

 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);

 
// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0;

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


//Criando arquivo para guardar as informacoes lidas pelo sensor
//File myFile;

  float tempC;
  int i=1;


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
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
     
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
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
    if (deviceAddress[i] < 16) Serial.print("0");
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
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Min : ");
  Serial.print(tempMin);
  Serial.print(" Max : ");
  Serial.println(tempMax); 
  Serial.println();

  delay(2000);
}


//Funcao que cria um arquivo para armazenar os valores da temperatura
/*void cartaosd(){

  
  String arquivo = String(tempC)+";"+String(tempMax)+";"+String(tempMin)+"\n";
  Serial.println(arquivo);

  //Solicita a criacao do arquivo no cartao de memoria. 
  myFile = SD.open("test.csv", FILE_WRITE);

 //Verifica o funcionamento do arquivo.
   if (myFile!=0){
        myFile.print(arquivo);
        myFile.close();
        return;
  }else{
  Serial.println("Erro ao ler arquivo");
  inicializarlcd();
  lcd.print("erro no arquivo");
  }
}
*/

//Funcao para imprimir os dados na tela do lcd
void mostrandolcd(){


inicializarlcd();
  
  lcd.setCursor(1,0);
  lcd.print("Temp.:       ");
  //Simbolo grau
  lcd.write(223);
  lcd.print("C");
  lcd.setCursor(8,0);
  lcd.print(tempC);
  lcd.setCursor(0,1);
  lcd.write(2);
  lcd.print(": ");
  lcd.setCursor(3,1);
  lcd.print(tempMin,1);
  lcd.setCursor(8,1);
  lcd.write(3);
  lcd.print(": ");
  lcd.setCursor(11,1);
  lcd.print(tempMax,1);


  variaTempC();

   delay(1000);

  
}


void variaTempC(){

      //comandos para fazer a temperatura ambiente variar de acordo com a temperatura 
 if((tempC>30.0) && (tempC<35.0)){
  
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
 
void setup(void)
{
  Serial.begin(9600);
  
  //inicializa o cartao de memoria
//  SD.begin(chipSelect);
    
 //Chamada das funcoes criadas anteriormente

 identificasensor();


  
   lcd.createChar(2,termometru);
   lcd.createChar(4,termometrumin);
   lcd.createChar(3,termometrumax);
   
  inicializarlcd();
  
}

void loop(){
  //Chamada das funcoes criadas anteriormente
    //cartaosd();
  medesensor();
  variaTempC();
  mostrandolcd();
}
