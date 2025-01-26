#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QClipboard>
#include <random>
#include <ctime>
#include <QDebug>
#include <QDir>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MainWindow::on_pushButton_2_clicked);

      QPixmap bkgnd(":/images/background.jpg");
        QPixmap scaledBkgnd = bkgnd.scaled(this->size(), Qt::KeepAspectRatioByExpanding);
        QPalette pal;
        pal.setBrush(QPalette::Window, scaledBkgnd);
        this->setPalette(pal);

 qDebug() << "Current working directory:" << QDir::currentPath();
    ui->spinBox->setMaximum(14);
    ui->spinBox->setMinimum(0);
    ui->horizontalSlider->setMaximum(14);
    ui->horizontalSlider->setMinimum(0);

    connect(ui->horizontalSlider, &QSlider::valueChanged, ui->spinBox, &QSpinBox::setValue);
    connect(ui->spinBox, QOverload<int>::of(&QSpinBox::valueChanged), ui->horizontalSlider, &QSlider::setValue);











}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::string pas = generatePassword(ui->horizontalSlider->value(),ui->checkBox_2->isChecked(),1,ui->checkBox_3->isChecked(),ui->checkBox->isChecked());
    QString qstrPassword = QString::fromStdString(pas); // Преобразование std::string в QString
    ui->lineEdit->setText(qstrPassword);
}

std::string MainWindow::generatePassword(int length, bool useLowercase, bool useUppercase, bool useNumbers, bool useSymbols) {
    std::string characters = "";
    if (useLowercase) {
        characters += "abcdefghijklmnopqrstuvwxyz";
    }
    if (useUppercase) {
        characters += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    }
    if (useNumbers) {
        characters += "0123456789";
    }
    if (useSymbols) {
        characters += "!@#$%^&*()_+=-`~[]\{}|;':\",./<>?";
    }

    if (characters.empty()) {
        return ""; // Возвращает пустую строку, если нет разрешенных символов
    }

    std::mt19937 generator(std::time(0));
    std::uniform_int_distribution<int> distribution(0, characters.length() - 1);


    std::string password = "";
    for (int i = 0; i < length; ++i) {
        password += characters[distribution(generator)];
    }
    return password;
}

void MainWindow::on_pushButton_2_clicked()
{
    QClipboard* clipboard = QApplication::clipboard();
    QString textToCopy = ui->lineEdit->text();
    clipboard->setText(textToCopy);
}

