#include "myweb.h"

myWeb::myWeb(QWidget *parent) : QWidget(parent)
{

}

void myWeb::keyPressEvent(QKeyEvent *keyEv)
{
    if(keyEv->key()==Qt::Key_F5)
    {
        this->webView->reload();
    }

}
