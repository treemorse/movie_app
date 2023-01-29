#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    renderArea = new RenderArea(ui->frame);
    ui->gridLayout_2->addWidget(renderArea);
}

AboutDialog::~AboutDialog()
{
    delete ui;
    delete renderArea;
}
