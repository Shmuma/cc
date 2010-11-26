#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <string>
#include <iterator>
#include <algorithm>

#include <iostream>


using namespace std;


struct lengthSort
{
    bool operator() (const string& a, const string& b)
    {
        return a.size () > b.size ();
    };
};


/* sort lines from stdin according to their length and output to stdout */
int main (int argc, char *argv[])
{
    vector<string> data;

    copy (istream_iterator<string> (cin), istream_iterator<string> (), back_inserter (data));
    sort (data.begin (), data.end (), lengthSort ());
    copy (data.begin (), data.end (), ostream_iterator<string> (cout, "\n"));

    return 0;
}
