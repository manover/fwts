/*
 * Copyright (C) 2016-2017 IBM Corporation
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef __FWTS_DEVICETREE_H__
#define __FWTS_DEVICETREE_H__

#include "fwts.h"

#ifdef HAVE_LIBFDT
#define FWTS_HAS_DEVICETREE 1
#else
#define FWTS_HAS_DEVICETREE 0
#endif

#define DT_FS_PATH "/sys/firmware/devicetree/base"
#define DT_LINUX_PCI_DEVICES "/sys/bus/pci/devices"
#define DT_PROPERTY_OPAL_PCI_SLOT "ibm,slot-label"
#define DT_PROPERTY_OPAL_SLOT_LOC "ibm,slot-location-code"
#define DT_PROPERTY_OPAL_PART_NUM "part-number"
#define DT_PROPERTY_OPAL_SERIAL_NUM "serial-number"
#define DT_PROPERTY_OPAL_MANUFACTURER_ID "manufacturer-id"
#define DT_PROPERTY_OPAL_STATUS "status"
#define DT_PROPERTY_OPAL_VENDOR "vendor"
#define DT_PROPERTY_OPAL_BOARD_INFO "board-info"

#if FWTS_HAS_DEVICETREE

int fwts_devicetree_read(fwts_framework *fwts);

#else /* !FWTS_HAS_DEVICETREE */
static inline int fwts_devicetree_read(fwts_framework *fwts
		__attribute__((unused)))
{
	return FWTS_OK;
}
#endif

int check_property_printable(fwts_framework *fw,
			const char *name,
			const char *buf,
			size_t len);

char *hidewhitespace(char *name);

#endif
