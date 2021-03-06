/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*  Monkey HTTP Daemon
 *  ------------------
 *  Copyright (C) 2010-2011, Jonathan Gonzalez V. <zeus@gnu.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA 02110-1301  USA.
 */

#ifndef LIANA_SSL_H_
#define LIANA_SSL_H_

#include <matrixssl/matrixsslApi.h>
#include <matrixssl/version.h>

struct mk_liana_ssl
{
    ssl_t *ssl;
    unsigned char *buf_ssl;
    uint32_t buf_len;
    uint32_t buf_used;
    int handshake_complete;
    int need_read;
    int need_write;
    int try_false_start;
    int socket_fd;
    struct mk_list cons;
};

#define MK_MATRIX_REQUIRE_MAJOR 3
#define MK_MATRIX_REQUIRE_MINOR 2
#define MK_MATRIX_REQUIRE_PATCH 0

int liana_ssl_handshake(struct mk_liana_ssl *conn);

char *config_dir;

#endif /* !LIANA_SSL_H_ */
