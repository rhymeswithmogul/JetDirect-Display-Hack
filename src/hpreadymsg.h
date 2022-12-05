/*
 * hpreadymsg -- a JetDirect Display Hack
 *   Original:  (c) 1997 Silicosis of L0pht <sili@l0pht.com>.
 *   This port: (c) 2022 Colin Cogle <colin@colincogle.name>.
 *
 * From https://www.irongeek.com/i.php?page=security/jetdirecthack:
 * "Back in 1997 Silicosis of L0pht (sili@l0pht.com) wrote a bit of exploit
 *  code for *nix systems that allows you to set the text that displays on
 *  the little LCD panel of an HP printer.  It accomplished this over the
 *  network by sending packets to the JetDirect box hooked to the printer
 *  (or built into it)."
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, visit: https://gnu.org/licenses/gpl-3.0.html
 */

#ifndef PACKAGE
#define PACKAGE "hpreadymsg"
#endif

#ifndef VERSION
#define VERSION 1.0
#endif

extern void credits();
extern void help(const char* const appName);