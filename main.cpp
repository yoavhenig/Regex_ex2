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
  regex searchWord(R"(^\w+(\s\[)?(\d+)?\,?(\d+)?(\])?$)");
  regex searchAnd(R"(^(\w+)\s\{AND\}\s(\w+)(\s\[)?(\d+)?\,?(\d+)?(\])?$)");
  regex searchOr(R"(^(\w+)\s\{OR\}\s(\w+)(\s\[)?(\d+)?\,?(\d+)?(\])?$)");
  // regex searchAndN(R"(^(\w+)(\s{\d}\s)(\w+)([\d,\d])?$.*)");

    if (argc != 2)
		{cerr << "No input file" << endl; return EXIT_FAILURE;}
    ifstream infile(argv[1]);
    if (!infile)
		{cerr << "No input file!" << endl; return EXIT_FAILURE;}
	TextQuery tq(infile); // store the file in a vector and build the query map
//	tq.display_map(); // debugging aid

  auto matches = smatch{};
  size_t leftline, rightline;

	while (true) {
		cout << "enter word to look for, or q to quit: ";
		string line;
		getline(cin, line);
		if (line.empty() || line == "q") break;

      else if(regex_match(line, matches, searchWord)){  //match for singel word
        std::cout << "searchWord..." << '\n';
        WordQuery query(line);
        auto result = query.eval(tq);
          if(matches[2].matched && matches[3].matched){
            if(matches[2].matched){
              leftline=std::stoi(matches[2]);
            }
            if(matches[3].matched){
              rightline=std::stoi(matches[3]);
            }
            std::cout << "left: "<<leftline<<" right: "<<rightline << '\n';
          }
    		print(cout, result) << endl;
      }



      else if(regex_match(line, matches, searchAnd)){ //match sor AND search
        std::cout << "searchAnd..." << '\n';
        AndQuery query(matches[1], matches[2]);
        auto result = query.eval(tq);
          if(matches[4].matched && matches[5].matched){
            if(matches[4].matched){
              leftline=std::stoi(matches[4]);
            }
            if(matches[5].matched){
              rightline=std::stoi(matches[5]);
            }
            std::cout << "left: "<<leftline<<" right: "<<rightline << '\n';
          }
    		print(cout, result) << endl;
      }



      else if(regex_match(line, matches, searchOr)){  //match sor OR search
        std::cout << "searchOr..." << '\n';
        OrQuery query(matches[1], matches[2]);
        auto result = query.eval(tq);
          if(matches[4].matched && matches[5].matched){
            if(matches[4].matched){
              leftline=std::stoi(matches[4]);
            }
            if(matches[5].matched){
              rightline=std::stoi(matches[5]);
            }
            std::cout << "left: "<<leftline<<" right: "<<rightline << '\n';
          }
    		print(cout, result) << endl;
      }




      // else if(regex_match(line, matches, searchAndN)){
      //   std::cout << "searchAndN..." << '\n';
      //   auto result = query.eval(tq);
  		//   print(cout, result) << endl;
      // }



      else{std::cout << "‫‪Unrecognized‬‬ ‫‪search‬‬" << '\n';} //no regex match


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
