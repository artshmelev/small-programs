#ifndef PARSER_H
#define PARSER_H

#include <QObject>
#include <QUrl>
#include <QtWebKit>

class Parser : public QObject
{
    Q_OBJECT
public:
    Parser();
    ~Parser();
    void loadPage(const QString&);
    void clearList();

signals:
    void dataLoaded(QStringList&);

public slots:
    void replyFinished(bool);

private:
    QWebView* webView;
    QStringList stringList;
};

#endif // PARSER_H
