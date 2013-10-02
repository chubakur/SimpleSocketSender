#ifndef WINDOW_H
#define WINDOW_H
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtNetwork/QTcpSocket>

class Window : public QWidget {
    Q_OBJECT
private:
    QLineEdit* address;
    QSpinBox* port;
    QPushButton* bind_button;
    QTextEdit* data;
    QPushButton* send_button;
    QVBoxLayout* main_layout;
    QHBoxLayout* host_layout;
    QHBoxLayout* data_layout;
    QTcpSocket* socket;
public:
    Window();
    ~Window();
public slots:
    void bind_socket();
    void send_data();
};

#endif // WINDOW_H
