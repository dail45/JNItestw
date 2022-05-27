#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QJniObject>
#include <QJniEnvironment>
#include <jni.h>
#include <QPushButton>
#include <QDebug>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QHBoxLayout *layout = new QHBoxLayout(this);
    QPushButton *btn = new QPushButton(this);
    static jstring cppNativeFunction(JNIEnv *env, jobject obj);

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
