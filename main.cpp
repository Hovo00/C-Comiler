#include <iostream>
#include <exception>
#include <memory>
#include "Lexer.h"
#include "Parser.h"
#include "Token.h"
#include "Stream.h"
#include "Expressions.h"
#include "AssemblyCodeGenerator.h"
#include "BinaryCodeGenerator.h"
#include "Exception.h"

int main(int argc, const char* argv[])
{
        try
        {
                std::unique_ptr<CStream> pIOStream = std::make_unique<CStream>("input.txt");
                std::unique_ptr<CLexer> pLexer = std::make_unique<CLexer>(pIOStream->getInput());

                std::list<CToken*> lstToken = pLexer->tokenize();

                std::unique_ptr<CParser> pParser = std::make_unique<CParser>(lstToken);

                IStatement* pSyntaxTree = pParser->parse();

                //CAssemblyCodeGenerator* pAssemblyGenerator = new CAssemblyCodeGenerator();
                //pSyntaxTree->accept(pAssemblyGenerator);
                //pIOStream->setOutput(pAssemblyGenerator->getOutput());

                CBinaryCodeGenerator* pBinaryGenerator = new CBinaryCodeGenerator();
                pSyntaxTree->accept(pBinaryGenerator);
                pIOStream->setOutput(pBinaryGenerator->getOutput(), true);

                delete pBinaryGenerator;
                //delete pAssemblyGenerator;

                //for (CToken* pToken : lstToken)
                //      delete pToken;

                //delete pSyntaxTree;
        }
        catch (CException &oExcept)
        {
                std::cerr << oExcept.what() << std::endl;
	}
	catch (std::exception &oExcept)
	{
		std::cerr << oExcept.what() << std::endl;
	}

	std::cout << "Complete.\n";

	CGarbageCollector &pGarbageCollector = CGarbageCollector::getInstance();
	pGarbageCollector.clearMemory();

	int *p = new int(0);

	getchar();
	return 0;
}
