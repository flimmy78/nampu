/*
 * nmp_io.h
 *
 * This file declares low level io, packet layer.
 *
 * Copyright(c) by Nampu, 2010~2014
 * Author:
*/

#ifndef __NMP_IO_H__
#define __NMP_IO_H__

#include <glib.h>
#include "nmp_watch.h"
#include "nmp_netproto.h"


G_BEGIN_DECLS

typedef struct _HmIO HmIO;
typedef struct _HmIOFuncs HmIOFuncs;

struct _HmIOFuncs
{
	HmWatch *(*create)(HmIO *w, NmpConnection *conn);

	gint (*recv)(HmIO *io, gchar *start, gsize size, gpointer from_lower);
	void (*error)(HmIO *io, gint rw, gint err);
	void (*close)(HmIO *io, gint async);

	gint (*format)(HmIO *io, gpointer msg, gchar buf[], gsize size);
	void (*finalize)(HmIO *io);
};


struct _HmIO			/* basic IO, packet layer */
{
	HmWatch		watch;

	NmpPacketProto	*proto;
	HmIOFuncs		*funcs;

	gchar			*buffer;

	gint			buff_size;
	gint			start_pos;
	gint			end_pos;
};


HmIO *nmp_io_new(NmpConnection *conn, NmpPacketProto *proto,
	HmIOFuncs *funcs, gsize size);

HmIO *nmp_listen_io_new(NmpConnection *conn, NmpPacketProto *proto,
	HmIOFuncs *funcs, gsize size);

G_END_DECLS

#endif	//__NMP_IO_H__
