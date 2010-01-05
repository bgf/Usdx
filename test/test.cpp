/*
 * UltraStar Deluxe - Karaoke Game
 *
 * UltraStar Deluxe is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
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
 * along with this program; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 */

#include <fstream>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TextTestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/TextOutputter.h>

int main(int argc, char **argv)
{
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

	// Create the event manager and test controller
	CppUnit::TestResult controller;

	// Add a listener that colllects test result
	CppUnit::TestResultCollector result;
	controller.addListener(&result);

	// Add a listener that print dots as test run.
	CppUnit::BriefTestProgressListener progress;
	controller.addListener(&progress);

	CppUnit::TextTestRunner runner;
	runner.addTest(registry.makeTest());
	runner.run(controller);

	CppUnit::TextOutputter outputter(&result, std::cout);
	outputter.write();

	std::fstream filestr;
	filestr.open ("test.xml", std::fstream::out | std::fstream::trunc);
	CppUnit::XmlOutputter xml_outputter(&result, filestr);
	xml_outputter.write();
	filestr.close();

	return result.testFailuresTotal();
}
