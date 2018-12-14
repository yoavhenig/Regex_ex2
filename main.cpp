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

  regex searchWord(R"(^(\w+)(\s\[(\d+)\,(\d+)\])?$)");
  regex searchAnd(R"(^(\w+)\s\{AND\}\s(\w+)(\s\[(\d+)\,(\d+)\])?$)");
  regex searchOr(R"(^(\w+)\s\{OR\}\s(\w+)(\s\[(\d+)\,(\d+)\])?$)");
  regex searchAndN(R"(^(\w+)\s\{(\d+)\}\s(\w+)(\s\[(\d+)\,(\d+)\])?$)");


    if (argc != 2)
		{cerr << "No input file" << endl; return EXIT_FAILURE;}
    ifstream infile(argv[1]);
    if (!infile)
		{cerr << "No input file!" << endl; return EXIT_FAILURE;}
	TextQuery tq(infile); // store the file in a vector and build the query map
//	tq.display_map();     // debugging aid


auto matches = smatch{};
size_t leftline, rightline;

	while (true) {
		cout << "Enter one or two words to look for, or q to quit:\n";
		string line;
		getline(cin, line);
		if (line.empty() || line == "q") break;


    else if(regex_match(line, matches, searchWord)){  //match for singel word
        WordQuery query(matches[1]);
        auto result = query.eval(tq);
          if(matches[3].matched && matches[4].matched){
              leftline=std::stoi(matches[3]);
              rightline=std::stoi(matches[4]);
            print(cout, result, leftline, rightline) << endl;
            continue;
          }
    		print(cout, result) << endl;
      }


        else if(regex_match(line, matches, searchAnd)){ //match for AND search
          AndQuery query(matches[1], matches[2]);
          auto result = query.eval(tq);
            if(matches[4].matched && matches[5].matched){
                leftline=std::stoi(matches[4]);
                rightline=std::stoi(matches[5]);
              print(cout, result, leftline, rightline) << endl;
              continue;
            }
      		print(cout, result) << endl;
        }



        else if(regex_match(line, matches, searchOr)){  //match for OR search
          OrQuery query(matches[1], matches[2]);
          auto result = query.eval(tq);
            if(matches[4].matched && matches[5].matched){
                leftline=std::stoi(matches[4]);
                rightline=std::stoi(matches[5]);
              print(cout, result, leftline, rightline) << endl;
              continue;
            }
      		print(cout, result) << endl;
        }




        else if(regex_match(line, matches, searchAndN)){  //match for AndN search
          NQuery query(matches[1], matches[3], std::stoi(matches[2]));
          auto result = query.eval(tq);
            if(matches[5].matched && matches[6].matched){
                leftline=std::stoi(matches[5]);
                rightline=std::stoi(matches[6]);
              print(cout, result, leftline, rightline) << endl;
              continue;
            }
      		print(cout, result) << endl;
        }



        else{std::cout <<"Unrecognized search\n"<< '\n';} //no regex match

  	}
	return 0;
}
