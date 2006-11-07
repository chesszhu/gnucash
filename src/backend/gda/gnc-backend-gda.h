/********************************************************************
 * gnc-backend-gda.h: load and save data to SQL via libgda          *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 51 Franklin Street, Fifth Floor    Fax:    +1-617-542-2652       *
 * Boston, MA  02110-1301,  USA       gnu@gnu.org                   *
\********************************************************************/
/** @file gnc-backend-gda.h
 *  @brief load and save data to SQL via libgda
 *  @author Copyright (c) 2000 Gnumatic Inc.
 *  @author Copyright (c) 2002 Derek Atkins <warlord@MIT.EDU>
 *  @author Copyright (c) 2003 Linas Vepstas <linas@linas.org>
 *  @author Copyright (c) 2006 Phil Longstaff <plongstaff@rogers.com>
 *
 * This file implements the top-level QofBackend API for saving/
 * restoring data to/from an SQL database via libgda
 */

#ifndef GNC_BACKEND_GDA_H_
#define GNC_BACKEND_GDA_H_

#include "qof.h"
#include <gmodule.h>

#include "qofbackend-p.h"
struct GncGdaBackend_struct
{
  QofBackend be;

  GdaClient* pClient;
  GdaConnection* pConnection;
  GdaDict* pDict;

  QofBook *primary_book;	/* The primary, main open book */
  gboolean	loading;		/* We are performing an initial load */
};
typedef struct GncGdaBackend_struct GncGdaBackend;

/**
 * Struct used to pass in a new data type for GDA storage.  This contains
 * the set of callbacks to read and write GDA for new data objects..  New
 * types should register an instance of this object with the engine.
 *
 * commit()			- commit an object to the db
 * initial_load()	- load stuff when new db opened
 */
#define GNC_GDA_BACKEND	"gnc:gda:1"
#define GNC_GDA_BACKEND_VERSION	1
typedef struct
{
  int		version;	/* backend version number */
  const char *	type_name;	/* The XML tag for this type */

  void		(*commit)( GncGdaBackend* pBackend, QofInstance* inst );
  void		(*initial_load)( GncGdaBackend* pBackend, QofBook* pBook );
} GncGdaDataType_t;

// This is now a static inside the module
//QofBackend * libgncmod_backend_gda_LTX_gnc_backend_new(void);

void gnc_gda_init_object_handlers( void );
void gnc_gda_execute_sql( GncGdaBackend* pBackend, const char* sql );
int gnc_gda_execute_select_get_count( GncGdaBackend* pBackend, const char* sql );

G_MODULE_EXPORT const gchar *
g_module_check_init(GModule *module);

#endif /* GNC_BACKEND_GDA_H_ */
