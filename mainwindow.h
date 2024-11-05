#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QLineEdit>
#include <QSpinBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void createActions();
    QAction *openAct;
    QAction *saveAct;
    QLineEdit *nameLineEdit;
    QLineEdit *emailLineEdit;
    QSpinBox *ageSpinBox;

private slots:
    void openFile();
    void saveFile();

};
#endif // MAINWINDOW_H
