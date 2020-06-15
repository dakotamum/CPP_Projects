// Dakota Mumford
// Bitonic Sort Project

#include <iostream>
#include <mpi.h>
#include <ctime>
#include <unistd.h>
#include <vector>
#include <cstdio>
#include <cmath>
#define MCW MPI_COMM_WORLD

using namespace std;

// get binary representation of some integer
string getBin(int someNum, int length){
    string binNum = "";
    int i = 0;
    while(someNum!=0 || i < length){
        if(someNum == 0)
            binNum.insert(binNum.begin(), ’0’);
        else{
            int remainder = someNum%2;
            someNum /= 2;
            if(remainder == 0)
                binNum.insert(binNum.begin(), ’0’);
            else
                binNum.insert(binNum.begin(), ’1’);
            1
        }
        i++;
    }
    return binNum;
}
// find a friend of a processor at a given mask
int findMyFriend(string myBinNumber, int mask){
    string maskBit = "";
    for(int i = 0; i < myBinNumber.size(); i++){
        if(i + 1 == mask)
            maskBit += ’1’;
        else
            maskBit += ’0’;
    }
    int myFriend = 0;
    int j = 0;
    for(int i = myBinNumber.size() - 1; i >= 0; i--){
        if(myBinNumber[i] != maskBit[i])
            myFriend += pow(2, j);
        j++;
    }
    return myFriend;
}
// find a friend function for after we have a bitonic list
int findMyFriendAfterBitonic(string myBinNumber, int mask)
{
    string maskBit = "";
    for(int i = 0; i < myBinNumber.size(); i++)
    {
        if(i == mask)
            maskBit += ’1’;
        else
            maskBit += ’0’;
    }
    int myFriend = 0;
    int j = 0;
    for(int i = myBinNumber.size() - 1; i >= 0; i--){
        if(myBinNumber[i] != maskBit[i])
            myFriend += pow(2, j);
        j++;
    }
    return myFriend;
}
// bitonic sort program
int main(int argc, char **argv){
    int pid, np;
    int myNumber, friendsNumber;
    vector<int> hector = {4, 3, 0, 7, 1, 6, 2, 5};
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MCW, &pid);
    MPI_Comm_size(MCW, &np);
    if(pid == 0){
        cout << "Unsorted list: ";
        2
            for(int i = 0; i < hector.size(); i++)
                cout << hector[i] << " ";
    }
    // get length of binaries to be used
    int bitLength = log2(np);
    // get string representation of my binary
    string myBin = getBin(pid, bitLength);
    myNumber = hector[pid];
    // first we need to make this thing bitonic
    int bitonicIterator = bitLength;
    bool iAmAscending;
    for (int i = 0; i < bitLength; i++){
        // am I ascending?
        int k = i;
        if(i == bitLength - 1)
            k = 1;
        if(myBin[myBin.size()-2-k] == ’0’){
            iAmAscending = true;
        }
        else{
            iAmAscending = false;
        }
        // I need a friend!
        int myFriend = findMyFriend(myBin, bitonicIterator);
        // keep track of mask for finding friends
        if(i == bitLength - 2)
            bitonicIterator = bitLength;
        else
            bitonicIterator--;
        // send your number to your friend!
        MPI_Send(&myNumber, 1, MPI_INT, myFriend, 1, MCW);
        // get your friend’s number!
        MPI_Recv(&friendsNumber, 1, MPI_INT, myFriend, 1, MCW, MPI_STATUS_IGNORE);
        // find out which number is bigger
        int smallNum = myNumber, bigNum = friendsNumber;
        if(friendsNumber < myNumber) smallNum = friendsNumber, bigNum = myNumber;
        // new int l to keep track of whether I’m ascending or descending
        int l = i;
        if(i == myBin.size()-1)
            l = 0; // resets at last iteration to complete bitonic list
        // decide which number I’m keeping
        if(iAmAscending)
        {
            if(myBin[myBin.size()-1-l] == ’0’)
                myNumber = smallNum;
            else
                myNumber = bigNum;
        }
        else
        {
            if(myBin[myBin.size()-1-l] == ’0’)
                myNumber = bigNum;
            else
                3
                    myNumber = smallNum;
        }
    }
    if(pid == 0){
        cout << "\n Bitonic list: ";
    }
    sleep(pid);
    cout << myNumber << " ";
    // now I have my bitonic list; now I need to sort it!
    for(int i = 0; i < bitLength; i++)
    {
        // set to false if descending order is desired
        iAmAscending = true;
        int myFriend = findMyFriendAfterBitonic(myBin, i);
        // exchange numbers with your friend
        MPI_Send(&myNumber, 1, MPI_INT, myFriend, 1, MCW);
        MPI_Recv(&friendsNumber, 1, MPI_INT, myFriend, 1, MCW, MPI_STATUS_IGNORE);
        // find out which number is bigger
        int smallNum = myNumber, bigNum = friendsNumber;
        if(friendsNumber < myNumber) smallNum = friendsNumber, bigNum = myNumber;
        // should I keep the number?
        if(iAmAscending){
            if(myBin[i] == ’0’)
                myNumber = smallNum;
            else
                myNumber = bigNum;
        }
        else{
            if(myBin[i] == ’0’)
                myNumber = bigNum;
            else
                myNumber = smallNum;
        }
    }
    if(pid == 0)
        cout << "\n Sorted List: ";
    sleep(pid);
    cout << myNumber << " ";
    MPI_Finalize();
    cout << endl;
    return 0;
}
