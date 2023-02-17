
const char webRootPage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8" data-bs-theme="dark">
  <title>Жарь цыплят, гони гусей</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css" type="text/css">
  <link rel="stylesheet" href="default/theme.css">
  <!-- Bootstrap CSS -->
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC" crossorigin="anonymous">
  <style>
    body{
      background: linear-gradient( #bbb, transparent 1px), linear-gradient( 90deg, #bbb, transparent 1px);
      background-size: 15px 15px;
      background-position: center center;
    }
  </style>
</head>

<body >
  <nav class="navbar navbar-expand-lg fixed-top ">
    <a class="navbar-brand" href="/_ac">Об этом</a>
    <button class="navbar-toggler" type="button" data-toggle="collapse" data-target="#navbarSupportedContent" aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="Toggle navigation">
      <span class="navbar-toggler-icon"></span>
    </button>
    <div class="collapse navbar-collapse " id="navbarSupportedContent">
      <ul class="navbar-nav mr-4">
        <li class="nav-item">
          <a class="nav-link " href="/led">Два светодиода</a>
        </li>
        <li class="nav-item">
          <a class="nav-link " href="/_ac/update">OTA</a>
        </li>
        <li class="nav-item">
          <a class="nav-link " href="/_ac/config">Новая AP</a>
        </li>
        <li class="nav-item">
          <a class="nav-link " href="/_ac/open">SSIDs</a>
        </li>
      </ul>
    </div>
  </nav>
  <p><br></p>


  <center>
  <div class="card">
    <div class="card-header">Данные с датчика DS18B20 и состояние светодиода.</div>
    <div class="card-body">
      <h4>Temp(ºC): <span id="adc_val">-300</span></h4>
      <h5>LED state: <span id="led_state">NA</span></h5>
    </div>
  </div>
  </center>
  <script>
    setInterval(function() {
      getData();
      getLedState();
    }, 2000);

    function getData() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("adc_val").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "ds18b20read", true);
      xhttp.send();
    }
    function getLedState() {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          document.getElementById("led_state").innerHTML = this.responseText;
        }
      };
      xhttp.open("GET", "led_state_read", true);
      xhttp.send();
    }
  </script>
  <script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous" style=""></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.6/umd/popper.min.js" integrity="sha384-wHAiFfRlMFy6i5SRaxvfOCifBUQy1xHdJ/yoi7FRNXMRBu5WHdZYu1hA6ZOblgut" crossorigin="anonymous"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/js/bootstrap.min.js" integrity="sha384-JjSmVgyd0p3pXB1rRibZUAYoIIy6OrQ6VrjIEaFf/nJGzIxFDsf4x0xIM+B07jRM" crossorigin="anonymous"></script>
</body>

</html>
)=====";