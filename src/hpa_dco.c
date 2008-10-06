/*

    File: hpa_dco.c

    Copyright (C) 2008 Christophe GRENIER <grenier@cgsecurity.org>
  
    This software is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
  
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
  
    You should have received a copy of the GNU General Public License along
    with this program; if not, write the Free Software Foundation, Inc., 51
    Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 */
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
 
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_UNISTD_H
#include <unistd.h>	/* lseek, read, write, close */
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_FCNTL_H
#include <fcntl.h> 	/* open */
#endif
#include <stdio.h>
#include <errno.h>
#include "types.h"
#ifdef HAVE_LINUX_TYPES_H
#include <linux/types.h>
#endif
#include "common.h"
#ifdef HAVE_SYS_IOCTL_H
#include <sys/ioctl.h>
#endif
#ifdef HAVE_LINUX_HDREG_H
#include <linux/hdreg.h>
#endif
#ifdef HAVE_SYS_STAT_H
#include <sys/stat.h>
#endif
#ifdef HAVE_FNCTL_H
#include <fnctl.h>
#endif
#ifdef HAVE_SCSI_SG_H
#include <scsi/sg.h>
#endif
#include "log.h"
#include "hpa_dco.h"

#define DISK_HAS_48_SUPPORT	0x01
#define DISK_HAS_HPA_SUPPORT 0x02
#define DISK_HAS_REMOVABLE_SUPPORT	0x04
#define DISK_HAS_DCO_SUPPORT	0x08

#define IDE_STATUS_OFFSET 7
#define DEVICE_CONFIGURATION_IDENTIFY 0xC2
#define SG_ATA_PROTO_NON_DATA 	( 3 << 1)
#define SG_ATA_PROTO_PIO_IN     ( 4 << 1)
#define SG_ATA_LBA48             1
#define SG_DRIVER_SENSE          0x08
#define SG_CHECK_CONDITION       0x02

enum {
  SG_CDB2_TLEN_NODATA     = 0 << 0,
  SG_CDB2_TLEN_FEAT       = 1 << 0,
  SG_CDB2_TLEN_NSECT      = 2 << 0,

  SG_CDB2_TLEN_BYTES      = 0 << 2,
  SG_CDB2_TLEN_SECTORS    = 1 << 2,

  SG_CDB2_TDIR_TO_DEV     = 0 << 3,
  SG_CDB2_TDIR_FROM_DEV   = 1 << 3,

  SG_CDB2_CHECK_COND      = 1 << 5,
};

#ifndef WIN_READ_NATIVE_MAX 
#define WIN_READ_NATIVE_MAX             0xF8 /* return the native maximum address */
#endif
  
#ifndef WIN_READ_NATIVE_MAX_EXT
#define WIN_READ_NATIVE_MAX_EXT         0x27 /* 48-Bit */
#endif

#ifndef IDE_DRIVE_TASK_NO_DATA
#define IDE_DRIVE_TASK_NO_DATA          0
#endif

#ifdef HDIO_DRIVE_CMD
static uint64_t read_native_max(int fd)
{
#ifdef HDIO_DRIVE_TASK
  unsigned char task_args[7];
  task_args[0] = WIN_READ_NATIVE_MAX;
  task_args[1] = 0x00;
  task_args[2] = 0x00;
  task_args[3] = 0x00;
  task_args[4] = 0x00;
  task_args[5] = 0x00;
  task_args[6] = 0x40;

  if (ioctl(fd, HDIO_DRIVE_TASK, &task_args))
  {
    return 0;
  }

  return ((task_args[6] & 0xf) << 24) +
    (task_args[5] << 16) +
    (task_args[4] << 8) + task_args[3];
#else
  return 0;
#endif
}

static uint64_t sg_read_native_max_ext(int fd)
{
#ifdef SG_IO
  unsigned char cdb[16];
  unsigned char sb[32];
  const unsigned char *desc= (const unsigned char*)(sb + 8);
  sg_io_hdr_t  io_hdr;

  memset(&cdb, 0, sizeof(cdb));
  cdb[ 0] = 0x85;
  cdb[ 1] = SG_ATA_PROTO_NON_DATA;
  cdb[ 2] = SG_CDB2_CHECK_COND;
  cdb[13] = 0x40; // dev;
  cdb[14] = WIN_READ_NATIVE_MAX_EXT; // command;
//  if (is_lba48)
  {
    cdb[ 1] |= SG_ATA_LBA48;
  }
  memset(&sb,     0, sizeof(sb));
  memset(&io_hdr, 0, sizeof(io_hdr));
  io_hdr.interface_id	= 'S';
  io_hdr.cmd_len	= sizeof(cdb);
  io_hdr.mx_sb_len	= sizeof(sb);
  io_hdr.dxfer_direction=  SG_DXFER_NONE;
  io_hdr.dxfer_len	= 0;
  io_hdr.dxferp		= NULL;
  io_hdr.cmdp		= cdb;
  io_hdr.sbp		= sb;
  io_hdr.pack_id	= 0;
  io_hdr.timeout	= 1000; /* msecs */

  if (ioctl(fd, SG_IO, &io_hdr) == -1) {
    return 0;	/* SG_IO not supported */
  }
  if (io_hdr.host_status || io_hdr.driver_status != SG_DRIVER_SENSE
      || (io_hdr.status && io_hdr.status != SG_CHECK_CONDITION))
    return 0;
  if (sb[0] != 0x72 || sb[7] < 14)
    return 0;
  if (desc[0] != 9 || desc[1] < 12)
    return 0;
  return desc[7]+(desc[9]<<8)+(desc[11]<<16)+
    ((desc[ 2] & 1)==0?0:(desc[6]<<24)+((uint64_t)desc[8]<<32)+((uint64_t)desc[10]<<40));
#else
  return 0;
#endif
}

static uint64_t sg_device_configuration_identify(int fd)
{
#ifdef SG_IO
  unsigned char cdb[16];
  unsigned char sb[32];
  unsigned char data[512];
  sg_io_hdr_t  io_hdr;

  memset(&cdb,    0, sizeof(cdb));
  memset(&sb,     0, sizeof(sb));
  memset(&io_hdr, 0, sizeof(io_hdr));
  memset(&data,   0, sizeof(data));
  cdb[ 0] = 0x85;
  cdb[ 1] = SG_ATA_PROTO_PIO_IN;
  cdb[ 2] = SG_CDB2_CHECK_COND;
  cdb[ 2] |= SG_CDB2_TLEN_NSECT | SG_CDB2_TLEN_SECTORS;
  cdb[ 2] |= SG_CDB2_TDIR_FROM_DEV;
  cdb[ 4] = 0xC2; /* Device Configuration Identify */
  cdb[ 6] = 0;	// lob.nsect;
  cdb[ 8] = 0;	// lob.lbal;
  cdb[10] = 0;	// lob.lbam;
  cdb[12] = 0;	// lob.lbah;
  cdb[13] = 0x40; // dev;
  cdb[14] = 0xB1; // command;
  io_hdr.interface_id	= 'S';
  io_hdr.cmd_len	= sizeof(cdb);
  io_hdr.mx_sb_len	= sizeof(sb);
  io_hdr.dxfer_direction= SG_DXFER_FROM_DEV;
  io_hdr.dxfer_len	= 512;
  io_hdr.dxferp		= &data;
  io_hdr.cmdp		= cdb;
  io_hdr.sbp		= sb;
  io_hdr.pack_id	= 0;
  io_hdr.timeout	= 1000; /* msecs */

  if (ioctl(fd, SG_IO, &io_hdr) == -1)
    return 0;	/* SG_IO not supported */
  if (io_hdr.host_status || io_hdr.driver_status != SG_DRIVER_SENSE
      || (io_hdr.status && io_hdr.status != SG_CHECK_CONDITION))
    return 0;
  if (sb[0] != 0x72 || sb[7] < 14)
    return 0;
  if(data[0x1fe]!=0xa5)
    return 0;
  return data[6] + (data[7]<<8) + (data[8]<<16) + (data[9]<<24) +
    ((uint64_t)data[10]<<32) + ((uint64_t)data[11]<<40) + ((uint64_t)data[12]<<48) + ((uint64_t)data[13]<<56);
#else
  return 0;
#endif
}

void disk_get_hpa_dco(const int fd, disk_t *disk, const int verbose)
{
#ifdef HDIO_DRIVE_CMD
  unsigned char id_args[4 + 512];
  const uint16_t *id_val=(const uint16_t *) & id_args[4];
  unsigned int flags=0;
  uint64_t user_max;
  uint64_t native_max;
  uint64_t dco;
  /* Execute the IDENTIFY DEVICE command */
  memset(id_args, 0, sizeof(id_args));
  id_args[0] = WIN_IDENTIFY;
  id_args[3] = 1;

  if (ioctl(fd, HDIO_DRIVE_CMD, &id_args)) {
    id_args[0] = WIN_PIDENTIFY;
    if (ioctl(fd, HDIO_DRIVE_CMD, &id_args)) {
      return;
    }
  }

  if (id_val[0] & 0x8000) {
    log_warning("%s is not an ATA disk\n", disk->device);
    return;
  }

  /* Give up if LBA is not supported */
  if ((id_val[49] & 0x0200) == 0) {
    log_error("%s: LBA mode not supported.\n", disk->device);
    return;
  }
  log_info("%s: LBA", disk->device);
  // see if the removable media feature is supported
  if (id_val[82] & 0x0004) {
    flags |= DISK_HAS_REMOVABLE_SUPPORT;
    log_info(", Removable");
  }

  // see if the HPA commands are supported
  if (id_val[82] & 0x0400) {
    flags |= DISK_HAS_HPA_SUPPORT;
    log_info(", HPA");
  }

  // see if word 83 is valid -- this is a signature check
  if ((id_val[83] & 0xc000) == 0x4000) {
    // see if the 48-bit commands are supported
    if (id_val[83] & 0x0400) {
      flags |= DISK_HAS_48_SUPPORT;
      log_info(", LBA48");
    }
    if (id_val[83] & 0x0800) {
      log_info(", DCO");
    }
  }
  log_info(" support\n");

  user_max = 0;
  if (flags & DISK_HAS_48_SUPPORT) {
    user_max = (uint64_t) id_val[103] << 48 |
      (uint64_t) id_val[102] << 32 |
      (uint64_t) id_val[101] << 16 | (uint64_t) id_val[100];
  }
  /* Use the 28-bit fields */
  if (user_max == 0) {
    user_max = (uint64_t) id_val[61] << 16 | id_val[60];
  }
  native_max=sg_read_native_max_ext(fd);
  if(native_max==0)
    native_max=read_native_max(fd);
  if(disk->sector_size!=0)
    log_info("%s: size       %llu\n", disk->device, (long long unsigned)(disk->disk_real_size/disk->sector_size));
  if(user_max!=0)
    log_info("%s: user_max   %llu\n", disk->device, (long long unsigned)user_max);
  if(native_max!=0)
    log_info("%s: native_max %llu\n", disk->device, (long long unsigned)(native_max+1));
  if(dco!=0)
    log_info("%s: dco        %llu\n", disk->device, (long long unsigned)(dco+1));
#endif
}
#else
void disk_get_hpa_dco(const int fd, disk_t *disk, const int verbose)
{
}
#endif
