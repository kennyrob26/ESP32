const char index_html[] PROGMEM = R"rawliteral(

<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>WebSocket Sensor de presença</title>
</head>
<body>
    <h1>Sensor de presença</h1>
    <p id="notifica">default</p>

    <script>
        var gateway = `ws://${window.location.hostname}/ws`;
        var websocket;
        
        window.addEventListener('load', onLoad);
        
        function iniciarWebSocket(){
            websocket = new WebSocket(gateway);
            websocket.onopen    = onOpen;
            websocket.onclose   = onClose;
            websocket.onmessage = onMessage;
        }

        function onOpen(event){
            console.log("Conexão aberta");
        }

        function onClose(event){
            console.log("Conexão foi fechada");
            setTimeout(iniciarWebsocket, 2000);
        }

        function onMessage(event){
            var notifica = document.getElementById("notifica");
            if(event.data == "movimento"){
                notifica.innerText = "ALERTA, movimento detectado";
                notifica.style.color = "red";
            }else if(event.data == "!movimento"){
                notifica.innerText = "Nenhum movimento detectado";
                notifica.style.color = "green";
            }

        }

        //Colocamos aqui as funções que serão chamadas após a página carregar
        function onLoad(event){
            iniciarWebSocket();
        }



    </script>
</body>
</html>

)rawliteral";