#ifndef WINDOW_H
#define WINDOW_H
#include <QtWidgets/QWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpinBox>
#include <QtNetwork/QTcpSocket>
#include <QtWidgets/QLabel>

class Window : public QWidget {
    Q_OBJECT
private:
    QLineEdit* address;
    QSpinBox* port;
    QPushButton* bind_button;
    QTextEdit* data;
    QTextEdit* data_hex;
    QPushButton* swap_data_widget;
    QPushButton* send_button;
    QVBoxLayout* main_layout;
    QHBoxLayout* host_layout;
    QHBoxLayout* data_layout;
    QTcpSocket* socket;
    QTextEdit* answer_widget;
    QLabel* status;
public:
    Window();
    ~Window();
public slots:
    void bind_socket();
    void send_data();
    void read_data();
    void connected();
    void connection_error(QAbstractSocket::SocketError socketError);
    void swap_data_widgets();
    void update_hex();
    void update_text();
};

#endif // WINDOW_H
