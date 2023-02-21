// бот отправляет обратно сообщения из любого чата (эхо-бот)

#include <FastBot.h>
FastBot bot(BOT_TOKEN);

void TelegramSetup() {

  bot.setChatID(CHAT_ID);
  bot.setTextMode(FB_MARKDOWN);     // вернуть по умолчанию - FB_TEXT
  // по форматированию читай тут https://core.telegram.org/bots/api#formatting-options
  bot.sendMessage(F("*Bold*, ||spoiler||, ~Strike~, `code`, [alexgyver.ru](https://alexgyver.ru/)"));
}

void TelegaLoop() {
  bot.tick();
}
