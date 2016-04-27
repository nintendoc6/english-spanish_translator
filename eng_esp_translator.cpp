/// Jared Lamb
/**
    The purpose of this program is to receive English text
    input and accurately translate it into the Spanish language.
    Additional functionality or other languages may or may
    not be added later.

    With this program I hope to improve on not-so-accurate translators
    such as Google Translate, and other incomplete translators.
*/

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// Function prototypes
void checkVerb(string, int[]);
string checkSubject(string, int[]);
string checkTense(string, int);
string conjugate(string, string, int, string);
void conjDriver();
void conjCondense(string, string, string, string);
string presConj(int, string, int, int);
string futureConj(int, int);
string imperfConj(int, int, string);
string pretConj(int, int, string, int);
string subPresConj();
string subImperfConj();
string subFutureConj();
string conditConj();
string commConj();
string perfConj();
string pickApart(string);
string modVerb(string, int[]);
string modVerbSearch(string, int, int, string, int[]);

// Structures
struct espTenseMod
{
    string presPerf;
    string futurePerf;
    string pastPerf;
};

struct engBe
{
    string infin;
    string pres1;
    string pres246;
    string pres3;
    string past1And3;
    string past246;
    string part;
    string prog;
};

struct engVerb
{
    string infinAndPres124;
    string pres3;
    string past;
    string part;
    string prog;
};

struct espVerb
{
    string infin;           // Infinitive form
    string presType;        // Types of present tense conjugation
    bool futureReg;         // Regular future tense conjugation
    bool imperfReg;         // Regular imperfect preterite tense conjugation
    string pretType;        // Type of simple preterite tense conjugation
    int stemBack;           // Variable used for strong stem preterites
    bool conditReg;         // Regular conditional tense conjugation
    bool tuPosComReg;       // Regular positive tú command conjugation
    bool perfReg;           // Regular perfect tense conjugation
};

// Verb arrays
engVerb engVerbs[][2] = {
                           {
                               {
                                   "have#b", "has#b", "had#b", "had#b", "having#b"
                               }
                           },
                           {
                               {
                                   "do#b", "does#b", "did#b", "done", "doing"
                               },
                               {
                                   "make#b", "makes#b", "made#b", "made#b", "making#b"
                               }
                           },
                           {
                               {
                                   "can", "can", "could", 
                               }
                           },
                           {
                               {
                                   "say#b", "says#b", "said#b", "said#b", "saying#b"
                               },
                               {
                                   "tell#b", "tells#b", "told#b", "told#b", "telling#b"
                               }
                           }
                       };

espVerb espVerbs[] = {
                         {
                             "ser", "f", true, false, "e", 0, true, false, true,
                         },
                         {
                             "estar", "f", true, false, "da", 2, true, true, true,
                         },
                         {
                             "tener", "bb", false, true, "da", 4, false, false, true,
                         },
                         {
                             "hacer", "cb", false, true, "dd", 4, false, false, false
                         },
                         {
                             "poder", "ba", false, true, "de", 4, false, true, true
                         },
                         {
                             "decir", "bc", false, true, "dc", 4, false, false, false
                         },
                         {
                             "ir", "f", true, false, "e", true, false, true
                         },
                         {
                             "ver", "cc", true, true, "e", true, true, false
                         },
                         {
                             "dar", "cc", true, true, "e", true, true, true
                         },
                         {
                             "saber", "cc", false, true, "dh", 4, false, true, true
                         },
                         {
                             "querer", "bb", false, true, "dg", 4, false, true, true
                         },
                         {
                             "llegar", "a", true, true, "bb", 0
                         },
                         {
                             "pasar", "a", true, true, "a", 0
                         },
                         {
                             "deber", "a", true, true, "a", 0
                         },
                         {
                             "poner", "cb", false, true, "df", 4,
                         },
                         {
                             "parecer", "ca", true, true, "a", 0,
                         },
                         {
                             "quedar", "a", true, true, "a", 0,
                         },
                         {
                             "creer", "a", true, true, "e", 0,
                         },
                         {
                             "hablar", "a", true, true, "a", 0,
                         },
                         {
                             "llevar", "a", true, true, "a", 0,
                         },
                         {
                             "dejar", "a", true, true, "a", 0,
                         },
                         {
                             "seguir", "gb", true, true, "cc", 0,
                         },
                         {
                             "encontrar", "ba", true, true, "a", 0,
                         },
                         {
                             "llamar", "a", true, true, "a", 0,
                         },
                         {
                             "venir", "bb", false, true, "di", 4,
                         },
                         {
                             "pensar", "bb", true, true, "a", 0,
                         },
                         {
                             "salir", "cb", false, true, "a", 0,
                         },
                         {
                             "volver", "ba", true, true, "a", 0,
                         }
                     };
                     
// Arrays
espTenseMod espTenseMods = {"he", "habré", "había"};

int main()
{
    // Variables
    string engInput;        // English user input
    string engSentence;     // Current sentence being translated
    int verb;               // Index of identified verb in engVerb array
    string tense;           // Tense of identified verb in engVerb array
    string subject;         // Subject of English sentence
    string translated;      // Translated English sentence into Spanish
    
    /* Test verb context identification (modVerb driver)
    int verbIndex[] = {-1, -1};
    string modded;
    string input;
    getline(cin, input);
    cout << modVerb(input, verbIndex);
    */
    
    /* Check verb identification (checkVerb driver)
    int verbIndex[] = {-1, -1};
    string input;
    cout << "Enter an English verb or English verb phrase: ";
    getline(cin, input);
    checkVerb(input, verbIndex);
    cout << "Index 1: " << verbIndex[0] << endl;
    cout << "Index 2: " << verbIndex[1] << endl;
    */
    
    /* Test subject identification (checkSubject driver)
    string engSubject;
    engSubject = checkSubject(input, verbIndex);
    cout << "Subject: " << engSubject << endl << endl;
    */
    
    /* Test conjugations (conjDriver driver)
    conjDriver();

    return 0;
}

//*****************************************************************************
// The checkVerb function analyzes an English sentence or phrase
// and determines the verb.
// The function receives as input an English sentence or phrase as a string and
// verb indexes as an int array.
// The function returns nothing.
//*****************************************************************************
void checkVerb (string engInput, int verb[])
{
    // Variables
    int index = -1;     // Index of English verb form found in input
    int letters = 0;    // Length of English verb form found in input
    int indexes;        // Last index value of English phrase
    
    // Get last index value of English phrase
    indexes = engInput.length() - 1;
    
    // Reset English verb indexes
    verb[0] = verb[1] = -1;

    // Traverse engVerbs array, looking for instance of each verb in any form
    for (int v = 0; v < 28; v++)
    {
        for (int i = 0; i < 2; i++)
        {
            index = engInput.find(engVerbs[v][i].infinAndPres124, 0);
            if (index != -1 && engVerbs[v][i].infinAndPres124.length() != 0)
            {
                letters = engVerbs[v][i].infinAndPres124.length();
                if ((engInput[index + letters] == ' '
                || index + letters - 1 == indexes)
                && (engInput[index - 1] == ' '
                || index == 0))
                {
                    verb[0] = v;
                    verb[1] = i;
                    break;
                }
            }
            index = engInput.find(engVerbs[v][i].pres3, 0);
            if (index != -1 && engVerbs[v][i].pres3.length() != 0)
            {
                letters = engVerbs[v][i].pres3.length();
                if ((engInput[index + letters] == ' '
                || index + letters - 1 == indexes)
                && (engInput[index - 1] == ' '
                || index == 0))
                {
                    verb[0] = v;
                    verb[1] = i;
                    break;
                }
            }
            index = engInput.find(engVerbs[v][i].past, 0);
            if (index != -1 && engVerbs[v][i].past.length() != 0)
            {
                letters = engVerbs[v][i].past.length();
                if ((engInput[index + letters] == ' '
                || index + letters - 1 == indexes)
                && (engInput[index - 1] == ' '
                || index == 0))
                {
                    verb[0] = v;
                    verb[1] = i;
                    break;
                }
            }
            index = engInput.find(engVerbs[v][i].part, 0);
            if (index != -1 && engVerbs[v][i].part.length() != 0)
            {
                letters = engVerbs[v][i].part.length();
                if ((engInput[index + letters] == ' '
                || index + letters - 1 == indexes)
                && (engInput[index - 1] == ' '
                || index == 0))
                {
                    verb[0] = v;
                    verb[1] = i;
                    break;
                }
            }
            index = engInput.find(engVerbs[v][i].prog, 0);
            if (index != -1 && engVerbs[v][i].prog.length() != 0)
            {
                letters = engVerbs[v][i].prog.length();
                if ((engInput[index + letters] == ' '
                || index + letters - 1 == indexes)
                && (engInput[index - 1] == ' '
                || index == 0))
                {
                    verb[0] = v;
                    verb[1] = i;
                    break;
                }
            }
        }
        if (verb[0] != -1)
            break;
    }
}

//*****************************************************************************
// The checkSubject function analyzes an English sentence or phrase and
// determines the subject.
// The function receives as input an English sentence or phrase as a string and
// the index of a verb in the English verb array as an int array.
// The function returns the subject as a string.
//*****************************************************************************
string checkSubject(string engInput, int verb[])
{
    int index;              // Index of verb in English sentence
    int v;                  // Outer index of verb in English verb array
    int i;                  // Inner index of verb in English verb array
    string firstWord = "";  // First word of the English sentence (if verb is not first)
    string prevWord = "";   // Word previous to verb
    string subject;         // Subject of the English verb
    int firstIndex = 0;     // Number used in determining the first word
    int prevIndex = 0;      // Number used in determining the previous word


    // Find index of verb in sentence
    v = verb[0];
    i = verb[1];
    index = engInput.find(engVerbs[v][i].infinAndPres124);
    if (index == -1)
    {
        index = engInput.find(engVerbs[v][i].pres3);
        if (index == -1)
        {
            index = engInput.find(engVerbs[v][i].past);
            if (index == -1)
                {
                    index = engInput.find(engVerbs[v][i].part);
                    if (index == -1)
                        index = engInput.find(engVerbs[v][i].prog);
                }
        }
    }

    // Determine the word previous to the verb
    if (index != 0)
    {
        for (int j = index - 2; j >= 0; j--)
        {
            if (j != 0)
            {
                if (engInput[j] == ' ')
                {
                    for (int z = j + 1; z <= index - 2; z++)
                    {
                        prevWord.insert(prevIndex, 1, engInput[z]);
                        prevIndex++;
                    }
                    subject = prevWord;
                    prevIndex = 0;
                    break;
                }
            }
            else if (j == 0)
            {
                do
                {
                    if (engInput[firstIndex] == ' ')
                        break;
                    firstWord.insert(firstIndex, 1, engInput[firstIndex]);
                    firstIndex++;
                } while (true);
                subject = firstWord;
            }
        }
    }

    return subject;
}

//******************************************************************************
// The checkTense function analyzes an English sentence or phrase and determines
// its tense.
// The function receives as input an English sentence or phrase as a string and
// the index of a verb in the Spanish verbs array as an int.
// The function returns the tense of the verb as an string.
//******************************************************************************
string checkTense(string engInput, int verb)
{
    
}

//******************************************************************************
// The conjugate function conjugates a Spanish verb based on the tense and
// subject used in an English sentence of phrase.
// The function receives as input an English sentence or phrase as a string, the
// person as an int, the index of the verb in the Spanish verb array as an int,
// and the verb tense as an int.
// The function returns the conjugated verb as a string.
//******************************************************************************
string conjugate(string engInput, int person, int verb, int tense)
{
    // Variables
    string infin;           // Infinitive form of verb to be conjugated
    string end = "";        // Infinitive verb ending ("ar", "er", "ir")
    string conjugated;      // Conjugated verb phrase
    int stemIndex;          // Variable used in conjugating stem-changers
    int endIndex;           // Index of last two letters of infinitive form
    int endCount = 0;       // Variable used in finding endIndex


    // Get verb and details
    infin = espVerbs[verb].infin;

    for (int j = infin.length() - 1; j >= (infin.length() - 2); j--)
    {
        end.insert(endIndex++, 1, infin[j]);
    }

    // Conjugate
    if (tense == 1)
        conjugated = presConj(verb, end, endIndex, person);

    return conjugated;
}

// ****************************************************************************
// The conjDriver function tests the functionality of the conjugation functions
// for each of the tenses.
// The function receives nothing.
// The returns nothing.
//*****************************************************************************
void conjDriver()
{
    // Variables
    int endIndex;
    int person = 1;
    string ending;
    string verbForm;    // Current Spanish verb form being printed
    
    // Create table header
    cout << "Verb\t\tPresent\t\tFuture\t\tImperfect\tPreterite\n";
    cout << "---------------------------------------------------------------" <<
            "----------\n";
    
    // Traverse Spanish verb array and output conjugations for each tense
    for (int j = 0; j < 28; j++)
    {
        endIndex = espVerbs[j].infin.length() - 2;
        ending = espVerbs[j].infin.substr(endIndex, 2);
        
        cout << espVerbs[j].infin << "\t";
        if (espVerbs[j].infin.length() <= 7)
            cout << "\t";
            
        for (int i = 1; i <= 6; i++)
        {
            // Present tense conjugation
            verbForm = presConj(j, ending, endIndex, i);
            conjCondense(verbForm, "á", "é", "€");
            
            // Future tense
            verbForm = futureConj(j, i);
            conjCondense(verbForm, "á", "é", "€");
            
            // Imperfect tense
            verbForm = imperfConj(j, i, ending);
            conjCondense(verbForm, "á", "é", "í");
            
            // Preterite tense
            verbForm = pretConj(j, i, ending, endIndex);
            conjCondense(verbForm, "á", "é", "€");
            
            // Create new line at end of table
            if (i != 6)
                cout << "\n\t\t";
            else
                cout << "\n\n";
        }
    }
}

//***************************************************************************
// The conjCondense function condenses the conjDriver function by analyzing
// Spanish verb forms and printing them in a table according to their length.
// The function accepts as an argument the Spanish verb form as a string.
// The function returns nothing.
//***************************************************************************
void conjCondense(string verbForm, string char1, string char2, string char3)
{
    // Variables
    bool formChar = false;  // Value used in determining how to space verb forms

    // Print verb form
    cout << verbForm << "\t";
    if (verbForm.find(char1, 0) != -1
    || verbForm.find(char2, 0) != -1
    || verbForm.find(char3, 0) != -1)
	    formChar = true;
    if (verbForm.length() <= 7 + formChar)
	    cout << "\t";
}

//***************************************************************************
// The modVerb function analyzes English verbs and appends codes to them, based
// on subject and sentence context.
// The function receives as input an English sentence or phrase as a string and
// an int array to hold the outer and inner indexes of the verb form found.
// The function returns the modified English sentence or phrase as a string.
//*****************************************************************************
string modVerb(string engInput, int verb[])
{
    // Variables
    int index = -1;         // Index of English verb form found in input
    int objPos = 0;         // Variable used in getting direct object
    string verbForm;        // English verb form found in English input
    string dObject = "";    // Direct object to which the verb refers
    string testObject;      // Current direct object used in searching for a match
    string code = "#b";     // Hashtag code to be appended to English verb
    
    // Files
    ifstream pObjectFile;   // File for people objects
    
    // Open files
    pObjectFile.open("objPeople.txt");
    
    // Traverse engVerbs array, looking for instance of each verb in any form
    for (int v = 0; v < 28; v++)
    {
        for (int i = 0; i < 2; i++)
        {
            verbForm = engVerbs[v][i].infinAndPres124;
            verbForm = modVerbSearch(engInput, v, i, verbForm, verb);
            if (verb[1] != -1)
                break;
            verbForm = engVerbs[v][i].pres3;
            verbForm = modVerbSearch(engInput, v, i, verbForm, verb);
            if (verb[1] != -1)
                break;
            verbForm = engVerbs[v][i].past;
            verbForm = modVerbSearch(engInput, v, i, verbForm, verb);
            if (verb[1] != -1)
                break;
            verbForm = engVerbs[v][i].part;
            verbForm = modVerbSearch(engInput, v, i, verbForm, verb);
            if (verb[1] != -1)
                break;
            verbForm = engVerbs[v][i].prog;
            verbForm = modVerbSearch(engInput, v, i, verbForm, verb);
            if (verb[1] != -1)
                break;
        }
        if (verb[0] != -1)
            break;
    }
    
    // Get index of English verb
    index = verb[2];
    
    // Analyze direct object
    for (int j = index; j > -1; j++)
    {
        if (engInput[j] == ' ')
        {
            do
            {
                dObject.insert(objPos++, 1, engInput[j++ + 1]);
            } while (isalpha(engInput[j + 1]) && engInput[j + 1] != ' ');
            break;
        }
    }
    
    // Check to see if direct object is a people object
    while (pObjectFile >> testObject)
    {
        if (testObject == dObject)
        {
            code = "#p";
            break;
        }
    }
    
    // Append hashtag code to English verb
    engInput.insert(index + verbForm.length(), code);
    
    // Close files
    pObjectFile.close();
    
    return engInput;
    
}

//******************************************************************************
// The modVerb search function condenses the modVerb function being repeatedly
// called to search the English input for a verb form.
// The function accepts as input the current outer index of the English verb
// array as an int, the current inner index of the English verb array as an int,
// the current verb form in the English verb array that is being searched, and
// an int array to hold the outer and inner indexes of the verb form found.
// The function returns the English verb found in the input.
//******************************************************************************
string modVerbSearch(string engInput, int v, int i, string verbForm, int verb[])
{
    // Variables
    int index = -1;         // Index of English verb form found in input
    int letters = 0;        // Length of English verb form found in input
    int indexes;            // Last index value of English input
    int hash;               // Index of hashtag phrase in English verb
    string initVerb;        // Verb form found (or not) in English verb array
    
    // Set value of current verb form (to see if there is one)
    initVerb = verbForm;
    
    // Get last index value of English phrase
    indexes = engInput.length() - 1;
    
    // Reset English verb indexes
    verb[0] = verb[1] = -1;
    
    // Look for instance of verb form in English input
    hash = verbForm.find('#', 0);
    verbForm = verbForm.substr(0, hash);
    index = engInput.find(verbForm, 0);
    if (index != -1 && initVerb.length() != 0)
    {
	    letters = verbForm.length();
	    if ((engInput[index + letters] = ' '
	    || index + letters - 1 == indexes)
	    && (engInput[index - 1] == ' '
	    || index == 0))
	    {
		    verb[0] = v;
		    verb[1] = i;
	    }
    }
    
    verb[2] = index;
    
    return verbForm;
}

//***************************************************************************
// The pickApart function makes an English sentence more suitable for Spanish
// translation via separating contractions, rearranging words, etc.
// The function receives as input an English sentence as a string.
// The function returns the modified English sentence as a string.
//***************************************************************************
string pickApart(string engSentence)
{
    // Variables
    string modSentence;     // Modified English sentence
    
    // Search for contractions
    
    // Change verbs

}

//******************************************************************************
// The presConj function conjugates a Spanish verb into the present tense, based
// on person.
// The function receives as input the index of a verb in the Spanish verb array,
// the verb's ending as a string, the index of the verb's ending as an
// int, and the person as an int.
// The function returns the Spanish verb, conjugated to the present tense, as a
// string.
//******************************************************************************
string presConj(int verb, string end, int endIndex, int person)
{
    // Variables
    int stemIndex;          // Index of stem for stem changers
    int irregIndex;         // Index of key letter for irregular verbs
    string type;            // Type of present tense conjugation
    string irregChar;       // Character to replace weak vowels (u - ú, i - í)
    string infin;           // Infinitive form of Spanish verb
    
    // Get type of present tense conjugation
    type = espVerbs[verb].presType;
    
    // Get infinitive form
    infin = espVerbs[verb].infin;
    
    // Conjugate
    if (end == "ar")
    {
        if (type == "a")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "o");
            else if (person == 2)
                infin.replace(endIndex + 1, 1, "s");
            else if (person == 3)
                infin.erase(endIndex + 1, 1);
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "áis");
            else if (person == 6)
                infin.replace(endIndex + 1, 1, "n");
        }
        else if (type == "ba")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'o')
                    stemIndex = j;
            }
            if (person == 1)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 1, 2, "o");
            }
            else if (person == 2)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 2, 1, "s");
            }
            else if (person == 3)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.erase(endIndex + 2, 1);
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "áis");
            else if (person == 6)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 2, 1, "n");
            }
        }
        else if (type == "bb")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'e')
                    stemIndex = j;
            }
            if (person == 1)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 1, 2, "o");
            }
            else if (person == 2)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 2, 1, "s");
            }
            else if (person == 3)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.erase(endIndex + 2, 1);
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "áis");
            else if (person == 6)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 2, 1, "n");
            }
        }
        else if (type == "bd")
        {
            if (person == 1)
                infin = "juego";
            else if (person == 2)
                infin = "juegas";
            else if (person == 3)
                infin = "juega";
            else if (person == 4)
                infin = "jugamos";
            else if (person == 5)
                infin = "jugáis";
            else if (person == 6)
                infin = "juegan";
        }
        else if (type == "cc")
        {
            if (person == 1)
                infin = "doy";
            else if (person == 2)
                infin.replace(endIndex + 1, 1, "s");
            else if (person == 3)
                infin.erase(endIndex + 1, 1);
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "ais");
            else if (person == 6)
                infin.replace(endIndex + 1, 1, "n");
        }
        else if (type == "d")
        {
            for (int j = 0; j < endIndex; j++)
            {
                if (infin[j] == 'u')
                {
                    irregIndex = j;
                    irregChar = "ú";
                }
                if (infin[j] == 'i')
                {
                    irregIndex = j;
                    irregChar = "í";
                }
            }
            if (person == 1)
            {
                infin.replace(irregIndex, 1, irregChar);
                infin.replace(endIndex, 2, "o");
            }
            else if (person == 2)
            {
                infin.replace(irregIndex, 1, irregChar);
                infin.replace(endIndex, 1, "s");
            }
            else if (person == 3)
            {
                infin.replace(irregIndex, 1, irregChar);
                infin.erase(endIndex + 1, 1);
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "amos");
            else if (person == 5)
                infin.replace(endIndex, 2, "áis");
            else if (person == 6)
            {
                infin.replace(irregIndex, 1, irregChar);
                infin.replace(endIndex + 1, 1, "n");
            }
        }
        else if (type == "f")
        {
            if (person == 1)
                infin = "estoy";
            else if (person == 2)
                infin = "estás";
            else if (person == 3)
                infin = "está";
            else if (person == 4)
                infin = "estamos";
            else if (person == 5)
                infin = "estáis";
            else if (person == 6)
                infin = "están";
        }
    }
    else if (end == "er")
    {
        if (type == "a")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "o");
            else if (person == 2)
                infin.replace(endIndex + 1, 1, "s");
            else if (person == 3)
                infin.erase(endIndex + 1, 1);
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "éis");
            else if (person == 6)
                infin.replace(endIndex + 1, 1, "n");
        }
        else if (type == "ba")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'o')
                    stemIndex = j;
            }
            if (person == 1)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 1, 2, "o");
            }
            else if (person == 2)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 2, 1, "s");
            }
            else if (person == 3)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.erase(endIndex + 2, 1);
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "éis");
            else if (person == 6)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 2, 1, "n");
            }
        }
        else if (type == "bb")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'e')
                    stemIndex = j;
            }
            if (person == 1)
            {
                if (verb == 2)
                    infin = "tengo";
                else
                {
                    infin.replace(stemIndex, 1, "ie");
                    infin.replace(endIndex + 1, 2, "o");
                }
            }
            else if (person == 2)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 2, 1, "s");
            }
            else if (person == 3)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.erase(endIndex + 2, 1);
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "éis");
            else if (person == 6)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 2, 1, "n");
            }
        }
        else if (type == "ca")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'c')
                    irregIndex = j;
            }
            if (person == 1)
            {
                infin.replace(irregIndex, 1, "zc");
                infin.replace(endIndex + 1, 2, "o");
            }
            else if (person == 2)
                infin.replace(endIndex + 1, 1, "s");
            else if (person == 3)
                infin.erase(endIndex + 1, 1);
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "éis");
            else if (person == 6)
                infin.replace(endIndex + 1, 1, "n");
        }
        else if (type == "cb")
        {
            if (person == 1)
            {
                if (infin.substr(endIndex - 1, 3) == "aer")
                    infin.replace(endIndex, 2, "igo");
                else if (infin.substr(endIndex - 1, 1) == "c")
                    infin.replace(endIndex - 1, 3, "go");
                else
                    infin.replace(endIndex, 2, "go");
            }
            else if (person == 2)
                infin.replace(endIndex + 1, 1, "s");
            else if (person == 3)
                infin.erase(endIndex + 1, 1);
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "éis");
            else if (person == 6)
                infin.replace(endIndex + 1, 1, "n");
        }
        else if (type == "cc")
        {
            if (verb == 600)
            {
                if (person == 1)
                    infin = "quepo";
                else if (person == 2)
                    infin.replace(endIndex + 1, 1, "s");
                else if (person == 3)
                    infin.erase(endIndex + 1, 1);
                else if (person == 4)
                    infin.replace(endIndex + 1, 1, "mos");
                else if (person == 5)
                    infin.replace(endIndex, 2, "éis");
                else if (person == 6)
                    infin.replace(endIndex + 1, 1, "n");
            }
            else if (verb == 9)
            {
                if (person == 1)
                    infin = "sé";
                else if (person == 2)
                    infin.replace(endIndex + 1, 1, "s");
                else if (person == 3)
                    infin.erase(endIndex + 1, 1);
                else if (person == 4)
                    infin.replace(endIndex + 1, 1, "mos");
                else if (person == 5)
                    infin.replace(endIndex, 2, "éis");
                else if (person == 6)
                    infin.replace(endIndex + 1, 1, "n");
            }
            else if (verb == 7)
            {
                if (person == 1)
                    infin = "veo";
                else if (person == 2)
                    infin.replace(endIndex + 1, 1, "s");
                else if (person == 3)
                    infin.erase(endIndex + 1, 1);
                else if (person == 4)
                    infin.replace(endIndex + 1, 1, "mos");
                else if (person == 5)
                    infin.replace(endIndex, 2, "eis");
                else if (person == 6)
                    infin.replace(endIndex + 1, 1, "n");
            }
        }
        else if (type == "f")
        {
            if (verb == 0)
            {
                if (person == 1)
                    infin = "soy";
                else if (person == 2)
                    infin = "eres";
                else if (person == 3)
                    infin = "es";
                else if (person == 4)
                    infin = "somos";
                else if (person == 5)
                    infin = "sois";
                else if (person == 6)
                    infin = "son";
            }
            else
            {
                if (person == 1)
                    infin = "huelo";
                else if (person == 2)
                    infin = "hueles";
                else if (person == 3)
                    infin = "huele";
                else if (person == 4)
                    infin = "olemos";
                else if (person == 5)
                    infin = "oléis";
                else if (person == 6)
                    infin = "huelen";
            }
        }
    }
    else if (end == "ir")
    {
        if (type == "a")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "o");
            else if (person == 2)
                infin.replace(endIndex, 2, "es");
            else if (person == 3)
                infin.replace(endIndex, 2, "e");
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "ís");
            else if (person == 6)
                infin.replace(endIndex, 2, "en");
        }
        else if (type == "ba")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'o')
                    stemIndex = j;
            }
            if (person == 1)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 1, 2, "o");
            }
            else if (person == 2)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 1, 2, "es");
            }
            else if (person == 3)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 1, 2, "e");
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "ís");
            else if (person == 6)
            {
                infin.replace(stemIndex, 1, "ue");
                infin.replace(endIndex + 1, 2, "en");
            }
        }
        else if (type == "bb")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'e')
                    stemIndex = j;
            }
            if (person == 1)
            {
                if (verb = 24)
                    infin = "vengo";
                else
                {
                    infin.replace(stemIndex, 1, "ie");
                    infin.replace(endIndex + 1, 2, "o");
                }
            }
            else if (person == 2)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 1, 2, "es");
            }
            else if (person == 3)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 1, 2, "e");
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "ís");
            else if (person == 6)
            {
                infin.replace(stemIndex, 1, "ie");
                infin.replace(endIndex + 1, 2, "en");
            }
        }
        else if (type == "bc")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'e')
                    stemIndex = j;
            }
            if (person == 1)
            {
                if (verb == 5)
                    infin = "digo";
                else
                {
                    infin.replace(stemIndex, 1, "i");
                    infin.replace(endIndex, 2, "o");
                }
            }
            else if (person == 2)
            {
                infin.replace(stemIndex, 1, "i");
                infin.replace(endIndex, 2, "es");
            }
            else if (person == 3)
            {
                infin.replace(stemIndex, 1, "i");
                infin.replace(endIndex, 2, "e");
            }
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "ís");
            else if (person == 6)
            {
                infin.replace(stemIndex, 1, "i");
                infin.replace(endIndex, 2, "en");
            }
        }
        else if (type == "ca")
        {
            for (int j = endIndex; j >= 0; j--)
            {
                if (infin[j] == 'c')
                    irregIndex = j;
            }
            if (person == 1)
            {
                infin.replace(irregIndex, 1, "zc");
                infin.replace(endIndex + 1, 2, "o");
            }
            else if (person == 2)
                infin.replace(endIndex + 1, 1, "s");
            else if (person == 3)
                infin.erase(endIndex + 1, 1);
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "éis");
            else if (person == 6)
                infin.replace(endIndex + 1, 1, "n");
        }
        else if (type == "cb")
        {
            if (person == 1)
                infin = "salgo";
            else if (person == 2)
                infin = "sales";
            else if (person == 3)
                infin = "sale";
            else if (person == 4)
                infin = "salimos";
            else if (person == 5)
                infin = "salís";
            else if (person == 6)
                infin = "salen";
        }
        else if (type == "f")
        {
            if (person == 1)
                infin = "voy";
            else if (person == 2)
                infin = "vas";
            else if (person == 3)
                infin = "va";
            else if (person == 4)
                infin = "vamos";
            else if (person == 5)
                infin = "vais";
            else if (person == 6)
                infin = "van";
        }
        else if (type == "ga")
        {
            if (person == 1)
            {
                if (infin.substr(endIndex - 2, 4) == "egir")
                    infin.replace(endIndex - 2, 4, "ijo");
                else
                    infin.replace(endIndex - 1, 3, "jo");
            }
            else if (person == 2)
                infin.replace(endIndex, 2, "es");
            else if (person == 3)
                infin.replace(endIndex, 2, "e");
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "ís");
            else if (person == 6)
                infin.replace(endIndex, 2, "en");
        }
        else if (type == "gb")
        {
            if (infin.substr(endIndex - 3, 5) == "eguir"
            || infin.substr(endIndex - 3, 5) == "rguir")
                infin.replace(endIndex - 3, 1, "i");
            if (person == 1)
                infin.replace(endIndex - 1, 3, "o");
            else if (person == 2)
                infin.replace(endIndex, 2, "es");
            else if (person == 3)
                infin.replace(endIndex, 2, "e");
            else if (person == 4)
                infin.replace(endIndex + 1, 1, "mos");
            else if (person == 5)
                infin.replace(endIndex, 2, "ís");
            else if (person == 6)
                infin.replace(endIndex, 2, "en");
        }
    }
    
    return infin;
}

//******************************************************************************
// The futureConj function conjugates a Spanish verb into the future tense,
// based on person.
// The function receives as input the index of a verb in the Spanish verb array
// as an int and the person as an int.
// The function returns the Spanish verb, conjugated to the future tense, as a
// string.
//******************************************************************************
string futureConj(int verb, int person)
{
    // Variables
    string infin;           // Infinitive form of Spanish verb
    bool reg;               // Future tense conjugation regularity
    
    // Get verb information
    infin = espVerbs[verb].infin;
    reg = espVerbs[verb].futureReg;
    
    // Conjugate
    if (reg == true)
    {
        if (person == 1)
            infin.insert(infin.length(), "é");
        else if (person == 2)
            infin.insert(infin.length(), "ás");
        else if (person == 3)
            infin.insert(infin.length(), "á");
        else if (person == 4)
            infin.insert(infin.length(), "emos");
        else if (person == 5)
            infin.insert(infin.length(), "éis");
        else if (person == 6)
            infin.insert(infin.length(), "án");
    }
    if (verb == 2 || verb == 14 || verb == 24 || verb == 26)
    {
        if (person == 1)
            infin.replace(infin.length() - 2, 2, "dré");
        else if (person == 2)
            infin.replace(infin.length() - 2, 2, "drás");
        else if (person == 3)
            infin.replace(infin.length() - 2, 2, "drá");
        else if (person == 4)
            infin.replace(infin.length() - 2, 2, "dremos");
        else if (person == 5)
            infin.replace(infin.length() - 2, 2, "dréis");
        else if (person == 6)
            infin.replace(infin.length() - 2, 2, "drán");
    }
    else if (verb == 3)
    {
        if (person == 1)
            infin.replace(infin.length() - 3, 3, "ré");
        else if (person == 2)
            infin.replace(infin.length() - 3, 3, "rás");
        else if (person == 3)
            infin.replace(infin.length() - 3, 3, "rá");
        else if (person == 4)
            infin.replace(infin.length() - 3, 3, "remos");
        else if (person == 5)
            infin.replace(infin.length() - 3, 3, "réis");
        else if (person == 6)
            infin.replace(infin.length() - 3, 3, "rán");
    }
    else if (verb == 4 || verb == 9 || verb == 10)
    {
        if (person == 1)
            infin.replace(infin.length() - 2, 2, "ré");
        else if (person == 2)
            infin.replace(infin.length() - 2, 2, "rás");
        else if (person == 3)
            infin.replace(infin.length() - 2, 2, "rá");
        else if (person == 4)
            infin.replace(infin.length() - 2, 2, "remos");
        else if (person == 5)
            infin.replace(infin.length() - 2, 2, "réis");
        else if (person == 6)
            infin.replace(infin.length() - 2, 2, "rán");
    }
    else if (verb == 5)
    {
        if (person == 1)
            infin = "diré";
        else if (person == 2)
            infin = "dirás";
        else if (person == 3)
            infin = "dirá";
        else if (person == 4)
            infin = "diremos";
        else if (person == 5)
            infin = "diréis";
        else if (person == 6)
            infin = "dirán";
    }
    
    return infin;
}

//******************************************************************************
// The imperfConj function conjugates a Spanish verb into the imperfect tense,
// based on person.
// The function receives as input the index of a verb in the Spanish verb array
// as an int, the person as an int and the verb's ending as a string.
// The function returns the Spanish verb, conjugated to the imperfect tense, as
// a string.
//******************************************************************************
string imperfConj(int verb, int person, string ending)
{
    // Variables
    string infin;       // Infinitive form of Spanish verb
    bool reg;           // Imperfect tense conjugation regularity
    
    // Get verb information
    infin = espVerbs[verb].infin;
    reg = espVerbs[verb].imperfReg;
    
    // Conjugate regular verbs
    if (reg == true)
    {
        if (ending == "ar")
        {
            if (person == 1 || person == 3)
                infin.replace(infin.length() - 2, 2, "aba");
            else if (person == 2)
                infin.replace(infin.length() - 2, 2, "abas");
            else if (person == 4)
                infin.replace(infin.length() - 2, 2, "ábamos");
            else if (person == 5)
                infin.replace(infin.length() - 2, 2, "abais");
            else if (person == 6)
                infin.replace(infin.length() - 2, 2, "aban");
        }
        else if (ending == "er")
        {
            if (person == 1 || person == 3)
                infin.replace(infin.length() - 2, 2, "ía");
            else if (person == 2)
                infin.replace(infin.length() - 2, 2, "ías");
            else if (person == 4)
                infin.replace(infin.length() - 2, 2, "íamos");
            else if (person == 5)
                infin.replace(infin.length() - 2, 2, "íais");
            else if (person == 6)
                infin.replace(infin.length() - 2, 2, "ían");
        }
        else if (ending == "ir")
        {
            if (person == 1 || person == 3)
                infin.replace(infin.length() - 2, 2, "ía");
            else if (person == 2)
                infin.replace(infin.length() - 2, 2, "ías");
            else if (person == 4)
                infin.replace(infin.length() - 2, 2, "íamos");
            else if (person == 5)
                infin.replace(infin.length() - 2, 2, "íais");
            else if (person == 6)
                infin.replace(infin.length() - 2, 2, "ían");
        }
    }
    
    // Conjugate irregular verbs
    if (verb == 0)
    {
        if (person == 1 || person == 3)
            infin = "era";
        else if (person == 2)
            infin = "eras";
        else if (person == 4)
            infin = "éramos";
        else if (person == 5)
            infin = "erais";
        else if (person == 6)
            infin = "eran";
    }
    else if (verb == 6)
    {
        if (person == 1 || person == 3)
            infin = "iba";
        else if (person == 2)
            infin = "ibas";
        else if (person == 4)
            infin = "íbamos";
        else if (person == 5)
            infin = "ibais";
        else if (person == 6)
            infin = "iban";
    }
    else if (verb == 7)
    {
        if (person == 1 || person == 3)
            infin = "veía";
        else if (person == 2)
            infin = "veías";
        else if (person == 4)
            infin = "veíamos";
        else if (person == 5)
            infin = "veíais";
        else if (person == 6)
            infin = "veían";
    }
    
    return infin;
}

//******************************************************************************
// The pretConj function conjugates a Spanish verb into the preterite tense,
// based on person.
// The function receives as input the index of a verb in the Spanish verb array
// as an int, the person as an int, the verb's ending as a string, the the index
// of the verb's ending as an int.
// The function returns the Spanish verb, conjugated to the imperfect tense, as
// a string.
//******************************************************************************
string pretConj(int verb, int person, string ending, int endIndex)
{
    // Variables
    string infin;       // Infinitive form of Spanish verb
    string type;        // Type of preterite tense conjugation
    int stemIndex;      // Index of stem for stem changers
    char stem;          // Changing character in stem changers
    string newStem;     // Changed character in stem changers
    int back;           // Variable used for strong stem preterites
    
    // Get verb information
    infin = espVerbs[verb].infin;
    type = espVerbs[verb].pretType;
    back = espVerbs[verb].stemBack;
    
    // Conjugate
    if (ending == "ar")
    {
        if (type == "a")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "é");
            else if (person == 2)
                infin.replace(endIndex + 1, 2, "ste");
            else if (person == 3)
                infin.replace(endIndex, 2, "ó");
            else if (person == 4)
                infin.replace(endIndex + 1, 2, "mos");
            else if (person == 5)
                infin.replace(endIndex + 1, 2, "steis");
            else if (person == 6)
                infin.replace(endIndex + 1, 2, "ron");
        }
        else if (type == "ba")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "qué");
            else if (person == 2)
                infin.replace(endIndex + 1, 2, "ste");
            else if (person == 3)
                infin.replace(endIndex, 2, "ó");
            else if (person == 4)
                infin.replace(endIndex + 1, 2, "mos");
            else if (person == 5)
                infin.replace(endIndex + 1, 2, "steis");
            else if (person == 6)
                infin.replace(endIndex + 1, 2, "ron");
        }
        else if (type == "bb")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "ué");
            else if (person == 2)
                infin.replace(endIndex + 1, 2, "ste");
            else if (person == 3)
                infin.replace(endIndex, 2, "ó");
            else if (person == 4)
                infin.replace(endIndex + 1, 2, "mos");
            else if (person == 5)
                infin.replace(endIndex + 1, 2, "steis");
            else if (person == 6)
                infin.replace(endIndex + 1, 2, "ron");
        }
        else if (type == "bc")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "cé");
            else if (person == 2)
                infin.replace(endIndex + 1, 2, "ste");
            else if (person == 3)
                infin.replace(endIndex, 2, "ó");
            else if (person == 4)
                infin.replace(endIndex + 1, 2, "mos");
            else if (person == 5)
                infin.replace(endIndex + 1, 2, "steis");
            else if (person == 6)
                infin.replace(endIndex + 1, 2, "ron");
        }
    }
    else if (ending == "er" || ending == "ir")
    {
        if (type == "a")
        {
            if (person == 1)
                infin.replace(endIndex, 2, "í");
            else if (person == 2)
                infin.replace(endIndex, 2, "iste");
            else if (person == 3)
                infin.replace(endIndex, 2, "ió");
            else if (person == 4)
                infin.replace(endIndex, 2, "imos");
            else if (person == 5)
                infin.replace(endIndex, 2, "isteis");
            else if (person == 6)
                infin.replace(endIndex, 2, "ieron");
        }
    }
    
    // -ir stem-changing preterites
    if (type == "ca" || type == "cb" || type == "cc")
    {
        if (type == "ca")
        {
            stem = 'o';
            newStem = "u";
        }
        else if (type == "cb" || type == "cc")
        {
            stem = 'e';
            newStem = "i";
        }
        for (int j = endIndex; j >= 0; j--)
        {
            if (infin[j] == stem)
                stemIndex = j;
        }
        if (person == 1)
            infin.replace(endIndex, 2, "í");
        else if (person == 2)
            infin.replace(endIndex, 2, "iste");
        else if (person == 3)
        {
            infin.replace(stemIndex, 1, newStem);
            infin.replace(endIndex, 2, "ió");
        }
        else if (person == 4)
            infin.replace(endIndex, 2, "imos");
        else if (person == 5)
            infin.replace(endIndex, 2, "isteis");
        else if (person == 6)
            infin.replace(endIndex, 2, "ieron");
    }
    
    // Strong stem preterites
    if (type == "da")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "uve");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "uviste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "uvo");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "uvimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "uvisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "uvieron");
    }
    else if (type == "db")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "je");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "jiste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "jo");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "jimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "jisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "jeron");
    }
    else if (type == "dc")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "ije");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "ijiste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "ijo");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "ijimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "ijisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "ijeron");
    }
    else if (type == "dd")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "ice");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "iciste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "izo");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "icimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "icisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "icieron");
    }
    else if (type == "de")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "ude");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "udiste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "udo");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "udimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "udisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "udieron");
    }
    else if (type == "df")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "use");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "usiste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "uso");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "usimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "usisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "usieron");
    }
    else if (type == "dg")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "ise");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "isiste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "iso");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "isimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "isisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "isieron");
    }
    else if (type == "dh")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "upe");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "upiste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "upo");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "upimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "upisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "upieron");
    }
    else if (type == "di")
    {
        if (person == 1)
            infin.replace(infin.length() - back, back, "ine");
        else if (person == 2)
            infin.replace(infin.length() - back, back, "iniste");
        else if (person == 3)
            infin.replace(infin.length() - back, back, "ino");
        else if (person == 4)
            infin.replace(infin.length() - back, back, "inimos");
        else if (person == 5)
            infin.replace(infin.length() - back, back, "inisteis");
        else if (person == 6)
            infin.replace(infin.length() - back, back, "inieron");
    }
    
    // -aer, -eer, -oír, and -oer verb preterites
    else if (type == "e")
    {
        if (person == 1)
            infin.replace(endIndex, 2, "í");
        else if (person == 2)
            infin.replace(endIndex, 2, "íste");
        else if (person == 3)
            infin.replace(endIndex, 2, "yó");
        else if (person == 4)
            infin.replace(endIndex, 2, "ímos");
        else if (person == 5)
            infin.replace(endIndex, 2, "ísteis");
        else if (person == 6)
            infin.replace(endIndex, 2, "yeron");
    }
    
    // Irregular preterites
    if (verb == 0 || verb == 6)
    {
        if (person == 1)
            infin = "fui";
        else if (person == 2)
            infin = "fuiste";
        else if (person == 3)
            infin = "fue";
        else if (person == 4)
            infin = "fuimos";
        else if (person == 5)
            infin = "fuisteis";
        else if (person == 6)
            infin = "fueron";
    }
    else if (verb == 7)
    {
        if (person == 1)
            infin = "vi";
        else if (person == 2)
            infin = "viste";
        else if (person == 3)
            infin = "vio";
        else if (person == 4)
            infin = "vimos";
        else if (person == 5)
            infin = "visteis";
        else if (person == 6)
            infin = "vieron";
    }
    else if (verb == 8)
    {
        if (person == 1)
            infin = "di";
        else if (person == 2)
            infin = "diste";
        else if (person == 3)
            infin = "dio";
        else if (person == 4)
            infin = "dimos";
        else if (person == 5)
            infin = "disteis";
        else if (person == 6)
            infin = "dieron";
    }
    
    
    return infin;
}
