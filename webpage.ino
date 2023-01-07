const char body[] PROGMEM = R"===(
<!DOCTYPE html>
<html>
<head>
<title>Sliders</title>
</head>
<body>
    <input type="text" id="message">
    <button type="button" onclick="sendRest()">REST</button>
    <button type="button" onclick="sendWall()">WALL</button>
    <button type="button" onclick="sendTower()">TOWER</button>
    <button type="button" onclick="sendPolice()">POLICE</button>
    <script>

        function sendRest(){
          var xhttp = new XMLHttpRequest();
          var str = "REST";
          var res = str;
          xhttp.open("GET", res, true);
          xhttp.send();
        }

        function sendTower(){
          var xhttp = new XMLHttpRequest();
          var str = "TOWER";
          var res = str;
          xhttp.open("GET", res, true);
          xhttp.send();
        }

        function sendWall(){
          var xhttp = new XMLHttpRequest();
          var str = "WALL";
          var res = str;
          xhttp.open("GET", res, true);
          xhttp.send();
        }

        function sendPolice(){
          var xhttp = new XMLHttpRequest();
          var str = "POLICE";
          var res = str;
          xhttp.open("GET", res, true);
          xhttp.send();
        }

        let msg = document.getElementById('message');
        

        msg.addEventListener("keydown", (event) => {
          if (event.repeat) return;
            if(event.key ==='w'){
              var xhttp = new XMLHttpRequest();
              var str = "LF";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='s'){
              var xhttp = new XMLHttpRequest();
              var str = "LB";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='u'){
              var xhttp = new XMLHttpRequest();
              var str = "RF";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='j'){
              var xhttp = new XMLHttpRequest();
              var str = "RB";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='g'){
              var xhttp = new XMLHttpRequest();
              var str = "LEFT";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='h'){
              var xhttp = new XMLHttpRequest();
              var str = "RIGHT";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
        });

        msg.addEventListener("keypress", (event) => {
            // handle keypress
        });

        msg.addEventListener("keyup", (event) => {
            if(event.key ==='w'){
              var xhttp = new XMLHttpRequest();
              var str = "LS";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='s'){
              var xhttp = new XMLHttpRequest();
              var str = "LS";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='u'){
              var xhttp = new XMLHttpRequest();
              var str = "RS";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='j'){
              var xhttp = new XMLHttpRequest();
              var str = "RS";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
            if(event.key ==='g' || event.key ==='h'){
              var xhttp = new XMLHttpRequest();
              var str = "SS";
              var res = str;
              xhttp.open("GET", res, true);
              xhttp.send();
            }
        });
    </script>
</body>
</html>)===";