#include "lobby.h"
#include "./ui_lobby.h"
#include <string>
#include <sstream>

lobby::lobby(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::lobby)
    , protocolo("localhost", "8080")
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

}

lobby::~lobby()
{
    delete ui;
}


void lobby::on_pushButton_connect_clicked()
{
    //TODO
}

void lobby::on_pushButton_join_clicked()
{
    if (currSelectedGame.size()) {
        protocolo.sendActions("UNIR " + currSelectedGame.toStdString());

        std::cout << protocolo.receiveResponse() << std::endl;

        on_pushButton_refresh_clicked();
        currSelectedGame.clear();
    }
}


void lobby::on_pushButton_refresh_clicked()
{
    protocolo.sendActions("LISTAR");
    std::string name_str, players_str;
    std::istringstream input_stream(protocolo.receiveResponse());
    int i = 1;
    model.removeRows(0, model.rowCount());
    //FIXME: hay que usar el protocolo nuevo
    while (input_stream >> name_str) {
        input_stream >> players_str;

        // Fijarse si se puede sacar lo de new.
        QStandardItem *name = new QStandardItem(QString::fromStdString(name_str));
        QStandardItem *players = new QStandardItem(QString::fromStdString(players_str));
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
    protocolo.sendActions("CREAR " + std::to_string(maxPlayers) + " " + create_gameName.toStdString());
    std::cout << protocolo.receiveResponse() << std::endl;
    on_pushButton_refresh_clicked();
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
