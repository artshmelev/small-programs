#ifndef CUSTOMWIDGETS_H
#define CUSTOMWIDGETS_H

#include <QTextEdit>

class QMenu;
class QContextMenuEvent;

class TextEdit : public QTextEdit
{
    Q_OBJECT
public:
    TextEdit(QWidget* parent = 0);

protected:
    virtual void contextMenuEvent(QContextMenuEvent* cme);

private:
    QMenu* cMenu;

};

#endif // CUSTOMWIDGETS_H
