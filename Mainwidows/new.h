#ifndef NEW_H
#define NEW_H

#include <QDialog>

namespace Ui {
class New;
}

class New : public QDialog
{
    Q_OBJECT

public:
    explicit New(QWidget *parent = 0);
    ~New();

private:
    Ui::New *ui;
};

#endif // NEW_H
