#include<iostream>
#include<string>
#include<fstream>
#include<algorithm>
#include<iomanip> 

using namespace std;

typedef struct node
{
	struct node* pRt, * pLf;
	string sWord, sMeaning;
}NODE;



class cDictionary
{
public:
	NODE* fCreate();
	void fAdd(NODE*);
	void fDelete(NODE*, string);
	void fUpdate(NODE*);
	void fDisplayIna(NODE*);
	void fDisplayPre(NODE*);
	void fDisplayPos(NODE*);
	void fSearch(NODE*);

};

NODE* cDictionary::fCreate()
{
	NODE* pRoot, * pNn, * pCn, * pParent = NULL;
	char cCh;
	pRoot = NULL;
	do
	{
		pNn = new NODE;
		pNn->pLf = pNn->pRt = NULL;
		cout << "Enter word: ";
		cin >> pNn->sWord;
		cout << " Enter meaning: ";
		cin >> pNn->sMeaning;

		if (pRoot == NULL)
			pRoot = pNn;
		else
		{
			pCn = pRoot; 
			while (pCn)
			{
				
				if (pCn->sWord < pNn->sWord)
					pCn = pCn->pRt;
				else
					pCn = pCn->pLf;

				pParent = pCn;
			}
			if (pParent->sWord < pNn->sWord)
				pParent->pRt = pNn;
			else
				pParent->pLf = pNn;

		}
		cout << "Do you want to continue(y/n) : ";
		cin >> cCh;

	} while (cCh == 'y' || cCh == 'Y');
	return pRoot;
}

void cDictionary::fAdd(NODE* pRoot)
{
	NODE* pCn, * pNn, * pParent = NULL;
	pNn = new NODE;
	pNn->pLf = pNn->pRt = NULL;
	cout << "Enter word: ";
	cin >> pNn->sWord;
	cout << "Enter Meaning: ";
	cin >> pNn->sMeaning;
	pCn = pRoot;
	while (pCn)
	{
		pParent = pCn;
		if (pCn->sWord < pNn->sWord)
			pCn = pCn->pRt;
		else
			pCn = pCn->pLf;
	}
	if (pParent->sWord < pNn->sWord)
		pParent->pRt = pNn;
	else
		pParent->pLf = pNn;
	cout << "Word is added Succesfully to the Dictionary \n";


}


void cDictionary::fDelete(NODE* root, string sData)
{
	NODE* pParent = NULL;
	NODE* pPtr = root;
	while (pPtr)
	{
		if (pPtr->sWord == sData)
			break;
		pParent = pPtr;
		if (pPtr->sWord < sData)
			pPtr = pPtr->pRt;
		else
			pPtr = pPtr->pLf;

	}
	//case 1 leaf node
	if (pPtr->pLf == NULL && pPtr->pRt == NULL)
	{
		if (pPtr == root)
			root = NULL;
		else
		{
			if (pParent->pRt == pPtr)
				pParent->pRt = NULL;
			else
				pParent->pLf = NULL;

		}
		delete(pPtr);
		cout << "Word is deleted Succesfully to the Dictionary! \n";

	}

	//case 2 only 1 child
	else if (pPtr->pLf == NULL && pPtr->pRt != NULL)
	{
		if (pPtr == root)
			root = pPtr->pRt;

		else {
			if (pParent->pRt == pPtr)
				pParent->pRt = pPtr->pRt;
			else
				pParent->pLf = pPtr->pRt;
		}
		delete(pPtr);
		cout << "Word is deleted Succesfully to the Dictionary! \n";

	}
	else if (pPtr->pRt == NULL && pPtr->pLf != NULL)
	{
		if (pPtr == root)
			root = pPtr->pLf;
		else {
			if (pParent->pLf == pPtr)
				pParent->pLf = pPtr->pRt;
			else
				pParent->pRt = pPtr->pLf;
		}
		delete(pPtr);
		cout << "Word is deleted Succesfully to the Dictionary! \n";

	}



	//case 3 two childs
	else
	{
		pParent = pPtr;
		NODE* pTemp;
		pTemp = pPtr->pRt;
		while (pTemp->pLf)
		{
			pParent = pTemp;
			pTemp = pTemp->pLf;
		}
		pPtr->sWord = pTemp->sWord;
		pPtr->sMeaning = pTemp->sMeaning;
		if (pParent == pPtr)
			pPtr->pRt = pTemp->pRt;
		else
			pParent->pLf = NULL;
		delete(pTemp);
		cout << "Word is deleted Succesfully to the Dictionary! \n";

	}

}




void cDictionary::fUpdate(NODE* pRoot)
{
	NODE* pCn;
	string sW;
	cout << "Enter word to Update : ";
	cin >> sW;
	pCn = pRoot;
	while (pCn)
	{
		if (pCn->sWord == sW)
		{
			cout << "Enter New Meaning : ";
			cin >> pCn->sMeaning;
			cout << "Meaning Updated succesfully \n";
			return;

		}
		else
		{
			if (pCn->sWord < sW)
				pCn = pCn->pRt;
			else
				pCn = pCn->pLf;
		}

	}
	cout << "Word not found!\n";
}


void cDictionary::fSearch(NODE* pRoot)
{
	NODE* pCn;
	string sW;
	cout << "Enter word to Search : ";
	cin >> sW;
	pCn = pRoot;
	while (pCn)
	{
		if (pCn->sWord == sW)
		{
			cout << "THe Meaning is : ";
			
			cout << pCn->sMeaning;
			return;

		}
		else
		{
			if (pCn->sWord < sW)
				pCn = pCn->pRt;
			else
				pCn = pCn->pLf;
		}

	}
	cout << "Word not found!\n";
}


void cDictionary::fDisplayIna(NODE* pPtr)
{
	if (pPtr)
	{
		fDisplayIna(pPtr->pLf);
		cout << pPtr->sWord << " : " << pPtr->sMeaning << "\n";
		fDisplayIna(pPtr->pRt);

	}

}

void cDictionary::fDisplayPre(NODE* pPtr)
{
	if (pPtr != NULL)
	{
		cout << pPtr->sWord << " : " << pPtr->sMeaning << "\n";
		fDisplayPre(pPtr->pLf);
		fDisplayPos(pPtr->pRt);
	}
}

void cDictionary::fDisplayPos(NODE* pPtr)
{
	if (pPtr != NULL)
	{
		fDisplayPos(pPtr->pLf);
		fDisplayPos(pPtr->pRt);
		cout << pPtr->sWord << " : " << pPtr->sMeaning << "\n";
	}
}








int main()
{
	NODE* pRoot = NULL;
	string sW;
	cDictionary oObj;
	char cCh;
	int iCh;
	string w;

	do
	{
		cout << "\n";
		cout << " Dictionary " << endl;
		cout << " ------------------------------------------- " << endl;
		cout << "\n";
		cout << " [1] Create dictionary\n";
		cout << " [2] Add new Word to the Dictionary\n";
		cout << " [3] Update Meaning of a Word\n";
		cout << " [4] Delete a word from Dictionary\n";
		cout << " [5] Display Dictionary Inorder\n";
		cout << " [6] Display Dictionary Preorder\n";
		cout << " [7] Display Dictionary Postorder\n";
		cout << " [8] Search \n";

		cout << "\n\n Enter your Choice : ";
		cin >> iCh;
		switch (iCh)
		{
		case 1:
			cout << "\n To add the word or meaning please don't type space between words but you can type '-' between words \n\n ";
			pRoot = oObj.fCreate();
			break;

		case 2:
			cout << "\n To add the word or meaning please don't type space between words but you can type '-' between words \n\n ";
			oObj.fAdd(pRoot);
			break;

		case 3:
			oObj.fUpdate(pRoot);
			break;

		case 4:
			cout << "Enter word to delete : ";
			cin >> sW;
			oObj.fDelete(pRoot, sW);
			break;
		case 5:
			oObj.fDisplayIna(pRoot);
			break;

		case 6:
			oObj.fDisplayPre(pRoot);
			break;
		case 7:
			oObj.fDisplayPos(pRoot);
			break;
		case 8:
			oObj.fSearch(pRoot);
			break;

           }
			cout << "\nPress 1 for Main Form and 2 to Exit : ";
			cin >> cCh;
		
	     
	     } while (cCh == '1');

		return 0;
	}
