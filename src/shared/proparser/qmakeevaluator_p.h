/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: http://www.qt-project.org/
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**************************************************************************/

#ifndef QMAKEEVALUATOR_P_H
#define QMAKEEVALUATOR_P_H

#include "proitems.h"

#include <QRegExp>

#define debugMsg if (!m_debugLevel) {} else debugMsgInternal
#define traceMsg if (!m_debugLevel) {} else traceMsgInternal
#ifdef PROEVALUATOR_DEBUG
#  define dbgBool(b) (b ? "true" : "false")
#  define dbgReturn(r) \
    (r == ReturnError ? "error" : \
     r == ReturnBreak ? "break" : \
     r == ReturnNext ? "next" : \
     r == ReturnReturn ? "return" : \
     "<invalid>")
#  define dbgKey(s) qPrintable(s.toString().toQString())
#  define dbgStr(s) qPrintable(formatValue(s, true))
#  define dbgStrList(s) qPrintable(formatValueList(s))
#  define dbgSepStrList(s) qPrintable(formatValueList(s, true))
#  define dbgStrListList(s) qPrintable(formatValueListList(s))
#  define dbgQStr(s) dbgStr(ProString(s))
#else
#  define dbgBool(b) 0
#  define dbgReturn(r) 0
#  define dbgKey(s) 0
#  define dbgStr(s) 0
#  define dbgStrList(s) 0
#  define dbgSepStrList(s) 0
#  define dbgStrListList(s) 0
#  define dbgQStr(s) 0
#endif

QT_BEGIN_NAMESPACE

namespace ProFileEvaluatorInternal {

struct QMakeStatics {
    QString field_sep;
    QString strtrue;
    QString strfalse;
    ProKey strCONFIG;
    ProKey strARGS;
    QString strDot;
    QString strDotDot;
    QString strever;
    QString strforever;
    QString strhost_build;
    ProKey strTEMPLATE;
#ifdef PROEVALUATOR_FULL
    ProKey strREQUIRES;
#endif
    QHash<ProKey, int> expands;
    QHash<ProKey, int> functions;
    QHash<ProKey, ProKey> varMap;
    ProStringList fakeValue;
};

extern QMakeStatics statics;

}

QT_END_NAMESPACE

#endif // QMAKEEVALUATOR_P_H
