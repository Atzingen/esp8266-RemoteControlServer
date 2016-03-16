#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <IRremoteESP8266.h>

String s_html ="<!DOCTYPE html>"
"<html>"
    "<head>"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1, maximum-scale=1\">"
        "<link rel=\"stylesheet\" href=\"http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.css\">"
        "<script src=\"http://code.jquery.com/jquery-1.11.3.min.js\"></script>"
        "<script src=\"http://code.jquery.com/mobile/1.4.5/jquery.mobile-1.4.5.min.js\"></script>"
        "<script>"
            "$(function(){"
                "$(\"a\").click( function(){"
                    "var botaoId = $(this).attr(\'id\');"
                    "$.ajax({"
                        "type: \'GET\',"
                        "url: \'/\' + botaoId,"
                        "success: function(){"
                            "$(\'#tela\').css(\"background-color\", \"rgb(18, 161, 231)\");"
                            "$(\'#tela\').delay(200).queue(function (next) {"
                                "$(this).css(\"background-color\", \"white\");"
                                "next();"
                            "});"
                        "},"
                        "error: function() {"
                            "$(\'#tela\').css(\"background-color\", \"rgb(179, 79, 76)\");"
                            "$(\'#tela\').delay(200).queue(function (next) {"
                                "$(this).css(\"background-color\", \"white\");"
                                "next();"
                            "});"
                        "}"
                    "});"
                "});"
            "});"
        "</script>"
        "<style>.center {text-align: center;}</style>"
    "</head>"

    "<body>"
        "<div data-role=\"page\">"
            "<div data-role=\"header\">"
            "<h1>  Controle TV </h1>"
        "</div>"
        "<div id=\"tela\" data-role=\"content\">"
            "<div class=\"ui-grid-c\">"
                "<div class=\"ui-block-a\"><a id=\"bt1\" class=\"ui-btn\">  1 </a></div>"
                "<div class=\"ui-block-b\"><a id=\"bt2\" class=\"ui-btn\">  2 </a></div>"
                "<div class=\"ui-block-c\"><a id=\"bt3\" class=\"ui-btn\">  3 </a></div>"
                "<div class=\"ui-block-d\"><a id=\"bt_mais\" class=\"ui-btn\" style=\"background: #339966; color: white;\">  Vol + </a></div>"
            "</div>"
            "<div class=\"ui-grid-c\">"
                "<div class=\"ui-block-a\"><a id=\"bt4\" class=\"ui-btn\"> 4 </a></div>"
                "<div class=\"ui-block-b\"><a id=\"bt5\" class=\"ui-btn\"> 5 </a></div>"
                "<div class=\"ui-block-c\"><a id=\"bt6\" class=\"ui-btn\"> 6 </a></div>"
                "<div class=\"ui-block-d\"><a id=\"bt_menos\" class=\"ui-btn\" style=\"background: #339966; color: white;\">  Vol - </a></div>"
            "</div>"
            "<div class=\"ui-grid-c\">"
                "<div class=\"ui-block-a\"><a id=\"bt7\" class=\"ui-btn\">  7 </a></div>"
                "<div class=\"ui-block-b\"><a id=\"bt8\" class=\"ui-btn\">  8 </a></div>"
                "<div class=\"ui-block-c\"><a id=\"bt9\" class=\"ui-btn\">  9 </a></div>"
                "<div class=\"ui-block-d\"><a id=\"bt_ch_mais\" class=\"ui-btn\" style=\"background: #6699FF; color: white;\">  Ch + </a></div>"
            "</div>"
            "<div class=\"ui-grid-c center\">"
                "<div class=\"ui-block-a\"><a id=\"bt0\" class=\"ui-btn\">  0 </a></div>"
                "<div class=\"ui-block-b\"><a id=\"bt_cima\" class=\"ui-btn ui-icon-arrow-u ui-btn-icon-notext ui-btn-inline\" > </a></div>"
                "<div class=\"ui-block-c\"><a id=\"bt_audio\" class=\"ui-btn\" style=\"background: #00CC99; color: white;\">  audio </a></div>"
                "<div class=\"ui-block-d\"><a id=\"bt_ch_menos\" class=\"ui-btn\" style=\"background: #6699FF; color: white;\"> Ch -</a></div>"
            "</div>"

            "<div class=\"ui-grid-c center\">"
                "<div class=\"ui-block-a\"><a id=\"bt_esquerda\" class=\"ui-btn ui-icon-arrow-l ui-btn-icon-notext ui-btn-inline\">   </a> </div>"
                "<div class=\"ui-block-b\"><a id=\"bt_ok\" class=\"ui-btn\" style=\"background: red; color: white;\">  Ok </a></div>"
                "<div class=\"ui-block-c\"><a id=\"bt_direita\" class=\"ui-btn ui-icon-arrow-r ui-btn-icon-notext ui-btn-inline\">   </a> </div>"
                "<div class=\"ui-block-d\"><a id=\"bt_agora\" class=\"ui-btn\"> Now </a></div>"
            "</div>"
            "<div class=\"ui-grid-c center\">"
                "<div class=\"ui-block-a\"><a id=\"bt_info\" class=\"ui-btn\"> info </a></div>"
                "<div class=\"ui-block-b\"><a id=\"bt_baixo\" class=\"ui-btn ui-icon-arrow-d ui-btn-icon-notext ui-btn-inline\">   </a> </div>"
                "<div class=\"ui-block-c\"><a id=\"bt_play\" class=\"ui-btn\"> Play </a></div>"
                "<div class=\"ui-block-d\"><a id=\"bt_stop\" class=\"ui-btn\"> Stop </a></div>"
            "</div>"
            "<div class=\"ui-grid-c\">"
                "<div class=\"ui-block-a\"><a id=\"bt_voltar\" class=\"ui-btn\"> Voltar </a></div>"
                "<div class=\"ui-block-b\"><a id=\"bt_menu\" class=\"ui-btn\"> menu </a></div>"
                "<div class=\"ui-block-c\"><a id=\"bt_sair\" class=\"ui-btn\"> Sair </a></div>"
                "<div class=\"ui-block-d\"><a id=\"bt_legenda\" class=\"ui-btn\" style=\"background: #FFCC66; color: white;\">  legenda </a></div>"
            "</div>"
        "</div>"
    "</body>"
"</html>";

IRsend irsend(5);
const char* ssid = "Sandra2";
const char* password = "sandra123";

MDNSResponder mdns;
ESP8266WebServer server(80);

const long Vbt_1 = 3782901887;
const long Vbt_2 = 3782885570;
const long Vbt_3 = 3782918208;
const long Vbt_4 = 3782877407;
const long Vbt_5 = 3782910047;
const long Vbt_6 = 3782893727;
const long Vbt_7 = 3782926367;
const long Vbt_8 = 3782873327;
const long Vbt_9 = 3782905967;
const long Vbt_0 = 3782869247;
const long Vbt_mais = 3782914127;
const long Vbt_menos = 3782987807;
const long Vbt_ch_mais = 3782871287;
const long Vbt_ch_menos = 3782891687;
const long Vbt_audio = 3782928407;
const long Vbt_legenda = 3782875367;
const long Vbt_ok = 3782912087;
const long Vbt_sair = 3782889647;
const long Vbt_voltar = 3782903927;
const long Vbt_menu = 3782919227;
const long Vbt_cima = 3782922287;
const long Vbt_baixo = 3782881487;
const long Vbt_esquerda = 3782924327;
const long Vbt_direita = 3782883527;
const long Vbt_agora = 3782899847;
const long Vbt_stop = 3782888627;
const long Vbt_play = 3782896787;
const long Vbt_info = 3782920247;

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void mainPage()
{
  server.send(200, "text/html", s_html);
}


void bt1()
{
  irsend.sendNEC(Vbt_1, 36);
  server.send(200);
}

void bt2()
{
  irsend.sendNEC(Vbt_2, 36);
  server.send(200);
}

void bt3()
{
  irsend.sendNEC(Vbt_3, 36);
  server.send(200);

}

void bt4()
{
  irsend.sendNEC(Vbt_4, 36);
  server.send(200);
}

void bt5()
{
  irsend.sendNEC(Vbt_5, 36);
  server.send(200);
}

void bt6()
{
  irsend.sendNEC(Vbt_6, 36);
  server.send(200);
}

void bt7()
{
  irsend.sendNEC(Vbt_7, 36);
  server.send(200);
}

void bt8()
{
  irsend.sendNEC(Vbt_8, 36);
  server.send(200);
}

void bt9()
{
  irsend.sendNEC(Vbt_9, 36);
  server.send(200);
}

void bt0()
{
  irsend.sendNEC(Vbt_0, 36);
  server.send(200);
}

void bt_mais()
{
  irsend.sendNEC(Vbt_mais, 36);
  server.send(200);
}

void bt_menos()
{
  irsend.sendNEC(Vbt_menos, 36);
  server.send(200);
}

void bt_ch_mais()
{
  irsend.sendNEC(Vbt_ch_mais, 36);
  server.send(200);
}

void bt_legenda()
{
  irsend.sendNEC(Vbt_legenda, 36);
  server.send(200);
}

void bt_cima()
{
  irsend.sendNEC(Vbt_cima, 36);
  server.send(200);
}

void bt_audio()
{
  irsend.sendNEC(Vbt_audio, 36);
  server.send(200);
}

void bt_ch_menos()
{
  irsend.sendNEC(Vbt_ch_menos, 36);
  server.send(200);
}

void bt_esquerda()
{
  irsend.sendNEC(Vbt_esquerda, 36);
  server.send(200);
}

void bt_baixo()
{
  irsend.sendNEC(Vbt_baixo, 36);
  server.send(200);
}

void bt_direita()
{
  irsend.sendNEC(Vbt_direita, 36);
  server.send(200);
}

void bt_agora()
{
  irsend.sendNEC(Vbt_agora, 36);
  server.send(200);
}

void bt_voltar()
{
  irsend.sendNEC(Vbt_voltar, 36);
  server.send(200);
}

void bt_play()
{
  irsend.sendNEC(Vbt_play, 36);
  server.send(200);
}

void bt_stop()
{
  irsend.sendNEC(Vbt_stop, 36);
  server.send(200);
}

void bt_menu()
{
  irsend.sendNEC(Vbt_menu, 36);
  server.send(200);
}

void bt_sair()
{
  irsend.sendNEC(Vbt_sair, 36);
  server.send(200);
}

void bt_ok()
{
  irsend.sendNEC(Vbt_ok, 36);
  server.send(200);
}

void bt_info()
{
  irsend.sendNEC(Vbt_info, 36);
  server.send(200);
}

void setup()
{
  irsend.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  if (mdns.begin("esp8266", WiFi.localIP())) {

  }
  server.on("/", mainPage);
  server.on("/bt1", bt1);
  server.on("/bt2", bt2);
  server.on("/bt3", bt3);
  server.on("/bt4", bt4);
  server.on("/bt5", bt5);
  server.on("/bt6", bt6);
  server.on("/bt7", bt7);
  server.on("/bt8", bt8);
  server.on("/bt9", bt9);
  server.on("/bt0", bt0);
  server.on("/bt_mais", bt_mais);
  server.on("/bt_menos", bt_menos);
  server.on("/bt_ch_mais", bt_ch_mais);
  server.on("/bt_legenda", bt_legenda);
  server.on("/bt_cima", bt_cima);
  server.on("/bt_audio", bt_audio);
  server.on("/bt_ch_menos", bt_ch_menos);
  server.on("/bt_esquerda", bt_esquerda);
  server.on("/bt_baixo", bt_baixo);
  server.on("/bt_direita", bt_direita);
  server.on("/bt_agora", bt_agora);
  server.on("/bt_voltar", bt_voltar);
  server.on("/bt_play", bt_play);
  server.on("/bt_info", bt_info);
  server.on("/bt_stop", bt_stop);
  server.on("/bt_menu", bt_menu);
  server.on("/bt_sair", bt_sair);
  server.on("/bt_ok", bt_ok);
  server.onNotFound(handleNotFound);
  server.begin();
}

void loop()
{
  server.handleClient();
  delay(1);
}
