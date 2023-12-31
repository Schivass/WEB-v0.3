#include "webConnection.hpp"

#define DEBUG false

int MyWebServer::initStartGameRequest()
{
    startGameRequest();
    return 0;
}

void MyWebServer::startGameRequest()
{
    server->on("/startGame", HTTP_GET, [this](AsyncWebServerRequest * request)
        {
            this->started=true;
            if(DEBUG)
                Serial.println("StartGame request:"+request->url()+" response:"+" ok");
            
            //send to all connected player that the game has started
            toSendToSerial += ("/startGame?playerList=" + constructPlayerList()+"\n");
            gameStartedSSE->send("start",NULL,millis(),100);
            request->send(200,"text/plain","ok");
        }
    );
}
