#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aboutdialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    enum class FileFormat {
        IDL,
        XML
    };
public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private slots:

    void on_idlPathBtn_clicked();

    void on_xmlPathBtn_clicked();

    void on_runBtn_clicked();

    void on_openIdlBtn_clicked();

    void on_openDirBtn_clicked();

    void on_aboutBtn_clicked();

private:
    //void DrawFile(QString file_path, FileFormat format);
    void keyPressEvent(QKeyEvent* event);
private:
    Ui::MainWindow* ui;
    AboutDialog* about;
    bool existIdlPath;
    bool existXmlPath;
};
#endif // MAINWINDOW_H
