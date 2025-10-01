# PA1 - UTF-8:

## Due Date: Thursday 10/9 at 11:59pm

## UTF-8

Representing text is straightforward using ASCII: one byte per character fits well within `char[]` and it represents most English text. However, there are many more than 256 characters in the text we use, from non-Latin alphabets (Cyrillic, Arabic, and Chinese character sets, etc.) to emojis and other symbols like €, to accented characters like é and ü.

The [UTF-8 encoding](https://en.wikipedia.org/wiki/UTF-8#Encoding) is the default encoding of text in the majority of software today.
If you've opened a web page, read a text message, or sent an email [in the past 15 years](https://en.wikipedia.org/wiki/UTF-8#/media/File:Unicode_Web_growth.svg) that had any special characters, the text was probably UTF-8 encoded.

Not all software handles UTF-8 correctly! For example, Joe got a marketing email recently with a header “Take your notes further with Connectâ€‹” We're guessing that was supposed to be an ellipsis (…), [UTF-8 encoded as the three bytes 0x11100010 0x10000000 0x10100110](https://www.compart.com/en/unicode/U+2026), and likely the software used to author the email mishandled the encoding and treated it as [three extended ASCII characters](https://en.wikipedia.org/wiki/Extended_ASCII).

This can cause serious problems for real people. For example, people with accented letters in their names can run into issues with sign-in forms (check out Twitter/X account [@yournameisvalid](https://x.com/yournameisvalid?lang=en) for some examples). People with names best written in an alphabet other than Latin can have their names mangled in official documents, and need to have a "Latinized" version of their name for business in the US. Joe had trouble [writing lecture notes](https://x.com/JoePolitz/status/1841175066845069552) because LaTeX does not support UTF-8 by default.

UTF-8 bugs can and do cause security vulnerabities in products we use every day. A simple search for UTF-8 in the CVE database of security vulnerabilities turns up [hundreds of results](https://cve.mitre.org/cgi-bin/cvekey.cgi?keyword=utf-8).

It's useful to get some experience with UTF-8 so you understand how it's supposed to work and can recognize when it doesn't.
To that end, you'll write several functions that work with UTF-8 encoded text, and use them to analyze some example texts.

## Getting Started

To get started, visit the [Github Classroom](https://classroom.github.com/a/Op6LmSos) assignment link. Select your username from the list (or if you don't see it, you can skip and use your Github username). A repository will be created for you to use to to your work. You can do your programming however you like; a Codespace will keep you in the environment we are using in class and lab.

## Milestones, Working Process, and Definitions

The functions described below are organized into milestones; you should definitely finish the functions in a milestone set before moving onto the next.

In general, you should work one function at a time, and earlier functions may be useful in implementing later functions.

A good first task is to implement _only_ `is_ascii` and the corresponding part of `main` needed to read input and print the result for `is_ascii`, and make sure you can test that. Then move onto `capitalize_ascii`, and so on.

You can and should save your work by using `git` commits (if you're comfortable with that), or even just saving copies of your `.c` file when you hit important milestones. We may ask to see your work from an earlier milestone if you ask us for help on a function from a later one.

Some reminders and information about the function signatures:

- `int32_t` is a 32-bit (4-byte) integer. You can think of it like `int` in Java, we just want to be explicit about sizes of things when we program in C, and `int` can mean different things on different systems. This type is defined in `stdint.h`, so `#include <stdint.h>` at the top of a program will make it usable.
- We use `cpi` as an abbreviation in some variable names, it stands for “code point index”.
- We use `bi` as an abbreviation in some variable names, it stands for “byte index”.

## Functions - Milestone 1

### `int32_t is_ascii(char str[])`

Takes a UTF-8 encoded string and returns if it is valid ASCII (e.g. all bytes are 127 or less).

#### Example Usage:

```
printf("Is 🔥 ASCII? %d\n", is_ascii("🔥"));

=== Output ===
Is 🔥 ASCII? 0

printf("Is abcd ASCII? %d\n", is_ascii("abcd"));

=== Output ===
Is abcd ASCII? 1
```

> 💡 **Hint:** Look at Problem Set: **_HW1.15. is_ascii_**

### `int32_t capitalize_ascii(char str[])`

Takes a UTF-8 encoded string and _changes_ it in-place so that any ASCII lowercase characters `a`-`z` are changed to their uppercase versions. Leaves all other characters unchanged. It returns the number of characters updated from lowercase to uppercase.

#### Example Usage:

```
int32_t ret = 0;
char str[] = "abcdé";
ret = capitalize_ascii(str);
printf("Capitalized String: %s\nCharacters updated: %d\n", str, ret);`

=== Output ===
Capitalized String: ABCDé
Characters updated: 4
```

> 💡 **Hint:** Look at Problem Set: **_HW1.13. capitalize_ascii_**

## Functions - Milestone 2

### `int32_t width_from_start_byte(char start_byte)`

Given the start byte of a UTF-8 sequence, return how many bytes it indicates the sequence will take (start byte + continuation bytes).

Returns 1 for ASCII characters, and -1 if byte is not a valid start byte.

#### Example Usage:

```
char s[] = "Héy"; // same as { 'H', 0xC3, 0xA9, 'y', 0 },   é is start byte + 1 cont. byte
printf("Width: %d bytes\n", width_from_start_byte(s[1])); // start byte 0xC3 indicates 2-byte sequence

=== Output ===
Width: 2 bytes

printf("Width: %d bytes\n", width_from_start_byte(s[2])); // start byte 0xA9 is a continuation byte, not a start byte

=== Output ===
Width: -1
```

> 💡 **Hint:** Look at Problem Set: **_HW1.16. UTF8 Codepoint Size_**

### `int32_t utf8_strlen(char str[])`

Takes a UTF-8 encoded string and returns the number of UTF-8 codepoints it represents.

Returns -1 if there are any errors encountered in processing the UTF-8 string.

#### Example Usage:

```
char str[] = "Joséph";
printf("Length of string %s is %d\n", str, utf8_strlen(str));  // 6 codepoints, (even though 7 bytes)

=== Output ===
Length of string Joséph is 6
```

> 💡 **Hint:** Look at Problem Set: **_HW1.17. Count UTF-8 String Length_**

### `int32_t codepoint_index_to_byte_index(char str[], int32_t cpi)`

Given a UTF-8 encoded string, and a codepoint index, return the byte index in the string where the Unicode character at the given codepoint index starts.

Returns -1 if there are any errors encountered in processing the UTF-8 string.

#### Example Usage:

```
char str[] = "Joséph";
int32_t idx = 4;
printf("Codepoint index %d is byte index %d\n", idx, codepoint_index_to_byte_index("Joséph", idx));

=== Output ===
Codepoint index 4 is byte index 5
```

> 💡 **Hint:** Look at Problem Set: **_HW1.16. UTF8 Codepoint Size_**

### `void utf8_substring(char str[], int32_t cpi_start, int32_t cpi_end, char result[])`

Takes a UTF-8 encoded string and start(inclusive) and end(exclusive) codepoint indices, and writes the substring between those indices to `result`, with a null terminator. Assumes that `result` has sufficient bytes of space available. (Hint: `result` will be created beforehand with a given size and passed as input here. Can any of the above functions be used to determine what the size of `result` should be?)

If `cpi_start` is greater than `cpi_end` or either is negative, the function should have no effect.

If the end index is larger than the `utf8_strlen` for the string, it should act as if the end index was exactly `utf8_strlen` of the string.

#### Example Usage:

```
char result[17];
utf8_substring("🦀🦮🦮🦀🦀🦮🦮", 3, 7, result)
printf("String: %s\nSubstring: %s", result); // these emoji are 4 bytes long

=== Output ===
String: 🦀🦮🦮🦀🦀🦮🦮
Substring: 🦀🦀🦮🦮
```

> 💡 **Hint:** Look at Problem Set: **_HW1.18. utf8_substring_**

## Functions - Milestone 3

### `int32_t codepoint_at(char str[], int32_t cpi)`

Takes a UTF-8 encoded string and a codepoint index, and returns a decimal representing the codepoint at that index.

#### Example Usage:

```
char str[] = "Joséph";
int32_t idx = 4;
printf("Codepoint at %d in %s is %d\n", idx, str, codepoint_at(str, idx)); // 'p' is the 4th codepoint

=== Output ===
Codepoint at 4 in Joséph is 112
```

> 💡 **Hint:** Look at Problem Set: **_HW1.5. Find UTF-8 Codepoint at Index_**

### `char is_animal_emoji_at(char str[], int32_t cpi)`

Takes a UTF-8 encoded string and an codepoint index, and returns if the code point at that index is an animal emoji.

For simplicity for this question, we will define that that the “animal emojii” are in two ranges: from 🐀 to 🐿️ and from 🦀 to 🦮. (Yes, this technically includes things like 🐽 which are only related to or part of an animal, and excludes a few things like 🙊, 😸, which are animal faces.). You may find the [wikipedia page on Unicode emoji](https://en.wikipedia.org/wiki/List_of_emojis) helpful here.

> 💡 **Hint:** Look at Problem Set: **_HW1.19. is_animal_emoji_at_**

## UTF-8 Analyzer

You'll also write a program that reads UTF-8 input and prints out some information about it.

Here's what the output of a sample run of your program should look like:

```
$ ./utf8analyzer
Enter a UTF-8 encoded string: My 🐩’s name is Erdős.
Valid ASCII: false
Uppercased ASCII:"MY 🐩’S NAME IS ERDőS.
Length in bytes: 27
Number of code points: 21
Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
Substring of the first 6 code points: My 🐩’s
Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
Animal emojis: 🐩
```

You can also test the contents of _files_ by using the `<` operator:

```
$ cat utf8test.txt
My 🐩’s name is Erdős.
$ ./utf8analyzer < utf8test.txt
Enter a UTF-8 encoded string:
Valid ASCII: false
Uppercased ASCII: MY 🐩’S NAME IS ERDőS.
Length in bytes: 27
Number of code points: 21
Bytes per code point: 1 1 1 4 3 1 1 1 1 1 1 1 1 1 1 1 1 1 2 1 1
Substring of the first 6 code points: My 🐩’s
Code points as decimal numbers: 77 121 32 128041 8217 115 32 110 97 109 101 32 105 115 32 69 114 100 337 115 46
Animal emojis: 🐩
```

## Testing

We provide 3 basic tests in the `tests` folder - which contain simple tests for detecting if there are errors in your code while identifying valid ASCII and converting ASCII lowercase to uppercase characters. We have provided a test bash file that checks if your program output contains each line in the .expect file. You can use the following commands to run the tests (You may need to change the permission of the `test_script` file to be executable with the command `chmod u+x test_script`.):

```
gcc *.c -o utfanalyzer // compiles your C code into an executable called utfanalyzer
./test_script utfanalyzer
```

Then it will print out result in your terminal.

You can see the result for a single test by using:

```
./utf8analyzer < test-file
```

Here are some other ideas for tests you should write. They aren't necessarily comprehensive (you should design your own!) but they should get you started. For each of these kinds of strings, you should check how UTF-8 analyzer handles them:

- Strings with a single UTF-8 character that is 1, 2, 3, 4 bytes
- Strings with two UTF-8 characters in all combinations of 1/2/3/4 bytes. (e.g. `"aa"`, `"aá"`, `"áa"`, `"áá"`, and so on)
- Strings with and without animal emojii, including at the beginning, middle, and end of the string, and at the beginning, middle, and end of the range
- Strings of exactly 5 characters

## PA Design Questions

You will answer the following questions **on PrairieLearn** under the assessment `pa1`.

Answer each of these with a few sentences or paragraphs; don't write a whole essay, but use good writing practice to communicate the essence of the idea. A good response doesn't need to be long, but it needs to have attention to detail and be clear. Examples help!

- Another encoding of Unicode is UTF-32, which encodes _all_ Unicode code points in 4 bytes. For things like ASCII, the leading 3 bytes are all 0's. What are some tradeoffs between UTF-32 and UTF-8?

- UTF-8 has a leading `10` on all the bytes past the first for multi-byte code points. This seems wasteful – if the encoding for 3 bytes were instead `1110XXXX XXXXXXXX XXXXXXXX` (where `X` can be any bit), that would fit 20 bits, which is over a million code points worth of space, removing the need for a 4-byte encoding. What are some tradeoffs or reasons the leading `10` might be useful? Can you think of anything that could go wrong with some programs if the encoding didn't include this restriction on multi-byte code points?

## Resources and Policy

Refer to [the policies on assignments](https://ucsd-cse29.github.io/fa25/#assignments-and-academic-integrity) for working with others or appropriate use of tools like ChatGPT or Github Copilot.

You can use any code from class, lab, or discussion in your work.

## What to Hand In

You will submit the files **on PrairieLearn**
- Any `.c` files you wrote (can be one file or many; it's totally reasonable to only have one). We will run `gcc *.c -o utfanalyzer` to compile your code, so you should make sure it works when we do that.
- A zip file named `tests.zip`, containing your tests with expected output in files tests/*.txt, tests/*.txt.expect.

Hand in to the `pa1` assessment on PrairieLearn. The submission system will show you the output of compiling and running your program on the test input described above to make sure the baseline format of your submission works. You will not get feedback about your overall grade before the deadline.
