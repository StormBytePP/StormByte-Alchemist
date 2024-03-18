#ifndef ALCHEMIST_ALCHEMIST_MAINWINDOW_H
#define ALCHEMIST_ALCHEMIST_MAINWINDOW_H

#include <QMainWindow>

namespace Alchemist::Alchemist {

    namespace Ui {
        class MainWindow;
    }

    class MainWindow : public QMainWindow {
        Q_OBJECT

        public:
            explicit MainWindow(QWidget *parent = nullptr);
            ~MainWindow();

        private:
            Ui::MainWindow *ui;
    };
}
#endif // ALCHEMIST_ALCHEMIST_MAINWINDOW_H
