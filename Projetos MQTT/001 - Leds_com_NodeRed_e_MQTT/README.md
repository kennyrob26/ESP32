# Controlando leds via Node-red
Projetinho bem simples utilizando a biblioteca PubSubClient, Node-red e o broker mosquitto, a minha base está nesse projeto do Rui Santos da [random nerd tutorials](https://randomnerdtutorials.com/esp32-mqtt-publish-subscribe-arduino-ide/). O projeto dele envolve também leitura de sensores, mas como é o meu primeiro contato com o node-res e o protocolo MQTT, preferi simplicar para apenas acionamento de leds.  

## Node Red

Criamos um único tópico no node red, com o nome de **esp32/leds**  
Esse tópico envia as seguintes mensagens **led1_on** ou **led1_off** caso aconteça alguma interação com o **botão led1**, e recebemos as mensagens **led2_on** ou **led2_off** no caso do **botão led2**  

## ESP32 / Arduino IDE

Como já foi dito vamos utilizar a biblioteca [PubSubClient](https://github.com/knolleary/pubsubclient), ela é bem simples de se utilizar.  
Como vimos anteriormente nós temos 2 botões, onde cada um deles envia mensagens para ligar ou desligar um dos leds, o código que trata essa informação pode ser visto abaixo:

``` 
  if(String(topic) == "esp32/leds"){
    Serial.print("Recebemos a mensagem:");

    //Apaga ou acende o led 1
    if(messageTemp == "led1_on"){
      Serial.println("led1_on");
      digitalWrite(led1, HIGH);
    }
    else if(messageTemp == "led1_off"){
      Serial.println("led1_off");
      digitalWrite(led1, LOW);
    }

    //apaga ou acende o led 2
    else if(messageTemp == "led2_on"){
      Serial.println("led2_on");
      digitalWrite(led2, HIGH);
    }
    else if(messageTemp == "led2_off"){
      Serial.println("led2_off");
      digitalWrite(led2, LOW);
    }
    
  }
```


