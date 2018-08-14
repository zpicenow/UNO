#ifndef HELPTEXT_H
#define HELPTEXT_H


#include <QWidget>

namespace Ui {
class helpText;
}

class helpText : public QWidget
{
    Q_OBJECT

public:
    explicit helpText(QWidget *parent = 0);
    ~helpText();

private:
    Ui::helpText *ui;
};

#endif // HELPTEXT_H
