#include <sys/types.h>
#include <unistd.h>

#include <QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
  srand(time(NULL) + getpid());

  QApplication app(argc, argv);
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
