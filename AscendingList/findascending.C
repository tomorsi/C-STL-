
#include <vector>
#include <iostream>


//
// Locate the largest sequence of numbers in a list using the STL. 
//


int rawData[] =
{
    20,45,4,5,6,1,3,5,8,10,12,15,16,4,5,6,7,8,9,10,4,5,5,3,2
};



class FindAscending {
    
    std::vector<int> m_ascending;
    std::vector<int> m_next_ascending;
    int *m_rawdata;
    int m_items;
    
public:
    FindAscending(int *rawData, int items)
	: m_rawdata(new int[items]),m_items(items)
    {
	std::cout << "array item count: " << m_items << std::endl;
	memcpy(m_rawdata,rawData,m_items*sizeof(int));
    }

    void parseList()
    {
	
	for (int i = 0; i < m_items-1; i++)
	{
	    if (m_rawdata[i] == (m_rawdata[i+1]-1))
	    {
		std::cout << "ascending match: " << m_rawdata[i] << "," <<  m_rawdata[i+1] << std::endl;

		// are we in a ascending list?
		if (m_next_ascending.size())
		{
		    m_next_ascending.push_back(m_rawdata[i+1]);
		}
		else
		{
		    m_next_ascending.push_back(m_rawdata[i]);
		    m_next_ascending.push_back(m_rawdata[i+1]);
		}
	    }
	    else
	    {
		if (m_next_ascending.size() > m_ascending.size())
		{
		    std::cout << "assigning next" << std::endl;
		    m_ascending = m_next_ascending;
		}
		m_next_ascending.clear();

	    }
	}


    }
	
    void printSolution()
    {
	std::cout << "list: " ;
	for (std::vector<int>::iterator i = m_ascending.begin(); i!=m_ascending.end(); i++)
	{
	    std::cout << *i << " ";
	}
	std::cout << std::endl;

    }
};


int main(void)
{
    FindAscending f(rawData,sizeof(rawData)/sizeof(rawData[0]));
    f.parseList();
    f.printSolution();
    return 0;
}
