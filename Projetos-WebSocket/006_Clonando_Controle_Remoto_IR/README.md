# Controlando TV via ESP32 utilizado IR
Exemplo de teste, para ver qual seria a viabilidade de automatizar equipamento IR (infra vermelho) com a biblioteca [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266)  
## Receber comando do controle e "salvar" no esp
Para obtermos o código RAW de cada tecla utilizamos os exemplos presentes dentro da própria biblioteca [IRrecvDump.ino](https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRrecvDump/IRrecvDump.ino) e [IRrecvDumpV2.ino](https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRrecvDumpV2/IRrecvDumpV2.ino), no caso do ESP32 o exemplo utilizará o pino 14 para coletar o código de cada tecla.  
## Enviar comandos do ESP para a TV
Para enviarmos comandos IR para a Televisão, também utilizamos o exemplo chamado de [IRsendDemo.ino](https://github.com/crankyoldgit/IRremoteESP8266/blob/master/examples/IRsendDemo/IRsendDemo.ino).  
## Controlando a TV via browser
Além disso, basicamente criei um servidor websocket no esp32 e do browser enviei comandos para o ESP, que por sua vez validava e enviava o comando correspondente para a tv.  
