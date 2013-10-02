#include "window.h"

Window::Window(){

    main_layout = new QVBoxLayout(this);

    host_layout = new QHBoxLayout(this);
    address = new QLineEdit(this);
    port = new QSpinBox(this);
    bind_button = new QPushButton("Bind", this);
    host_layout->addWidget(address);
    host_layout->addWidget(port);
    host_layout->addWidget(bind_button);

    data_layout = new QHBoxLayout(this);
    send_button = new QPushButton("Send", this);
    data = new QTextEdit(this);
    data_layout->addWidget(data);
    data_layout->addWidget(send_button);



    main_layout->addLayout(host_layout);
    main_layout->addLayout(data_layout);

    setLayout(main_layout);
    socket = new QTcpSocket(this);
    connect(bind_button, SIGNAL(clicked()), SLOT(bind_socket()));
    connect(send_button, SIGNAL(clicked()), SLOT(send_data()));
}

Window::~Window(){

}

void Window::bind_socket(){
    socket->connectToHost(address->text(), port->value());
}

void Window::send_data(){
    QString d = data->toPlainText();
    socket->write(d.toLocal8Bit());
}
