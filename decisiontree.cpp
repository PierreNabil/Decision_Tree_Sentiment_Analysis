#include "decisiontree.h"

std::vector<QString> DecisionTree::ComparisonNames = {};
std::vector<bool> DecisionTree::ComparisonValues = {};
std::vector<std::array<int,4>> DecisionTree::ComparisonScores = {};



template <typename T>
T min(const T& a, const T& b)
{
    if(a<b)
        return a;
    return b;
}



DecisionTree::DecisionTree(): DecisionTree(nullptr, false){}

DecisionTree::DecisionTree(Node* Root, bool IsTemp = false): root(Root), isTemp(IsTemp) {}

DecisionTree::~DecisionTree()
{
    if(!isTemp)
        if(root != nullptr)
            delete root;
}



int DecisionTree::size() {return root->size();}

float DecisionTree::Error() {return root->Error();}

bool DecisionTree::Comparison(QString QStr)
{
    for(size_t i=0; i<ComparisonNames.size(); i++)
    {
        if(ComparisonNames[i] == QStr)
            return ComparisonValues[i];
    }
    return false;
}

void DecisionTree::incScores(bool isPositive)
{
    if(isPositive)
        root->incRightDataPoint();
    else
        root->incLeftDataPoint();
    for(size_t i=0; i<ComparisonNames.size(); i++)
    {
        if(ComparisonValues[i])
        {
            if(isPositive)
                ComparisonScores[i][3]++;
            else
                ComparisonScores[i][2]++;
        }
        else
        {
            if(isPositive)
                ComparisonScores[i][1]++;
            else
                ComparisonScores[i][0]++;
        }
    }
}

int DecisionTree::getMinError()
{
    float minError=Error(); //find first error value
    size_t minIdx;

    for(size_t i=0; i<ComparisonNames.size(); i++)
        if(root->isPrevCompType(ComparisonNames[i]) == false)
            if(getError(i) < minError)
            {
                minIdx = i;
                minError = getError(i);
            }

    if(minError == Error())
        return -1;
    else
        return (int)minIdx;
}

float DecisionTree::getError(int CompIdx)
{
    return ((float)(min(ComparisonScores[CompIdx][0],ComparisonScores[CompIdx][1]) + min(ComparisonScores[CompIdx][2],ComparisonScores[CompIdx][3])))
            /((float)(ComparisonScores[CompIdx][0]+ComparisonScores[CompIdx][1]+ComparisonScores[CompIdx][2]+ComparisonScores[CompIdx][3]));
}

bool DecisionTree::DataPointNotInThisBranch()
{
    for(size_t i=0; i<root->prevCompTypes.size(); i++)
        if(Comparison(root->prevCompTypes[i]) != root->compValue)
            return true;

    return false;
}



bool DecisionTree::getLine(std::ifstream& f, QString& Qs)
{
    std::string stdS;
    if(getline(f,stdS))
    {
        Qs = QString::fromStdString(stdS);
        return true;
    }
    return false;
}

bool DecisionTree::getData(QString DataStr)
{
    unsigned int ValuesCntr =0;
    //Get Input Data
    for(int i =0; i<DataStr.length(); i++)
    {
        if(DataStr[i] == ',')
            continue;
        if(DataStr[i] < '0' || DataStr[i] > '9')
            break;

        if(DataStr[i] == '0')
            ComparisonValues[ValuesCntr] = false;
        else
            ComparisonValues[ValuesCntr] = true;

        if(ComparisonValues.size() <= ++ValuesCntr)
            break;
    }

    //Get Result
    bool Answer;
    if(DataStr.right(8) == "Positive")
        Answer = true;
    else //if(DataStr.right(8) == "Negative")
        Answer = false;

    return Answer;
}

void DecisionTree::setCompNames(std::ifstream& f)
{
    ComparisonNames.clear();
    ComparisonValues.clear();
    ComparisonScores.clear();
    QString DataStr, temp;
    getLine(f, DataStr);
    int i;

    //Get Input Data
    for(i =0; i<DataStr.length(); i++)
    {
        if(DataStr[i] == ',')
        {
            ComparisonNames.push_back(temp);
            ComparisonValues.push_back(false);
            ComparisonScores.push_back({0,0,0,0});
            temp = "";
        }
        else
            temp += DataStr[i];
    }

    if(ComparisonNames[ComparisonNames.size()-1] == "reviews.text")
    {
        ComparisonNames.pop_back();
        ComparisonValues.pop_back();
        ComparisonScores.pop_back();
    }
}

void DecisionTree::clearScores()
{
    for(size_t i=0; i<ComparisonNames.size(); i++)
        ComparisonScores[i] = {0,0,0,0};
}


void DecisionTree::train(std::ifstream& File)
{
    if(root != nullptr)
        delete root;
    root = new Node();

    setCompNames(File);
    trainmore(File);
}
void DecisionTree::trainmore(std::ifstream& File)
{
    QString DataStr;
    bool Ans;
    bool isDone = true;

    File.clear();
    File.seekg(0, std::ios::beg);
    getLine(File, DataStr);
    clearScores();

    while(getLine(File, DataStr))
    {
        Ans = getData(DataStr);
        if(DataPointNotInThisBranch())
            continue;
        incScores(Ans);
        isDone = false;
    }

    if(isDone)
        return; //No More Data Points

//    if(root->Error() == 0)
//        return;

    int minErrorIdx = getMinError();
    if(minErrorIdx == -1)
        return; //Done Training
    else
    {
        root->compType = ComparisonNames[minErrorIdx];
        root->makeChildren();

        DecisionTree(root->getleftChild(),true).trainmore(File);
        DecisionTree(root->getrightChild(),true).trainmore(File);
    }
}

bool DecisionTree::traverse(QString iData)
{
    getData(iData);
    return traverse();
}
bool DecisionTree::traverse(std::vector<bool> iData)
{
    ComparisonValues = iData;
    return traverse();
}
bool DecisionTree::traverse()
{
    if(root->isLeaf())
        return root->ExpectedValue();
    else if(Comparison(root->compType))
        return DecisionTree(root->getrightChild(),true).traverse();
    else
        return DecisionTree(root->getleftChild(),true).traverse();
}


//----------------------------------------------------------------------------------------------------------------------------------------------------


DecisionTree::Node::Node(): Node(nullptr, {}, {}){}

DecisionTree::Node::Node(Node* Parent, std::vector<QString> PrevCompTypes, std::vector<bool> PrevCompValues)
    :parent(Parent),
     leftChild(nullptr), rightChild(nullptr),
     leftDataPoints(0), rightDataPoints(0),
     prevCompTypes(PrevCompTypes), prevCompValues(PrevCompValues){}

DecisionTree::Node::~Node()
{
    if(rightChild != nullptr)
    {
        delete leftChild;
        delete rightChild;
    }
}



bool DecisionTree::Node::isLeaf()
{
    if(leftChild == nullptr)
        return true;
    else
        return false;
}

DecisionTree::Node* DecisionTree::Node::getleftChild() {return leftChild;}

DecisionTree::Node* DecisionTree::Node::getrightChild(){return rightChild;}

DecisionTree::Node* DecisionTree::Node::getparent() {return parent;}

void DecisionTree::Node::incLeftDataPoint(){leftDataPoints += 1;}
void DecisionTree::Node::incRightDataPoint(){rightDataPoints += 1;}

int DecisionTree::Node::size() {return leftDataPoints+rightDataPoints;}

float DecisionTree::Node::Error()
{
    if(leftDataPoints == 0 || rightDataPoints == 0)
        return 0;
    if(isLeaf())
        return ((float)min(leftDataPoints, rightDataPoints))/((float)size());

    return ((float)(leftChild->Error()*leftChild->size() + rightChild->Error()*rightChild->size()))/((float)size());
}

bool DecisionTree::Node::ExpectedValue()
{
    if(leftDataPoints > rightDataPoints)
        return false;
    else
        return true;
}

bool DecisionTree::Node::isPrevCompType(QString CompName)
{
    for(size_t i=0; i<prevCompTypes.size(); i++)
        if(prevCompTypes[i] == CompName)
            return true;

    return false;
}



DecisionTree::Node* DecisionTree::Node::makeChild()
{
    std::vector<QString> newCompTypes = prevCompTypes;
    newCompTypes.push_back(compType);

    std::vector<bool> newCompValues = prevCompValues;
    newCompValues.push_back(compValue);

    return new Node(this, newCompTypes, newCompValues);
}

void DecisionTree::Node::makeChildren()
{
    leftChild = makeChild();
    leftChild->compValue = 0;

    rightChild = makeChild();
    rightChild->compValue = 1;
}
