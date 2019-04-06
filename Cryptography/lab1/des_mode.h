#ifndef DESMODE_H
#define DESMODE_H

enum DESMode
{
    ECB, // electronic code book — режим «электронной кодовой книги» (простая замена)
    CBC, // cipher block chaining — режим сцепления блоков
    CFB, // cipher feed back — режим обратной связи по шифротексту
    OFB, // output feed back — режим обратной связи по выходу
};

#endif // DESMODE_H
