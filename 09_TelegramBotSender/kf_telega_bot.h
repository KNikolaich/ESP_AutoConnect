// Custom libraries

#include <FastBot.h>
FastBot bot(TLG_TOKEN);
/**************************************************************************************************/

// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим всю информацию о сообщении
  Serial.println(msg.toString());

  // отправить сообщение обратно
  bot.sendMessage(msg.text, msg.chatID);  
}

/* Main Function */
void TelegramSetup() {  
  bot.attach(newMsg);  
}

unsigned long delayForTb = millis();  // таймер для работы со считываниями
void TelegaLoop() {
  if (millis() - delayForTb > 100)
  {
    bot.tick();
    delayForTb = millis();
  }
}
