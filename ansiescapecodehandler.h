/****************************************************************************
**
** Copyright (C) 2016 Petar Perisin <petar.perisin@gmail.com>
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#pragma once

#include <QObject>
#include <QTextCharFormat>
#include <QTextCursor>

class QScrollBar;

namespace Utils {

class FormattedText {
public:
    FormattedText() = default;
    FormattedText(const FormattedText &other) = default;
    FormattedText(const QString &txt, const QTextCharFormat &fmt = QTextCharFormat()) :
        text(txt), format(fmt)
    { }
    FormattedText(QString &&txt, QTextCharFormat &&fmt = QTextCharFormat()) :
        text(txt), format(fmt)
    { }

    QString text;
    QTextCharFormat format;
};
}

Q_DECLARE_TYPEINFO(Utils::FormattedText, Q_MOVABLE_TYPE);
Q_DECLARE_TYPEINFO(QList<Utils::FormattedText>, Q_MOVABLE_TYPE);

namespace Utils {
class AnsiEscapeCodeHandler : public QObject
{
    Q_OBJECT
public:
    AnsiEscapeCodeHandler();
    AnsiEscapeCodeHandler(QTextCursor textCursor, QScrollBar *scrollBar = nullptr);
    AnsiEscapeCodeHandler& operator=(AnsiEscapeCodeHandler&& move);
    QList<FormattedText> parseText(const FormattedText &input);

public slots:
    void appendAnsiText(const QString& text);

private:
    void endFormatScope();
    void setFormatScope(const QTextCharFormat &charFormat);

    bool            m_previousFormatClosed = true;
    bool            m_waitingForTerminator = false;
    QString         m_alternateTerminator;
    QTextCharFormat m_previousFormat;
    QString         m_pendingText;
    QTextCursor     m_textCursor;
    QScrollBar     *m_scrollBar;
};

} // namespace Utils

