#include <QApplication>
#include "index.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Index q;
    q.setWindowTitle("UNO");
    q.show();

    return a.exec();
}
