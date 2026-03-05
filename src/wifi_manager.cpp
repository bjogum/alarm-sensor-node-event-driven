#include <WiFi3.h>

void maintainWiFi(){
    if (WiFi.status() == WL_CONNECTED){
        return;
    }

    


    // kolla om vi är anslutan till wifi
    // om inte - kolla så vi fått tid sen senast -> isf: försök ansluta igen.
    // sätt 'wifiConnected' variabel till = false .. bool func() return
}