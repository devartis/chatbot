/*
 * Copyright (C) 2012 Andres Pagliano, Gabriel Miretti, Gonzalo Buteler,
 * Nestor Bustamante, Pablo Perez de Angelis
 *
 * This file is part of LVK Botmaster.
 *
 * LVK Botmaster is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LVK Botmaster is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LVK Botmaster.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef RULEINPUTWIDGET_H
#define RULEINPUTWIDGET_H

#include <QWidget>
#include <QString>
#include <QStringList>

class QLineEdit;
class QPlainTextEdit;
class QLayout;
class QLabel;
class QListWidget;

/**
 * \brief Custom widget to edit or display NLP rule inputs
 */

class RuleInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RuleInputWidget(QWidget *parent = 0);

    ~RuleInputWidget();

    void clear();

    QStringList inputList();

    void setInputList(const QStringList &inputList);

    void setFocusOnInput();

    void setFocusOnInputVariants();

    void installEventFilter(QObject *eventFilter);

    bool eventFilter(QObject *object, QEvent *event);

    void keyPressEvent(QKeyEvent *event);

public slots:

    void clearHighlight();

    void highlightInput(int number);

signals:
    void inputTextEdited(const QString &);
    void inputVariantsEdited();

private:
    RuleInputWidget(RuleInputWidget&);
    RuleInputWidget& operator=(RuleInputWidget&);

    QLayout        *m_layout;
    QLabel         *m_targetLabel;
    QLineEdit      *m_target;
    QLabel         *m_inputLabel;
    QLineEdit      *m_input;
    QLabel         *m_inputVariantsLabel;
    QPlainTextEdit *m_inputVariants;
    QObject        *m_eventFilter;
    QListWidget    *m_list;

    void connectTextChangedSignal();
    void disconnectTextChangedSignal();

private slots:
    void onTargetTextEdited(QString);
    void onTargetLostFocus();
};

#endif // RULEINPUTWIDGET_H
