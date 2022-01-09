#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <QWidget>

namespace Ui {
class Carousel;
}

class Carousel : public QWidget
{
    Q_OBJECT

public:
    explicit Carousel(QWidget *parent = nullptr);
    ~Carousel();

private:
    Ui::Carousel *ui;
};

#endif // CAROUSEL_H
