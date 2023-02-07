#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QDesktopServices>
#include <QProcess>
#include <QMessageBox>
#include <QKeyEvent>
#include <QTimer>

#define TEXT_LEFT_MARGIN    3
#define TEXT_RIGHT_MARGIN   3
#define TEXT_TOP_MARGIN     0
#define TEXT_BOTTOM_MARGIN  0

void delay(int millisecondsWait)
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(millisecondsWait);
    loop.exec();
}

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , about(nullptr)
    , existIdlPath(false)
    , existXmlPath(false)
{
    QMargins text_margin = {TEXT_LEFT_MARGIN, TEXT_TOP_MARGIN, TEXT_RIGHT_MARGIN, TEXT_BOTTOM_MARGIN};
    ui->setupUi(this);
    ui->idlPathEdit->setStyleSheet("background-color: #e5ffcc");
    ui->xmlPathEdit->setStyleSheet("background-color: #e5ffcc");
    ui->idlPathEdit->setTextMargins(text_margin);
    ui->xmlPathEdit->setTextMargins(text_margin);
    ui->idlPathEdit->setCursor(Qt::IBeamCursor);
    ui->xmlPathEdit->setCursor(Qt::IBeamCursor);
    ui->xmlPathEdit->setText("<same as input directory>");
    qApp->setStyleSheet("QMainWindow { background:rgb(245,245,245); }"
                        "QGroupBox { border: 1px solid silver; margin-top: 10px; }"
                        "QGroupBox::title { left: 5px; top: -8px; }");
    ui->label->setStyleSheet("margin-bottom: 3px");
    ui->label_2->setStyleSheet("margin-bottom: 3px");
    ui->lowwidget->setStyleSheet("background:rgb(255,255,255)");
    ui->openDirBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    if (event->key()==Qt::Key_Escape) {
        qApp->quit();
    }
}

void MainWindow::on_idlPathBtn_clicked()
{
    QString openDirPath;
    if(existIdlPath) {
        openDirPath = QFileInfo(ui->idlPathEdit->text()).absoluteDir().absolutePath();
    } else {
        openDirPath = QDir::homePath();
    }

    QString file_path = QFileDialog::getOpenFileName(this, "open File", openDirPath, "File (*.idl)");
    if(file_path.length() == 0) {
        file_path = ui->idlPathEdit->text();
    } else {
        existIdlPath = true;
        ui->idlPathEdit->setStyleSheet("background-color: #e5ffcc");
    }
    ui->idlPathEdit->setText(file_path);

    if(existIdlPath) {
        ui->runBtn->setEnabled(true);
        ui->openDirBtn->setEnabled(true);
    }
}

void MainWindow::on_xmlPathBtn_clicked()
{
    QString openDirPath;
    if(existXmlPath) {
        openDirPath = ui->xmlPathEdit->text();
    } else if(existIdlPath) {
        openDirPath = QFileInfo(ui->idlPathEdit->text()).absoluteDir().absolutePath();
    } else {
        openDirPath = QDir::homePath();
    }

    QString dir_path = QFileDialog::getExistingDirectory(this, "search Folder", openDirPath, QFileDialog::ShowDirsOnly);
    if(dir_path.length() == 0) {
        dir_path = ui->xmlPathEdit->text();
    } else {
        existXmlPath = true;
        ui->openDirBtn->setEnabled(true);
    }
    ui->xmlPathEdit->setText(dir_path);

    if(existIdlPath)
        ui->runBtn->setEnabled(true);
}

void MainWindow::on_runBtn_clicked()
{
    QString program = QCoreApplication::applicationDirPath() + "/idl2xml";
    QStringList arguments;
    QString xmlDirPath;
    if(!existXmlPath) {
        xmlDirPath = QFileInfo(ui->idlPathEdit->text()).absoluteDir().absolutePath();
    } else {
        xmlDirPath = ui->xmlPathEdit->text();
    }
    arguments << ui->idlPathEdit->text() << xmlDirPath;
    QProcess* myProcess = new QProcess();
    myProcess->start(program, arguments);
    if(myProcess->waitForStarted(1000)) {
        if(myProcess->waitForFinished(1000)) {
            QMessageBox msgBox;
            msgBox.move(this->geometry().center().x() - (msgBox.frameGeometry().right()/7),
                        this->geometry().center().y() - (msgBox.frameGeometry().bottom()/11));

            if(myProcess->exitCode() == 0) {
                msgBox.setWindowTitle(" ");
                msgBox.setText("Conversion succeeded.");
                msgBox.exec();
            } else {
                QString bufStr = QString(myProcess->readAllStandardOutput());
                QString errStr;
                int eIdx = bufStr.indexOf("E") + 3;

                for(int i = eIdx; i < bufStr.length()-1; i++)
                    errStr.append(bufStr.at(i));

                if(errStr.length() > 0)
                    msgBox.critical(this, "error", "\n" + errStr);
            }
        }
    }
}

void MainWindow::on_openIdlBtn_clicked()
{
    if(!existIdlPath) {
        ui->idlPathEdit->setText("Please select the input file");
        ui->idlPathEdit->setStyleSheet("background-color: #f8d4d4");
        return;
    }
    QString file_path = ui->idlPathEdit->text();
    QDesktopServices::openUrl(QUrl("file:///" + file_path, QUrl::TolerantMode));
    ui->openIdlBtn->setEnabled(false);
    delay(1000);
    ui->openIdlBtn->setEnabled(true);
}

void MainWindow::on_openDirBtn_clicked()
{
    QString url = ui->xmlPathEdit->text();
    if(!existXmlPath) {
        url = QFileInfo(ui->idlPathEdit->text()).absoluteDir().absolutePath();
    }

    QDesktopServices::openUrl(QUrl::fromLocalFile(url));
}

void MainWindow::on_aboutBtn_clicked()
{
    about = new AboutDialog(this);
    about->setStyleSheet("background:rgb(245,245,245)");
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->show();
}
