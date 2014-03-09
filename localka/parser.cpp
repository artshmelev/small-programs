#include "parser.h"

#include <QUrl>

Parser::Parser()
{
    webView = new QWebView();
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("koi8-r"));
    connect(webView->page()->mainFrame(), SIGNAL(loadFinished(bool)),
            this, SLOT(replyFinished(bool)));
}

Parser::~Parser()
{
    delete webView;
    //delete stringList;
}

void Parser::loadPage(const QString& strQuery)
{
    //QString str = (QString)strQuery.toAscii().toPercentEncoding();
    QString str = QTextCodec::codecForName("koi8-r")->fromUnicode(strQuery)
                  .toPercentEncoding();
    qDebug() << QString("http://allter.mipt.ru/?search=%1&type=3")
            .arg(str);
    webView->page()->mainFrame()->load(QString("http://allter.mipt.ru/?search=%1&type=3")
                                       .arg(str));
}

void Parser::replyFinished(bool ok)
{
    QWebElementCollection elTitles =
            webView->page()->mainFrame()->findAllElements("p.f");
    QWebElementCollection elPaths =
            webView->page()->mainFrame()->findAllElements("p.d");
    QStringList strListTitles, strListPaths;
    QRegExp rx("^[0-9]* - ");
    foreach (QWebElement e, elTitles)
        strListTitles << e.findFirst("b").toPlainText().replace(rx, "");
    foreach (QWebElement e, elPaths)
        strListPaths << e.findFirst("a").attribute("href");
    for (int i = 0; i < strListTitles.size(); i++)
        stringList << strListPaths.at(i) + strListTitles.at(i);
    qDebug() << strListTitles.size() << strListPaths.size();
    emit dataLoaded(stringList);
}

void Parser::clearList()
{
    stringList.clear();
}
