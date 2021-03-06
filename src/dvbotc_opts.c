/*-----------------------------------------------------
 Implementation of DVBOTC
 for command line options

 This program is free software; you can redistribute it and/or
 modify it under the terms of version 2 of the GNU General
 Public License as published by the Free Software Foundation.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor,
 Boston, MA  02110-1301, USA.

 Copyright Damien Morrissey 2007 All rights reserved

 Generated by aargh 1.2
 Fri Aug 17 16:47:33 2007
-----------------------------------------------------*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "dvbotc_opts.h"

static void initialize( DVBOTC * pOpts )
{
	pOpts->new_argc = 0;
	pOpts->new_argv = NULL;

	pOpts->chan_bw_found = 0;
	pOpts->chan_bw = NULL;
	pOpts->cell_id_found = 0;
	pOpts->cell_id = NULL;
	pOpts->debug_output_prefix_found = 0;
	pOpts->debug_output_prefix = NULL;
	pOpts->guard_interval_found = 0;
	pOpts->guard_interval = NULL;
	pOpts->help = 0;
	pOpts->input_file_found = 0;
	pOpts->input_file = NULL;
	pOpts->output_found = 0;
	pOpts->output = NULL;
	pOpts->puncturing_rate_found = 0;
	pOpts->puncturing_rate = NULL;
	pOpts->qam_level_found = 0;
	pOpts->qam_level = NULL;
	pOpts->no_write = 0;
}

int get_dvbotc_opts( int argc, char * argv[], DVBOTC * pOpts )
{
	int rc = 0; /* return code */
	int opt;

	/* Define valid option characters */

	const char optstring[] = ":b:c:d:g:hi:o:p:q:x";

	/* Initialize members of struct */

	initialize( pOpts );

	/* Suppress error messages from getopt() */

	opterr = 0;

	/* Examine command line options */

	while( ( opt = getopt( argc, argv, optstring ) ) != -1 )
	{
		switch( opt )
		{
			case 'b' :   /* Get chan_bw */
				if( pOpts->chan_bw_found )
				{
					fprintf( stderr, "Only one occurrence of -b option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->chan_bw_found = 1;

				/* Call validator function */

				if( val_bw( optarg ) )
				{
					fprintf( stderr, "Argument to -b option \"%s\" "
						"is invalid\n", optarg );
					rc = 1;
				}

				pOpts->chan_bw = optarg;
				break;
			case 'c' :   /* Get cell_id */
				if( pOpts->cell_id_found )
				{
					fprintf( stderr, "Only one occurrence of -c option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->cell_id_found = 1;

				/* Call validator function */

				if( val_id( optarg ) )
				{
					fprintf( stderr, "Argument to -c option \"%s\" "
						"is invalid\n", optarg );
					rc = 1;
				}

				pOpts->cell_id = optarg;
				break;
			case 'd' :   /* Get debug_output_prefix */
				if( pOpts->debug_output_prefix_found )
				{
					fprintf( stderr, "Only one occurrence of -d option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->debug_output_prefix_found = 1;

				pOpts->debug_output_prefix = optarg;
				break;
			case 'g' :   /* Get guard_interval */
				if( pOpts->guard_interval_found )
				{
					fprintf( stderr, "Only one occurrence of -g option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->guard_interval_found = 1;

				/* Call validator function */

				if( val_gi( optarg ) )
				{
					fprintf( stderr, "Argument to -g option \"%s\" "
						"is invalid\n", optarg );
					rc = 1;
				}

				pOpts->guard_interval = optarg;
				break;
			case 'h' :   /* Get help */
				pOpts->help = 1;
				break;
			case 'i' :   /* Get input_file */
				if( pOpts->input_file_found )
				{
					fprintf( stderr, "Only one occurrence of -i option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->input_file_found = 1;

				pOpts->input_file = optarg;
				break;
			case 'o' :   /* Get output */
				if( pOpts->output_found )
				{
					fprintf( stderr, "Only one occurrence of -o option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->output_found = 1;

				pOpts->output = optarg;
				break;
			case 'p' :   /* Get puncturing_rate */
				if( pOpts->puncturing_rate_found )
				{
					fprintf( stderr, "Only one occurrence of -p option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->puncturing_rate_found = 1;

				/* Call validator function */

				if( val_pu( optarg ) )
				{
					fprintf( stderr, "Argument to -p option \"%s\" "
						"is invalid\n", optarg );
					rc = 1;
				}

				pOpts->puncturing_rate = optarg;
				break;
			case 'q' :   /* Get qam_level */
				if( pOpts->qam_level_found )
				{
					fprintf( stderr, "Only one occurrence of -q option allowed\n" );
					rc = 1;
					break;
				}
				pOpts->qam_level_found = 1;

				/* Call validator function */

				if( val_qa( optarg ) )
				{
					fprintf( stderr, "Argument to -q option \"%s\" "
						"is invalid\n", optarg );
					rc = 1;
				}

				pOpts->qam_level = optarg;
				break;
			case 'x' :   /* Get no_write */
				pOpts->no_write = 1;
				break;
			case ':' : /* Missing argument */
				fprintf( stderr, "Required argument missing on -%c option\n",
					(char) optopt );
				rc = 1;
				break;
			case '?' : /* Invalid option */
				fprintf( stderr, "Invalid option '-%c' on command line\n",
					(char) optopt );
				rc = 1;
				break;
			default :  /* Programmer error */
				fprintf( stderr, "Internal error: unexpected value '-%c'"
					"for optopt", (char) optopt );
				rc = 1;
				break;
		} /* end switch */
	} /* end while */

	/* See if required options were supplied; apply defaults */

	if( ! pOpts->chan_bw_found )
		pOpts->chan_bw = "6";

	if( ! pOpts->guard_interval_found )
		pOpts->guard_interval = "1/4";

	if( ! pOpts->input_file_found )
	{
		fprintf( stderr, "Required option -i not provided on command line\n" );
		rc = 1;
	}

	if( ! pOpts->output_found )
		pOpts->output = "dvbotc.bin";

	if( ! pOpts->puncturing_rate_found )
		pOpts->puncturing_rate = "2/3";

	if( ! pOpts->qam_level_found )
		pOpts->qam_level = "16";

	if( optind > argc )
	{
		/* This should never happen! */

		fprintf( stderr, "Program error: found more arguments than expected\n" );
		rc = 1;
	}
	else
	{
		/* Calculate new_argcv and new_argc to reflect */
		/* the number of arguments consumed */

		pOpts->new_argc = argc - optind + 1;
		pOpts->new_argv = argv + optind - 1;
	}

	return rc;
}
