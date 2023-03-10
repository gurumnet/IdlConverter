#include "licensedialog.h"
#include "ui_licensedialog.h"

LicenseDialog::LicenseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LicenseDialog)
{
    ui->setupUi(this);
    ui->textBrowser->setStyleSheet("QTextBrowser { background:rgb(255,255,255) }");
}

LicenseDialog::~LicenseDialog()
{
    delete ui;
}

void LicenseDialog::on_buttonBox_accepted()
{
   this->close();
}
