/* -*- Mode: C; tab-width: 8; indent-tabs-mode: nil; c-basic-offset: 8 -*- */

/*  Monkey HTTP Daemon
 *  ------------------
 *  Copyright (C) 2001-2008, Eduardo Silva P.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#define _GNU_SOURCE
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#include "memory.h"
#include "request.h"
#include "header.h"

void *mk_mem_malloc(size_t size)
{
	char *aux=0;

	if((aux=malloc(size))==NULL){
		perror("malloc");
		return NULL;						
	}
	return (void *) aux;
}

void *mk_mem_malloc_z(size_t size)
{
	char *buf=0;

	buf = mk_mem_malloc(size);
	if(!buf)
	{
		return NULL;
	}

	memset(buf, '\0', sizeof(size));
	return buf;
}

void *mk_mem_realloc(void* ptr, size_t size)
{
	char *aux=0;

	if((aux=realloc(ptr, size))==NULL){
		perror("realloc");
		return NULL;						
	}

	return (void *) aux;
}
	
void mk_mem_free(void *ptr)
{
	if(ptr!=NULL){
		free(ptr);
	}
}

mk_pointer mk_pointer_create(char *buf, long init, long end)
{
	mk_pointer p;

        mk_pointer_reset(&p);
	p.data = buf+init;

        if(init!=end)
        {
                p.len = (end - init);
        }
        else{
                p.len = 1;
        }

	return p;
}

void mk_pointer_reset(mk_pointer *p)
{
	p->data = NULL;
	p->len = 0;
}

void mk_pointer_free(mk_pointer *p)
{
	mk_mem_free(p->data);
	p->len = 0;
}

char *mk_pointer_to_buf(mk_pointer p)
{
	char *buf;

	buf = strndup(p.data, p.len);
	return (char *) buf;
}

void mk_pointer_print(mk_pointer p)
{
        int i;

        printf("\nDEBUG MK_POINTER: '");
        for(i=0; i<p.len; i++){
                printf("%c", p.data[i]);
        }
        printf("'");
        fflush(stdout);
}

void mk_pointer_set(mk_pointer *p, char *data)
{
	p->data = data;
	p->len = strlen(data);
}

void mk_mem_pointers_init()
{
	/* Error messages */
	mk_pointer_set(&request_error_msg_400, ERROR_MSG_400);
	mk_pointer_set(&request_error_msg_403, ERROR_MSG_403);
	mk_pointer_set(&request_error_msg_404, ERROR_MSG_404); 
	mk_pointer_set(&request_error_msg_405, ERROR_MSG_405);
	mk_pointer_set(&request_error_msg_408, ERROR_MSG_408);
	mk_pointer_set(&request_error_msg_411, ERROR_MSG_411);
	mk_pointer_set(&request_error_msg_500, ERROR_MSG_500);
        mk_pointer_set(&request_error_msg_501, ERROR_MSG_501);
	mk_pointer_set(&request_error_msg_505, ERROR_MSG_505);

	/* Short server response headers */
	mk_pointer_set(&mk_header_short_date, MK_HEADER_SHORT_DATE);
	mk_pointer_set(&mk_header_short_location, MK_HEADER_SHORT_LOCATION);
	mk_pointer_set(&mk_header_short_ct, MK_HEADER_SHORT_CT);

        /* Request vars */
        mk_pointer_set(&mk_crlf, MK_CRLF);
        mk_pointer_set(&mk_endblock, MK_ENDBLOCK);

	/* Server response first header */
        mk_pointer_set(&mk_hr_http_ok, MK_HR_HTTP_OK);
        mk_pointer_set(&mk_hr_http_partial, MK_HR_HTTP_PARTIAL);
        mk_pointer_set(&mk_hr_redir_moved, MK_HR_REDIR_MOVED);
        mk_pointer_set(&mk_hr_redir_moved_t, MK_HR_REDIR_MOVED_T);
        mk_pointer_set(&mk_hr_not_modified, MK_HR_NOT_MODIFIED);
        mk_pointer_set(&mk_hr_client_bad_request, MK_HR_CLIENT_BAD_REQUEST);
        mk_pointer_set(&mk_hr_client_forbidden, MK_HR_CLIENT_FORBIDDEN);
        mk_pointer_set(&mk_hr_client_not_found, MK_HR_CLIENT_NOT_FOUND);
        mk_pointer_set(&mk_hr_client_method_not_allowed, 
                       MK_HR_CLIENT_METHOD_NOT_ALLOWED);
        mk_pointer_set(&mk_hr_client_request_timeout,
                       MK_HR_CLIENT_REQUEST_TIMEOUT);
        mk_pointer_set(&mk_hr_client_length_required,
                       MK_HR_CLIENT_LENGTH_REQUIRED);
        mk_pointer_set(&mk_hr_server_internal_error,
                       MK_HR_SERVER_INTERNAL_ERROR);
        mk_pointer_set(&mk_hr_server_not_implemented,
                       MK_HR_SERVER_NOT_IMPLEMENTED);
        mk_pointer_set(&mk_hr_server_http_version_unsup,
                       MK_HR_SERVER_HTTP_VERSION_UNSUP);

        /* Server response normal headers */
	mk_pointer_set(&mk_header_conn_ka, MK_HEADER_CONN_KA);
	mk_pointer_set(&mk_header_conn_close, MK_HEADER_CONN_CLOSE);
	mk_pointer_set(&mk_header_accept_ranges, MK_HEADER_ACCEPT_RANGES);
	mk_pointer_set(&mk_header_te_chunked, MK_HEADER_TE_CHUNKED);
}
