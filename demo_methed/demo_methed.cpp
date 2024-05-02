#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <cmath>

using namespace std;

// Enum type representing the types of lexemes
enum LexemeType {
	KEYWORD,
	IDENTIFIER,
	OPERATOR,
	NUMBER,
	FLOAT,
	SEMICOLON,
	OPEN_PAREN,
	CLOSE_PAREN,
	SQUARE_BRACKET,
	COMPARISON,
	ASSIGNMENT,
	MISTAKE,
	SPACE,
};
// Struct to store information of each lexeme
struct Lexeme {
	string value; // Value of the lexeme
	LexemeType type; // Type of the lexeme
	int position; // Position of the lexeme in the input string
	double numericValue = 0.0; // Numeric value for numbers
};

// Converts a single character to its integer value
int charToInt(char c) {
	return c - '0';
}

// Function to check if a string is a keyword
bool isKeyword(const string& str) {
	return (str == "int" || str == "float" || str == "if" || str == "while" || str == "else" || str == "str" || str == "begin" || str == "end" || str == "cin" || str == "cout");
}

// Function to analyze lexemes from the input string
vector<Lexeme> analyzeLexemes(const string& input) {
	vector<Lexeme> lexemes;

	string currentLexeme = "";
	int position = 0;
	bool isFloatingPoint = false; // Indicates whether we're dealing with a float
	double floatingFactor = 0.1; // Factor for building floating-point numbers
	int integerValue = 0; // Holds the integer part of the number
	double floatValue = 0.0; // Holds the floating-point part

	for (size_t i = 0; i < input.size(); ++i) {
		char ch = input[i];

		if (isspace(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == ';' || ch == '(' || ch == ')' || ch == '=' || ch == '!' || ch == ':' || ch == '>' || ch == '<' || ch == '[' || ch == ']') {
			if (!currentLexeme.empty()) {
				Lexeme lex;
				lex.value = currentLexeme;
				lex.position = position - currentLexeme.size();

				if (isKeyword(currentLexeme)) {
					lex.type = KEYWORD;
				}
				else if (isalpha(currentLexeme[0])) {
					lex.type = IDENTIFIER;
				}
				else if (isdigit(currentLexeme[0])) {
					if (isFloatingPoint) {
						lex.type = FLOAT;
						lex.numericValue = integerValue + floatValue; // Combine the float value
					}
					else {
						lex.type = NUMBER;
						lex.numericValue = integerValue; // Store integer value
					}
				}
				else {
					lex.type = MISTAKE;
				}

				lexemes.push_back(lex);

				// Reset for the next lexeme
				currentLexeme = "";
				isFloatingPoint = false;
				integerValue = 0;
				floatValue = 0.0;
				floatingFactor = 0.1;
			}

			// Handle specific cases for operators and separators
			if (ch == ':') {
				if (i + 1 < input.size() && input[i + 1] == '=') {
					Lexeme lex;
					lex.value = ":=";
					lex.type = ASSIGNMENT;
					lex.position = position;
					/*lex.numericValue = 0;*/
					lexemes.push_back(lex);
					++i; // Skip the next '='
				}
			}
			if (ch == '-') {
				Lexeme lex;
				lex.value = "-";
				lex.type = OPERATOR;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == '*') {
				Lexeme lex;
				lex.value = "*";
				lex.type = OPERATOR;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == '/') {
				Lexeme lex;
				lex.value = "/";
				lex.type = OPERATOR;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == '(') {
				Lexeme lex;
				lex.value = "(";
				lex.type = OPEN_PAREN;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == ')') {
				Lexeme lex;
				lex.value = ")";
				lex.type = CLOSE_PAREN;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == '[') {
				Lexeme lex;
				lex.value = "[";
				lex.type = SQUARE_BRACKET;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == ']') {
				Lexeme lex;
				lex.value = "]";
				lex.type = SQUARE_BRACKET;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == ';') {
				Lexeme lex;
				lex.value = ";";
				lex.type = SEMICOLON;
				lex.position = position;
				lexemes.push_back(lex);
			}
			if (ch == '!') {
				if (i + 1 < input.size() && input[i + 1] == '=') {
					Lexeme lex;
					lex.value = "!=";
					lex.type = COMPARISON;
					lex.position = position;
					//lex.numericValue = 0;
					lexemes.push_back(lex);
					++i; // Skip the next '='
				}
			}
			if (ch == '=') {
				if (i + 1 < input.size() && input[i + 1] == '=') {
					// Check for comparison operator ">="
					Lexeme lex;
					lex.value = "==";
					lex.type = COMPARISON;
					lex.position = position;
					lexemes.push_back(lex);
					++i; // Skip the next character '='
				}
				else
				{
					Lexeme lex;
					lex.value = "=";
					lex.type = COMPARISON;
					lex.position = position;
					lexemes.push_back(lex);
				}
			}
			if (ch == '>') {
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
			if (ch == '<') {
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
		}
		else {

			// If it's a number, update integer or float value
			if (isdigit(ch)) {
				int num = charToInt(ch); // Convert to an integer value

				if (isFloatingPoint) {
					floatValue += num * floatingFactor; // Build floating-point part
					floatingFactor *= 0.1; // Update the floating factor
				}
				else {
					integerValue = integerValue * 10 + num; // Build integer value
				}
			}

			if (ch == '.') {
				isFloatingPoint = true; // Detected a floating-point number
			}
			currentLexeme += ch; // Build the current lexeme

		}

		++position; // Update the current position
	}

	if (!currentLexeme.empty()) {
		Lexeme lex;
		lex.value = currentLexeme;
		lex.position = position - currentLexeme.size();

		if (isKeyword(currentLexeme)) {
			lex.type = KEYWORD;
		}
		// Check if the first character in currentLexeme is a digit
		// Check if the first character in currentLexeme is a digit
		// Check if the first character in currentLexeme is a digit
		// Check if the first character in currentLexeme is a digit
		// Check if the first character in currentLexeme is a digit
		if (isdigit(currentLexeme[0])) {
			bool hasLetterAfterDigit = false;
			bool hasDecimalPoint = false;

			// Iterate through the characters in currentLexeme
			for (int i = 0; i < currentLexeme.length(); ++i) {
				char ch = currentLexeme[i];

				// Check if the current character is a letter immediately following a digit
				if (i > 0 && isdigit(currentLexeme[i - 1]) && isalpha(ch)) {
					hasLetterAfterDigit = true;
					break;
				}

				// Check for multiple decimal points
				if (ch == '.') {
					if (hasDecimalPoint) {
						// If a second decimal point is found, mark as a mistake
						lex.type = MISTAKE;
						break;
					}
					hasDecimalPoint = true;
				}

				// Check if the current character is not a digit or a decimal point
				if (!isdigit(ch) && ch != '.') {
					// If a non-digit or non-decimal point character is found, mark as a mistake
					lex.type = MISTAKE;
					break;
				}
			}
			// If no mistakes were found, determine the type of number
			if (hasLetterAfterDigit || hasDecimalPoint) {
				// If a letter follows a digit or a decimal point is present, mark as a mistake
				lex.type = MISTAKE;
			}
			else {
				bool hasNonDigitCharacter = false;

				// Iterate through the characters in currentLexeme
				for (char ch : currentLexeme) {
					// Check if the current character is not a digit
					if (!isdigit(ch)) {
						// If a non-digit character is found, mark as a mistake
						hasNonDigitCharacter = true;
						break;
					}
				}

				// If any non-digit character was found, mark as a mistake
				if (hasNonDigitCharacter) {
					lex.type = MISTAKE;
				}
				else {
					// Otherwise, determine the type of number based on the presence of a decimal point
					if (hasDecimalPoint || isFloatingPoint) {
						lex.type = FLOAT;
						lex.numericValue = integerValue + floatValue; // Combine the float value
					}
					else {
						lex.type = NUMBER;
						lex.numericValue = integerValue; // Store integer value
					}
				}
			}
		}
		else
		{
			lex.type = MISTAKE;
		}

		lexemes.push_back(lex);
	}

	return lexemes;

}

// Function 
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
			cout << "Number (Numeric Value: " << lexeme.numericValue << ")";
			break;
		case FLOAT:
			cout << "Float (Numeric Value: " << lexeme.numericValue << ")";
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
		case SQUARE_BRACKET:
			cout << "Square Bracket";
			break;
		case COMPARISON:
			cout << "Comparison";
			break;
		case ASSIGNMENT:
			cout << "Assignment";
			break;
		case MISTAKE:
			cout << "Mistake";
			break;
		}
		cout << ", Position: " << lexeme.position << endl;
	}
}
// Main function to analyze input
int main() {
	string input;
	cout << "Enter an input: ";
	getline(cin, input);

	vector<Lexeme> lexemes = analyzeLexemes(input);
	displayLexemes(lexemes);

	return 0;
}