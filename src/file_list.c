/*

    File: file_list.c

    Copyright (C) 1998-2009 Christophe GRENIER <grenier@cgsecurity.org>

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

#include <stdio.h>
#include "types.h"
#include "filegen.h"

extern const file_hint_t file_hint_7z;
extern const file_hint_t file_hint_a;
extern const file_hint_t file_hint_abcdp;
extern const file_hint_t file_hint_accdb;
extern const file_hint_t file_hint_ace;
extern const file_hint_t file_hint_addressbook;
extern const file_hint_t file_hint_ahn;
extern const file_hint_t file_hint_aif;
extern const file_hint_t file_hint_all;
extern const file_hint_t file_hint_als;
extern const file_hint_t file_hint_amd;
extern const file_hint_t file_hint_amr;
extern const file_hint_t file_hint_apa;
extern const file_hint_t file_hint_ape;
extern const file_hint_t file_hint_apple;
extern const file_hint_t file_hint_arj;
extern const file_hint_t file_hint_asf;
extern const file_hint_t file_hint_asm;
extern const file_hint_t file_hint_atd;
extern const file_hint_t file_hint_au;
extern const file_hint_t file_hint_bkf;
extern const file_hint_t file_hint_blend;
extern const file_hint_t file_hint_bmp;
extern const file_hint_t file_hint_bz2;
extern const file_hint_t file_hint_cab;
extern const file_hint_t file_hint_cam;
extern const file_hint_t file_hint_chm;
extern const file_hint_t file_hint_class;
extern const file_hint_t file_hint_cm;
extern const file_hint_t file_hint_compress;
extern const file_hint_t file_hint_crw;
extern const file_hint_t file_hint_ctg;
extern const file_hint_t file_hint_cwk;
extern const file_hint_t file_hint_d2s;
extern const file_hint_t file_hint_dat;
extern const file_hint_t file_hint_dbf;
extern const file_hint_t file_hint_dim;
extern const file_hint_t file_hint_dir;
extern const file_hint_t file_hint_djv;
extern const file_hint_t file_hint_doc;
extern const file_hint_t file_hint_dpx;
extern const file_hint_t file_hint_drw;
extern const file_hint_t file_hint_ds2;
extern const file_hint_t file_hint_dsc;
extern const file_hint_t file_hint_dss;
extern const file_hint_t file_hint_dta;
extern const file_hint_t file_hint_dump;
extern const file_hint_t file_hint_dv;
extern const file_hint_t file_hint_dwg;
extern const file_hint_t file_hint_dxf;
extern const file_hint_t file_hint_edb;
extern const file_hint_t file_hint_elf;
extern const file_hint_t file_hint_emf;
extern const file_hint_t file_hint_evt;
extern const file_hint_t file_hint_exe;
extern const file_hint_t file_hint_ext2_sb;
extern const file_hint_t file_hint_fbk;
extern const file_hint_t file_hint_fcp;
extern const file_hint_t file_hint_fcs;
extern const file_hint_t file_hint_fdb;
extern const file_hint_t file_hint_fh10;
extern const file_hint_t file_hint_fh5;
extern const file_hint_t file_hint_fits;
extern const file_hint_t file_hint_flac;
extern const file_hint_t file_hint_fasttxt;
extern const file_hint_t file_hint_flp;
extern const file_hint_t file_hint_flv;
extern const file_hint_t file_hint_fob;
extern const file_hint_t file_hint_fp7;
extern const file_hint_t file_hint_frm;
extern const file_hint_t file_hint_fs;
extern const file_hint_t file_hint_gho;
extern const file_hint_t file_hint_gif;
extern const file_hint_t file_hint_gpg;
extern const file_hint_t file_hint_gz;
extern const file_hint_t file_hint_hds;
extern const file_hint_t file_hint_hr9;
extern const file_hint_t file_hint_ico;
extern const file_hint_t file_hint_ifo;
extern const file_hint_t file_hint_imb;
extern const file_hint_t file_hint_indd;
extern const file_hint_t file_hint_iso;
extern const file_hint_t file_hint_itunes;
extern const file_hint_t file_hint_jpg;
extern const file_hint_t file_hint_kdb;
extern const file_hint_t file_hint_ldf;
extern const file_hint_t file_hint_logic;
extern const file_hint_t file_hint_lnk;
extern const file_hint_t file_hint_m2ts;
extern const file_hint_t file_hint_max;
extern const file_hint_t file_hint_mb;
extern const file_hint_t file_hint_mcd;
extern const file_hint_t file_hint_mdb;
extern const file_hint_t file_hint_mdf;
extern const file_hint_t file_hint_mfa;
extern const file_hint_t file_hint_mfg;
extern const file_hint_t file_hint_mid;
extern const file_hint_t file_hint_mk5;
extern const file_hint_t file_hint_mkv;
extern const file_hint_t file_hint_mov;
extern const file_hint_t file_hint_mp3;
extern const file_hint_t file_hint_mpg;
extern const file_hint_t file_hint_mrw;
extern const file_hint_t file_hint_mus;
extern const file_hint_t file_hint_mxf;
extern const file_hint_t file_hint_mysql;
extern const file_hint_t file_hint_njx;
extern const file_hint_t file_hint_nk2;
extern const file_hint_t file_hint_ogg;
extern const file_hint_t file_hint_one;
extern const file_hint_t file_hint_orf;
extern const file_hint_t file_hint_paf;
extern const file_hint_t file_hint_pap;
extern const file_hint_t file_hint_pcap;
extern const file_hint_t file_hint_pct;
extern const file_hint_t file_hint_pcx;
extern const file_hint_t file_hint_pdf;
extern const file_hint_t file_hint_pfx;
extern const file_hint_t file_hint_png;
extern const file_hint_t file_hint_prc;
extern const file_hint_t file_hint_prt;
extern const file_hint_t file_hint_ps;
extern const file_hint_t file_hint_psd;
extern const file_hint_t file_hint_psp;
extern const file_hint_t file_hint_pst;
extern const file_hint_t file_hint_ptb;
extern const file_hint_t file_hint_pyc;
extern const file_hint_t file_hint_qbb;
extern const file_hint_t file_hint_qdf;
extern const file_hint_t file_hint_qxd;
extern const file_hint_t file_hint_ra;
extern const file_hint_t file_hint_raf;
extern const file_hint_t file_hint_rar;
extern const file_hint_t file_hint_raw;
extern const file_hint_t file_hint_rdc;
extern const file_hint_t file_hint_reg;
extern const file_hint_t file_hint_res;
extern const file_hint_t file_hint_riff;
extern const file_hint_t file_hint_rm;
extern const file_hint_t file_hint_rns;
extern const file_hint_t file_hint_rpm;
extern const file_hint_t file_hint_ses;
extern const file_hint_t file_hint_sib;
extern const file_hint_t file_hint_sit;
extern const file_hint_t file_hint_skp;
extern const file_hint_t file_hint_sp3;
extern const file_hint_t file_hint_spe;
extern const file_hint_t file_hint_spf;
extern const file_hint_t file_hint_spss;
extern const file_hint_t file_hint_sqlite;
extern const file_hint_t file_hint_sqm;
extern const file_hint_t file_hint_stl;
extern const file_hint_t file_hint_stuffit;
extern const file_hint_t file_hint_swf;
extern const file_hint_t file_hint_tar;
extern const file_hint_t file_hint_tax;
extern const file_hint_t file_hint_tib;
extern const file_hint_t file_hint_tiff;
extern const file_hint_t file_hint_tph;
extern const file_hint_t file_hint_ttf;
extern const file_hint_t file_hint_txt;
extern const file_hint_t file_hint_tz;
extern const file_hint_t file_hint_veg;
extern const file_hint_t file_hint_vmdk;
extern const file_hint_t file_hint_wks;
extern const file_hint_t file_hint_wmf;
extern const file_hint_t file_hint_wnk;
extern const file_hint_t file_hint_wpd;
extern const file_hint_t file_hint_wv;
extern const file_hint_t file_hint_x3f;
extern const file_hint_t file_hint_xcf;
extern const file_hint_t file_hint_xm;
extern const file_hint_t file_hint_xsv;
extern const file_hint_t file_hint_xpt;
extern const file_hint_t file_hint_xv;
extern const file_hint_t file_hint_zip;

file_enable_t list_file_enable[]=
{
  { .enable=0, .file_hint=&file_hint_7z   },
  { .enable=0, .file_hint=&file_hint_a    },
  { .enable=0, .file_hint=&file_hint_abcdp},
  { .enable=0, .file_hint=&file_hint_accdb},
  { .enable=0, .file_hint=&file_hint_ace  },
  { .enable=0, .file_hint=&file_hint_addressbook},
  { .enable=0, .file_hint=&file_hint_ahn  },
  { .enable=0, .file_hint=&file_hint_aif  },
  { .enable=0, .file_hint=&file_hint_all  },
  { .enable=0, .file_hint=&file_hint_als  },
  { .enable=0, .file_hint=&file_hint_amd  },
  { .enable=0, .file_hint=&file_hint_amr  },
  { .enable=0, .file_hint=&file_hint_apa  },
  { .enable=0, .file_hint=&file_hint_ape  },
  { .enable=0, .file_hint=&file_hint_apple },
  { .enable=0, .file_hint=&file_hint_arj  },
  { .enable=0, .file_hint=&file_hint_asf  },
  { .enable=0, .file_hint=&file_hint_asm  },
  { .enable=0, .file_hint=&file_hint_atd  },
  { .enable=0, .file_hint=&file_hint_au   },
  { .enable=0, .file_hint=&file_hint_bkf  },
  { .enable=0, .file_hint=&file_hint_blend },
  { .enable=0, .file_hint=&file_hint_bmp  },
  { .enable=0, .file_hint=&file_hint_bz2  },
  { .enable=0, .file_hint=&file_hint_cab  },
  { .enable=0, .file_hint=&file_hint_cam  },
  { .enable=0, .file_hint=&file_hint_chm  },
  { .enable=0, .file_hint=&file_hint_class },
  { .enable=0, .file_hint=&file_hint_cm  },
  { .enable=0, .file_hint=&file_hint_compress },
  { .enable=0, .file_hint=&file_hint_crw  },
  { .enable=0, .file_hint=&file_hint_ctg  },
  { .enable=0, .file_hint=&file_hint_cwk  },
  { .enable=0, .file_hint=&file_hint_d2s  },
  { .enable=0, .file_hint=&file_hint_dat  },
  { .enable=0, .file_hint=&file_hint_dbf  },
  { .enable=0, .file_hint=&file_hint_dim  },
  { .enable=0, .file_hint=&file_hint_dir  },
  { .enable=0, .file_hint=&file_hint_djv  },
  { .enable=0, .file_hint=&file_hint_drw  },
  { .enable=0, .file_hint=&file_hint_doc  },
  { .enable=0, .file_hint=&file_hint_dpx  },
  { .enable=0, .file_hint=&file_hint_ds2  },
  { .enable=0, .file_hint=&file_hint_dsc  },
  { .enable=0, .file_hint=&file_hint_dss  },
  { .enable=0, .file_hint=&file_hint_dta  },
  { .enable=0, .file_hint=&file_hint_dump },
  { .enable=0, .file_hint=&file_hint_dv   },
  { .enable=0, .file_hint=&file_hint_dwg  },
  { .enable=0, .file_hint=&file_hint_dxf  },
  { .enable=0, .file_hint=&file_hint_edb  },
  { .enable=0, .file_hint=&file_hint_elf  },
  { .enable=0, .file_hint=&file_hint_emf  },
  { .enable=0, .file_hint=&file_hint_evt  },
  { .enable=0, .file_hint=&file_hint_exe  },
  { .enable=0, .file_hint=&file_hint_ext2_sb },
  { .enable=0, .file_hint=&file_hint_fbk  },
  { .enable=0, .file_hint=&file_hint_fcp  },
  { .enable=0, .file_hint=&file_hint_fcs  },
  { .enable=0, .file_hint=&file_hint_fdb  },
  { .enable=0, .file_hint=&file_hint_fh10  },
  { .enable=0, .file_hint=&file_hint_fh5  },
  { .enable=0, .file_hint=&file_hint_fits },
  { .enable=0, .file_hint=&file_hint_flac },
  { .enable=0, .file_hint=&file_hint_flp  },
  { .enable=0, .file_hint=&file_hint_flv  },
  { .enable=0, .file_hint=&file_hint_fob  },
  { .enable=0, .file_hint=&file_hint_fp7  },
  { .enable=0, .file_hint=&file_hint_frm  },
  { .enable=0, .file_hint=&file_hint_fs   },
  { .enable=0, .file_hint=&file_hint_gho  },
  { .enable=0, .file_hint=&file_hint_gif  },
  { .enable=0, .file_hint=&file_hint_gpg  },
  { .enable=0, .file_hint=&file_hint_gz   },
  { .enable=0, .file_hint=&file_hint_hds  },
  { .enable=0, .file_hint=&file_hint_hr9  },
  { .enable=0, .file_hint=&file_hint_ico  },
  { .enable=0, .file_hint=&file_hint_ifo  },
  { .enable=0, .file_hint=&file_hint_imb  },
  { .enable=0, .file_hint=&file_hint_indd  },
  { .enable=0, .file_hint=&file_hint_iso  },
  { .enable=0, .file_hint=&file_hint_itunes  },
  { .enable=0, .file_hint=&file_hint_jpg  },
  { .enable=0, .file_hint=&file_hint_kdb  },
  { .enable=0, .file_hint=&file_hint_ldf  },
  { .enable=0, .file_hint=&file_hint_logic},
  { .enable=0, .file_hint=&file_hint_lnk  },
  { .enable=0, .file_hint=&file_hint_m2ts },
  { .enable=0, .file_hint=&file_hint_max  },
  { .enable=0, .file_hint=&file_hint_mb   },
  { .enable=0, .file_hint=&file_hint_mcd  },
  { .enable=0, .file_hint=&file_hint_mdb  },
  { .enable=0, .file_hint=&file_hint_mdf  },
  { .enable=0, .file_hint=&file_hint_mfa  },
  { .enable=0, .file_hint=&file_hint_mfg  },
  { .enable=0, .file_hint=&file_hint_mid  },
  { .enable=0, .file_hint=&file_hint_mk5  },
  { .enable=0, .file_hint=&file_hint_mkv  },
  { .enable=0, .file_hint=&file_hint_mov  },
  { .enable=0, .file_hint=&file_hint_mp3  },
  { .enable=0, .file_hint=&file_hint_mpg  },
  { .enable=0, .file_hint=&file_hint_mrw  },
  { .enable=0, .file_hint=&file_hint_mus  },
  { .enable=0, .file_hint=&file_hint_mysql },
  { .enable=0, .file_hint=&file_hint_mxf  },
  { .enable=0, .file_hint=&file_hint_njx  },
  { .enable=0, .file_hint=&file_hint_nk2  },
  { .enable=0, .file_hint=&file_hint_ogg  },
  { .enable=0, .file_hint=&file_hint_one  },
  { .enable=0, .file_hint=&file_hint_orf  },
  { .enable=0, .file_hint=&file_hint_paf  },
  { .enable=0, .file_hint=&file_hint_pap  },
  { .enable=0, .file_hint=&file_hint_pcap },
  { .enable=0, .file_hint=&file_hint_pct  },
  { .enable=0, .file_hint=&file_hint_pcx  },
  { .enable=0, .file_hint=&file_hint_pdf  },
  { .enable=0, .file_hint=&file_hint_pfx  },
  { .enable=0, .file_hint=&file_hint_png  },
  { .enable=0, .file_hint=&file_hint_prc  },
  { .enable=0, .file_hint=&file_hint_prt  },
  { .enable=0, .file_hint=&file_hint_ps   },
  { .enable=0, .file_hint=&file_hint_psd  },
  { .enable=0, .file_hint=&file_hint_psp  },
  { .enable=0, .file_hint=&file_hint_pst  },
  { .enable=0, .file_hint=&file_hint_ptb  },
  { .enable=0, .file_hint=&file_hint_pyc  },
  { .enable=0, .file_hint=&file_hint_qbb  },
  { .enable=0, .file_hint=&file_hint_qdf  },
  { .enable=0, .file_hint=&file_hint_qxd  },
  { .enable=0, .file_hint=&file_hint_ra  },
  { .enable=0, .file_hint=&file_hint_raf  },
  { .enable=0, .file_hint=&file_hint_rar  },
  { .enable=0, .file_hint=&file_hint_raw  },
  { .enable=0, .file_hint=&file_hint_rdc  },
  { .enable=0, .file_hint=&file_hint_reg  },
  { .enable=0, .file_hint=&file_hint_res  },
  { .enable=0, .file_hint=&file_hint_riff },
  { .enable=0, .file_hint=&file_hint_rm   },
  { .enable=0, .file_hint=&file_hint_rns  },
  { .enable=0, .file_hint=&file_hint_rpm  },
  { .enable=0, .file_hint=&file_hint_ses  },
  { .enable=0, .file_hint=&file_hint_sib  },
  { .enable=0, .file_hint=&file_hint_sit  },
  { .enable=0, .file_hint=&file_hint_skp  },
  { .enable=0, .file_hint=&file_hint_sp3  },
  { .enable=0, .file_hint=&file_hint_spe  },
  { .enable=0, .file_hint=&file_hint_spf  },
  { .enable=0, .file_hint=&file_hint_spss },
  { .enable=0, .file_hint=&file_hint_sqlite	},
  { .enable=0, .file_hint=&file_hint_sqm  },
  { .enable=0, .file_hint=&file_hint_stl  },
  { .enable=0, .file_hint=&file_hint_stuffit  },
  { .enable=0, .file_hint=&file_hint_swf  },
  { .enable=0, .file_hint=&file_hint_tar  },
  { .enable=0, .file_hint=&file_hint_tax  },
  { .enable=0, .file_hint=&file_hint_tib  },
  { .enable=0, .file_hint=&file_hint_tiff },
  { .enable=0, .file_hint=&file_hint_tph  },
  { .enable=0, .file_hint=&file_hint_ttf  },
  { .enable=0, .file_hint=&file_hint_fasttxt  },
  { .enable=0, .file_hint=&file_hint_txt  },
  { .enable=0, .file_hint=&file_hint_tz   },
  { .enable=0, .file_hint=&file_hint_vmdk },
  { .enable=0, .file_hint=&file_hint_veg  },
  { .enable=0, .file_hint=&file_hint_wks  },
  { .enable=0, .file_hint=&file_hint_wmf  },
  { .enable=0, .file_hint=&file_hint_wnk  },
  { .enable=0, .file_hint=&file_hint_wpd  },
  { .enable=0, .file_hint=&file_hint_wv   },
  { .enable=0, .file_hint=&file_hint_x3f  },
  { .enable=0, .file_hint=&file_hint_xcf  },
  { .enable=0, .file_hint=&file_hint_xm   },
  { .enable=0, .file_hint=&file_hint_xsv  },
  { .enable=0, .file_hint=&file_hint_xpt  },
  { .enable=0, .file_hint=&file_hint_xv   },
  { .enable=0, .file_hint=&file_hint_zip  },
  { .enable=0, .file_hint=NULL }
};

