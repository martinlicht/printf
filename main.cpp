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


#include <cstdarg>
#include <cstdio>
#include <cstddef>
#include <algorithm>





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
enum class SizeSpecifier {
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
    SizeSpecifier size = SizeSpecifier::NONE;

    // Conversion specifier
    ConversionSpecifier conversion = ConversionSpecifier::NONE;
    
    FormatSpecifier(
        bool leftAlign = false,
        bool showSign = false,
        bool spaceBeforePositive = false,
        bool alternateForm = false,
        bool zeroPadding = false,
        int width = -1,                        // Default: not specified
        int precision = -1,                    // Default: not specified
        SizeSpecifier size = SizeSpecifier::NONE,
        ConversionSpecifier conversion = ConversionSpecifier::NONE
    ) 
        : leftAlign(leftAlign),
          showSign(showSign),
          spaceBeforePositive(spaceBeforePositive),
          alternateForm(alternateForm),
          zeroPadding(zeroPadding),
          width(width),
          precision(precision),
          size(size),
          conversion(conversion) {}
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
std::string to_string(SizeSpecifier modifier) {
    switch (modifier) {
        case SizeSpecifier::NONE:           return "NONE";
        case SizeSpecifier::SHORT:          return "SHORT ('h')";
        case SizeSpecifier::CHAR:           return "CHAR ('hh')";
        case SizeSpecifier::LONG:           return "LONG ('l')";
        case SizeSpecifier::LONG_LONG:      return "LONG_LONG ('ll')";
        case SizeSpecifier::LONG_DOUBLE:    return "LONG_DOUBLE ('L')";
        case SizeSpecifier::SIZE_T:         return "SIZE_T ('z')";
        case SizeSpecifier::PTRDIFF_T:      return "PTRDIFF_T ('t')";
        case SizeSpecifier::MAX_T:          return "MAX_T ('j')";
        case SizeSpecifier::CUSTOM_UNKNOWN: return "CUSTOM_UNKNOWN";
        default:                           return "UNKNOWN";
    }
}

// Utility function for debugging: Print a FormatSpecifier
std::string to_string(const FormatSpecifier& fs) {
    std::stringstream ss;
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
    return ss.str();
}














// Function to parse a non-negative integer from char*
const char* parse_unsigned_decimal_integer( const char* input, unsigned long* result ) 
{
    
    assert( input ); // Return 0 for null input
    assert( result );
    
    while ( *input && std::isdigit(*input) ) 
    {
        *result = *result * 10 + ( *input - '0' );
        ++input;
    }

    return input;
}













// Function to parse a format specifier
FormatSpecifier readFormatSpecifier(const char** format, va_list args) {
    FormatSpecifier fs;

    const char* current = *format;

    // 1. Parse flags
    while (*current == '-' || *current == '+' || *current == ' ' || *current == '#' || *current == '0') {
        switch (*current) {
            case '-': fs.leftAlign = true; break;
            case '+': fs.showSign = true; break;
            case ' ': fs.spaceBeforePositive = true; break;
            case '#': fs.alternateForm = true; break;
            case '0': fs.zeroPadding = true; break;
        }
        ++current;
    }

    // 2. Parse width
    if (std::isdigit(*current)) {
        fs.width = std::strtol(current, const_cast<char**>(&current), 10);
    } else if (*current == '*') {
        fs.width = va_arg(args, int);
        ++current;
    }

    // 3. Parse precision
    if (*current == '.') {
        ++current; // Skip '.'
        if (std::isdigit(*current)) {
            fs.precision = std::strtol(current, const_cast<char**>(&current), 10);
        } else if (*current == '*') {
            fs.precision = va_arg(args, int);
            ++current;
        } else {
            fs.precision = 0; // Default precision if only '.' is present
        }
    }

    // 4. Parse size specifier
    if (*current == 'h') {
        ++current;
        if (*current == 'h') {
            fs.size = SizeSpecifier::CHAR;
            ++current;
        } else {
            fs.size = SizeSpecifier::SHORT;
        }
    } else if (*current == 'l') {
        ++current;
        if (*current == 'l') {
            fs.size = SizeSpecifier::LONG_LONG;
            ++current;
        } else {
            fs.size = SizeSpecifier::LONG;
        }
    } else if (*current == 'L') {
        fs.size = SizeSpecifier::LONG_DOUBLE;
        ++current;
    } else if (*current == 'z') {
        fs.size = SizeSpecifier::SIZE_T;
        ++current;
    } else if (*current == 't') {
        fs.size = SizeSpecifier::PTRDIFF_T;
        ++current;
    } else if (*current == 'j') {
        fs.size = SizeSpecifier::MAX_T;
        ++current;
    }

    // 5. Parse conversion specifier
    switch (*current) {
        case 'd': case 'i': fs.conversion = ConversionSpecifier::INTEGER_SIGNED_DECIMAL;; break;
        case 'o': fs.conversion = ConversionSpecifier::INTEGER_OCTAL; break;
        case 'x': fs.conversion = ConversionSpecifier::INTEGER_HEXADECIMAL_LOWER; break;
        case 'X': fs.conversion = ConversionSpecifier::INTEGER_HEXADECIMAL_UPPER; break;
        case 'f': fs.conversion = ConversionSpecifier::FLOAT_DECIMAL; break;
        case 'e': fs.conversion = ConversionSpecifier::FLOAT_EXPONENTIAL_LOWER; break;
        case 'E': fs.conversion = ConversionSpecifier::FLOAT_EXPONENTIAL_UPPER; break;
        case 'g': fs.conversion = ConversionSpecifier::FLOAT_SHORTEST_LOWER; break;
        case 'G': fs.conversion = ConversionSpecifier::FLOAT_SHORTEST_UPPER; break;
        case 'c': fs.conversion = ConversionSpecifier::CHARACTER; break;
        case 's': fs.conversion = ConversionSpecifier::STRING; break;
        case 'p': fs.conversion = ConversionSpecifier::POINTER; break;
        case '%': fs.conversion = ConversionSpecifier::PERCENT_SIGN; break;
        default: fs.conversion = ConversionSpecifier::NONE; break;
    }
    if (fs.conversion != ConversionSpecifier::NONE) {
        ++current;
    }

    // Update the input pointer to reflect the consumed characters
    *format = current;

    return fs;
}



// Function to write an integer into a buffer with arbitrary radix
void integer_to_string(int value, char buffer[100], int radix) {
    if( radix < 2 || radix > 36) {
        buffer[0] = '\0'; // Invalid radix
        return;
    }

    const char* digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    
    if( value == 0) {
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

    if( isNegative) temp[index++] = '-';

    int bufferIndex = 0;
    for (int i = index - 1; i >= 0; --i) buffer[bufferIndex++] = temp[i];

    buffer[bufferIndex] = '\0';
}



// Core function taking a va_list
int my_vsnprintf( char* buffer, size_t n, const char* format, va_list args ) 
{
    
    size_t buffer_index = 0; // Tracks the current index in the buffer. Number of characters written 
    const char* current = format;

    while( *current != '\0' ) 
    {
        if( *current == '%') {
            
            ++current; // Advance past '%'

            if( *current == '%') {
                
                // Handle "%%": Output a literal '%'
                if( buffer_index < n - 1) {
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
            if( buffer_index < n - 1) {
                buffer[buffer_index] = *current;
            }
    
            ++buffer_index;
            ++current;
        }
    }

    // Null-terminate the buffer if space is available
    if( n > 0) {
        buffer[std::min(buffer_index, n - 1)] = '\0';
    }

    // Return the total number of characters that would have been written
    return static_cast<int>(buffer_index);
}

// Wrapper function taking variadic arguments
int my_snprintf(char* buffer, size_t n, const char* format, ...) {
    va_list args;
    va_start(args, format);                      // Initialize the variable argument list
    int result = my_vsnprintf(buffer, n, format, args); // Forward to the core function
    va_end(args);                                // Clean up
    return result;
}





int my_vsnprintf2(char *buffer, size_t n, const char *format, va_list args) {
    size_t i = 0;   // Index for format string
    size_t j = 0;   // Index for output buffer
    char c;

    // Loop over the format string
    while ((c = format[i++]) != '\0') {
        // Assert no percentage signs
        assert(c != '%' && "Format specifiers are not supported in this implementation!");

        // Write the character to the buffer if there is space
        if( j + 1 < n) { // Reserve space for the null terminator
            buffer[j++] = c;
        }
    }

    // Null-terminate the buffer if space is available
    if( n > 0) {
        buffer[j < n ? j : n - 1] = '\0';
    }

    // Return the total number of characters that would have been written
    return j;
}




void WriteFormatted ( const char * format1, const char * format2, ... )
{
  va_list args;
  va_list args2;
  
  va_start (args, format2);
  
  vprintf (format1, args);
  
  va_copy( args2, args );
  
  vprintf (format2, args );
  va_end (args);
  
  vprintf (format2, args2 );
  va_end (args2);
  
}


















// Function to format output based on FormatSpecifier
int format_with_specifier(char* buffer, size_t n, const FormatSpecifier& fs, va_list args) {
    int written = 0;

    if (n == 0) {
        return 0; // No buffer space available
    }

    // Temporary buffer for formatted output
    char temp[1024]; // Large enough to hold intermediate data
    temp[0] = '\0';  // Ensure null-termination

    // Handle different conversion specifiers
    switch (fs.conversion) {
        case ConversionSpecifier::INTEGER_SIGNED_DECIMAL: {
            int value = va_arg(args, int); // Get the next integer argument
            if (fs.showSign && value >= 0) {
                snprintf(temp, sizeof(temp), "+%d", value);
            } else if (fs.spaceBeforePositive && value >= 0) {
                snprintf(temp, sizeof(temp), " %d", value);
            } else {
                snprintf(temp, sizeof(temp), "%d", value);
            }
            break;
        }
        case ConversionSpecifier::INTEGER_HEXADECIMAL_LOWER: {
            unsigned int value = va_arg(args, unsigned int);
            if (fs.alternateForm) {
                snprintf(temp, sizeof(temp), "0x%x", value);
            } else {
                snprintf(temp, sizeof(temp), "%x", value);
            }
            break;
        }
        case ConversionSpecifier::STRING: {
            const char* value = va_arg(args, const char*);
            if (!value) {
                value = "(null)";
            }
            snprintf(temp, sizeof(temp), "%.*s", fs.precision >= 0 ? fs.precision : (int)strlen(value), value);
            break;
        }
        case ConversionSpecifier::CHARACTER: {
            char value = (char)va_arg(args, int); // Characters are passed as int
            snprintf(temp, sizeof(temp), "%c", value);
            break;
        }
        case ConversionSpecifier::PERCENT_SIGN: {
            snprintf(temp, sizeof(temp), "%%");
            break;
        }
        default: {
            snprintf(temp, sizeof(temp), "[unsupported]");
            break;
        }
    }

    // Handle width and alignment
    char formatted[1024]; // Final formatted string
    if (fs.width > 0) {
        if (fs.leftAlign) {
            snprintf(formatted, sizeof(formatted), "%-*s", fs.width, temp);
        } else {
            snprintf(formatted, sizeof(formatted), "%*s", fs.width, temp);
        }
    } else {
        strncpy(formatted, temp, sizeof(formatted) - 1);
        formatted[sizeof(formatted) - 1] = '\0';
    }

    // Write to the buffer
    strncpy(buffer, formatted, n - 1);
    buffer[n - 1] = '\0'; // Null-terminate
    written = strlen(formatted);

    return written;
}











// Main function to test the functionality
int main() {
    
    {
       WriteFormatted ( "Call with %d variable argument.\n", "Call with %d variable %s.\n", 1, 2, "arguments" );
    }
    
    {
        char buffer[50];
        int written;
    
        // Test case 1: Normal string without %
        written = my_snprintf(buffer, sizeof(buffer), "Hello, World!");
        printf("Buffer: %s\n", buffer);
        printf("Characters Written: %d\n", written);
    
        // Test case 2: Literal %%
        written = my_snprintf(buffer, sizeof(buffer), "Progress: 50%% complete.");
        printf("Buffer: %s\n", buffer);
        printf("Characters Written: %d\n", written);
    
        // Test case 3: Truncation
        written = my_snprintf(buffer, 6, "Hello, World!");
        printf("Buffer (truncated): %s\n", buffer);
        printf("Characters Written: %d\n", written);
    
    }

    {
        char buffer[50];
        FormatSpecifier fs;
    
        // Test case 1: Integer with sign
        fs = FormatSpecifier{false, true, false, false, false, 10, -1, SizeSpecifier::NONE, ConversionSpecifier::INTEGER_SIGNED_DECIMAL};
        va_list args;
        // va_start(args, fs); // Start with an integer (test value: 42)
        int written = format_with_specifier(buffer, sizeof(buffer), fs, NULL );
        // va_end(args);
        printf("Buffer: %s (Written: %d)\n", buffer, written);
    
        // Test case 2: Hexadecimal with alternate form
        fs = {false, false, false, true, false, 10, -1, SizeSpecifier::NONE, ConversionSpecifier::INTEGER_HEXADECIMAL_LOWER};
        // va_start(args, fs); // Start with an unsigned integer (test value: 255)
        written = format_with_specifier(buffer, sizeof(buffer), fs, NULL );
        // va_end(args);
        printf("Buffer: %s (Written: %d)\n", buffer, written);
    
        // Test case 3: String with precision
        fs = {false, false, false, false, false, 15, 5, SizeSpecifier::NONE, ConversionSpecifier::STRING};
        // va_start(args, fs); // Start with a string (test value: "Hello, World!")
        written = format_with_specifier(buffer, sizeof(buffer), fs, NULL );
        // va_end(args);
        printf("Buffer: %s (Written: %d)\n", buffer, written);
    
        // Test case 4: Character
        fs = {false, false, false, false, false, 5, -1, SizeSpecifier::NONE, ConversionSpecifier::CHARACTER};
        // va_start(args, fs); // Start with a char (test value: 'A')
        written = format_with_specifier(buffer, sizeof(buffer), fs, NULL );
        // va_end(args);
        printf("Buffer: %s (Written: %d)\n", buffer, written);
    }
    
    {
        // Testing enums
        std::cout << "FormatFlag: " << to_string(FormatFlag::PLUS) << "\n";
        std::cout << "SizeSpecifier: " << to_string(SizeSpecifier::LONG_LONG) << "\n";
        std::cout << "ConversionSpecifier: " << to_string(ConversionSpecifier::INTEGER_SIGNED_DECIMAL) << "\n";

        FormatSpecifier fs;
        fs.leftAlign = true;
        fs.zeroPadding = true;
        fs.width = 10;
        fs.precision = 2;
        fs.size = SizeSpecifier::LONG;
        fs.conversion = ConversionSpecifier::INTEGER_UNSIGNED_DECIMAL;

        std::cout << "FormatSpecifier: " << to_string(fs) << "\n";
    }

    
    {
        const char* format = "%-+ #015.8lld";
        va_list args; // Dummy va_list for this example
    
        FormatSpecifier fs = readFormatSpecifier(&format, args);
    
        std::cout << to_string(fs) << std::endl;
        
    }

    // Testing parse_unsigned_decimal_integer
    // Testing integer_to_string
    {
        const char* testInput = "12345abc";
        unsigned long int result;
        parse_unsigned_decimal_integer( testInput, &result );
        std::cout << "Parsed integer: " << result << "\n";

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
        written = my_vsnprintf2(buffer, sizeof(buffer), "Hello, World!", NULL);
        std::cout << "TEST" << std::endl;
        printf("Buffer: %s\n", buffer);
        printf("Characters Written: %d\n", written);
        
        // Test case 2: Buffer too small
        written = my_vsnprintf2(buffer, 6, "Hello, World!", NULL);
        printf("Buffer (truncated): %s\n", buffer);
        printf("Characters Written: %d\n", written);
    
        // Test case 3: String with a percentage (should trigger assert)
        // Uncomment to test assertion failure
        // written = vsnprintf(buffer, sizeof(buffer), "Hello, %s!", NULL);
    }
    

    return 0;
}
