#ifndef LICENSEDIALOG_H
#define LICENSEDIALOG_H

#include <QDialog>

namespace Ui {
class LicenseDialog;
}

class LicenseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LicenseDialog(QWidget* parent = nullptr);
    ~LicenseDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::LicenseDialog* ui;
};

#endif // LICENSEDIALOG_H
