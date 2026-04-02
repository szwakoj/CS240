# Stock Price Analyzer: Dynamic Arrays and Records

## Due Date: 4/7/26

## Description

In this homework you will build a working stock price analyzer in C. You will be given real price data for several stocks and a plotting function that draws charts directly in your terminal. Your job is to implement the data structure and functions that load, store, and analyze that data.

The core challenge is that you do not know how many days of data are in a file before you open it. This is the motivation for a **dynamic array**, a structure that starts small and grows itself as needed at runtime. By the end of this assignment you will have built one from scratch, loaded real financial data into it, and produced terminal visualizations of a full year of price history.

This assignment builds directly on the two lessons covering [records](../lessons/5_data_structs1.md) and [linear data structures](../lessons/6_data_structs2.md). If you are unclear on `struct`, heap allocation, `malloc`, `realloc`, or `free`, re-read those lessons before starting.

---

### Project Structure

```
CS220-HW3-LastName/
├── bin/                # Target directory for compilation
│   ├── stock
│   └── test_stock_array
├── include/
│   └── stock_array.h   # Provided: do not modify
├── src/
│   ├── stock_array.c   # Your implementation this is what you submit
│   ├── main.c          # Provided: your REPL and test driver
│   └── test_stock_array.c  # Provided: your test suite
├── data/
│   └── *.txt           # Provided: stock data files
└── Makefile            # Provided:do not modify
```

All files must compile together with no warnings under:

```bash
make
```

Which runs:

```bash
gcc -Wall -Wextra -std=c11 -Iinclude -o stock src/main.c src/stock_array.c
gcc -Wall -Wextra -std=c11 -Iinclude -o test_stock_array src/test_stock_array.c 
```

Which populates `bin`:
```bash
> ls bin
stock
test_stock_array
> ./bin/stock
```

Download the starting point [here](../homework/HW3_start.zip). You will only write code in `src/stock_array.c` and `src/main.c`. Everything else is provided.

---
###  Provided Test

There is a test program provided to help you along the way. It is made to test the project and give you feedback if any of your functions are not correct. It is meant only to test `stock_array.c`and not `main.c`. You are to use it as the first step after completing your function implementations to see if your code can be used for the terminal tool. The test is made with `make` alongside the main program.

---

### The Data Format

Each `.txt` file in `data/` represents one stock ticker for one year. The format alternates: a date line followed by a price line with four space-separated values; open, high, low, and close for that trading day.

```
2024-01-02
182.45 184.10 181.20 183.00
2024-01-03
179.30 180.50 178.10 179.90
2024-01-04
185.10 186.20 184.80 185.50
```

You do not know how many days are in a file. This is intentional.

---

### The Provided Header

`stock_array.h` declares two structs and ten functions. Read the comment block above every function before you implement it, each one describes exactly what the function must do, what it takes, and what it returns.

### Structs

```c
typedef struct {
    char   date[DATE_LEN];  // "YYYY-MM-DD"
    double high;            // Highest price sample for the day
    double low;             // Lowest price sample for the day
    double avg;             // Average of all samples for the day
} DayRecord;

typedef struct {
    DayRecord* records;     // Heap-allocated array of DayRecords
    size_t     size;        // Number of records currently stored
    size_t     capacity;    // Total slots currently allocated
} StockArray;
```

---

## Part 1: Lifecycle Functions (20 points)

**File:** `src/stock_array.c`

Implement the two functions that create and destroy a `StockArray`.

```c
StockArray sa_create(size_t initial_capacity);
void       sa_destroy(StockArray* sa);
```

**Requirements:**

- `sa_create` must heap-allocate the `records` array with `initial_capacity` slots using `malloc`. Set `size` to 0 and `capacity` to `initial_capacity`.
- `sa_destroy` must free the `records` pointer and set all fields to zero or NULL. Failing to do this is a memory leak.
- After `sa_destroy` is called, the struct must be in a safe zeroed state. Accessing a freed pointer is undefined behavior; setting it to NULL makes any accidental access crash immediately rather than silently corrupt memory.

**Verification:** The first block of `test_stock_array` checks these two functions. All checks in `[ sa_create / sa_destroy ]` must print PASS before moving on.

---

## Part 2: Core Dynamic Array Operations (25 points)

**File:** `src/stock_array.c`

Implement the two fundamental operations on the array.

```c
void      sa_append(StockArray* sa, DayRecord record);
DayRecord sa_get(StockArray* sa, size_t index);
```

### sa_get (5 points)

Returns the record at the given index. You may assume the index is valid. This is one line.

### sa_append (20 points)

Appends a record to the end of the array. This is where the dynamic behavior lives:

- If `size == capacity`, the array is full. Double the capacity and resize the heap allocation using `realloc` before inserting.
- Copy the record into `records[size]` and increment `size`.

**Why doubling?** Doubling the capacity on each resize means resizes happen logarithmically rarely as the array grows. The average cost of an append, spread across all appends including the rare expensive ones, works out to O(1). Growing by a fixed amount instead would make that average O(n). This is called **amortized analysis** and is why doubling specifically is the standard strategy.

**Common mistake:** After calling `realloc`, always use the returned pointer. `realloc` may move the allocation to a new address. If you ignore the return value and keep using the old pointer, your program will corrupt memory silently.

**Verification:** The `[ sa_append / sa_get ]` block in the test suite starts with a capacity of 2 and appends 3 records, forcing a resize on the third. If your data does not survive the resize, the value checks after it will fail.

---

## Part 3: File Loading (25 points)

**File:** `src/stock_array.c`

Implement the function that reads a data file into the array.

```c
int sa_load_data(StockArray* sa, const char* filename);
```

**Requirements:**

- Open the file. If it cannot be opened, return 0 immediately.
- Read the file line by line. Each pair of lines is one day: a date line followed by a price line.
- For each day, parse the four price values (open, high, low, close) from the price line and compute:
    - `high` - the largest of the four values
    - `low` - the smallest of the four values
    - `avg` - the mean of all four values
- Build a `DayRecord` from the date and computed values and append it to the array.
- Return 1 on success.

**Hint:** Use `fgets` to read one line at a time. To parse the four doubles from the price line, `sscanf` with four `%lf` format specifiers is the simplest approach since you know each line always has exactly four values:

```c
double open, high, low, close;
sscanf(price_line, "%lf %lf %lf %lf", &open, &high, &low, &close);
```

**Common mistake:** `fgets` keeps the newline character at the end of the string. If you copy the date line directly into `r.date` without stripping the newline, your date strings will contain `\n` and string comparisons will fail unexpectedly. Strip it the same way `clean_buffer` does in `main.c`.

**Verification:** The `[ sa_load_data ]` block writes a temporary file to disk and loads it, checking that each day's date, high, low, and avg were parsed correctly. The bad filename test checks that you return 0 on failure rather than crashing.

---

## Part 4: Analysis Functions (20 points)

**File:** `src/stock_array.c`

Implement the three summary statistics functions and the three extraction functions.

### Summary Statistics (10 points)

```c
double sa_overall_high(StockArray* sa);
double sa_overall_low(StockArray* sa);
double sa_overall_avg(StockArray* sa);
```

Each walks the entire array and returns a single value:

- `sa_overall_high` - the largest `high` field across all records
- `sa_overall_low` - the smallest `low` field across all records
- `sa_overall_avg` - the mean of all `avg` fields across all records

These are straightforward loops. Initialize from `records[0]` and walk from index 1.

### Extraction Functions (10 points)

```c
double* sa_extract_highs(StockArray* sa);
double* sa_extract_lows(StockArray* sa);
double* sa_extract_avgs(StockArray* sa);
```

Each allocates a fresh `double` array of `sa->size` elements, copies the relevant field from every record into it in order, and returns the pointer.

**The caller owns the returned array and is responsible for freeing it.** This is a deliberate design choice. The extraction functions produce a plain `double[]` because that is exactly what `plot_series` expects. Mixing the concerns of storage and plotting inside the struct would make both worse.

**Common mistake:** Do not return a pointer into `sa->records` itself. The returned array must be a separate heap allocation. The test suite checks for this explicitly.

---

## Part 5: The REPL (20 points)

**File:** `src/main.c`

The provided `main.c` contains a working read-eval-print loop skeleton with two commands already implemented: `plot test`, which plots a hardcoded array of test data so you can verify `plot_series` works before loading any files, and `exit`, which cleans up and quits.

Your job is to extend the loop with the six commands below. Each one maps directly to a function you implemented in Parts 1-4. If your earlier functions are correct, none of these should require more than a few lines each.

```
Stock Plotting Program
Commands: load <filename>, plot high, plot low, plot avg, max, min, exit
> _
```

---

### Commands to Implement

#### `load <filename>` (6 points)

Loads a stock data file into the `StockArray`. The filename follows the command after a space, so `load data/aapl.txt` should open `data/aapl.txt`.

**Requirements:**

- If a file is already loaded, destroy the existing array before creating a new one. This allows the user to switch stocks without restarting the program.
- Create a new `StockArray` with `INITIAL_CAPACITY` and call `sa_load_data`.
- On success, print how many days were loaded and from which file:

```
Loaded 252 days from data/aapl.txt
```

- On failure (file not found), print an error and leave `loaded` as 0:

```
Error: could not open data/aapl.txt
```


**Hint:** The filename starts at `buffer + 5`, five characters past the beginning of the buffer, skipping past `"load "`. No extra parsing needed.

#### `plot high` (3 points)

Extracts the daily high prices and passes them to `plot_series`.

**Requirements:**

- If no file is loaded, print an error and do nothing:

```
Error: no file loaded, use load <filename>
```

- Call `sa_extract_highs`, pass the result and `sa.size` to `plot_series` with the label `"Daily High"`, then free the extracted array.


#### `plot low` (3 points)

Same as `plot high` but for daily lows. Label: `"Daily Low"`.


#### `plot avg` (3 points)

Same as `plot high` but for daily averages. Label: `"Daily Average"`.


#### `max` (2 points)

Prints the highest price seen across all loaded days.

**Requirements:**

- Guard against no file loaded with the same error message as the plot commands.
- Call `sa_overall_high` and print the result to two decimal places:

```
Overall high: 199.62
```


#### `min` (3 points)

Prints the lowest price seen across all loaded days.

**Requirements:**

- Guard against no file loaded.
- Call `sa_overall_low` and print the result to two decimal places:

```
Overall low: 124.17
```


---

### Expected Session

A correct implementation should produce a session like the following. Use this as your own acceptance test before submitting:

```
Stock Plotting Program
Commands: load <filename>, plot high, plot low, plot avg, max, min, exit
> plot avg
Error: no file loaded, use load <filename>
> load data/fake.txt
Error: could not open data/fake.txt
> load data/aapl.txt
Loaded 252 days from data/aapl.txt
> max
Overall high: 199.62
> min
Overall low: 124.17
> plot avg

  Daily Average
  257.33 |
         |                                                           *
         |                                                          *
         |                                                         *
         |                                                        *
  232.75 |                                *                      *
         |                                                ***
         |                               * *    ***   ** *     **
         |                                   * *   ***  *    **
         |                              *   *
  208.17 |                           ***
         |                                    *
         |
         |                          *
         |    *                  * *
  183.59 |* ** **               * *
         | *     ***           *
         |          *  *
         |           **    *
         |              *** ***
         +------------------------------------------------------------
         0                                                day 250
> load data/nvda.txt
Loaded 252 days from data/nvda.txt
> plot high

  Daily High
  ...
> exit
Info: Exiting...
```

Note that loading a second file after the first works cleanly, the old array is destroyed and replaced without a crash or leak.

---

## Common Mistakes

**Not guarding against `loaded == 0`.** Every command except `load` and `exit` requires data to be present. If you call `sa_extract_highs` on an uninitialized `StockArray` the program will crash or produce garbage. Check `loaded` first on every command that needs it.

**Forgetting to free the extracted array.** Each `sa_extract_*` call returns a heap allocation. Call `free` on it after `plot_series` returns or you will leak memory on every plot command.

**Not destroying the old array on a second `load`.** If you skip the `sa_destroy` call before loading a new file, the previous `records` allocation is leaked. The `loaded` flag exists precisely to guard this; only call `sa_destroy` if `loaded` is 1.

---

## Grading Rubric

| Section                                                         | Points  |
| --------------------------------------------------------------- | ------- |
| Part 1: `sa_create` and `sa_destroy` correct                    | 20      |
| Part 2: `sa_append` including resize, `sa_get`                  | 25      |
| Part 3: `sa_load_data` parses all fields correctly              | 25      |
| Part 4: Summary statistics and extraction functions             | 20      |
| Part 5: REPL commands and main                                  | 20      |
| No memory leaks: every `malloc`/`realloc` has a matching `free` | 5       |
| Code style: comments, naming, no warnings                       | 5       |
| **Total**                                                       | **120** |

**Deductions:**

- Returning a pointer into `sa->records` from an extract function instead of a fresh allocation: -5 per function
- Using a fixed-size stack array instead of a dynamic heap array for `records`: -20
- Code does not compile: maximum 40 points total

---

## Submission Guidelines

Submit a single `.zip` file named `lastname_firstname_hw_stock.zip` containing:

```
CS220-HW3-LastName/
├── bin/
├── include/
│   └── stock_array.h
├── src/
│   ├── stock_array.c
│   ├── main.c
│   └── test_stock_array.c
├── data/
│   └── *.txt
└── Makefile
```

Do not include compiled binaries or object files. The grader will compile from source. Run `make` and then `./test_stock_array` and confirm all tests print PASS before submitting.

---

## Tips and Common Mistakes

**Run the test suite before the REPL.** The test suite checks every function in isolation with known inputs. The REPL only shows you the final behavior. If something looks wrong in the plot, the bug is almost certainly in a function the test suite would have caught

**`realloc` can move your memory.** After any call to `realloc`, use the returned pointer. Never use the old one. The most common symptom of getting this wrong is data that is correct before the first resize and garbage afterwards.

**Strip the newline from date strings.** `fgets` includes the `\n` at the end of the line. If you see dates printing as `"2024-01-02\n"` or string comparisons mysteriously failing, this is why. Look at how `clean_buffer` in `main.c` handles it.

**Free extracted arrays after plotting.** The extract functions return heap-allocated arrays. The REPL in `main.c` does this for you, but if you write any additional test code that calls an extract function, free the result when you are done with it.

**`sa_destroy` is called on `load` if a file is already loaded.** The REPL allows loading a new file at any time. If you load the same file twice without destroying the first array, you will leak the first allocation. The provided `main.c` handles this for you, but only if `sa_destroy` correctly frees and zeros the struct.