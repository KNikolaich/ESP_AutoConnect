// бот отправляет обратно сообщения из любого чата (эхо-бот)

// закрепление и открепление сообщений
// напиши unpin для открепления всех сообщений

#define BOT_TOKEN "your bot token"
#define CHAT_ID "your chat id"

#include <FastBot.h>
FastBot bot(BOT_TOKEN);

// обработчик сообщений
void newMsg(FB_msg& msg) {
  // выводим всю информацию о сообщении
  Serial.println(msg.toString());

  // отправить сообщение обратно
  bot.sendMessage(msg.text, msg.chatID);  
}

void bot_setup() {
  bot.attach(newMsg);
}

void bot_loop() {
  bot.tick();
}

