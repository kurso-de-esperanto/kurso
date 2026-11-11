#include "sendujo.h"
#include "ui_sendujo.h"

sendujo::sendujo(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::sendujo)
{
    ui->setupUi(this);
}

sendujo::~sendujo()
{
    delete ui;
}
