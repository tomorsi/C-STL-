

#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <iterator>
#include <algorithm>


//
// 
// Time Spentd 6 hours. 
//
// This is the input for the processing:
//
//  professionals list in vector of strings 
//  ["Jack", "Leon", "Maria"] - professionals list in a vector of strings.
//  
//  professsions listed in a vector of vector of strings, each v[n] corresponds
//  to the profesional at index n in the professionals vector of strings. 
//  [
//   ["Computer repair", "Handyman", "House cleaning"],
//   ["Computer lessons", "Computer repair", "Data recovery service"],
//   ["Computer lessons", "House cleaning"]
//  ]
//
//  results stored in vector of vector of vector of strings.
//  v[n][0] - contains a vector with a single string for professions, 1 to n professions. 
//  v[n][1] - contains a vector with multiple strings for professionals associated with their profession.
// 
//  [
//   [["Computer lessons"{0,0,0}], ["Leon"{0,1,0}, "Maria"{0,1,1}]],
//   [["Computer repair"{1,0,0},], ["Jack"{1,1,0}, "Leon"{1,1,1}]],
//   [["Data recovery service"], ["Leon"]],
//   [["Handyman"], ["Jack"]],
//   [["House cleaning"], ["Jack", "Maria"]]
//  ]


// The result 3d vector. 
typedef std::vector<std::vector<std::vector<std::string> > > ResultsTriVectorType;
// The preferences set that is a unique list of sorted preferences. 
typedef std::set<std::string> PrefsVectorType;


// Add in the list of preferences and empty pros vector to the results 3d vector
void addPrefsProsToResults(ResultsTriVectorType& resultsTriVector, const PrefsVectorType &prefsVector) 
{ 
    // clear preferences vector in results which is v[0][0-n] , vector.
    resultsTriVector.clear();

    std::vector<std::string> v1;
    std::vector<std::vector<std::string> > v2(2,v1);
    resultsTriVector = ResultsTriVectorType(prefsVector.size(),v2);

    int k = 0;
    for (PrefsVectorType::iterator i = prefsVector.begin();
	 i != prefsVector.end(); i++)
    {
	resultsTriVector[k][0].push_back(*i);
	k++;
    }
};

std::vector<std::vector<std::vector<std::string> > > 
categorize(std::vector<std::string> pros, 
		 std::vector<std::vector<std::string> > prefs)
{
    std::vector<std::vector<std::vector<std::string> > > results;
    std::set<std::string> prefsSet;
    std::vector<std::set<std::string> > proSetV;

    // collection unique preferences in set.
    std::vector<std::vector<std::string> >::iterator iterOuter;
    std::vector<std::string>::iterator prosIter = pros.begin();  
    for (iterOuter = prefs.begin(); iterOuter!=prefs.end(); iterOuter++)
    {
	std::vector<std::string> v = *iterOuter;
	prefsSet.insert(v.begin(),v.end());
    }

    addPrefsProsToResults(results,prefsSet);

    int j = 0;
    for (std::vector<std::string>::iterator i = pros.begin();
	 i != pros.end();
	 i++)
    {
	// get preferences for this pro.
	std::vector<std::string> prosPrefs  = prefs[j];

	// find preferences vector in results.
	for (std::vector<std::string>::iterator k = prosPrefs.begin();
	     k != prosPrefs.end(); k++)
	{ 
	    std::set<std::string>::iterator l =  prefsSet.find(*k);
	    int index = std::distance(prefsSet.begin(),l);

	    results[index][1].push_back(*i);
	}
	j++;
    } 

    return results;
}


void printResults(std::vector<std::vector<std::vector<std::string> > > r)
{
    typedef std::vector<std::string> vType;
    typedef std::vector<vType> vvType;
    typedef std::vector<vvType> vvvType;

    for (vvvType::iterator i = r.begin();
	 i != r.end(); i++)
    {
	vvType vvVector = *i;

	std::cout << "preference: " << vvVector[0][0] << " ";

        vType vVector = vvVector[1];
	std::cout << "profesionals: " ;
	for (vType::iterator k = vVector.begin();
	     k!=vVector.end(); k++)
	{
	    std::cout << "  " << *k; 		
	}
	std::cout << std::endl;
    }


}

std::vector<std::string> pros;
std::vector<std::vector<std::string> > prefs;


int main(void)
{
    pros.push_back("Jack");
    pros.push_back("Leon");
    pros.push_back("Maria");

    std::vector<std::string> jacksPrefs;
    jacksPrefs.push_back("Computer repair");
    jacksPrefs.push_back("Handyman");
    jacksPrefs.push_back("House Cleaning");

    prefs.push_back(jacksPrefs);

    std::vector<std::string> leonsPrefs;
    leonsPrefs.push_back("Computer lessons");
    leonsPrefs.push_back("Computer repair");
    leonsPrefs.push_back("Data recovery service");

    prefs.push_back(leonsPrefs);

    std::vector<std::string> mariasPrefs;
    mariasPrefs.push_back("Computer lessons");
    mariasPrefs.push_back("House Cleaning");

    prefs.push_back(mariasPrefs);

    // main prototype. 
    std::vector<std::vector<std::vector<std::string> > > results;
    results = categorize(pros,prefs);

    printResults(results);

    return 0;
}



