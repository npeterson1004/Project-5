#include <fstream>
using namespace std;

main()
{
	fstream test("delfile.dat",ios::app|ios::out|ios::in);
	test <<"abcdefg";
	test.seekp(0,ios::beg);
	test <<"xyz";
}
