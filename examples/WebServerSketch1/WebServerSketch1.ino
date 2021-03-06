
/*
 * 2016-11-26 dvb
 * An example server with two pages and buttons to go between them.
 */
#include <OmEspHelpers.h>

// These includes arent used in this file, but tells Arduino IDE that this project uses them.
#include <ESP8266WebServer.h> 
#include <ESP8266WiFi.h> 

OmWebServer s;
OmWebPages p;

void setup() 
{
  Serial.begin(115200);
  Serial.printf("\n\n\nWelcome to the Sketch\n\n");

  // Add networks to attempt connection with.
  // It will go down the list and repeat until on succeeds.
  // This only happens when tick() is called.
  s.addWifi("connection will fail", "haha");
  s.addWifi("omino warp", "0123456789");
  s.addWifi("caffe pergolesi", "yummylatte");

  // Configure the web pages
  // This is just setting them up; they'll be delivered
  // by the web server when queried.
  p.beginPage("page 1");
  p.addPageLink("page 2"); // shows up as a button.

  // This html code is executed on each request, so
  // current values and state can be shown.
  p.addHtml([] (OmXmlWriter &w, int ref1, void *ref2)
  {
    w.addContent("welcome to page 1");
    w.addElement("hr");
    w.addContent("the milliseconds are...");
    w.beginElement("h1");
    w.addContentF("%dms", millis());
    w.endElement();
  });
  
  p.beginPage("page 2");
  p.addPageLink("page 1");
  p.addHtml([] (OmXmlWriter &w, int ref1, void *ref2)
  {
    w.addContent("welcome to page 2");
    w.addElement("hr");
    w.beginElement("pre");
    w.addContentF("serverIp: %s\n", omIpToString(s.getIp()));
    w.addContentF("  yourIp: %s\n", omIpToString(s.getClientIp()));
    w.endElement();
  });
    
  s.setHandler(p);
}

int ticks = 0;
void loop() 
{
  delay(10);
  s.tick();
}
