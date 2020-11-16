### Ryan Rosiak and Grant Dawson
COSC 420-001
11/15/20

# Project-2: arXiv Search Engine
In this project:
1. You will create a serach engine to search scientific articles stored on arXiv
2. This will consist of two components:
    (a) An index of test search terms, to know whcih documents are appropriate results to be returned
    (b) A ranking algorithm to determine which papers are the most "impoprtant", relative
    to the given serach term. This will use the PageRank and HITS algorithms
3. You will use two data files: arxiv-metadata.txt and arxiv-citations.txt
4. Your project will need two main "modules"
5. Actual usage will be done by a single program

## Project Description:
This project demonstrates the usage of the HITS and PageRank algorithm. These algorithms
use advanced linear algebra techniques in order to obtain useful numbers to perform
a hypertext based search. This project also demonstrates the usage of memory management
as there is a copious amount of data to move around, load, and unload. Lastly, file
management and preprocessing are pivotal features to this large project.

## Folders to pay attention to:

BST, CitationFile, MetadataFile, PageRank - These are the folders containing active modules

## How to Run:

See README's in each folder to run each module separately. Currently, a final build of
this project bringing all of the data together is not complete.

***Important Note*** - Each README file in each folder gives in depth explanations on
how each module works, the possible issues with the module, and test results.

## Questions:

#### (a) How long does it take to process the raw data into your index format?

#### (b) How long does it take to laod your database into memory?

#### (c) How long does it take to return results to a user?

#### (d) Where is there room for improvement?

#### Would your program make a decent "Google for research papers"?

