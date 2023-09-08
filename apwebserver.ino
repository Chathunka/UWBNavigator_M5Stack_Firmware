
String jsonString;

AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>UWB_Navigator</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
  html {
    font-family: Arial, Helvetica, sans-serif;
    text-align: center;
  }
  h1 {
    font-size: 1.8rem;
    color: white;
  }
  h2{
    font-size: 1.5rem;
    font-weight: bold;
    color: #143642;
  }
  .topnav {
    overflow: hidden;
    background-color: #0f8b8d;
  }
  body {
    margin: 0;
  }
  .content {
    padding: 30px;
    max-width: 600px;
    margin: 0 auto;
  }
  .card {
    background-color: #F8F7F9;;
    box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5);
    padding-top:10px;
    padding-bottom:20px;
  }
  .button {
    padding: 15px 50px;
    font-size: 24px;
    text-align: center;
    outline: none;
    color: #fff;
    background-color: #0f8b8d;
    border: none;
    border-radius: 5px;
    -webkit-touch-callout: none;
    -webkit-user-select: none;
    -khtml-user-select: none;
    -moz-user-select: none;
    -ms-user-select: none;
    user-select: none;
    -webkit-tap-highlight-color: rgba(0,0,0,0);
   }
   /*.button:hover {background-color: #0f8b8d}*/
   .button:active {
     background-color: #0f8b8d;
     box-shadow: 2 2px #CDCDCD;
     transform: translateY(2px);
   }
   .state {
     font-size: 1.5rem;
     color:#8c8c8c;
     font-weight: bold;
   }
  </style>
<title>UWB_Naviagtor</title>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="icon" href="data:,">
</head>
<body>
  <div class="topnav">
    <h1>UWB Naviagtor</h1>
  </div>
  <div class="content">
    <div class="card">
      <h2>Distance data from Station 1</h2>
      <p class="state"><span id="state1">%STATE%</span> m</p>
    </div>
    <br/>
    <div class="card">
      <h2>Distance data from Station 2</h2>
      <p class="state"><span id="state2">%STATE%</span> m</p>
    </div>
    <br/>
    <div class="card">
      <h2>Distance data from Station 3</h2>
      <p class="state"><span id="state3">%STATE%</span> m</p>
    </div>
  </div>
<script>
  var gateway = `ws://${window.location.hostname}/ws`;
  var websocket;
  window.addEventListener('load', onLoad);
  function initWebSocket() {
    console.log('Trying to open a WebSocket connection...');
    websocket = new WebSocket(gateway);
    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage; // <-- add this line
  }
  function onOpen(event) {
    console.log('Connection opened');
  }
  function onClose(event) {
    console.log('Connection closed');
    setTimeout(initWebSocket, 2000);
  }
  function onMessage(event) {
    console.log(event.data);
    var myObj = JSON.parse(event.data);
    var keys = Object.keys(myObj);
  
    for (var i = 0; i < keys.length; i++){
      var key = keys[i];
      document.getElementById(key).innerHTML = myObj[key];
    }
  }
  function onLoad(event) {
    initWebSocket();
    initButton();
  }
  function initButton() {
    document.getElementById('button').addEventListener('click', toggle);
  }
  function toggle(){
    websocket.send('toggle');
  }
</script>
</body>
</html>
)rawliteral";

void notifyClients() {
  ws.textAll(jsonString);
}

void handleWebSocketMessage(void *arg, uint8_t *data, size_t len) {
  AwsFrameInfo *info = (AwsFrameInfo*)arg;
  if (info->final && info->index == 0 && info->len == len && info->opcode == WS_TEXT) {
    data[len] = 0;
    if (strcmp((char*)data, "toggle") == 0) {
      notifyClients();
    }
  }
}

void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type,
             void *arg, uint8_t *data, size_t len) {
  switch (type) {
    case WS_EVT_CONNECT:
      Serial.printf("WebSocket client #%u connected from %s\n", client->id(), client->remoteIP().toString().c_str());
      break;
    case WS_EVT_DISCONNECT:
      Serial.printf("WebSocket client #%u disconnected\n", client->id());
      break;
    case WS_EVT_DATA:
      handleWebSocketMessage(arg, data, len);
      break;
    case WS_EVT_PONG:
    case WS_EVT_ERROR:
      break;
  }
}

void initWebSocket() {
  ws.onEvent(onEvent);
  server.addHandler(&ws);
}

//String processor(const String& var){
//  Serial.println(var);
//  if(var == "STATE"){
//    if (ledState){
//      return "ON";
//    }
//    else{
//      return "OFF";
//    }
//  }
//  return String();
//}

void initAPServer(){
  Serial.print("Setting AP (Access Point)…");
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  initWebSocket();
  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  server.begin();
  delay(1000);
}

void updateClients(String dataString){
  if (WiFi.status() != WL_CONNECTED && WiFi.softAPgetStationNum() < 1) {
  }else {
    ws.cleanupClients();
    jsonString = dataString;
    notifyClients();
  }
}


void setWifi(int WIFIMODE){
  switch (WIFIMODE) {
    case 0:
        Serial.println("Wifi AP mode enter");
        if(!WIFIAPSetupDone){
          Serial.println("Wifi AP mode enter working");
          //set ap
          #ifdef APWEBSERVER
            initAPServer();
            delay(1000);
          #endif
          Serial.println("AP Mode setup finished.");
          WIFIAPSetupDone = true;
          WIFISTASetupDone = false;
        }
        break;
    case 1:
        if(!WIFISTASetupDone){
          //set station or shut down
          WiFi.enableAP(false);
          WiFi.softAPdisconnect();
          WiFi.softAPdisconnect(false);
          WiFi.mode(WIFI_MODE_STA);
          delay(1000);
          Serial.println("Station Mode setup finished.");
          WIFISTASetupDone = true;
          WIFIAPSetupDone = false;
        }
        break;
  }
}

void turnWifiAdapter(bool state){
  if(state){
    Serial.println("Turning on wifi");
    WiFi.reconnect();
    setWifi(0);
    //WiFi.forceSleepWake();  
  }else{
    Serial.println("Turning off wifi");
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
    //WiFi.forceSleepBegin();
    delay(1);
  }
}