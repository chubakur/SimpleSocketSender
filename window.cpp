#include "window.h"

Window::Window(){

    main_layout = new QVBoxLayout(this);

    host_layout = new QHBoxLayout(this);
    address = new QLineEdit(this);
    port = new QSpinBox(this);
    port->setRange(0,65535);
    bind_button = new QPushButton("Bind", this);
    host_layout->addWidget(address);
    host_layout->addWidget(port);
    host_layout->addWidget(bind_button);

    data_layout = new QHBoxLayout(this);
    send_button = new QPushButton("Send", this);
    data = new QTextEdit(this);
    swap_data_widget = new QPushButton("<-=->", this);
    data_hex = new QTextEdit(this);
    data_hex->setEnabled(false);
    data_layout->addWidget(data);
    data_layout->addWidget(swap_data_widget);
    data_layout->addWidget(data_hex);
    data_layout->addWidget(send_button);

    answer_widget = new QTextEdit(this);
    status = new QLabel("Not connected", this);



    main_layout->addLayout(host_layout);
    main_layout->addLayout(data_layout);
    main_layout->addWidget(answer_widget);
    main_layout->addWidget(status);

    setLayout(main_layout);
    socket = new QTcpSocket(this);
    connect(bind_button, SIGNAL(clicked()), SLOT(bind_socket()));
    connect(send_button, SIGNAL(clicked()), SLOT(send_data()));
    connect(socket, SIGNAL(readyRead()), SLOT(read_data()));
    connect(socket, SIGNAL(connected()), SLOT(connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), SLOT(connection_error(QAbstractSocket::SocketError)));
    connect(swap_data_widget, SIGNAL(clicked()), SLOT(swap_data_widgets()));
    connect(data, SIGNAL(textChanged()), SLOT(update_hex()));
    connect(data_hex, SIGNAL(textChanged()), SLOT(update_text()));

}

Window::~Window(){

}

void Window::bind_socket(){
    socket->disconnectFromHost();
    socket->connectToHost(address->text(), port->value());
    status->setText("Connecting...");
}

void Window::send_data(){
    QString d = data->toPlainText();
    socket->write(d.toLatin1());
    //socket->flush();
}

void Window::read_data(){
    QString answer = socket->readAll();
    answer_widget->setPlainText(answer);
}

void Window::connected(){
    status->setText("Connected!");
}

void Window::connection_error(QAbstractSocket::SocketError socketError){
    status->setText("Error "+QString::number(socketError));
}

void Window::swap_data_widgets(){
    bool active = data->isEnabled();
    data->setEnabled(!active);
    data_hex->setEnabled(active);
}


void Window::update_hex(){
    if(data_hex->isEnabled())
        return;
    QString plain = data->toPlainText();
    QByteArray hex = plain.toLatin1().toHex();
    int hex_in_block = 0;
    QString a;
    for(int i=0; i<hex.size(); ++i){
        a.append(hex.at(i));
        hex_in_block = (hex_in_block+1) % 2;
        if(!hex_in_block)
            a.append(' ');
    }
    data_hex->setPlainText(a);
}

void Window::update_text(){
    if(data->isEnabled())
        return;
    QString hex=data_hex->toPlainText();
    hex.remove(' ');
    QString result(QByteArray::fromHex(hex.toLatin1()));
    data->setPlainText(result);
}
