#include "customwidgets.h"
#include "syntaxhighlighter.h"

#include <QContextMenuEvent>
#include <QMenu>

TextEdit::TextEdit(QWidget* parent)
        : QTextEdit(parent)
{
    setWordWrapMode(QTextOption::ManualWrap);
    QFont fnt("Sans", 16, QFont::Bold);
    document()->setDefaultFont(fnt);
    setTabStopWidth(4 * QFontMetrics(fnt).width(' '));
    new SyntaxHighlighter(document());

    cMenu = new QMenu(this);

    cMenu->addAction(tr("Cu&t"), this, SLOT(cut()),
                     QKeySequence("CTRL+X"));
    cMenu->addAction(tr("&Copy"), this, SLOT(copy()),
                     QKeySequence("CTRL+C"));
    cMenu->addAction(tr("&Paste"), this, SLOT(paste()),
                     QKeySequence("CTRL+V"));

}

void TextEdit::contextMenuEvent(QContextMenuEvent* cme)
{
    cMenu->exec(cme->globalPos());
}
