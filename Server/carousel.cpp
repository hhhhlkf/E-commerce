#include "carousel.h"
#include "ui_carousel.h"

Carousel::Carousel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Carousel)
{
    ui->setupUi(this);
}

Carousel::~Carousel()
{
    delete ui;
}
