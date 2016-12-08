/**
 * @file test.testable.h
 * @author Team Rogue++
 * @date December 08, 2016
 *
 * @brief Member declarations for the Testable class
 */ 

#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
 * @brief      Base class for unit tests.
 */
class Testable {
	public:
		/**
 		  * @brief      Test entry point.
 		  */
		virtual void test() = 0;

		/**
		 * @brief      Asserts the given condition is true and associates the result with the provided comment.
		 *
		 * @param[in]  condition  The condition to be assert
		 * @param[in]  comment    The associated comment
		 */
		void assert(bool condition, std::string comment);

		/**
		 * @brief      Displays the given comment.
		 *
 		 * @param[in]  comment  The comment to be displayed.
 		 */
		void comment(std::string comment);

	private:
		int count = 0;
		bool onlyShowFailures = false;
};
