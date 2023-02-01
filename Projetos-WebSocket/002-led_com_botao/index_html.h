const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Servidor Web Socket</title>
    <style>
        body{
            background-color: rgb(65, 64, 64);
            font-family: Arial, Helvetica, sans-serif;
            width: 350px;
            margin: auto;
            text-align: center;
            color: rgba(255, 255, 255, 0.747);
        }
        section{
            margin: auto;
            padding: 10px 20px 10px 20px;
            width: 100px;
            border: 1px solid rgba(255, 255, 255, 0.336);
            box-shadow: 1px 1px 3px rgba(0, 0, 0, 0.425);
        }
        h1{
            text-shadow: 2px 2px 4px rgba(0, 0, 0, 0.719);
        }
        p{
            font-size: 1.2em;
            font-weight: bold;
            margin: 2px;
            text-shadow: 1px 1px 3px black;
        }
        #botao{
            color: white;
            //background-color: gray;
            border-radius: 10px;
            padding: 6px;
            font-weight: bold;

        }
    </style>
</head>
<body>
    <h1>Trabalhando com WebSocket</h1>
    <section>
        <p >GPIO 2</p>
        <p><button id="botao">Default</button></p>
    </section>

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
            var botao = document.getElementById('botao');
            var paragrafo = document.getElementById('estado');
            if (event.data == "1"){
                estado = "ON";
                botao.style.background = "green";
            }
            else{
                estado = "OFF";
                botao.style.background= "red";
            }
            botao.innerText = estado;
            //paragrafo.innerHTML = estado;
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