#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <typeinfo>
#include <type_traits>


using namespace std;
// Enum type representing the types of lexemes
enum LexemeType {
	KEYWORD,
	IDENTIFIER,
	OPERATOR,
	NUMBER,
	//FLOAT,
	SEMICOLON,
	OPEN_PAREN,//(
	CLOSE_PAREN,//)
	SQUARE_BRACKET,//[]
	COMPARISON,
	ASSIGNMENT,
	OTHER,
	SPACE,
	ARRAY,
};

// Struct to store information of each lexeme
struct Lexeme {
	string value;    // Value of the lexeme
	LexemeType type; // Type of the lexeme
	int position;    // Position of the lexeme in the input string
};

// Function to check if a string is a keyword
bool isKeyword(const string& str) {
	return (str == "int" || str == "float" || str == "if" || str == "while" || str == "else" || str == "str" || str == "begin" || str == "end");
}

// Function to analyze lexemes from the input string
vector<Lexeme> analyzeLexemes(const string& input) {
	vector<Lexeme> lexemes;

	string currentLexeme = "";
	int position = 0;


	for (size_t i = 0; i < input.size(); ++i) {
		char ch = input[i];

		if (isspace(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '=' || ch == '!' || ch == ':' || ch == '>' || ch == '<' || ch == '[' || ch == ']') {
			if (!currentLexeme.empty()) {
				Lexeme lex;
				lex.value = currentLexeme;
				lex.position = position - currentLexeme.size();
				// Determine the type of the lexeme
				if (isKeyword(currentLexeme)) {
					lex.type = KEYWORD;
				}
				else if (isalpha(currentLexeme[0])) {
					lex.type = IDENTIFIER;
				}
				else if (isdigit(currentLexeme[0]))
				{
					lex.type = NUMBER;
				}


				else {
					lex.type = OTHER;
				}
				lexemes.push_back(lex);
				currentLexeme = "";// Reset currentLexeme
			}
			if (ch == ':') {
				if (i + 1 < input.size() && input[i + 1] == '=') {
					// Check for comparison operator ":="
					Lexeme lex;
					lex.value = ":=";
					lex.type = ASSIGNMENT;
					lex.position = position;
					lexemes.push_back(lex);
					++i; // Skip the next character '='
				}
			}
			else if (ch == '-') {
				Lexeme lex;
				lex.value = "-";
				lex.type = OPERATOR;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == '*') {
				Lexeme lex;
				lex.value = "*";
				lex.type = OPERATOR;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == '/') {
				Lexeme lex;
				lex.value = "/";
				lex.type = OPERATOR;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == '(') {
				Lexeme lex;
				lex.value = "(";
				lex.type = OPEN_PAREN;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == ')') {
				Lexeme lex;
				lex.value = ")";
				lex.type = CLOSE_PAREN;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == '[') {
				Lexeme lex;
				lex.value = "[";
				lex.type = SQUARE_BRACKET;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == ']') {
				Lexeme lex;
				lex.value = "]";
				lex.type = SQUARE_BRACKET;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == ';') {
				Lexeme lex;
				lex.value = ";";
				lex.type = SEMICOLON;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == ' ') {
				Lexeme lex;
				lex.value = " ";
				lex.type = SPACE;
				lex.position = position;
				lexemes.push_back(lex);
			}
			/*else if (ch == '>') {
				Lexeme lex;
				lex.value = ">";
				lex.type = COMPARISON;
				lex.position = position;
				lexemes.push_back(lex);
			}
			else if (ch == '<') {
				Lexeme lex;
				lex.value = "<";
				lex.type = COMPARISON;
				lex.position = position;
				lexemes.push_back(lex);
			}*/
			else if (ch == '+') {
				Lexeme lex;
				lex.value = "+";
				lex.type = OPERATOR;
				lex.position = position;
				lexemes.push_back(lex);
			}
			// Process the current operator or separator as a separate lexeme
			else if (ch == '=' && i + 1 < input.size() && input[i + 1] == '=') {
				// Check for comparison operator "=="
				Lexeme lex;
				lex.value = "==";
				lex.type = COMPARISON;
				lex.position = position;
				lexemes.push_back(lex);
				++i; // Skip the next character '='
			}
			else if (ch == '!') {
				if (i + 1 < input.size() && input[i + 1] == '=') {
					// Check for comparison operator "!="
					Lexeme lex;
					lex.value = "!=";
					lex.type = COMPARISON;
					lex.position = position;
					lexemes.push_back(lex);
					++i; // Skip the next character '='
				}
			}
			else if (ch == '>') {
				if (i + 1 < input.size() && input[i + 1] == '=') {
					// Check for comparison operator ">="
					Lexeme lex;
					lex.value = ">=";
					lex.type = COMPARISON;
					lex.position = position;
					lexemes.push_back(lex);
					++i; // Skip the next character '='
				}
				else
				{
					Lexeme lex;
					lex.value = ">";
					lex.type = COMPARISON;
					lex.position = position;
					lexemes.push_back(lex);
				}
			}
			else if (ch == '<') {
				if (i + 1 < input.size() && input[i + 1] == '=') {
					// Check for comparison operator "<="
					Lexeme lex;
					lex.value = "<=";
					lex.type = COMPARISON;
					lex.position = position;
					lexemes.push_back(lex);
					++i; // Skip the next character '='
				}
				else
				{
					Lexeme lex;
					lex.value = "<";
					lex.type = COMPARISON;
					lex.position = position;
					lexemes.push_back(lex);
				}
			}
			else {
				// Process other single-character operators and separators
				Lexeme lex;
				lex.value = string(1, ch); // Convert char to string
				lex.position = position;
				lex.type = OTHER;
				lexemes.push_back(lex);
			}
		}
		else {
			currentLexeme += ch;
		}
		++position;
	}

	// Final check for any remaining lexeme
	if (!currentLexeme.empty()) {
		Lexeme lex;
		lex.value = currentLexeme;
		lex.position = position - currentLexeme.size();

		// Determine the type of the lexeme
		if (isKeyword(currentLexeme)) {
			lex.type = KEYWORD;
		}
		else if (isalpha(currentLexeme[0])) {
			lex.type = IDENTIFIER;
		}
		else if (isdigit(currentLexeme[0])) {
			lex.type = NUMBER;
		}
		else if (currentLexeme == "+") {
			lex.type = OPERATOR;
		}

		else {
			lex.type = OTHER;
		}

		lexemes.push_back(lex);
	}

	return lexemes;
}

// Function to display information of lexemes
void displayLexemes(const vector<Lexeme>& lexemes) {
	for (const auto& lexeme : lexemes) {
		cout << "Lexeme: " << lexeme.value << ", Type: ";
		switch (lexeme.type) {
		case KEYWORD:
			cout << "Keyword";
			break;
		case IDENTIFIER:
			cout << "Identifier";
			break;
		case OPERATOR:
			cout << "Operator";
			break;
		case NUMBER:
			cout << "Number";
			break;
		case SEMICOLON:
			cout << "Semicolon";
			break;
		case OPEN_PAREN:
			cout << "Open Parenthesis";
			break;
		case CLOSE_PAREN:
			cout << "Close Parenthesis";
			break;
		case COMPARISON:
			cout << "Comparison Operator";
			break;
		case ASSIGNMENT:
			cout << "Assignment Operator";
			break;

			break;
		case SPACE:
			cout << "Space";
			break;
		case SQUARE_BRACKET:
			cout << "square bracket";
			break;
		case OTHER:
			cout << "Other";
			break;
		}
		cout << ", Position: " << lexeme.position << endl;
	}
}

int main() {
	string input;
	cout << "Enter an input: ";
	getline(cin, input);

	vector<Lexeme> lexemes = analyzeLexemes(input);
	displayLexemes(lexemes);

	return 0;
}
