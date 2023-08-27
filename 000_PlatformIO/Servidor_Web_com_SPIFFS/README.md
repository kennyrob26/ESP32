# Criando um servidor utilizando SPIFFS

## O diretório data
O diretŕio data é onde colocamos os arquivos desejados, no caso desse exemplo nós temos um arquivo **html** e um arquivo **css**.  
Lembrando que é necessário upar a imagem dos arquivos para a memória eeprom do ESP.  

## Relembrando conceitos sobre a biblioteca AsyncWebServer
A biblioteca AsyncWebServer permite uma comunicação assincrona entre servidor e cliente. Para fazer uso da biblioteca nós a incluimos, e também conectamos o ESP ao WiFi.  

```AsyncWebServer server(80);``` -> Instancia o objeto server  
```
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, atualizaStatus);
  });
```
Nesse caso "/" representa a home do nosso site "IpDoSite/". *request->send* recebe 5 argumentos, sendo eles:  
1. **SPIFFS**         -> Significa que é um conteúdo presente na memória EEPROM do ESP.  
2. **"/index.html"**  -> É o arquivo que estamos buscando.
3. **String()**       -> É o cabeçalho HTTP, nesse caso ele é vazio
4. **false**          -> É relacionado com o envio da mensagem, false para bloco único, e true para segmentar a mensagem
5. **atualizaStatus** -> É a função callback que será chamada, ou seja quando o usuário acessar "/" a função atualizaStatus será chamada.  

```server.begin();``` -> é onde de fato o nosso servidor será iniciado.