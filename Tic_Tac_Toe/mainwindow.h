#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "msgdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static inline const char DEFAULT_OPTIONS[2]{'X', 'O'};
    static inline int turn{0};
    static inline bool returnGame{false};
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void checkAndSet(const int& i, const int& j);
    Ui::MainWindow *ui;
    // Ritorna lo stato della cella: "" (vuota), "O", "X"
    QString stato(int riga, int colonna);
    // Ritorna vero se le condizioni di vittoria sono soddisfatte
    bool vittoria();
    // Array con puntatori ai widget dell'interfaccia grafica
    QPushButton* m_celle[3][3];
    void initMatrix();
    bool noWinners();

public slots:
    void onClicked_00();
    void onClicked_01();
    void onClicked_02();
    void onClicked_10();
    void onClicked_11();
    void onClicked_12();
    void onClicked_20();
    void onClicked_21();
    void onClicked_22();

};
#endif // MAINWINDOW_H
