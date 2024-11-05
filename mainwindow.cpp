#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QAction>
#include <QKeySequence>
#include <QFile>
#include <QMessageBox>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>

//Constructor
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Title and central widget
    setWindowTitle("XML");
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    createActions();    //Creating menu bar

    //Creating and adding objects to main layout
    QFormLayout *layout = new QFormLayout;

    nameLineEdit = new QLineEdit();
    emailLineEdit = new QLineEdit();
    ageSpinBox = new QSpinBox();

    layout->addRow("&Name:", nameLineEdit);
    layout->addRow("&Email:", emailLineEdit);
    layout->addRow("&Age:", ageSpinBox);
    widget -> setLayout((layout));

    setMinimumSize(160, 160);
    resize(250, 180);
}

// Function creating menu bar and open and save actions
void MainWindow::createActions()
{
    openAct = new QAction("&Open", this);
    openAct -> setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile); //Connecting menu element to function

    saveAct = new QAction("&Save", this);
    saveAct -> setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile); //Connecting menu element to function

    menuBar() -> addAction(openAct);
    menuBar() -> addAction(saveAct);
}

void MainWindow::openFile()
{
    QDomDocument doc("student");
    QFile file("C:\\Users\\Karthik Sreekumar\\Desktop\\FAU\\S3\\Qt\\Xml2\\student.xml");

    // If file doesn't exist
    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox msgBox;
        msgBox.setText("File does not exist. Creating empty file.");
        msgBox.exec();
        file.open(QFile::WriteOnly);
        return;
    }
    if(!doc.setContent(&file))
    {
        file.close();
        return;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomNode n = docElem.firstChild();

    QDomElement e = n.toElement();
    this->nameLineEdit->setText(e.attribute("name"));
    this->emailLineEdit->setText(e.attribute("email"));
    this->ageSpinBox->setValue(e.attribute("age").toInt());

}

void MainWindow::saveFile()
{
    QDomDocument doc;
    QDomElement students = doc.createElement("students");
    doc.appendChild(students);
    QDomElement student1 = doc.createElement("student1");
    students.appendChild(student1);
    student1.setAttribute("name", this->nameLineEdit->text());
    student1.setAttribute("email", this->emailLineEdit->text());
    student1.setAttribute("age", this->ageSpinBox->value());

    QFile file("C:\\Users\\Karthik Sreekumar\\Desktop\\FAU\\S3\\Qt\\Xml2\\student.xml");
    if(file.open(QFile::WriteOnly | QFile::Text)){
        QTextStream in(&file);
        in<<doc.toString();
        file.flush();
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
