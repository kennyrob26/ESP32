const char index_html[] PROGMEM = R"rawliteral( 
<!DOCTYPE html>
<html lang="pt-br">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Led PWM via browser</title>
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
            width: 200px;
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
        p#resultado{
            margin-top: 1px;
        }
    </style>
</head>
<body>

    <h1>Controlando o brilho de um led</h1>
    <section>
        
        <p>Defina o brilho:</p>
        <p><input id="barra" type="range" onchange="atualiza()" min="0" max="255"></p>
        <p id="resultado"></p>
    </section>


    <script>
        function atualiza(){
            var barra = document.getElementById("barra").value;
            var resultado = document.getElementById("resultado");
            resultado.innerText = barra;

            var req = new XMLHttpRequest();
            req.open("GET", "/led?canal=0&brilho="+barra, true)
            req.send();
        }

    </script>
</body>
</html>

)rawliteral";