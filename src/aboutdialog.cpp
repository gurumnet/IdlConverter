#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include <QPixmap>

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    QPixmap pix(QCoreApplication::applicationDirPath() + "/../resource/logo.png");
    ui->label_logo->setPixmap(pix.scaled(300,300,Qt::KeepAspectRatio));
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    this->close();
}

void AboutDialog::on_licenseBtn_clicked()
{
    license = new LicenseDialog(this);
    license->setStyleSheet("background:rgb(245,245,245)");
    license->setAttribute(Qt::WA_DeleteOnClose);
    license->show();
}
