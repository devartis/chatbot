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

#ifndef LVK_NLP_TREE_H
#define LVK_NLP_TREE_H

#include <QStringList>

#include "nlp-engine/engine.h"

namespace Lvk
{

/// \addtogroup Lvk
/// @{

namespace Nlp
{

class Rule;

/// \ingroup Lvk
/// \addtogroup Nlp
/// @{

/**
 * \brief The Tree class provides ...
 */
class Tree
{
public:

    /**
     * Constructs an empty tree
     */
    Tree();

    /**
     * Adds \a rule to the tree
     */
    void add(const Rule &rule);

    /**
     * Gets the list of responses for the given input
     */
    QStringList getResponses(const QString &input, Engine::MatchList &matches);

};

/// @}

} // namespace Nlp

/// @}

} // namespace Lvk


#endif // LVK_NLP_TREE_H

