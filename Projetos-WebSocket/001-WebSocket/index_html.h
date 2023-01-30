const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Servidor Web Socket</title>
</head>
<body>
    <h1>Trabalhando com WebSocket</h1>
    <p >GPIO 2: <span id="estado">%ESTADO%</span></p>
    <p><button id="botao">ON/OFF</button></p>

    <script>
        var gateway = `ws://${window.location.hostname}/ws`;
        var websocket;
        window.addEventListener('load', onLoad);



        function iniciarWebSocket(){
            console.log('Tentando iniciar uma conexão websocket');
            websocket = new WebSocket(gateway);
            websocket.onopen = onOpen;
            websocket.onclose = onClose;
            websocket.onmessage = onMessage;
        }

        function onOpen(event){
            console.log("Conexão aberta");
        }

        function onClose(event){
            console.log("A conexão foi fechada");
            //Ou seja, se a conexão for fechada ele inicia novamente em 2 segundos
            setTimeout(iniciarWebSocket, 2000);
        }

        function onMessage(event){
            var estado;
            if (event.data == "1"){
                estado = "ON";
            }
            else{
                estado = "OFF";
            }
            var paragrafo = document.getElementById('estado');
            paragrafo.innerHTML = estado;
        }

        function onLoad(event){
            iniciarWebSocket();
            checaBotao();
        }

        function checaBotao(){
            var botao = document.getElementById('botao');
            botao.addEventListener('click', pressionou);
        }

        function pressionou(){
            websocket.send('pressionou');
        }

    </script>
</body>
</html>
)rawliteral";