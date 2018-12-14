#include "Query.h"
#include "TextQuery.h"
#include <memory>
#include <set>
#include <algorithm>
#include <iostream>
#include <cstddef>
#include <iterator>
#include <cmath>
using namespace std;

QueryResult
AndQuery::eval(const TextQuery& text) const
{
    auto left = left_query.eval(text), right = right_query.eval(text);
	// set to hold the intersection of left and right
    auto ret_lines = make_shared<set<line_no>>();
    // writes the intersection of two ranges to a destination iterator
    set_intersection(left.begin(), left.end(),
                   right.begin(), right.end(),
                   inserter(*ret_lines, ret_lines->begin()));
    return QueryResult(s1 + " {AND} " + s2, ret_lines, left.get_file());
}

QueryResult
OrQuery::eval(const TextQuery& text) const
{
    auto left = left_query.eval(text), right = right_query.eval(text);
	// copy the line numbers from the left-hand operand into the result set
	auto ret_lines =
	     make_shared<set<line_no>>(left.begin(), left.end());
	// insert lines from the right-hand operand
	ret_lines->insert(right.begin(), right.end());
	// return the new QueryResult representing the union of lhs and rhs
    return QueryResult(s1 + " {OR} " + s2, ret_lines, left.get_file());
}

QueryResult
NQuery::eval(const TextQuery& text) const
{
    QueryResult qr = AndQuery::eval(text);
    qr.sought=(s1 + " {"+ std::to_string(n) +"} " + s2);
    set<size_t> out_of_range;
    for (auto num : *qr.lines) // for every element in the set
    {
      std::istringstream iss(*(qr.file->begin() + num));
      std::istream_iterator<std::string> begin(iss), end;

      //putting all the tokens in the vector
      std::vector<std::string> sentence(begin, end);
      size_t distance = std::abs(find(sentence.begin(), sentence.end(), s1)
                            - find(sentence.begin(), sentence.end(), s2))-1;
      if(distance>n){
        out_of_range.insert(num);
      }
    }
    for(auto num : out_of_range) qr.lines.get()->erase(num);
    return qr;
}

ostream &print(ostream &os, const QueryResult &qr)
{
    // print each line in which the word appeared
	for (auto num : *qr.lines) // for every element in the set
        os << "(line " << num + 1 << ") "
		   << *(qr.file->begin() + num) << endl;
	// print the count and all occurrences
    os << "\"" << qr.sought << "\" occurs " << qr.lines->size() << " times" << endl;
	return os;
}

ostream &print(ostream &os, const QueryResult &qr, size_t from, size_t to)  //range print
{
  int counter=0;
    // print each line in which the word appeared
	for (auto num : *qr.lines) // for every element in the set
  {
    if((num+1)>from&&(num+1)<to){ //if the line is in range
        os << "(line " << num + 1 << ") "
		   << *(qr.file->begin() + num) << endl;
       ++counter;
     }
	// print the count and all occurrences
  }
    os << "\"" << qr.sought << "\" occurs " << counter << " times" << endl;
	return os;
}
