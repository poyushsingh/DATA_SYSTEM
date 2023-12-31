#include "global.h"

bool syntacticParse()
{
    logger.log("syntacticParse");
    string possibleQueryType = tokenizedQuery[0];
    if (tokenizedQuery.size() < 2)
    {
        cout << "SYNTAX ERROR" << endl;
        return false;
    }
    if (possibleQueryType == "CLEAR")
        return syntacticParseCLEAR();
    else if (possibleQueryType == "INDEX")
        return syntacticParseINDEX();
    else if (possibleQueryType == "LIST")
        return syntacticParseLIST();
    else if (possibleQueryType == "LOAD")
        return syntacticParseLOAD();
    else if (possibleQueryType == "PRINT")
    {
        if (tokenizedQuery.size() == 3 and tokenizedQuery[1] == "MATRIX")
            return syntacticParsePRINTMATRIX();
        return syntacticParsePRINT();
    }
    else if (possibleQueryType == "RENAME")
    {
        if (tokenizedQuery.size() == 4 and tokenizedQuery[1] == "MATRIX")
            return syntacticParseRENAMEMATRIX();
        return syntacticParseRENAME();
    }
    else if (possibleQueryType == "RENAME")
        return syntacticParseRENAME();
    else if (possibleQueryType == "EXPORT")
        return syntacticParseEXPORT();
    else if (possibleQueryType == "SOURCE")
        return syntacticParseSOURCE();
    else if (possibleQueryType == "TRANSPOSE")
        return syntacticParseTRANSPOSE();
    else if (possibleQueryType == "CHECKSYMMETRY")
        return syntacticParseCHECKSYMMETRY();
    else if (possibleQueryType == "COMPUTE")
        return syntacticParseCOMPUTE();
    else if(possibleQueryType == "SORT")
        return syntacticParseSORT();
    else
    {
        string resultantRelationName = possibleQueryType;
        if (tokenizedQuery[1] != "<-" || tokenizedQuery.size() < 3)
        {
            cout << "SYNTAX ERROR" << endl;
            return false;
        }
        possibleQueryType = tokenizedQuery[2];
        if (possibleQueryType == "PROJECT")
            return syntacticParsePROJECTION();
        else if (possibleQueryType == "SELECT")
            return syntacticParseSELECTION();
        else if (possibleQueryType == "JOIN")
            return syntacticParseJOIN();
        else if (possibleQueryType == "CROSS")
            return syntacticParseCROSS();
        else if (possibleQueryType == "DISTINCT")
            return syntacticParseDISTINCT();
        else if (possibleQueryType == "SORT")
            return syntacticParseSORT();
        else if(possibleQueryType == "ORDER" and tokenizedQuery[3] == "BY")
            return syntacticParseOrderBy();
        else if (tokenizedQuery[2] == "GROUP")
            return syntacticParseGROUP();
        else
        {
            cout << "SYNTAX ERROR" << endl;
            return false;
        }
    }
    return false;
}

ParsedQuery::ParsedQuery()
{
}

void ParsedQuery::clear()
{
    logger.log("ParseQuery::clear");
    this->queryType = UNDETERMINED;

    this->clearRelationName = "";

    this->crossResultRelationName = "";
    this->crossFirstRelationName = "";
    this->crossSecondRelationName = "";
    this->computeRelationName = "";

    this->distinctResultRelationName = "";
    this->distinctRelationName = "";

    this->exportRelationName = "";
    this->exportMatrixRelationName = "";

    this->indexingStrategy = NOTHING;
    this->indexColumnName = "";
    this->indexRelationName = "";

    this->joinBinaryOperator = NO_BINOP_CLAUSE;
    this->joinResultRelationName = "";
    this->joinFirstRelationName = "";
    this->joinSecondRelationName = "";
    this->joinFirstColumnName = "";
    this->joinSecondColumnName = "";

    this->loadRelationName = "";

    this->orderByResultRelationName = "";
    this->orderByRelationName = "";
    this->orderByAttr = "";
    this->orderByStrategy = "";

    this->printRelationName = "";
    this->printMatrixName = "";

    this->projectionResultRelationName = "";
    this->projectionColumnList.clear();
    this->projectionRelationName = "";

    this->renameFromColumnName = "";
    this->renameToColumnName = "";
    this->renameRelationName = "";
    this->renameMatrixFromName = "";
    this->renameMatrixToName = "";

    this->selectType = NO_SELECT_CLAUSE;
    this->selectionBinaryOperator = NO_BINOP_CLAUSE;
    this->selectionResultRelationName = "";
    this->selectionRelationName = "";
    this->selectionFirstColumnName = "";
    this->selectionSecondColumnName = "";
    this->selectionIntLiteral = 0;

    this->sortingStrategy = NO_SORT_CLAUSE;
    this->sortResultRelationName = "";
    this->sortColumnName = "";
    this->sortRelationName = "";
    this->sortAttributes.clear();
    this->sortAttributesStrategy.clear();

    this->sourceFileName = "";
    this->symmetryRelationName = "";
    this->transposeRelationName = "";

    this->groupByBinaryOperator = NO_BINOP_CLAUSE;
    this->groupByResultRelationName = "";
    this->groupByGroupAttributeName = "";
    this->groupByRelationName = "";
    this->groupByHavingAggregateFunctionName = "";
    this->groupByHavingAttributeName = "";
    this->groupByHavingConditionValue = "";
    this->groupByReturnaggregateFunctionName = "";
    this->groupByReturnAttributeName = "";
}

/**
 * @brief Checks to see if source file exists. Called when LOAD command is
 * invoked.
 *
 * @param tableName
 * @return true
 * @return false
 */
bool isFileExists(string tableName)
{
    string fileName = "../data/" + tableName + ".csv";
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer) == 0);
}

/**
 * @brief Checks to see if source file exists. Called when SOURCE command is
 * invoked.
 *
 * @param tableName
 * @return true
 * @return false
 */
bool isQueryFile(string fileName)
{
    fileName = "../data/" + fileName + ".ra";
    struct stat buffer;
    return (stat(fileName.c_str(), &buffer) == 0);
}
