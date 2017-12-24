#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;
class Huffman;

typedef struct symbol
{
	char character = '\0';
	int frequency = 0;
	symbol* leftSymbol = NULL;
	symbol* rightSymbol = NULL;

	symbol(char character, int frequency);
	symbol(symbol* sym1, symbol* sym2);
} symbol;

typedef struct code
{
public:
	char symbol;
	int codeLength;
	string codeWord;

	code(char symbol, string codeWord);
} code;

class Huffman {

public:
	static stringstream ReadFile(string filePath);
	static deque<symbol*>* FindCharacterFrequency(stringstream* fileContents);
	static void MinHeapify(deque<symbol*>* symbolArray);
	static symbol* GenerateHuffmanTree(deque<symbol*>* symbolArray);
	static void FindHuffmanCode(map<char, code*>* huffmanTable, symbol* huffmanTree, string codeWord);
	static void PrintHuffmanTranslation(map<char, code*>* huffmanCode, stringstream* fileContents);

	static void PrintHuffmanCode(map<char, code*>* huffmanCode);

//private:
	static bool CompareByFrequency(symbol* sym1, symbol* sym2);
	static void ResortMinHeap(deque<symbol*>* symbolArray);
	static void InsertMinHeap(deque<symbol*>* symbolArray, symbol* newSymbol);
	static void PrintMinHeap(deque<symbol*>* minHeap);

};