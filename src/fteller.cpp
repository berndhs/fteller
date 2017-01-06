#include "fteller.h"
namespace fteller {

fteller::fteller(QWidget *parent, Qt::WindowFlags flags)
  :QMainWindow(parent,flags)
{
  fortuneTicker = new QTimer(this);
}

} // namespace
