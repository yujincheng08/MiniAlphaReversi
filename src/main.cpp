#include <QApplication>
#include <QtGlobal>
#include "src/view/mainwindow.h"

int main(int argc, char *argv[]) {
#if QT_VERSION > QT_VERSION_CHECK(5, 5, 0)
  qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", QByteArray("1"));
#else
  qputenv("QT_DEVICE_PIXEL_RATIO", QByteArray("auto"));
#endif
  QApplication a(argc, argv);
  // new and show mainwindow
  MainWindow w;
  w.show();

  return a.exec();
}
