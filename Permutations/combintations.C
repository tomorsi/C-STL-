
#include <string>
#include <iostream>

class Combinations
{
private:
    std::string m_str;

    void permute(std::string s, int start, int end) 
    {
	if (start == end)
	    std::cout << s << std::endl;
	else
	{
	    for (int i = start ; i <= end; i++)
	    {

		// std::cout << "string=" << s << " swap{start="<< s[start] << "," << "i=" << s[i] << "}" << std::endl;
  
		// swap chars
		char t = s[start];
		s[start] = s[i];
		s[i] = t;
		
		permute(s, start+1, end);
		
		// unswap
		t = s[start];
		s[start] = s[i];
		s[i] = t;
	    }
	}	
    }

public:
    Combinations(std::string s) : m_str(s) { }

    void permute(void) {
	std::cout << "Combinations for: " << m_str << std::endl;
	permute(m_str, 0, m_str.length()-1);
    }

};

//
// Question How to modify this WITHOUT using a list to track found
// results to handle the case where there are duplicate characters. 
//
int main(void)
{
    // fails prints duplicates.
    Combinations c1("abb");
    c1.permute();

    // fails prints duplicates, ok when all characters are unique. 
    Combinations c2("abc");
    c2.permute();

}
