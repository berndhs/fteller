#ifndef FTELLER_H
#define FTELLER_H

#include <QMainWindow>
#include <QStringList>
#include <QGuiApplication>
#include "config-edit.h"
#include <QTimer>

namespace fteller {
class fteller : public QMainWindow
{
  Q_OBJECT
public:
  explicit fteller(QWidget *parent = 0, Qt::WindowFlags flags = Qt::WindowFlags());
  void  Init (QGuiApplication &ap);

  void  AddConfigMessages (const QStringList & cm)
           { configMessages.append (cm); }

signals:

private slots:

  void Quit ();
  void Restart ();
  void EditSettings ();
  void SetSettings ();
  void About ();
  void License ();
  void Exiting ();

private:

  QGuiApplication    *app;

  QStringList     fortuneData;
  QTimer       *fortuneTicker;
  QStringList     configMessages;

  ConfigEdit       configEdit;
};

} // namespace

#endif // FTELLER_H
