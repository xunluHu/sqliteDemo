#ifndef MYWEB_H
#define MYWEB_H

#include <QWidget>
#include <QKeyEvent>
#include <QWebView>

class myWeb : public QWidget
{
    Q_OBJECT
public:
    explicit myWeb(QWidget *parent = 0);
    QWebView *webView;

signals:

public slots:
    void keyPressEvent(QKeyEvent *);
};

#endif // MYWEB_H
