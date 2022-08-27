#include <bits/stdc++.h>
#define checkBit(n,p) (bool)(n&(1<<p))
#include <bitset>
#include <iostream>
#include <sstream>
#include<conio.h>
using namespace std;





map<string,string> getMap(string path)
{
    string word,value;
    map<string,string> m;
    ifstream file(path);
    while(file>>word>>value)
    {
        m[word] = value;
    }
    file.close();
    return m;
}







string decToBin(int num,int length)
{
    string result = "";
    for(int i=0;i<length;i++)
    {
        if(checkBit(num,i))
        {
            result = "1" + result;
        }
        else
        {
            result = "0" + result;
        }
    }
    return result;
}

























int main()
{
    cout << "--------10 Bit Assembler---------\n" <<endl;
    int val;
    string ins,op,r1,r2,r3,cmnt;
    map<string,string> R_TYPE,I_TYPE,J_TYPE,RegisterValue;   //Obtaining static values from storage
    R_TYPE = getMap("File/R_TYPE.txt");
    I_TYPE = getMap("File/I_TYPE.txt");
    J_TYPE = getMap("File/J_TYPE.txt");
    RegisterValue = getMap("File/RegisterValue.txt");
    ifstream inputFile("File/input.txt");   //ifstream inputFile("File/.txt");
    ofstream outputFile("File/output.txt"); //ofstream outputFile("File/.txt");











    while(getline(inputFile,ins))
    {
        stringstream ss;
        cout << ins << endl;
        //Checking if instruction is empty or not
        if(ins.size()==0)
        {
            cout << "Invalid: Instruction is empty\n" << endl;
            continue;
        }
        ss << ins;
        ss >> op;
        ss >> r1;

        if(op!="go")
        {
            if(r1[0]!='$')
            {
                cout << "Invalid: '$' sign is missing before rd\n" << endl;
                outputFile << "Invalid: '$' sign is missing before rd\n" << endl;
                continue;
            }
            else if(r1[r1.size()-1]!=',')
            {
                cout << "Invalid: ',' is missing after rd\n" << endl;
                outputFile << "Invalid: ',' is missing after rd\n" << endl;
                continue;
            }
            r1.erase(r1.end()-1);
        }

        //If operation code is R Type then the program will go in here
        if(R_TYPE.find(op)!=R_TYPE.end())
        {
            val = 0;
            if(op=="go")
            {
                r2 = r3 = "$zero";
                goto print;
            }

            ss >> r2;
            if(r2[0]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs\n" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs\n" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=',')
                {
                    cout << "Invalid: ',' is missing after rs\n" << endl;
                    outputFile << "Invalid: ',' is missing after rs\n" << endl;
                    continue;
                }
                r2.erase(r2.end()-1);

            ss >> r3;
            if(r3[0]!='$')
            {
                cout << "Invalid: '$' sign is missing before rt\n" << endl;
                outputFile << "Invalid: '$' sign is missing before rt\n" << endl;
                continue;
            }

            //Checking instruction validities
            print:
            if(r1=="$zero")
            {
                cout << "Invalid: $zero can not be used\n" << endl;
                outputFile << "Invalid: $zero can not be used\n" << endl;
            }

            else if(RegisterValue.find(r1)==RegisterValue.end())
            {
                cout << "Invalid: rd not found\n" << endl;
                outputFile << "Invalid: rd not found\n" << endl;
            }
            else if(RegisterValue.find(r2)==RegisterValue.end())
            {
                cout << "Invalid: rs not found\n" << endl;
                outputFile << "Invalid: rs not found\n" << endl;
            }
            else if(RegisterValue.find(r3)==RegisterValue.end())
            {
                cout << "Invalid: rt not found\n" << endl;
                outputFile << "Invalid: rt not found\n" << endl;
            }
            else if(val<0)
            {
                cout << "Invalid: value can not be neg\n" << endl;
                outputFile << "Invalid: value can not be neg\n" << endl;
            }
            else if(val>15)
            {
                cout << "Invalid: value is too large\n" << endl;
                outputFile << "Invalid: value is too large\n" << endl;
            }
            else if(ss>>cmnt&&(cmnt[0]!='/'||cmnt[1]!='/'))
            {
            	cout << "Invalid: comment structure not maintained\n" << endl;
            	outputFile << "Invalid: comment structure not maintained\n" << endl;
            }

            //Printing machine code if instruction is valid
            else
            {
               cout << R_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2] << " " << RegisterValue[r3] << " "  << endl;
               //cout << GetHexFromBin(R_TYPE[op]) << " " << GetHexFromBin(RegisterValue[r1]) << " " << GetHexFromBin(RegisterValue[r2]) << " " << GetHexFromBin(RegisterValue[r3]) << " "  << "\n" << endl;
               outputFile << R_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2] << " " << RegisterValue[r3] << " "  << endl;
               //outputFile << GetHexFromBin(R_TYPE[op]) << " " << GetHexFromBin(RegisterValue[r1]) << " " << GetHexFromBin(RegisterValue[r2]) << " " << GetHexFromBin(RegisterValue[r3]) << " "  << "\n" << endl;
            }
        }

         //If operation code is I Type then the program will go in here
        else if(I_TYPE.find(op)!=I_TYPE.end())
        {
        	val = -1;
        	if(op=="lw"||op=="sw")
        	{
        		ss >> val >> r2;
        		if(r2[0]!='(')
                {
                    cout << "Invalid: '(' is missing before rs\n" << endl;
                    outputFile << "Invalid: '(' is missing before rs\n" << endl;
                    continue;
                }
                else if(r2[r2.size()-1]!=')')
                {
                    cout << "Invalid: ')' is missing after rs\n" << endl;
                    outputFile << "Invalid: ')' is missing after rs\n" << endl;
                    continue;
                }
                else if(r2[1]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs\n" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs\n" << endl;
                    continue;
                }
        		r2.erase(r2.begin());
        		r2.erase(r2.end()-1);

        		if(r1=="$zero")
                {
                    r1 = "";
                    cout << "Invalid: $zero can to be used\n" << endl;
                    outputFile << "Invalid: $zero can to be used\n" << endl;
                    continue;
                }
                else if(r2=="$zero")
                {
                    r2 = "";
                    cout << "Invalid: $zero can to be used\n" << endl;
                    outputFile << "Invalid: $zero can to be used\n" << endl;
                    continue;
                }
        	}

        	else
        	{

        		ss >> r2 >> val;
        		if(r2[0]!='$')
                {
                    cout << "Invalid: '$' sign is missing before rs\n" << endl;
                    outputFile << "Invalid: '$' sign is missing before rs\n" << endl;
                    continue;
                }

                else if(r2[r2.size()-1]!=',')
                {
                    cout << "Invalid: ',' is missing after rs\n" << endl;
                    outputFile << "Invalid: ',' is missing after rs\n" << endl;
                    continue;
                }

        		r2.erase(r2.end()-1);

        		if(op=="addi"||op=="andi"||op=="ori"||op=="xori")
        		{

        		    if(r1=="$zero")
                    {
                        r1 = "";
                        cout << "Invalid: $zero can to be used\n" << endl;
                        outputFile << "Invalid: $zero can to be used\n" << endl;
                        continue;
                    }
                 }
            }
        	//Checking instruction validities
            if(RegisterValue.find(r1)==RegisterValue.end())
            {
                cout << "Invalid: rd not found\n" << endl;
                outputFile << "Invalid: rd not found\n" << endl;
            }
            else if(RegisterValue.find(r2)==RegisterValue.end())
            {
                cout << "Invalid: rs not found\n" << endl;
                outputFile << "Invalid: rs not found\n" << endl;
            }

            else if(op!="addi"&&op!="andi"&&op!="ori"&&op!="xori"&&val<0)
            {
                cout << "Invalid: value can not be neg\n" << endl;
                outputFile << "Invalid: value can not be neg\n" << endl;
            }
            else if(val>7) //2^4 = 16 //4 is imm bit
            {
                cout << "Invalid: value is too large\n" << endl;
                outputFile << "Invalid: value is too large\n" << endl;
            }
            else if(val<-8) //2^4 = 16 //4 is imm bit
            {
                cout << "Invalid: value is too small\n" << endl;
                outputFile << "Invalid: value is too small\n" << endl;
            }
            else if(ss>>cmnt&&(cmnt[0]!='/'||cmnt[1]!='/'))
            {
            	cout << "Invalid: comment structure not maintained\n" << endl;
            	outputFile << "Invalid: comment structure not maintained\n" << endl;
            }

            //Printing machine code if instruction is valid
            else
            {
            	cout << I_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2]<< " " << decToBin(val,2) << endl;
            	//cout << GetHexFromBin(I_TYPE[op]) << " " << GetHexFromBin(RegisterValue[r1]) << " " << GetHexFromBin(RegisterValue[r2])<< " " << GetHexFromBin(decToBin(val,4)) << "\n" << endl;
                outputFile << I_TYPE[op] << " " << RegisterValue[r1] << " " << RegisterValue[r2]<< " " << decToBin(val,2) << endl;
                //outputFile << GetHexFromBin(I_TYPE[op]) << " " << GetHexFromBin(RegisterValue[r1]) << " " << GetHexFromBin(RegisterValue[r2])<< " " << GetHexFromBin(decToBin(val,4)) << "\n"  << endl;

            }
        }
        else
        {
        	cout << "Invalid: Op code not found\n" << endl;
        	outputFile << "Invalid: Op code not found\n" << endl;
        }
    }
    inputFile.close();
}
