#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
    QJniObject MyJni = QJniObject("org/example/JNItest/MyJNI",
                                  "(Landroid/app/Activity;)V",
                                  activity.object<jobject>());
    QJniEnvironment env;
    jclass objectClass = env->GetObjectClass(MyJni.object<jobject>());
    JNINativeMethod methods[] = {{"nativeFun", "()Ljava/lang/String;", reinterpret_cast<void*>(cppNativeFunction)}};
    env->RegisterNatives(objectClass, methods, sizeof(methods) / sizeof(methods[0]));
    env->DeleteLocalRef(objectClass);
    layout->addWidget(btn);
    btn->setText("click me");
    btn->setStyleSheet("QPushButton {padding: 25px;}");
    QObject::connect(btn, &QPushButton::clicked, this, [this]() {
        auto activity = QJniObject(QNativeInterface::QAndroidApplication::context());
        QJniObject MyJni = QJniObject("org/example/JNItest/MyJNI",
                                      "(Landroid/app/Activity;)V",
                                      activity.object<jobject>());
        QJniObject res = MyJni.callObjectMethod("jniFun", "()Ljava/lang/String;").object<jobject>();
        this->btn->setText(res.toString());
    });
}

Widget::~Widget()
{
    delete ui;
}

int counter = 0;
jstring Widget::cppNativeFunction(JNIEnv *env, jobject obj) {
        qDebug() << "Hello from java!" << QString::number(counter++);
        return QJniObject::fromString("Hello from C++/Qt!").object<jstring>();
    }
