const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
    <html lang="pt-BR">
    <head>
        <meta charset="UTF-8">
        <meta http-equiv="X-UA-Compatible" content="IE=edge">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Controlando Led</title>
        <style>

        </style>
    </head>
    <body>
        <h1>Botão no browser</h1>
        <p><button id="acender" onclick="acender()" >ON</button></p>
        <p><button id="apagar" onclick="apagar()" >OFF</button></p>

        <script>
            function acender(){
                var req = new XMLHttpRequest();
                req.open("GET", "/update?output=2&state=1", true);
                req.send();
            }
            function apagar(){
                var req = new XMLHttpRequest();
                req.open("GET", "/update?output=2&state=0", true);
                req.send()
            }

            

        </script>
    </body>
    </html>
  
 )rawliteral";
    
