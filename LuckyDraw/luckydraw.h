#ifndef LUCKYDRAW_H
#define LUCKYDRAW_H

#include <QMainWindow>
#include <QThread>

namespace Ui {
class LuckyDraw;
}

class LuckyDraw : public QMainWindow
{
    Q_OBJECT

public:
    explicit LuckyDraw(QWidget *parent = 0);
    ~LuckyDraw();

    void init();

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void updateText(QString &s);

private:
    Ui::LuckyDraw *ui;
    QList<QString> m_list;
};

class MyThread : QThread {
    Q_OBJECT
public:
    MyThread(QWidget *recevier);
    //~MyThread();

    void run() override;

signals:
    void updateText();
private:
    QSharedPointer<QWidget> m_receiver;
};


#endif // LUCKYDRAW_H
