#include "Huffman.h"
#include <algorithm>

int main(int argc, char* argv[])
{
	string inputFile("test2.txt");
	stringstream fileContents(Huffman::ReadFile(inputFile));
	cout << "Input Text:" << endl;
	cout << fileContents.str() << endl;

	deque<symbol*> *charFrequencies = new deque<symbol*>();
	charFrequencies = Huffman::FindCharacterFrequency(&fileContents);

	cout << endl << "Character Frequencies:" << endl;
	Huffman::PrintMinHeap(charFrequencies);

	Huffman::MinHeapify(charFrequencies);

	cout << endl << "Post Heapify:" << endl;
	Huffman::PrintMinHeap(charFrequencies);

	symbol* huffmanTree;
	huffmanTree = Huffman::GenerateHuffmanTree(charFrequencies);

	map<char, code*>* huffmanCode = new map<char, code*>();
	Huffman::FindHuffmanCode(huffmanCode, huffmanTree, "");

	cout << endl << "Huffman Code:" << endl;
	Huffman::PrintHuffmanCode(huffmanCode);

	cout << endl << "Huffman Translation:" << endl;
	Huffman::PrintHuffmanTranslation(huffmanCode, new stringstream(fileContents.str()));

}