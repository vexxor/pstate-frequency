/*
 * pstate-frequency Easier control of the Intel p-state driver
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
 * For questions please contact pyamsoft at pyam.soft@gmail.com
 */

#ifndef CPP_PSFREQ_LOGGER_H
#define CPP_PSFREQ_LOGGER_H

#include <iostream>
#include <sstream>
#include <string>

namespace psfreq {

class logger {
private:

	static std::ostringstream oss;
	static int verbose;

public:
	logger()
	{
		verbose = 0;
	}

	~logger()
	{
		oss.clear();
	}

	static void log(std::string& str)
	{
		oss << str;
	}

	static void d()
	{
		if (verbose == 1) {
			const std::string str = flush();
			std::cout << str;
		}
	}

	static void e()
	{
		if (verbose == 1) {
			const std::string str = flush();
			std::cerr << str;
		}
	}

	static const std::string flush()
	{
		if (verbose == 1) {
			const std::string str = oss.str();
			oss.clear();
			return str;
		} else {
			return "";
		}
	}

	static void setQuiet()
	{
		verbose = -1;
	}

	static void setDebug()
	{
		verbose = 1;
	}
};

}

#endif
