#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>

class QTextDocument;

class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
public:
    SyntaxHighlighter(QTextDocument* parent = 0);

protected:
    enum { NormalState = -1, InsideCStyleComment,
           InsideCString, InsideNumber };
    virtual void highlightBlock(const QString&);
    QString getKeyword(int, const QString&, bool&) const;

};

#endif // SYNTAXHIGHLIGHTER_H
