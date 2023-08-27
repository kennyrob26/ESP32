# Trabalhando com Ponto de acesso no ESP32 (modo AP)

## Qual a utilidade de um Ponto de acesso?
Em geral é muito comum nos conectarmos a uma rede WiFi, mas em certas ocasiões
é interessante o uso do esp como um Ponto de Acesso, assim conseguimos nos comunicar
com o microcontrolador sem acesso a internet, conectando diretamente com o mesmo, via WiFi.  
Para mais informações sobre como utilizar, e as vantagens do modo AP, eu recomendo o tutorial
do [*Random Nerd Tutorials - How to Set an ESP32 Access Point (AP) for Web Server*](https://randomnerdtutorials.com/esp32-access-point-ap-web-server/).  

## Como utilizar o ESP em modo AP?
### A biblioteca WiFi.h
Para isso nós utilizamos a conhecida biblioteca ```WiFi.h```. Vamos ver alguns detalhes do código:  
Se você já está acostumado com a biblioteca ```WiFi.h``` é bem provável que conheça o método
```.begin();``` que conecta em uma rede WiFI.  

### O método .softAP()
Mas para utilizarmos o **esp como AP**, é necessário
utilizarmos um outro método que possuí sintaxe muito parecida, este método é o ```.softAP();```:  
```
WiFi.softAP(ssid, senha);
```  
onde:  
* **ssid  ->** é o nome do ponto de acesso, ou seja, o que vamos buscar na redes WiFi disponíveis.
* **senha ->** é a senha necessária para que um usuário se conecte ao ponto de acesso.  

### Todos os atributos do .softAP()
Esse é o modo mais simples de utilizar o método. Mas existem outros atributos que são importantes:  
```
WiFi.softAP(const char* ssid, const char* senha, int canal, int ssid_hidden, int max_connection );  
```  
onde:  
* **ssid           ->** é o nome do ponto de acesso, ou seja, o que vamos buscar na redes WiFi disponíveis.
* **senha          ->** é a senha necessária para que um usuário se conecte ao ponto de acesso.  
* **canal          ->** é o canal WiFI que o ponto de acesso utilizará  (0 - 13)
* **ssid_hidden    ->** é possível ocultar a visibilidade do SSID (se 1 estará oculto, se 0 estará visível);
* **max_connection ->** é possível limitar a quantidade de usuários simultâneos (1 - 4);  
 
 ### Obter o IP do Ponto de Acesso
 Para saber o IP do ponto de acesso nós utilizamos o método ```.softAPIP();```, que também é bem simples
 de se utilizar:   
 ```
 IPAdress IP = WiFI.softAPIP();
 Serial.println(IP);
 ```