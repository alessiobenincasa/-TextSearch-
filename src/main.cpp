#include "Indexer.h"
#include "SearchEngine.h"
#include "UserInterface.h"

int main() {
    Indexer indexer;
    indexer.indexDocument("data/documents/doc1.txt");

    SearchEngine searchEngine(indexer.getIndex());
    UserInterface ui(searchEngine);

    ui.run();

    return 0;
}
