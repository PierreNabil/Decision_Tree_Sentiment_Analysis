#ifndef DECISIONTREE_H
#define DECISIONTREE_H

#include <QString>
#include <string>
#include <array>
#include <vector>
#include <fstream>

class DecisionTree
{
    class Node;

    Node* root;
    bool isTemp;

    /**
     * similar to getline(ifstream, std::string) but for QString.
     * @param file
     * @param output QString
     * @return false if eof else true
     */
    static bool getLine(std::ifstream& f, QString& Qs);
    /**
     * Gets Data from a string to the ComparisonValues vector.
     * @param DataStr
     * @return result answer (Positive or Negative)
     */
    bool getData(QString DataStr);
    /**
     * Sets the ComparisonNames vector.
     * @param file to get input
     */
    void setCompNames(std::ifstream& f);
    /**
     * cleans ComparisonScores.
     */
    void clearScores();
    /**
     * Gets the Size of the Tree.
     * @return Size
     */
    int size();
    /**
     * Helper Function that traverses the Tree and returns the Expected Value.
     * @return Expected Value
     */
    bool traverse();

    /**
     * Comparison[Qstr].
     * @param Comparison Name
     * @return Comparison Value
     */
    bool Comparison(QString QStr);
    /**
     * increments Scores for all Comparisons.
     * @param is Review Positive
     */
    void incScores(bool isPositive);
    /**
     * returns the index of the best next comparison.
     * @return -1 if no comparison is best else CompIdx
     */
    int getMinError();
    /**
     * Calculates the Error for a particular comparison.
     * @param Comparison Index
     * @return Error Value
     */
    static float getError(int CompIdx);
    /**
     * Checks whether this data point is in another branch of the tree.
     * @return true if in another brach else false
     */
    bool DataPointNotInThisBranch();

    /**
     * Recursive Friendly Helper Function for train().
     * @param File
     */
    void trainmore(std::ifstream& File);

public:
    static std::vector<QString> ComparisonNames;
    static std::vector<bool> ComparisonValues;
    static std::vector<std::array<int,4>> ComparisonScores;

    const std::vector<QString>& getCompNames() {return ComparisonNames;}

    /**
     * Constructors and Destructors
     * Constructor Creates a New Tree with root = Root.
     * Destructor Deletes the Tree.
     * @param Root new root of the Tree
     */
    DecisionTree();
    DecisionTree(Node* Root, bool IsTemp);
    ~DecisionTree();

    /**
     * Calculates The Current Error of the Tree.
     * @return error as a number between 0 and 1
     */
    float Error();

    /**
     * Creates the Decision Tree by Training on the input file.
     * @param File
     */
    void train(std::ifstream& File);
    /**
     * Traverses the Tree and returns the Expected Value
     * @param iData input Data as String
     * @param iData input Data
     * @return Expected Value
     */
    bool traverse(QString iData);
    bool traverse(std::vector<bool> iData);
};

//----------------------------------------------------------------------------------------------------------------------------------------------------

class DecisionTree::Node
{
    Node* parent;
    Node* leftChild;
    Node* rightChild;

    int leftDataPoints;
    int rightDataPoints;

    /**
     * Helper Function for makeChildren()
     * @return Node pointer new created child
     */
    Node* makeChild();


public:
    QString compType;
    bool compValue;
    std::vector<QString> prevCompTypes;
    std::vector<bool> prevCompValues;

    /**
     * Constructors and Destructors
     * Constructor Creates a New Node with the specified Parent and old CompTypes.
     * Destructor Deletes the Node and it's Children.
     * @param Parent of the Node, nullptr if root
     * @param PrevCompTypes the Previous Comparison Types
     */
    Node();
    Node(Node* Parent, std::vector<QString> PrevCompTypes, std::vector<bool> PrevCompValues);
    ~Node();

    /**
     * Checks if the Node has Children.
     * @return true if no children else false.
     */
    bool isLeaf();
    /**
     * returns the pointer to the left or right child.
     * @return child pointer
     */
    Node* getleftChild();
    Node* getrightChild();
    /**
     * returns the pointer to the parent.
     * @return parent pointer
     */
    Node* getparent();
    /**
     * Used by Tree::train() to increment Data Points.
     */
    void incLeftDataPoint();
    void incRightDataPoint();
    /**
     * gets the Datapoints that belong to this Node.
     * @return leftDataPoints + rightDataPoints
     */
    int size();
    /**
     * Calculates the Error of the Tree starting from this Node.
     * @return error as a number between 0 and 1
     */
    float Error();
    /**
     * Chooses the Predicted Value of the Node
     * @return The Prediction
     */
    bool ExpectedValue();
    /**
     * Checks if the Given Comparison Name is in prevCompNames.
     * @param Comparison Name
     * @return true if CompName in prevCompName else false
     */
    bool isPrevCompType(QString CompName);

    /**
     * Creates 2 Children for the root.
     */
    void makeChildren();
};


#endif // DECISIONTREE_H
