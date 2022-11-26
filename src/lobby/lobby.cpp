#include "lobby.h"
#include "./ui_lobby.h"
#include "src/constants/response_values.h"
#include <string>

lobby::lobby(QWidget *parent,
             const char *servname,
             const char *port)
    : QMainWindow(parent)
    , ui(new Ui::lobby)
    , connection(servname, port)
    , _client(connection)
{
    ui->setupUi(this);
    maxPlayers = 2;
    horizontalHeader.append("Game Name");
    horizontalHeader.append("Status");
    horizontalHeader.append("Players");

    model.setHorizontalHeaderLabels(horizontalHeader);

    ui->gamesListTable->setModel(&model);
    ui->gamesListTable->verticalHeader()->setVisible(false);
    ui->gamesListTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    currSelectedGame.clear();

    //TODO, solo para testing
    ui->pushButton_join->setEnabled(true);

}

lobby::~lobby()
{
    this->connection.closeConnection();
    delete ui;
}


void lobby::on_pushButton_connect_clicked()
{
    //TODO
}

void lobby::on_pushButton_join_clicked()
{   //TODO UNIR
    if (this->currSelectedGame.isEmpty()) { return; }

    std::string join = CommandValues().DESERIALIZED_JOIN;
    std::string firstParameter = this->currSelectedGame.toStdString();
    Command c = ProtocolCommands().createCommand(this->connection.getId(), join, firstParameter);
    this->connection.push(c);
    Response r = this->connection.pop();

    while (!r.isRecipient(this->connection.getId())) {
        r = this->connection.pop();
    }

    if (r.getStatus() == ResponseValues().OK) {
        this->connection.setConnectedGameName(firstParameter);
        hide();
        _client.run();
        show();
    }

    currSelectedGame.clear();
}


void lobby::on_pushButton_refresh_clicked()
{   //TODO LISTAR
    std::string list = CommandValues().DESERIALIZED_LIST;
    Command c = ProtocolCommands().createCommand(this->connection.getId(), list);
    this->connection.push(c);
    Response r = this->connection.pop();

    while (!r.isRecipient(this->connection.getId())) {
        r = this->connection.pop();
    }

    model.removeRows(0, model.rowCount());

    std::string name_str, players_str;

    for (auto &room : r.getRooms()) {
        QStandardItem *name = new QStandardItem(QString::fromStdString(room.getName()));
        QStandardItem *players = new QStandardItem(QString::fromStdString(room.getPlayers()));
        QStandardItem *status = new QStandardItem("-------");
        model.appendRow( QList<QStandardItem*>() << name << status << players);
    }
}


void lobby::on_gamesListTable_clicked(const QModelIndex &index)
{
    currSelectedGame = ui->gamesListTable->model()->data(ui->gamesListTable->model()->index(index.row(),0)).toString();
    ui->pushButton_join->setEnabled(true);
}


void lobby::on_pushButton_createGame_clicked()
{
    //TODO CREAR
    if (this->maxPlayers < 1 || this->create_gameName.isEmpty()) {
        return;
    }

    std::string create = CommandValues().DESERIALIZED_CREATE;
    std::string firstParameter = std::to_string(this->maxPlayers);
    std::string secondParameter = this->create_gameName.toStdString();
    Command c = ProtocolCommands().createCommand(this->connection.getId(), create,
                                                 firstParameter, secondParameter);
    this->connection.push(c);
    Response r = this->connection.pop();

    while (!r.isRecipient(this->connection.getId())) {
        r = this->connection.pop();
    }

    if (r.getStatus() == ResponseValues().OK) {
        this->connection.setConnectedGameName(secondParameter);
        hide();
        _client.run();
        show();
    }
}


void lobby::on_maxPlayers_count_valueChanged(int arg1)
{
    maxPlayers=arg1;
}


void lobby::on_lineEdit_gameName_textChanged(const QString &arg1)
{
    create_gameName = arg1;
    if (arg1.size()){
        ui->pushButton_createGame->setEnabled(true);
    } else {
        ui->pushButton_createGame->setEnabled(false);
    }
}

//void lobby::closeEvent(QCloseEvent *bar) {
//    this->connection.closeConnection();
//    QWidget::closeEvent(bar);
//}
//
