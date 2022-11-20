#include "lobby.h"
#include "./ui_lobby.h"
#include "src/constants/response_values.h"
#include <string>
#include <sstream>

lobby::lobby(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lobby)
    , connection("localhost", "8080")
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
    if (currSelectedGame.size()) {
        std::string value = CommandValues().DESERIALIZED_JOIN;
        std::string parameter = currSelectedGame.toStdString();
        Command command = ProtocolCommands().createCommand(this->connection.getId(),
                                                           value,
                                                           parameter);
        this->connection.push(command);
        on_pushButton_refresh_clicked();
        currSelectedGame.clear();
        Response r = this->connection.pop();

//        while (r.getActionId() != this->connection.getId()) {
//            r = this->connection.pop();
//        }

        std::vector<RoomResponse> rooms = r.getRoomResponses();

        std::string name_str, players_str;
        model.removeRows(0, model.rowCount());

        for (auto& room : rooms) {
            std::string statusText = "Comenzada";

            if (room.getWaitingForPlayers()) {
                statusText = "Esperando jugadores";
            }
            QStandardItem *name = new QStandardItem(QString::fromStdString(room.getName()));
            QStandardItem *players = new QStandardItem(QString::fromStdString(std::to_string(room.getCurrentPlayers())));
            QStandardItem *status = new QStandardItem(QString::fromStdString(statusText));
            model.appendRow( QList<QStandardItem*>() << name << status << players);
        }

        if (r.getStatus() == ResponseValues().OK) {
            hide();
            _client.run();
            show();
        }
    }
}


void lobby::on_pushButton_refresh_clicked()
{   //TODO LISTAR
    std::string value = CommandValues().DESERIALIZED_LIST;
    Command command = ProtocolCommands().createCommand(this->connection.getId(), value);
    this->connection.push(command);
    Response r = this->connection.pop();
    std::vector<RoomResponse> rooms = r.getRoomResponses();

    std::string name_str, players_str;
    model.removeRows(0, model.rowCount());

    for (auto& room : rooms) {
        std::string statusText = "Comenzada";

        if (room.getWaitingForPlayers()) {
            statusText = "Esperando jugadores";
        }
        QStandardItem *name = new QStandardItem(QString::fromStdString(room.getName()));
        QStandardItem *players = new QStandardItem(QString::fromStdString(std::to_string(room.getCurrentPlayers())));
        QStandardItem *status = new QStandardItem(QString::fromStdString(statusText));
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
    std::string value = CommandValues().DESERIALIZED_CREATE;
    std::string firstParameter = std::to_string(maxPlayers);
    std::string secondParameter = create_gameName.toStdString();
    Command command = ProtocolCommands().createCommand(this->connection.getId(),
                                                       value,
                                                       firstParameter,
                                                       secondParameter);
    this->connection.push(command);
    Response r = this->connection.pop();
    while (r.getActionId() != this->connection.getId()) {
        r = this->connection.pop();
    }

    std::vector<RoomResponse> rooms = r.getRoomResponses();

    std::string name_str, players_str;
    model.removeRows(0, model.rowCount());

    for (auto& room : rooms) {
        std::string statusText = "Comenzada";

        if (room.getWaitingForPlayers()) {
            statusText = "Esperando jugadores";
        }
        QStandardItem *name = new QStandardItem(QString::fromStdString(room.getName()));
        QStandardItem *players = new QStandardItem(QString::fromStdString(std::to_string(room.getCurrentPlayers())));
        QStandardItem *status = new QStandardItem(QString::fromStdString(statusText));
        model.appendRow( QList<QStandardItem*>() << name << status << players);
    }

    if (r.getStatus() == ResponseValues().OK) {
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
