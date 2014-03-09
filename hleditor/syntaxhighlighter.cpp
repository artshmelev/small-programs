#include "syntaxhighlighter.h"

SyntaxHighlighter::SyntaxHighlighter(QTextDocument* parent)
        : QSyntaxHighlighter(parent)
{
}

void SyntaxHighlighter::highlightBlock(const QString& str)
{
    int nState = previousBlockState();
    int nStart = 0;
    for (int i=0; i<str.length(); i++)
    {
        if (nState == InsideCStyleComment)
        {
            if (str.mid(i, 2) == "*/")
            {
                nState = NormalState;
                setFormat(nStart, i - nStart + 2, Qt::darkGray);
                i++;
            }
        }
        else if (nState == InsideCString)
        {
            if (str.mid(i, 1) == "\"" || str.mid(i, 1) == "\'")
            {
                if (str.mid(i-1, 2) != "\\\"" &&
                    str.mid(i-1, 2) != "\\\'")
                {
                    nState = NormalState;
                    setFormat(nStart, i - nStart + 1, Qt::blue);
                }
            }
        }
        else if (nState == InsideNumber)
        {
            if (!str[i].isDigit())
            {
                nState = NormalState;
                setFormat(nStart, i - nStart, Qt::darkMagenta);
                i--;
            }
        }
        else
        {
            if (str.mid(i, 2) == "//")
            {
                setFormat(i, str.length() - i, Qt::darkGray);
                break;
            }
            else if (str.mid(i, 1) == "#")
            {
                setFormat(i, str.length() - i, Qt::darkGreen);
                break;
            }
            else if (str[i].isNumber() &&
                     (i == 0 || !str[i-1].isLetter() &&
                     !str[i-1].isDigit() && str[i-1] != QChar('_')))
            {
                nStart = i;
                nState = InsideNumber;
            }
            else if (str.mid(i, 2) == "/*")
            {
                nStart = i;
                nState = InsideCStyleComment;
            }
            else if (str.mid(i, 1) == "\"" || str.mid(i, 1) == "\'")
            {
                nStart = i;
                nState = InsideCString;
            }
            else
            {
                bool mode;
                QString strKeyword = getKeyword(i, str, mode);
                if (!strKeyword.isEmpty())
                {
                    if (mode == 0)
                    {
                        setFormat(i, strKeyword.length(), Qt::red);
                        i += strKeyword.length() - 1;
                    }
                    else
                    {
                        setFormat(i, strKeyword.length(), Qt::darkYellow);
                        i += strKeyword.length() - 1;
                    }
                }
            }
        }
    }
    if (nState == InsideCStyleComment)
    {
        setFormat(nStart, str.length() - nStart, Qt::darkGray);
    }
    if (nState == InsideCString)
    {
        setFormat(nStart, str.length() - nStart, Qt::blue);
    }
    if (nState == InsideNumber)
    {
        setFormat(nStart, str.length()-nStart, Qt::darkMagenta);
        nState = NormalState;
    }
    setCurrentBlockState(nState);
}

QString SyntaxHighlighter::getKeyword(int nPos, const QString& str,
                                      bool& mode) const
{
    QString strTemp = "";
    QStringList lstNameKeywords, lstSignKeywords;
    lstNameKeywords
        << "bool" << "int" << "void" << "double" << "float"
        << "char" << "delete" << "class" << "const" << "virtual"
        << "this" << "struct" << "union" << "throw" << "for"
        << "if" << "else" << "false" << "true" << "namespace"
        << "switch" << "case" << "public" << "private" << "protected"
        << "new" << "return" << "using" << "friend" << "static"
        << "auto" << "break" << "continue" << "default" << "do"
        << "enum" << "extern" << "goto" << "long" << "register"
        << "short" << "signed" << "sizeof" << "typedef" << "unsigned"
        << "volatile" << "while" << "asm" << "catch" << "const_cast"
        << "dynamic_cast" << "explicit" << "inline" << "mutable" << "operator"
        << "reinterpret_cast" << "template" << "typeid" << "typename" << "wchar_t"
        << "static_cast" << "try";
    lstSignKeywords
        << "->" << ">>" << "<<" << "<" << ">" << "(" << ")"
        << "{" << "}" << "[" << "]" << "+" << "-" << "*" << "/"
        << "=" << "!" << "." << "," << ";" << ":" << "&" << "|";

    foreach (QString strKeyword, lstSignKeywords)
    {
        if (str.mid(nPos, strKeyword.length()) == strKeyword)
        {
            strTemp = strKeyword;
            mode = 0;
            return strTemp;
        }
    }

    foreach (QString strKeyword, lstNameKeywords)
    {
        if ((str == strKeyword) ||
            (nPos == 0 &&
            (str.mid(nPos, strKeyword.length()+1) == strKeyword + " " ||
             str.mid(nPos, strKeyword.length()+1) == strKeyword + "\t" ||
             str.mid(nPos, strKeyword.length()+1) == strKeyword + "*" ||
             str.mid(nPos, strKeyword.length()+1) == strKeyword + "&" ||
             str.mid(nPos, strKeyword.length()+1) == strKeyword + "(" ||
             str.mid(nPos, strKeyword.length()+1) == strKeyword + ":" ||
             str.mid(nPos, strKeyword.length()+1) == strKeyword + ",")) ||
            (nPos == str.length()-strKeyword.length() &&
            (str.mid(nPos-1, strKeyword.length()+1) == " " + strKeyword ||
             str.mid(nPos-1, strKeyword.length()+1) == "\t" + strKeyword ||
             str.mid(nPos-1, strKeyword.length()+1) == "(" + strKeyword ||
             str.mid(nPos-1, strKeyword.length()+1) == ";" + strKeyword ||
             str.mid(nPos-1, strKeyword.length()+1) == "," + strKeyword)) ||
            (nPos != 0 && nPos != str.length()-strKeyword.length() &&
            (str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + " " ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + " " ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + "\t" ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + "\t" ||
             str.mid(nPos-1, strKeyword.length()+2) == "(" + strKeyword + ")" ||
             str.mid(nPos-1, strKeyword.length()+2) == "<" + strKeyword + ">" ||
             str.mid(nPos-1, strKeyword.length()+2) == "," + strKeyword + "," ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + ")" ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + ")" ||
             str.mid(nPos-1, strKeyword.length()+2) == ";" + strKeyword + " " ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + " " ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + "," ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + "," ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + "(" ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + "(" ||
             str.mid(nPos-1, strKeyword.length()+2) == ";" + strKeyword + "(" ||
             str.mid(nPos-1, strKeyword.length()+2) == "(" + strKeyword + " " ||
             str.mid(nPos-1, strKeyword.length()+2) == "(" + strKeyword + "," ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + "&" ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + "*" ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + "&" ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + "*" ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + ";" ||
             str.mid(nPos-1, strKeyword.length()+2) == "*" + strKeyword + "<" ||
             str.mid(nPos-1, strKeyword.length()+2) == " " + strKeyword + "<" ||
             str.mid(nPos-1, strKeyword.length()+2) == "\t" + strKeyword + "<")))
        {
            strTemp = strKeyword;
            mode = 1;
            return strTemp;
        }
    }

    return strTemp;
}
