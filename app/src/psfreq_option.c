/**
 * @file psfreq_option.c
 * @author pyamsoft <pyam(dot)soft(at)gmail(dot)com>
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * @section DESCRIPTION
 * Helper functions for processing and handling getopt output
 */

#include <getopt.h>

#include "psfreq_log.h"
#include "psfreq_option.h"

void psfreq_option_init(psfreq_option_type *options)
{
        options->action = ACTION_TYPE_UNDEFINED;

        /* options->cpu_turbo = malloc(sizeof(char *)); */
        options->cpu_turbo = TURBO_UNDEFINED;

        /* options->cpu_max = malloc(sizeof(char *)); */
        options->cpu_max = CPU_UNDEFINED;

        /* options->cpu_min = malloc(sizeof(char *)); */
        options->cpu_min = CPU_UNDEFINED;

        /* options->cpu_governor = malloc(sizeof(char *)); */
        options->cpu_governor = GOVERNOR_UNDEFINED;

        /* options->cpu_plan = malloc(sizeof(char *)); */
        options->cpu_plan = PLAN_UNDEFINED;

        options->cpu_get_type = CPU_GET_TYPE_CURRENT;
        options->cpu_sleep = SLEEP;
        options->color_enabled = NO_COLOR;
}

unsigned char psfreq_option_parse(psfreq_option_type *options, const int opt)
{
        switch(opt) {
        case 0:
                /* end of options */
                return EXIT_SUCCESS;
        case 'H':
                /* Help */
                if (options->action == ACTION_TYPE_UNDEFINED) {
			options->action = ACTION_TYPE_HELP;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"Cannot define multiple actions");
			return EXIT_FAILURE;
		}
        case 'V':
                /* Version */
                if (options->action == ACTION_TYPE_UNDEFINED) {
			options->action = ACTION_TYPE_VERSION;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"Cannot define multiple actions");
			return EXIT_FAILURE;
		}
        case 'G':
                /* ACTION: Get */
                if (options->action == ACTION_TYPE_UNDEFINED) {
			options->action = ACTION_TYPE_CPU_GET;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"Cannot define multiple actions");
			return EXIT_FAILURE;
		}
        case 'c':
                /*
                 * The --current option is only valid when using
                 * pstate-frequency to get CPU values
                 */
                if (options->action == ACTION_TYPE_CPU_GET) {
                        options->cpu_get_type = CPU_GET_TYPE_CURRENT;
                        return EXIT_SUCCESS;
                } else {
			psfreq_log_error("psfreq_option_parse",
				"The switch -c|--current is only available when acting with -G|--get");
                        return EXIT_FAILURE;
                }
        case 'r':
                /*
                 * The --real option is only valid when using
                 * pstate-frequency to get CPU values
                 */
                if (options->action == ACTION_TYPE_CPU_GET) {
                        options->cpu_get_type = CPU_GET_TYPE_REAL;
                        return EXIT_SUCCESS;
                } else {
			psfreq_log_error("psfreq_option_parse",
				"The switch -r|--real is only available when acting with -G|--get");
                        return EXIT_FAILURE;
                }
        case 'S':
                /* ACTION: Set */
                if (options->action == ACTION_TYPE_UNDEFINED) {
			options->action = ACTION_TYPE_CPU_SET;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"Cannot define multiple actions");
			return EXIT_FAILURE;
		}
        case 'p':
                /*
                 * The --plan option is only valid when using pstate-frequency
                 * to set CPU values
                 */
                if (options->action == ACTION_TYPE_CPU_SET) {
			options->cpu_plan = optarg;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"The switch -p|--plan is only available when acting with -S|--set");
                        return EXIT_FAILURE;
		}
        case 'm':
                /*
                 * The --max option is only valid when using pstate-frequency
                 * to set CPU values
                 */
                if (options->action == ACTION_TYPE_CPU_SET) {
			options->cpu_max = optarg;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"The switch -m|--max is only available when acting with -S|--set");
                        return EXIT_FAILURE;
		}
        case 'g':
                /*
                 * The --governor option is only valid when using
                 * pstate-frequency to set CPU values
                 */
                if (options->action == ACTION_TYPE_CPU_SET) {
			options->cpu_governor = optarg;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"The switch -g|--governor is only available when acting with -S|--set");
                        return EXIT_FAILURE;
		}
        case 'n':
                /*
                 * The --min option is only valid when using
                 * pstate-frequency to set CPU values
                 */
                if (options->action == ACTION_TYPE_CPU_SET) {
			options->cpu_min = optarg;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"The switch -n|--min is only available when acting with -S|--set");
                        return EXIT_FAILURE;
		}
        case 't':
                /*
                 * The --turbo option is only valid when using
                 * pstate-frequency to set CPU values
                 */
                if (options->action == ACTION_TYPE_CPU_SET) {
			options->cpu_turbo = optarg;
			return EXIT_SUCCESS;
		} else {
			psfreq_log_error("psfreq_option_parse",
				"The switch -t|--turbo is only available when acting with -S|--set");
                        return EXIT_FAILURE;
		}
        case 'd':
                /* enable debugging */
                psfreq_log_set_debug();
                return EXIT_SUCCESS;
        case 'q':
                psfreq_log_set_quiet();
                return EXIT_SUCCESS;
        case '2':
                /* Do not sleep for 2 seconds */
                options->cpu_sleep = NO_SLEEP;
                return EXIT_SUCCESS;
        case '1':
                /* Enable color messages */
                options->color_enabled = COLOR;
                return EXIT_SUCCESS;
        case ':':
                /* Missing arguments */
                psfreq_log_error("psfreq_option_parse",
                                "Missing option arguments");
                return EXIT_FAILURE;
        case '?':
                /* Invalid option */
                psfreq_log_error("psfreq_option_parse", "Invalid option");
                return EXIT_FAILURE;
        default:
                psfreq_log_error("psfreq_option_parse",
                                "End of options, no matching option supported");
                return EXIT_FAILURE;
        }
}
