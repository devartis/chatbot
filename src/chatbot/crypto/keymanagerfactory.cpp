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

#include "keymanagerfactory.h"

#ifdef DA_CONTEST
#  ifdef DA_KEY_MANAGER
#    include "crypto/dakeymanager.h"
#  else
#    error "dakeymanager.h is required to build a DA release"
#    error "Contact andres.pagliano@lvklabs.com for support"
#  endif
#else
#  include "crypto/defaultkeymanager.h"
#endif

//--------------------------------------------------------------------------------------------------
// KeyManagerFactory
//--------------------------------------------------------------------------------------------------

Lvk::Crypto::KeyManager * Lvk::Crypto::KeyManagerFactory::create()
{
#ifdef DA_CONTEST
    return new Crypto::DAKeyManager();
#else
    return new Crypto::DefaultKeyManager();
#endif
}
