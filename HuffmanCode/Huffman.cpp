#include "Huffman.h"

code::code(char symbol, string codeword)
{
	this->symbol = symbol;
	this->codeWord = codeword;
	this->codeLength = codeword.length();
}

symbol::symbol(char character, int frequency)
{
	this->character = character;
	this->frequency = frequency;
	this->leftSymbol = NULL;
	this->rightSymbol = NULL;
}

symbol::symbol(symbol* sym1, symbol* sym2)
{
	this->character = '\0';
	this->frequency = sym1->frequency + sym2->frequency;
	if (Huffman::CompareByFrequency(sym1, sym2))
	{
		this->leftSymbol = sym1;
		this->rightSymbol = sym2;
	}
	else
	{
		this->leftSymbol = sym2;
		this->rightSymbol = sym1;
	}
}

stringstream Huffman::ReadFile(string filePath)
{
	ifstream inFile(filePath);
	
	if (!inFile)
	{
		cout << "Cannot open file for Huffman Coding." << endl;
		cout << "Exiting Program..." << endl;
		exit(1);
	}

	stringstream fileContents;
	fileContents << inFile.rdbuf();
	inFile.close();

	return fileContents;
}

deque<symbol*>* Huffman::FindCharacterFrequency(stringstream* fileContents)
{
	map<char, symbol*> symbolMap;

	while (!fileContents->eof())
	{
		char tempChar = fileContents->get();

		if ((int)tempChar == -1) // fix this end of line bug later
		{
			continue;
		}

		if (symbolMap.find(tempChar) != symbolMap.end())
		{
			map<char, symbol*>::iterator it = symbolMap.find(tempChar);
			symbolMap[tempChar]->frequency++;
		}
		else
		{
			symbol* newSymbol = (symbol*)malloc(sizeof(symbol));
			newSymbol->character = tempChar;
			newSymbol->frequency = 1;
			symbolMap.insert(pair<char, symbol*>(tempChar, newSymbol));
		}
	}
	
	deque<symbol*>* symbolArray = new deque<symbol*>();

	unsigned int i = 0;
	for (map<char,symbol*>::iterator iter = symbolMap.begin(); iter != symbolMap.end(); iter++)
	{
		symbol* symArrElm = new symbol(iter->second->character, iter->second->frequency);
		symbolArray->push_back(symArrElm);
		i++;
	}

	return symbolArray;
}

void Huffman::MinHeapify(deque<symbol*>* symbolArray)
{
	sort(symbolArray->begin(), symbolArray->end(), CompareByFrequency);
}

symbol* Huffman::GenerateHuffmanTree(deque<symbol*>* symbolArray)
{
	while (symbolArray->size() > 1)
	{
		symbol* symbol1 = symbolArray->front();
		Huffman::ResortMinHeap(symbolArray);
		symbol* symbol2 = symbolArray->front();
		Huffman::ResortMinHeap(symbolArray);
		
		symbol* minCumulativeSymbol = new symbol(symbol1, symbol2);
		Huffman::InsertMinHeap(symbolArray, minCumulativeSymbol);
	}	
	return symbolArray->front();
}

void Huffman::FindHuffmanCode(map<char, code*>* huffmanTable, symbol* huffmanTree, string codeWord)
{
	if (huffmanTree->leftSymbol != NULL)
	{
		Huffman::FindHuffmanCode(huffmanTable, huffmanTree->leftSymbol, codeWord + "0");
	}
	
	if (huffmanTree->rightSymbol != NULL)
	{
		Huffman::FindHuffmanCode(huffmanTable, huffmanTree->rightSymbol, codeWord + "1");
	}

	if (huffmanTree->leftSymbol == NULL && huffmanTree->rightSymbol == NULL)
	{
		code* newCode = new code(huffmanTree->character, codeWord);
		huffmanTable->insert(pair<char,code*>(huffmanTree->character, newCode));
	}


}

void Huffman::PrintHuffmanTranslation(map<char,code*>* huffmanCode, stringstream* fileContents)
{
	while (!fileContents->eof())
	{
		char nextLetter = fileContents->get();
		if (nextLetter == -1) { continue; }
		string codeWord = huffmanCode->find(nextLetter)->second->codeWord;
		cout << codeWord;
	}
	cout << endl;
}

void Huffman::PrintHuffmanCode(map<char, code*>* huffmanCode)
{
	for (map<char, code*>::iterator iter = huffmanCode->begin(); iter != huffmanCode->end(); iter++)
	{
		cout << iter->second->symbol << "\t" << iter->second->codeWord << "\t" << iter->second->codeLength << endl;
	}
}

bool Huffman::CompareByFrequency(symbol* sym1, symbol* sym2)
{
	return sym1->frequency < sym2->frequency;
}

void Huffman::ResortMinHeap(deque<symbol*>* symbolArray)
{
	if (symbolArray->size() < 2)
	{
		symbolArray->pop_back();
		return;
	}

	iter_swap(symbolArray->begin(), symbolArray->begin() + symbolArray->size()-1);
	symbolArray->pop_back();

	unsigned int index = 0;
	unsigned int compIndex = 1;

	while (true)
	{
		if (compIndex >= symbolArray->size()-1)
		{
			if (compIndex >= symbolArray->size())
			{
				break;
			}
			else {
				if (Huffman::CompareByFrequency(symbolArray->at(compIndex), symbolArray->at(index)))
				{
					iter_swap(symbolArray->begin() + index, symbolArray->begin() + compIndex);
				}
				break;
			}
		}

		if (Huffman::CompareByFrequency(symbolArray->at(compIndex+1), symbolArray->at(compIndex)))
		{
			compIndex = compIndex++;
		}

		if (Huffman::CompareByFrequency(symbolArray->at(compIndex), symbolArray->at(index)))
		{
			iter_swap(symbolArray->begin() + index, symbolArray->begin() + compIndex);
			index = compIndex;
			compIndex = index * 2 + 1;
		}
		else
		{
			break;
		}
	}

}

void Huffman::InsertMinHeap(deque<symbol*>* symbolArray, symbol* newSymbol)
{
	symbolArray->push_back(newSymbol);
	int index = symbolArray->size() - 1;
	int compIndex = (index-1) / 2;

	while (Huffman::CompareByFrequency(newSymbol, symbolArray->at(compIndex)) && index > 0)
	{
		iter_swap(symbolArray->begin()+index, symbolArray->begin()+compIndex);
		index = compIndex;
		compIndex = (index-1) / 2;
	}
}

void Huffman::PrintMinHeap(deque<symbol*>* minHeap)
{
	for (unsigned int i = 0; i < minHeap->size(); i++)
	{
		cout << minHeap->at(i)->character << " " << minHeap->at(i)->frequency << endl;
	}
}
