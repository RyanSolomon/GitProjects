#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <iomanip>
using namespace std;
//This is the same exact code as my previous submission, I just wanted to submit a commented version 
//so everything is easier to understand.

//the getOutDegree function takes a string and gets the number
//of times it points to another url, returning the outdegree.
int getOutDegree(string name, vector<string> urls){

    int counter = 0;
    for(int i = 0; i < urls.size(); i++){
        if (urls[i] == name){
            counter++;
        }
       
    }
   
     return counter;
 
  
}

//the returnIndex method takes in a string and returns the 
//index (UNIQUE ID) that is associated with that url.
int returnIndex(string name, vector<string> urls){
    int counter = 0;
    for(int i = 0; i < urls.size(); i++) {
        if(urls[i] == name){
           
            return counter;
        }
        
        counter++;
    }

    return 0;
}


int main(){

    string line;

    vector<string> originalInput;
    
    vector<string> allUrls;


    while(getline(cin, line)){   
        string firstWord = line.substr(0, line.find(' '));     //takes in each line and separates it word by word.
        string secondWord = line.substr(line.find(' ')+1);
        
        allUrls.push_back(firstWord);
        allUrls.push_back(secondWord);

        if(find(originalInput.begin(), originalInput.end(), firstWord) != originalInput.end() )
        {
            //

        }
        
        else{
                       originalInput.push_back(firstWord);        

                   }
        
        //Both if-else statements (above and below) check to see if the first or second word from 
        //the line of input is already in the vector, leaving just unique URL names at the end.
        
        if (find(originalInput.begin(), originalInput.end(), secondWord) != originalInput.end()){
            //

        }
        else{
            originalInput.push_back(secondWord);

        }
        

    }

    vector<string> names;
    for(int i = 0; i < originalInput.size()-2; i++){
        names.push_back(originalInput[i+2]);            //this for loop removes both numbers from the originalInput
                                                        //vector, leaving just a vector with unique URLs.
    }
    sort(names.begin(), names.end());        //sorts the unique URLs.
    
    vector <string> cleanedUrls;
    for(int i = 0; i < allUrls.size()-2; i++){
        cleanedUrls.push_back(allUrls[i+2]);            //this for loop removes both numbers from the vector
                                                        //that contains all of the URLs that were inputted. 
    }
    vector<string> secondColumnUrls;
    for(int i = 1; i < cleanedUrls.size();){
        secondColumnUrls.push_back(cleanedUrls[i]);        
        i = i + 2;
    }
    //Both for loops (above and below) split the cleanedUrls vector into a first and second column.
    vector<string> firstColumnUrls;
    for(int i = 0; i < cleanedUrls.size();){
        firstColumnUrls.push_back(cleanedUrls[i]);
       i = i + 2;
    }

    int tableSize = names.size();
    
    double table[tableSize][tableSize];
    for(int i = 0; i < tableSize; i++){
        for(int j = 0; j < tableSize; j++){        //initializes a matrix that is (uniqueUrls x uniqueUrls)
            table[i][j] = 0;                        //and sets all values to 0;
        }
    }
    
   double table2[tableSize][1];
    for(int i = 0; i < tableSize; i++){
        table2[i][1] = (double)1/tableSize;        //initializes the matrix that we use for the first 
        }                                            //iteration of the matrix multiplication.

    vector<double> sentValues;    //this is the vector that contains the pageRank value of each URL.
 
    for(int i = 0; i < names.size(); i++){
        if(getOutDegree(names[i], firstColumnUrls) == 0){
            sentValues.push_back(0);                    
        }
        else{
        sentValues.push_back((double)1/getOutDegree(names[i], firstColumnUrls));        
        }    //inserts the pageRank value by sending each unique URL along with the firstColumn vector to return
                //the outdegree of that unique URL.
    }
    
    
    //this for loop gives the adjacency matrix a position ([][]) each iteration by finding the index(UNIQUE ID) 
    //of that name in each column by checking it against the sorted unique URL vector.
    //Once the position is found, the pageRank at the index in sentValues is found by getting the index of each URL 
    //and matching it to our sorted vector.
    for(int i = 0; i < firstColumnUrls.size(); i++){
      
        table[returnIndex(secondColumnUrls[i], names)][returnIndex(firstColumnUrls[i], names)] =             sentValues[returnIndex(firstColumnUrls[i], names)];        
     
    }
    
     double results[tableSize][1];
    
     int iterationCap = stoi(originalInput[1]);
    int iterations = 0;
    if(iterationCap == 1){
        for(int i = 0; i < tableSize; i++){
        results[i][1] = (double)1/tableSize;            
        }
    }
    else{
    while(iterations < iterationCap - 1){
        
       
    for(int i = 0; i < tableSize; i++){
         double sum = 0;
       for(int j = 0; j < tableSize; j++){                                                                   //the pageRanks with the table that originally will contain

           sum += table[i][j] * table2[j][1];            
               
       }
    
        if(sum < .001){
            results[i][1] = 0;                    
        }
        else{                    
        results[i][1] = sum;                        //puts the sum of each row into a new [i][1] matrix.
        }
    }
        
        iterations++;
        for(int i = 0; i < tableSize; i++){
            table2[i][1] = results[i][1];            //after ecah iteration, update the matrix that is being multiplied
        }                                            //by the original adjacency matrix.
                        
   
    }
    }
    
    for(int i = 0; i < tableSize; i++){
       
        if(results[i][1] < 0){
            cout << names[i] << " " << "0" << endl;
        }
        else{
        cout << names[i] << " " << fixed << setprecision(2) << results[i][1] << endl;        //prints the results using
        }                                                                                    //fixed and setprecision.
    }


    return 0;
}