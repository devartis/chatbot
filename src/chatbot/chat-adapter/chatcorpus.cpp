/*
 * Copyright (C) 2012 Andres Pagliano, Gabriel Miretti, Gonzalo Buteler,
 * Nestor Bustamante, Pablo Perez de Angelis
 *
 * This file is part of LVK Chatbot.
 *
 * LVK Chatbot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * LVK Chatbot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with LVK Chatbot.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "chat-adapter/chatcorpus.h"
#include "common/csvdocument.h"
#include "common/globalstrings.h"
#include "common/settings.h"
#include "common/settingskeys.h"

#include <QFile>
#include <QDir>
#include <QStringList>
#include <QRegExp>
#include <QMutex>
#include <QMutexLocker>
#include <QDateTime>
#include <QtDebug>

#define CORPUS_FILE     "corpus.dat"

//--------------------------------------------------------------------------------------------------
// Helpers
//--------------------------------------------------------------------------------------------------

namespace
{

QString sanitize(const QString &str)
{
    return str.simplified();
}

} // namespace


//--------------------------------------------------------------------------------------------------
// ChatCorpus
//--------------------------------------------------------------------------------------------------

bool Lvk::CA::ChatCorpus::m_init = false;

QFile Lvk::CA::ChatCorpus::m_corpusFile;

QList<Lvk::CA::ChatCorpus::CorpusEntry> Lvk::CA::ChatCorpus::m_corpus;

QMutex *Lvk::CA::ChatCorpus::m_mutex = new QMutex();

//--------------------------------------------------------------------------------------------------

Lvk::CA::ChatCorpus::ChatCorpus()
{
    init();
}

//--------------------------------------------------------------------------------------------------

void Lvk::CA::ChatCorpus::init()
{
    if (!m_init) {
        QMutexLocker locker(m_mutex);
        if (!m_init) {
            Cmn::Settings settings;
            QString dataPath = settings.value(SETTING_DATA_PATH).toString();

            m_corpusFile.setFileName(dataPath + QDir::separator() + CORPUS_FILE);

            load();

            if (!m_corpusFile.open(QFile::Append)) {
                qWarning() << QObject::tr("Warning: cannot open corpus file for writing");
            }

            m_init = true;
        }
    }
}

//--------------------------------------------------------------------------------------------------

void Lvk::CA::ChatCorpus::add(const QString &user, const QString &message, const QString &thread)
{
    CorpusEntry entry;
    entry.timestamp = QDateTime::currentDateTime();
    entry.thread = thread;
    entry.username = user;
    entry.message = message;

    add(entry);
}

//--------------------------------------------------------------------------------------------------

void Lvk::CA::ChatCorpus::add(const CorpusEntry &entry)
{
    QMutexLocker locker(m_mutex);

    m_corpus.append(entry);

    if (m_corpusFile.isOpen()) {
        Cmn::CsvRow row;
        row.append(entry.timestamp.toString(STR_CHAT_CORPUS_DATE_TIME_FORMAT));
        row.append(sanitize(entry.thread));
        row.append(sanitize(entry.username));
        row.append(sanitize(entry.message));

        m_corpusFile.write(row.toString().toUtf8());
        m_corpusFile.write("\n");
        m_corpusFile.flush();
    }
}

//--------------------------------------------------------------------------------------------------

QList<Lvk::CA::ChatCorpus::CorpusEntry> Lvk::CA::ChatCorpus::corpus()
{
    QMutexLocker locker(m_mutex);
    return m_corpus;
}

//--------------------------------------------------------------------------------------------------

void Lvk::CA::ChatCorpus::load()
{
    if (!m_corpusFile.exists()) {
        // Nothing to do
        return;
    }
    if (!m_corpusFile.open(QFile::ReadOnly)) {
        qWarning() << QObject::tr("Warning: cannot open corpus file for reading");
        return;
    }

    char buf[10*1024];
    qint64 len = 0;
    QString line;
    Cmn::CsvRow row;

    do {
        len = m_corpusFile.readLine(buf, sizeof(buf));
        if (len > 0) {
            line = QString::fromUtf8(buf);
            row = Cmn::CsvRow(line);

            if (row.size() == 4) {
                CorpusEntry entry;
                entry.timestamp = QDateTime::fromString(row[0], STR_CHAT_CORPUS_DATE_TIME_FORMAT);
                entry.thread    = row[1];
                entry.username  = row[2];
                entry.message   = row[3];

                m_corpus.append(entry);
            }
        }
    } while (len != -1);

    m_corpusFile.close();
}

