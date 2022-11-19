#ifndef LOBBY_H
#define LOBBY_H

#include <QMainWindow>
#include <QMap>
#include "qtablewidget.h"
#include <QStandardItemModel>
#include "../src/handlers/server_connection.h"
#include "../src/client/client.h"

QT_BEGIN_NAMESPACE
namespace Ui { class lobby; }
QT_END_NAMESPACE

//TODO: cambiarle el nombre

class lobby : public QMainWindow
{
    Q_OBJECT

public:
    lobby(QWidget *parent = nullptr);
    ~lobby();

private slots:
    //void closeEvent(QCloseEvent *event);

    void on_pushButton_connect_clicked();

    void on_pushButton_join_clicked();

    void on_pushButton_refresh_clicked();

    void on_gamesListTable_clicked(const QModelIndex &index);

    void on_pushButton_createGame_clicked();

    void on_maxPlayers_count_valueChanged(int arg1);

    void on_lineEdit_gameName_textChanged(const QString &arg1);

private:
    Ui::lobby *ui;
    QList<QTableWidgetItem> gamesList;
    QStandardItemModel model;
    QStringList horizontalHeader;
    QString currSelectedGame;
    int maxPlayers;
    QString create_gameName;
    ServerConnection connection;
    Client _client;
};
#endif // LOBBY_H
