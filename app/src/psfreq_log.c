/**
 * @file psfreq_log.c
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
 * A convenience class which allows for easy logging of messages that are
 * sorted by levels: debugging, normal messages, quiet messages, and
 * entirely silenced output using the all_quiet mode.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "psfreq_log.h"

typedef int8_t psfreq_log_level;

static psfreq_log_level psfreq_log_state = PSFREQ_LOG_NORMAL;

static bool psfreq_log_should_display(uint8_t log_level);

static bool psfreq_log_should_display(uint8_t log_level)
{
        return (psfreq_log_state < log_level);
}

void psfreq_log_debug(const char *const fmt, ...)
{
        if (psfreq_log_should_display(PSFREQ_LOG_NORMAL)) {
                va_list arg;
                va_start(arg, fmt);
                vfprintf(stdout, fmt, arg);
                va_end(arg);
        }
}

void psfreq_log_normal(const char *const fmt, ...)
{
        if (psfreq_log_should_display(PSFREQ_LOG_QUIET)) {
                va_list arg;
                va_start(arg, fmt);
                vfprintf(stdout, fmt, arg);
                va_end(arg);
        }
}

void psfreq_log_error(const char *const fmt, ...)
{
        if (psfreq_log_should_display(PSFREQ_LOG_ALL_QUIET)) {
                va_list arg;
                va_start(arg, fmt);
                vfprintf(stderr, fmt, arg);
                va_end(arg);
        }
}
