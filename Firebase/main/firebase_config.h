#ifndef FIREBASE_CONFIG_H
#define FIREBASE_CONFIG_H

// Wifi Credentials
 #define SSID "VIVO-10"
 #define PASSWORD "nina2017j09"

//#define SSID "Andreia_NeoRede"
//#define PASSWORD "70960600"



// Read readme.md to properly configure api key and authentication

// create a new api key and add it here 
#define API_KEY "AIzaSyDLVTKNaeNSG_lSELBeVdZoQPbkmXfg-Ow"
// Copy your firebase real time database link here 
#define DATABASE_URL "https://pi-3-esp32-default-rtdb.firebaseio.com/"  

#define USER_EMAIL "testemail@gmail.com"   // This gmail does not exist outside your database. it only exists in the firebase project as a user
#define USER_PASSWORD "testpass"      // Dont add your gmail credentials. Setup users authentication in your Firebase project first


#define TEMPERATURA__LIDA       "temperatura_lida"
#define UMIDADE_AR_LIDA         "umidade_lida_ar"
#define UMIDADE_SOLO_LIDA       "umidade_lida_solo"
#define STATUS_BATERIA          "status_bateria"
#define LUMINOSIDADE_LIDA       "luminosidade_lida"


#endif