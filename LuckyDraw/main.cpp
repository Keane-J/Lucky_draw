#include "luckydraw.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LuckyDraw w;
    w.init();
    w.show();
    return a.exec();
}
