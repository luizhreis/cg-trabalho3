#include <Trabalho3.h>
#include <MainWindow.h>

int Trabalho3::run(int argc, char* argv[])
{
    QApplication trabalho3(argc, argv);
    MainWindow *mainWindow = new MainWindow();

    mainWindow->show();

    return trabalho3.exec();
}

int main(int argc, char* argv[])
{
    Trabalho3* trab3 = new Trabalho3();
    return trab3->run(argc, argv);
}
