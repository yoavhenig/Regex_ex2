// This file contains code from "C++ Primer, Fourth Edition",
// by Stanley B.Lippman, Jose Lajoie, and Barbara E. Moo
#include "Query.h"
#include "TextQuery.h"
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

int main(int argc, char **argv)
{
  regex searchWord(R"(^\w+(\[\d\,\d\])?$)");
  regex searchAnd(R"(^(\w+)\s+\{AND\}\s+(\w+)$)");
  regex searchOr(R"(^(\w+)\s+\{OR\}\s+(\w+)$)");
  // regex searchAndN(R"(^(\w+)(\s{\d}\s)(\w+)([\d,\d])?$.*)");

    if (argc != 2)
		{cerr << "No input file" << endl; return EXIT_FAILURE;}
    ifstream infile(argv[1]);
    if (!infile)
		{cerr << "No input file!" << endl; return EXIT_FAILURE;}
	TextQuery tq(infile); // store the file in a vector and build the query map
//	tq.display_map(); // debugging aid

  auto matches = smatch{};

	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string line;
		getline(cin, line);
		if (line.empty() || line == "q") break;

      else if(regex_match(line, matches, searchWord)){
        std::cout << "searchWord..." << '\n';
        WordQuery query(line);
        auto result = query.eval(tq);
    		print(cout, result) << endl;
      }
      else if(regex_match(line, matches, searchAnd)){
        std::cout << "searchAnd..." << '\n';
        AndQuery query(matches[1], matches[2]);
        auto result = query.eval(tq);
    		print(cout, result) << endl;
      }
      else if(regex_match(line, matches, searchOr)){
        std::cout << "searchOr..." << '\n';
        OrQuery query(matches[1], matches[2]);
        auto result = query.eval(tq);
    		print(cout, result) << endl;
      }
      // else if(regex_match(line, matches, searchAndN)){
      //   std::cout << "searchAndN..." << '\n';
      //   break;
      // }
      // else{std::cout << "Default" << '\n';}


    // auto result = query.eval(tq);
		// print(cout, result) << endl;



		// AndQuery aquery("Unix", "system");
		// result = aquery.eval(tq);
		// print(cout, result) << endl;
    //
		// OrQuery oquery("Unix", "system");
		// result = oquery.eval(tq);
		// print(cout, result) << endl;

		// AndNQuery anquery("Unix", "system", 3);
		// result = anquery.eval(tq);
		// print(cout, result) << endl;
		// will print:
		// "Unix {3} system" occurs ...
	}
	return 0;
}
