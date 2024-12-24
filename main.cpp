#include <cstdarg>
#include <cstring> // For size_t

#include <iostream>
#include <sstream>
#include <cctype>
#include <cstring>

#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <assert.h>






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



// Enum for conversion specifiers
enum class ConversionSpecifier {
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
    NONE,                         // None given 
    CUSTOM_UNKNOWN                // For undefined or unsupported specifiers
};

// Enum for length modifiers
enum class SizeModifier {
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

struct FormatSpecifier {
    // Boolean flags
    bool leftAlign           = false; // '-' flag
    bool showSign            = false; // '+' flag
    bool spaceBeforePositive = false; // ' ' flag
    bool alternateForm       = false; // '#' flag
    bool zeroPadding         = false; // '0' flag

    // Width and precision
    int width     = -1;        // Width (-1 means not specified)
    int precision = -1;        // Precision (-1 means not specified)

    // Size specifier
    SizeModifier size = SizeModifier::NONE;

    // Conversion specifier
    ConversionSpecifier conversion = ConversionSpecifier::NONE;
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

// Convert conversion specifier enum to string
std::string to_string(ConversionSpecifier specifier) {
    switch (specifier) {
        case ConversionSpecifier::INTEGER_SIGNED_DECIMAL:   return "INTEGER_SIGNED_DECIMAL";
        case ConversionSpecifier::INTEGER_UNSIGNED_DECIMAL: return "INTEGER_UNSIGNED_DECIMAL";
        case ConversionSpecifier::INTEGER_OCTAL:            return "INTEGER_OCTAL";
        case ConversionSpecifier::INTEGER_HEXADECIMAL_LOWER:return "INTEGER_HEXADECIMAL_LOWER";
        case ConversionSpecifier::INTEGER_HEXADECIMAL_UPPER:return "INTEGER_HEXADECIMAL_UPPER";
        case ConversionSpecifier::FLOAT_DECIMAL:            return "FLOAT_DECIMAL";
        case ConversionSpecifier::FLOAT_EXPONENTIAL_LOWER:  return "FLOAT_EXPONENTIAL_LOWER";
        case ConversionSpecifier::FLOAT_EXPONENTIAL_UPPER:  return "FLOAT_EXPONENTIAL_UPPER";
        case ConversionSpecifier::FLOAT_SHORTEST_LOWER:     return "FLOAT_SHORTEST_LOWER";
        case ConversionSpecifier::FLOAT_SHORTEST_UPPER:     return "FLOAT_SHORTEST_UPPER";
        case ConversionSpecifier::CHARACTER:                return "CHARACTER";
        case ConversionSpecifier::STRING:                   return "STRING";
        case ConversionSpecifier::POINTER:                  return "POINTER";
        case ConversionSpecifier::PERCENT_SIGN:             return "PERCENT_SIGN";
        case ConversionSpecifier::NONE:                     return "NONE";
        case ConversionSpecifier::CUSTOM_UNKNOWN:           return "CUSTOM_UNKNOWN";
        default:                                            return "UNKNOWN";
    }
}

// Convert length modifier enum to string
std::string to_string(SizeModifier modifier) {
    switch (modifier) {
        case SizeModifier::NONE:           return "NONE";
        case SizeModifier::SHORT:          return "SHORT ('h')";
        case SizeModifier::CHAR:           return "CHAR ('hh')";
        case SizeModifier::LONG:           return "LONG ('l')";
        case SizeModifier::LONG_LONG:      return "LONG_LONG ('ll')";
        case SizeModifier::LONG_DOUBLE:    return "LONG_DOUBLE ('L')";
        case SizeModifier::SIZE_T:         return "SIZE_T ('z')";
        case SizeModifier::PTRDIFF_T:      return "PTRDIFF_T ('t')";
        case SizeModifier::MAX_T:          return "MAX_T ('j')";
        case SizeModifier::CUSTOM_UNKNOWN: return "CUSTOM_UNKNOWN";
        default:                           return "UNKNOWN";
    }
}

// Utility function for debugging: Print a FormatSpecifier
std::to_string to_string(const FormatSpecifier& fs) {
    sstream ss;
    ss << "Flags:\n";
    ss << "\t  Left Align (-): " << (fs.leftAlign ? "true" : "false") << "\n";
    ss << "\t  Show Sign (+): " << (fs.showSign ? "true" : "false") << "\n";
    ss << "\t  Space Before Positive ( ): " << (fs.spaceBeforePositive ? "true" : "false") << "\n";
    ss << "\t  Alternate Form (#): " << (fs.alternateForm ? "true" : "false") << "\n";
    ss << "\t  Zero Padding (0): " << (fs.zeroPadding ? "true" : "false") << "\n";
    ss << "\t  Width: " << (fs.width >= 0 ? std::to_string(fs.width) : "not specified") << "\n";
    ss << "\t  Precision: " << (fs.precision >= 0 ? std::to_string(fs.precision) : "not specified") << "\n";
    ss << "\t  Size Specifier: " << to_string( fs.size ) << "\n";
    ss << "\t  Conversion Specifier: " << to_string( fs.conversion ) << "\n";
    return ss.to_string();
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




int my_vsnprintf(char *buffer, size_t n, const char *format, va_list args) {
    size_t i = 0;   // Index for format string
    size_t j = 0;   // Index for output buffer
    char c;

    // Loop over the format string
    while ((c = format[i++]) != '\0') {
        // Assert no percentage signs
        assert(c != '%' && "Format specifiers are not supported in this implementation!");

        // Write the character to the buffer if there is space
        if (j + 1 < n) { // Reserve space for the null terminator
            buffer[j++] = c;
        }
    }

    // Null-terminate the buffer if space is available
    if (n > 0) {
        buffer[j < n ? j : n - 1] = '\0';
    }

    // Return the total number of characters that would have been written
    return j;
}




// Main function to test the functionality
int main() {
    
    // Testing enums
    std::cout << "ConversionSpecifier: " << to_string(ConversionSpecifier::INTEGER_SIGNED_DECIMAL) << "\n";
    std::cout << "FormatFlag: " << to_string(FormatFlag::PLUS) << "\n";
    std::cout << "SizeModifier: " << to_string(SizeModifier::LONG_LONG) << "\n";

    // Testing parse_decimal_integer
    const char* testInput = "12345abc";
    std::cout << "Parsed integer: " << parse_decimal_integer(testInput) << "\n";

    {
        FormatSpecifier fs;
        fs.leftAlign = true;
        fs.zeroPadding = true;
        fs.width = 10;
        fs.precision = 2;
        fs.size = SizeModifier::LONG;
        fs.conversion = ConversionSpecifier::INTEGER_UNSIGNED_DECIMAL;

        std::cout << "FormatSpecifier: " << to_string(fs) << "\n";
    }

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
    
    {
        char buffer[14];
        int written;
    
        // Test case 1: Normal string without %
        written = my_vsnprintf(buffer, sizeof(buffer), "Hello, World!", NULL);
        std::cout << "TEST" << std::endl;
        printf("Buffer: %s\n", buffer);
        printf("Characters Written: %d\n", written);
        
        // Test case 2: Buffer too small
        written = my_vsnprintf(buffer, 6, "Hello, World!", NULL);
        printf("Buffer (truncated): %s\n", buffer);
        printf("Characters Written: %d\n", written);
    
        // Test case 3: String with a percentage (should trigger assert)
        // Uncomment to test assertion failure
        // written = vsnprintf(buffer, sizeof(buffer), "Hello, %s!", NULL);
    }
    

    return 0;
}
