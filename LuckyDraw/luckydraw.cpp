#include "luckydraw.h"
#include "ui_luckydraw.h"
#include <QFile>
#include <QTextStream>
#include <QList>
#include <QString>
#include <QDebug>
#include <QDir>
#include <QDateTime>
#include <QtAlgorithms>

LuckyDraw::LuckyDraw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LuckyDraw)
{
    ui->setupUi(this);
    QThread * t = new QThread();
    connect(t, SIGNAL(finished()), t, SLOT(QObject::deleteLater()));
    t->start();
}

void LuckyDraw::init() {
    QFile * file = new QFile(QString(":/name.txt"), this);
    qDebug() << QDir::currentPath();
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "222";
        return;
    }
    qDebug() << "111";
    QTextStream in(file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        m_list.append(line);
        //process_line(line);
    }
}
LuckyDraw::~LuckyDraw()
{
    delete ui;
}

void LuckyDraw::on_pushButton_3_clicked()
{
    exit(0);
}

void LuckyDraw::on_pushButton_clicked()
{
    //int m = 10;
    if (m_list.empty()) {
        qDebug() << "empty list";
        ui->lineEdit->setText("李四");
        return;
    }
    MyThread *thread = new  MyThread(ui);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();
}

void LuckyDraw::on_pushButton_2_clicked()
{
    QThread *thread = findChild<QThread *>("thread");
    if (thread) {
        thread->exit(0);
    }
}

void LuckyDraw::updateText(QString &s) {
    ui->lineEdit->setText(s);
}


MyThread::MyThread(QWidget *recevier) : m_receiver(recevier) {

}

void MyThread::run() {
    if (m_receiver.isNull()) {
        exit(0);
    }
    connect(this, SIGNAL(updateText(QString &s)), m_receiver.data(), updateText(QString &s));
    qsrand((uint)QDateTime::currentMSecsSinceEpoch());
    int n = qrand() % m_list.size();
    emit updateText(m_list.at(n));
    exec();
}
