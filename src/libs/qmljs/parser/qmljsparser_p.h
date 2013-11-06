/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
****************************************************************************/


//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

//
//  W A R N I N G
//  -------------
//
// This file is automatically generated from qmljs.g.
// Changes should be made to that file, not here. Any change to this file will
// be lost!
//
// To regenerate this file, run:
//    qlalr --no-debug --no-lines --qt qmljs.g
//

#ifndef QMLJSPARSER_P_H
#define QMLJSPARSER_P_H

#include "qmljsglobal_p.h"
#include "qmljsgrammar_p.h"
#include "qmljsast_p.h"
#include "qmljsengine_p.h"

#include <QtCore/qlist.h>
#include <QtCore/qstring.h>

QT_QML_BEGIN_NAMESPACE

namespace QmlJS {

class Engine;

class QML_PARSER_EXPORT Parser: protected QmlJSGrammar
{
public:
    union Value {
      int ival;
      double dval;
      AST::ArgumentList *ArgumentList;
      AST::CaseBlock *CaseBlock;
      AST::CaseClause *CaseClause;
      AST::CaseClauses *CaseClauses;
      AST::Catch *Catch;
      AST::DefaultClause *DefaultClause;
      AST::ElementList *ElementList;
      AST::Elision *Elision;
      AST::ExpressionNode *Expression;
      AST::Finally *Finally;
      AST::FormalParameterList *FormalParameterList;
      AST::FunctionBody *FunctionBody;
      AST::FunctionDeclaration *FunctionDeclaration;
      AST::Node *Node;
      AST::PropertyName *PropertyName;
      AST::PropertyAssignment *PropertyAssignment;
      AST::PropertyAssignmentList *PropertyAssignmentList;
      AST::SourceElement *SourceElement;
      AST::SourceElements *SourceElements;
      AST::Statement *Statement;
      AST::StatementList *StatementList;
      AST::Block *Block;
      AST::VariableDeclaration *VariableDeclaration;
      AST::VariableDeclarationList *VariableDeclarationList;

      AST::UiProgram *UiProgram;
      AST::UiHeaderItemList *UiHeaderItemList;
      AST::UiPragma *UiPragma;
      AST::UiImport *UiImport;
      AST::UiParameterList *UiParameterList;
      AST::UiPublicMember *UiPublicMember;
      AST::UiObjectDefinition *UiObjectDefinition;
      AST::UiObjectInitializer *UiObjectInitializer;
      AST::UiObjectBinding *UiObjectBinding;
      AST::UiScriptBinding *UiScriptBinding;
      AST::UiArrayBinding *UiArrayBinding;
      AST::UiObjectMember *UiObjectMember;
      AST::UiObjectMemberList *UiObjectMemberList;
      AST::UiArrayMemberList *UiArrayMemberList;
      AST::UiQualifiedId *UiQualifiedId;
      AST::UiQualifiedPragmaId *UiQualifiedPragmaId;
    };

public:
    Parser(Engine *engine);
    ~Parser();

    // parse a UI program
    bool parse() { return parse(T_FEED_UI_PROGRAM); }
    bool parseStatement() { return parse(T_FEED_JS_STATEMENT); }
    bool parseExpression() { return parse(T_FEED_JS_EXPRESSION); }
    bool parseSourceElement() { return parse(T_FEED_JS_SOURCE_ELEMENT); }
    bool parseUiObjectMember() { return parse(T_FEED_UI_OBJECT_MEMBER); }
    bool parseProgram() { return parse(T_FEED_JS_PROGRAM); }

    AST::UiProgram *ast() const
    { return AST::cast<AST::UiProgram *>(program); }

    AST::Statement *statement() const
    {
        if (! program)
            return 0;

        return program->statementCast();
    }

    AST::ExpressionNode *expression() const
    {
        if (! program)
            return 0;

        return program->expressionCast();
    }

    AST::UiObjectMember *uiObjectMember() const
    {
        if (! program)
            return 0;

        return program->uiObjectMemberCast();
    }

    AST::Node *rootNode() const
    { return program; }

    QList<DiagnosticMessage> diagnosticMessages() const
    { return diagnostic_messages; }

    inline DiagnosticMessage diagnosticMessage() const
    {
        foreach (const DiagnosticMessage &d, diagnostic_messages) {
            if (d.kind != Severity::Warning)
                return d;
        }

        return DiagnosticMessage();
    }

    inline QString errorMessage() const
    { return diagnosticMessage().message; }

    inline int errorLineNumber() const
    { return diagnosticMessage().loc.startLine; }

    inline int errorColumnNumber() const
    { return diagnosticMessage().loc.startColumn; }

protected:
    bool parse(int startToken);

    void reallocateStack();

    inline Value &sym(int index)
    { return sym_stack [tos + index - 1]; }

    inline QStringRef &stringRef(int index)
    { return string_stack [tos + index - 1]; }

    inline AST::SourceLocation &loc(int index)
    { return location_stack [tos + index - 1]; }

    AST::UiQualifiedId *reparseAsQualifiedId(AST::ExpressionNode *expr);
    AST::UiQualifiedPragmaId *reparseAsQualifiedPragmaId(AST::ExpressionNode *expr);

protected:
    Engine *driver;
    MemoryPool *pool;
    int tos;
    int stack_size;
    Value *sym_stack;
    int *state_stack;
    AST::SourceLocation *location_stack;
    QStringRef *string_stack;

    AST::Node *program;

    // error recovery
    enum { TOKEN_BUFFER_SIZE = 3 };

    struct SavedToken {
       int token;
       double dval;
       AST::SourceLocation loc;
       QStringRef spell;
    };

    double yylval;
    QStringRef yytokenspell;
    AST::SourceLocation yylloc;
    AST::SourceLocation yyprevlloc;

    SavedToken token_buffer[TOKEN_BUFFER_SIZE];
    SavedToken *first_token;
    SavedToken *last_token;

    QList<DiagnosticMessage> diagnostic_messages;
};

} // end of namespace QmlJS



#define J_SCRIPT_REGEXPLITERAL_RULE1 87

#define J_SCRIPT_REGEXPLITERAL_RULE2 88

QT_QML_END_NAMESPACE



#endif // QMLJSPARSER_P_H
