// Definitions of AutoConnectAux page
static const char HOME[] PROGMEM = R"(
{
  "title": "Hello",
  "uri": "/",
  "menu": true,
  "element": [
    {
      "name": "cap",
      "type": "ACText",
      "value": "This is a custom web page."
    }
  ]
}
)";
//
//
const char* HELLO_URI = "/hello";
ACText(Caption, "Hello, world", "", "", AC_Tag_DIV);
ACRadio(Styles, {}, "");
ACSubmit(Apply, "Apply", HELLO_URI);
//
//
//// AutoConnectAux for the custom Web page.
AutoConnectAux helloPage(HELLO_URI, "Hello", true, { Caption, Styles, Apply });

// Redirects from root to the hello page.
void onRoot() {
  WiFiWebServer&  webServer = Portal.host();
 // ACText(Caption, "Hello, world", "", "", AC_Tag_DIV);
  // ACInput("portalName", )
  webServer.sendHeader("Location", String("http://") + webServer.client().localIP().toString() + "/hello");
 webServer.send(302, "text/plain", "");
 webServer.client().flush();
 webServer.client().stop();
  //webServer.send(200, "text/html", HOME);
}

// & тут обязательный символ, обозначает пердачу объекта в качестве ссылки
void joinPages(AutoConnect       &portal)
{  
 portal.join(helloPage);     // Join the hello page.
// portal.append("/hello", helloPage); // т.о. можно добавить какую то кастомную страницу
  
 WiFiWebServer&  webServer = portal.host();
  webServer.on("/", onRoot); 
}
