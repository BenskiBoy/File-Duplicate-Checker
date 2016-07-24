#include <iostream>
#include <fstream>
#include <cstring> // for std::strlen
#include <cstddef> // for std::size_t -> is a typedef on an unsinged int
#include <iomanip>
#include <sstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //for uint16_t
#include <unistd.h> //for getopt()

using namespace std ;

#ifdef DEBUG
#define DEBUG_STDERR(x) (std::cerr << x)
#define DEBUG_STDOUT(x) (std::cout << x)
#else 
#define DEBUG_STDERR(x)
#define DEBUG_STDOUT(x)
#endif

//Compare file A and file B

int main( int argc, char **argv )
{

  string fileAName= "";
  string fileBName = "";
  string reportFileName = "Duplicate-Checker-Output.txt";
  int c;
  bool generateReportFlag = false;

  //Upon the discovery that the files are not identical, by default the program shall end
  bool continueFlag = false;

  opterr = 0;
  
  while ((c = getopt (argc, argv, "cra:b:")) != -1){
    switch (c)
      {
      case 'r':
	generateReportFlag = true;
	break;
	
      case 'c':
	continueFlag = true;
	break;

      case 'a':
	fileAName= optarg;
	break;

      case 'b':
	fileBName = optarg;
	break;

      case '?':
	if (optopt == 'a' || optopt == 'b'){
	  cerr << "Option " << optopt << "requires an argument. " << endl;
	}
	else if (isprint (optopt)){
	  cerr << "Unknown option " << static_cast<char>(optopt) << endl;
	}

	else{
	  cerr << "Unknown option characer " << static_cast<char>(optopt) << "." << endl;
	}
	return 1;

	break;

      default:
	abort();
      }
  }

  	ifstream fileA;
	ifstream fileB;
	
	size_t fileASize = 0;
	size_t fileBSize = 0;

	cout << "Opening [A] file: " << fileAName << endl;
	fileA.open( fileAName .c_str(), ios::in|ios::binary);
	if(!fileA.is_open()){
	  cerr << "Error opening: " << fileAName << endl;
	  return 1;
	}
	
	cout << "Opening [B] file: " << fileBName << endl;
	fileB.open( fileBName .c_str(), ios::in|ios::binary);
	if(!fileB.is_open()){
	  cerr << "Error opening: " << fileBName << endl;
	  return 1;
	}

	unsigned char* fileAData = 0;
	unsigned char* fileBData = 0;
	
	fileA.seekg(0, ios::end); // set the pointer to the end
	fileB.seekg(0, ios::end);
	
	fileASize = fileA.tellg() ; // get the length of the file
	fileBSize = fileB.tellg();

	cout << "Size of file [A]: " << fileASize << " bytes" << endl;
	cout << "Size of file [B]: " << fileBSize << " bytes" << endl;
	cout << endl;

	if (fileASize != fileBSize){
	  cout << "file [A] and file [B] are not identical" << endl;
	  return 0;
	}
		
	fileA.seekg(0, ios::beg); // set the pointer to the beginning
	fileB.seekg(0, ios::beg);
	
	fileAData = new unsigned char[ fileASize + 1 ]; //  for the '\0'
	fileBData = new unsigned char[ fileASize + 1 ];
	
	fileA.read( (char*)fileAData, fileASize );
	fileB.read( (char*)fileBData, fileBSize );

	//fileAData[fileASize] = '\0' ; // set '\0'
	//fileBData[fileBSize] = '\0';

	if( generateReportFlag == true ) {
	  	ofstream reportFile;
		cout << "Opening output file name: " << reportFileName << endl;
		reportFile.open( reportFileName.c_str(), ios::out|ios::binary);
		if(!reportFile.is_open()){
	  		cerr << "Error opening: " << reportFileName << endl;
	  		return 1;
		}
	}

	bool filesIdentical = true;
	for( size_t i = 0; i < fileASize; i++ ){
		if( fileAData[i] != fileBData[i] ){
		  filesIdentical = false;
		  cout << "Files Not Identical at Location: 0x" << hex << i << endl;
		  cout << fileAName << " value: " << hex << fileAData[i] << endl;
		  cout << fileBName << " value: " << hex << fileBData[i] << endl;
		  cout << endl;
		  if ( continueFlag == false ){
		    if ( generateReportFlag == true ){
		      //reportFile.close();
		    }
		    return 0;
		  }
		}
	}

	
	if (filesIdentical == true){
	  cout << endl << "Finshed Successfully" << endl;
	}
	
	if( generateReportFlag == true ){
	  //reportFile.close();
	}
	
	return 0;
}
