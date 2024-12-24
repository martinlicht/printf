#include <cstdarg>
#include <cstring> // For size_t

#include <iostream>
#include <cctype>
#include <cstring>

// Enum for format flags
enum class FormatFlag {
    NONE,            // No specific flag
    PLUS,            // '+' flag
    SPACE,           // ' ' flag
    ZERO_PADDING,    // '0' flag
    SHARP,           // '#' flag
    LEFT_ALIGN,      // '-' flag
    CUSTOM_UNKNOWN   // Unknown or unsupported flag
};

// Convert format flag enum to string
std::string to_string(FormatFlag flag) {
    switch (flag) {
        case FormatFlag::NONE:           return "NONE";
        case FormatFlag::PLUS:           return "PLUS ('+')";
        case FormatFlag::SPACE:          return "SPACE (' ')";
        case FormatFlag::ZERO_PADDING:   return "ZERO_PADDING ('0')";
        case FormatFlag::SHARP:          return "ZERO_PADDING ('0')";
        case FormatFlag::LEFT_ALIGN:     return "LEFT_ALIGN ('-')";
        case FormatFlag::CUSTOM_UNKNOWN: return "CUSTOM_UNKNOWN";
        default:                         return "UNKNOWN";
    }
}




// Enum for format specifiers
enum class FormatSpecifier {
    INTEGER_SIGNED_DECIMAL,       // %d or %i
    INTEGER_UNSIGNED_DECIMAL,     // %u
    INTEGER_OCTAL,                // %o
    INTEGER_HEXADECIMAL_LOWER,    // %x
    INTEGER_HEXADECIMAL_UPPER,    // %X
    FLOAT_DECIMAL,                // %f or %F
    FLOAT_EXPONENTIAL_LOWER,      // %e
    FLOAT_EXPONENTIAL_UPPER,      // %E
    FLOAT_SHORTEST_LOWER,         // %g
    FLOAT_SHORTEST_UPPER,         // %G
    CHARACTER,                    // %c
    STRING,                       // %s
    POINTER,                      // %p
    PERCENT_SIGN,                 // %%
    CUSTOM_UNKNOWN                // For undefined or unsupported specifiers
};

// Convert format specifier enum to string
std::string to_string(FormatSpecifier specifier) {
    switch (specifier) {
        case FormatSpecifier::INTEGER_SIGNED_DECIMAL:   return "INTEGER_SIGNED_DECIMAL";
        case FormatSpecifier::INTEGER_UNSIGNED_DECIMAL: return "INTEGER_UNSIGNED_DECIMAL";
        case FormatSpecifier::INTEGER_OCTAL:            return "INTEGER_OCTAL";
        case FormatSpecifier::INTEGER_HEXADECIMAL_LOWER:return "INTEGER_HEXADECIMAL_LOWER";
        case FormatSpecifier::INTEGER_HEXADECIMAL_UPPER:return "INTEGER_HEXADECIMAL_UPPER";
        case FormatSpecifier::FLOAT_DECIMAL:            return "FLOAT_DECIMAL";
        case FormatSpecifier::FLOAT_EXPONENTIAL_LOWER:  return "FLOAT_EXPONENTIAL_LOWER";
        case FormatSpecifier::FLOAT_EXPONENTIAL_UPPER:  return "FLOAT_EXPONENTIAL_UPPER";
        case FormatSpecifier::FLOAT_SHORTEST_LOWER:     return "FLOAT_SHORTEST_LOWER";
        case FormatSpecifier::FLOAT_SHORTEST_UPPER:     return "FLOAT_SHORTEST_UPPER";
        case FormatSpecifier::CHARACTER:                return "CHARACTER";
        case FormatSpecifier::STRING:                   return "STRING";
        case FormatSpecifier::POINTER:                  return "POINTER";
        case FormatSpecifier::PERCENT_SIGN:             return "PERCENT_SIGN";
        case FormatSpecifier::CUSTOM_UNKNOWN:           return "CUSTOM_UNKNOWN";
        default:                                        return "UNKNOWN";
    }
}





// Enum for length modifiers
enum class LengthModifier {
    NONE,         // No length modifier
    SHORT,        // 'h'
    CHAR,         // 'hh'
    LONG,         // 'l'
    LONG_LONG,    // 'll'
    LONG_DOUBLE,  // 'L'
    SIZE_T,       // 'z'
    PTRDIFF_T,    // 't'
    MAX_T,        // 'j'
    CUSTOM_UNKNOWN // Unknown or unsupported length modifier
};

// Convert length modifier enum to string
std::string to_string(LengthModifier modifier) {
    switch (modifier) {
        case LengthModifier::NONE:           return "NONE";
        case LengthModifier::SHORT:          return "SHORT ('h')";
        case LengthModifier::CHAR:           return "CHAR ('hh')";
        case LengthModifier::LONG:           return "LONG ('l')";
        case LengthModifier::LONG_LONG:      return "LONG_LONG ('ll')";
        case LengthModifier::LONG_DOUBLE:    return "LONG_DOUBLE ('L')";
        case LengthModifier::SIZE_T:         return "SIZE_T ('z')";
        case LengthModifier::PTRDIFF_T:      return "PTRDIFF_T ('t')";
        case LengthModifier::MAX_T:          return "MAX_T ('j')";
        case LengthModifier::CUSTOM_UNKNOWN: return "CUSTOM_UNKNOWN";
        default:                             return "UNKNOWN";
    }
}





// Function to parse a non-negative integer from char*
unsigned long parse_decimal_integer(const char* input) 
{
    
    if (!input) return 0; // Return 0 for null input
    
    unsigned long result = 0;

    while ( *input && std::isdigit(*input) ) 
    {
        result = result * 10 + (*input - '0');
        ++input;
    }

    return result;
}

// Function to write an integer into a buffer with arbitrary radix
void integer_to_string(int value, char buffer[100], int radix) {
    if (radix < 2 || radix > 36) {
        buffer[0] = '\0'; // Invalid radix
        return;
    }

    const char* digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    
    if (value == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }

    bool isNegative = (value < 0 && radix == 10);
    unsigned int absValue = (value < 0) ? -value : value;

    char temp[100];
    int index = 0;

    while (absValue > 0) {
        temp[index++] = digits[absValue % radix];
        absValue /= radix;
    }

    if (isNegative) temp[index++] = '-';

    int bufferIndex = 0;
    for (int i = index - 1; i >= 0; --i) buffer[bufferIndex++] = temp[i];

    buffer[bufferIndex] = '\0';
}



int my_snprintf(char* buffer, size_t n, const char* format, ...) {
    // Initialize the variable argument list
    va_list args;
    va_start(args, format);

    size_t buffer_index = 0; // Tracks the current index in the buffer
    const char* current = format;

    while (*current != '\0') {
        if (*current == '%') {
            ++current; // Advance past '%'

            if (*current == '%') {
                // Handle "%%": Output a literal '%'
                if (buffer_index < n - 1) {
                    buffer[buffer_index] = '%';
                }
                ++buffer_index;
                ++current;
            } else {
                // Unsupported specifier (for now, we ignore it)
                ++current;
            }
        } else {
            // Handle normal characters
            if (buffer_index < n - 1) {
                buffer[buffer_index] = *current;
            }
            ++buffer_index;
            ++current;
        }
    }

    // Null-terminate the buffer if space is available
    if (n > 0) {
        buffer[std::min(buffer_index, n - 1)] = '\0';
    }

    va_end(args);

    // Return the total number of characters that would have been written
    return static_cast<int>(buffer_index);
}




// Main function to test the functionality
int main() {
    
    // Testing enums
    std::cout << "FormatSpecifier: " << to_string(FormatSpecifier::INTEGER_SIGNED_DECIMAL) << "\n";
    std::cout << "FormatFlag: " << to_string(FormatFlag::PLUS) << "\n";
    std::cout << "LengthModifier: " << to_string(LengthModifier::LONG_LONG) << "\n";

    // Testing parse_decimal_integer
    const char* testInput = "12345abc";
    std::cout << "Parsed integer: " << parse_decimal_integer(testInput) << "\n";

    // Testing integer_to_string
    {
        char buffer[100];
        integer_to_string(12345, buffer, 10);
        std::cout << "12345 in base 10: " << buffer << "\n";
        integer_to_string(255, buffer, 16);
        std::cout << "255 in base 16: " << buffer << "\n";
        integer_to_string(-12345, buffer, 10);
        std::cout << "-12345 in base 10: " << buffer << "\n";
    }
    
    {
        char buffer[100];
    
        // Test cases
        my_snprintf(buffer, sizeof(buffer), "This is a test: %%");
        printf("Buffer: %s\n", buffer); // Expected: "This is a test: %"
    
        my_snprintf(buffer, sizeof(buffer), "%%%%%%");
        printf("Buffer: %s\n", buffer); // Expected: "%%%"
        
        my_snprintf(buffer, 5, "A%%B%%C%%");
        printf("Buffer (truncated): %s\n", buffer); // Expected: "A%B" // TODO: Fix behavior
    }

    return 0;
}
