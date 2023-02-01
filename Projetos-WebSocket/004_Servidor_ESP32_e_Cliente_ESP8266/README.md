# Websocket com cliente e servidor ESP

## Resumo
Projetinho muito simples mas importante, permitindo a conexão entre ESPs através da rede WiFi, no exemplo em questão um ESP32 faz a função de servidor e um ESP8266 é o cliente, mas obviamente é possível conectar outros ESPs como cliente, ou até mesmo gerar conteúdo para o browser.  
O projeto é muito importante pois é a base para qualquer projeto IoT, aqui nós conseguimos centralizar toda a informação em um únco ESP, que poderia ser um servidor local (PHP, C# etc..), um servidor na nuvem, um raspberry PI... Ou seja, conseguimos criar uma aplicação que se comunica com o servidor e este por sua vez faz a comunicação com os ESPs presente em um ambiente, recebendo e enviando dados.  
