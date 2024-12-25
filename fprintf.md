### The `fprintf` function

#### Synopsis
```c
#include <stdio.h>
int fprintf(FILE * restrict stream, const char * restrict format, ...);
```

#### Description

The `fprintf` function writes output to the stream pointed to by `stream`, under the control of the string pointed to by `format` that specifies how subsequent arguments are converted for output. 

- If there are insufficient arguments for the format, the behavior is undefined. 
- If the format is exhausted while arguments remain, the excess arguments are evaluated (as always) but are otherwise ignored. 
- The `fprintf` function returns when the end of the format string is encountered.

The `format` shall be a multibyte character sequence, beginning and ending in its initial shift state. The format is composed of zero or more directives:

- Ordinary multibyte characters (not `%`), which are copied unchanged to the output stream.
- Conversion specifications, each of which results in fetching zero or more subsequent arguments, converting them, if applicable, according to the corresponding conversion specifier, and then writing the result to the output stream.

Each conversion specification is introduced by the character `%`. After the `%`, the following appear in sequence:

- **Zero or more flags** (in any order) that modify the meaning of the conversion specification.

- **An optional minimum field width.**  
  If the converted value has fewer characters than the field width, it is padded with spaces (by default) on the left (or right, if the left adjustment flag, described later, has been given) to the field width.  
  The field width takes the form of an asterisk (`*`, described later) or a nonnegative decimal integer. [^321]

- **An optional precision** that gives:
  - The minimum number of digits to appear for the `b`, `B`, `d`, `i`, `o`, `u`, `x`, and `X` conversions.
  - The number of digits to appear after the decimal-point character for the `a`, `A`, `e`, `E`, `f`, and `F` conversions.
  - The maximum number of significant digits for the `g` and `G` conversions.
  - The maximum number of bytes to be written for `s` conversions.  
  If a precision appears with any other conversion specifier, the behavior is undefined.
  The precision takes the form of a period (`.`) followed either by an asterisk (`*`, described later) or by an optional nonnegative decimal integer; if only the period is specified, the precision is taken as zero.  
 
- **An optional length modifier** that specifies the size of the argument.
- **A conversion specifier character** that specifies the type of conversion to be applied.
 

As noted previously, a field width, or precision, or both, may be indicated by an asterisk (`*`). In this case, an `int` argument supplies the field width or precision. 

- The arguments specifying field width, or precision, or both, shall appear (in that order) **before** the argument (if any) to be converted.  
- A negative field width argument is taken as a `-` flag followed by a positive field width.  
- A negative precision argument is taken as if the precision were omitted.



The flag characters and their meanings are:

- `-`  
  The result of the conversion is **left-justified** within the field.  
  *(It is right-justified if this flag is not specified.)*

- `+`  
  The result of a signed conversion always begins with a plus (`+`) or minus (`-`) sign.  
  *(It begins with a sign only when a value with a negative sign is converted if this flag is not specified.)* [^322]

- (space)  
  If the first character of a signed conversion is not a sign, or if a signed conversion results in no characters, a space is prefixed to the result.  
  *(If the space and `+` flags both appear, the space flag is ignored.)*

- `#`  
  The result is converted to an **"alternative form"**:  
  - For `o` conversion, it increases the precision, if and only if necessary, to force the first digit of the result to be a zero.  
    *(If the value and precision are both 0, a single `0` is printed.)*  
  - For `b` conversion, a nonzero result has `0b` prefixed to it.  
  - For the optional `B` conversion, a nonzero result has `0B` prefixed to it.  
  - For `x` (or `X`) conversion, a nonzero result has `0x` (or `0X`) prefixed to it.  
  - For `a`, `A`, `e`, `E`, `f`, `F`, `g`, and `G` conversions, the result of converting a floating-point number always contains a decimal-point character, even if no digits follow it.  
    *(Normally, a decimal-point character appears in the result of these conversions only if a digit follows it.)*  
  - For `g` and `G` conversions, trailing zeros are **not removed** from the result.  
  - For other conversions, the behavior is undefined.

- `0`  
  For `b`, `B`, `d`, `i`, `o`, `u`, `x`, `X`, `a`, `A`, `e`, `E`, `f`, `F`, `g`, and `G` conversions:  
  - Leading zeros (following any indication of sign or base) are used to pad to the field width, rather than performing space padding.  
    *(Except when converting an infinity or NaN.)*  
  - If the `0` and `-` flags both appear, the `0` flag is ignored.  
  - For `b`, `B`, `d`, `i`, `o`, `u`, `x`, and `X` conversions, if a precision is specified, the `0` flag is ignored.  
  - For other conversions, the behavior is undefined.

---

#### Footnotes:
[^322]: The results of all floating conversions of a negative zero, and of negative values that round to zero, include a minus sign.

---

#### Footnotes:
[^319]: The buffer has to have a lifetime at least as great as the open stream, so not closing the stream before a buffer that has automatic storage duration is deallocated upon block exit results in undefined behavior.

[^320]: The `fprintf` functions perform writes to memory for the `%n` specifier.

[^321]: Note that `0` is taken as a flag, not as the beginning of a field width.
