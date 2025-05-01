// Test Case 1: Simple Linear Flow
// Description: A function with no branches or loops, just sequential instructions.
int linear_flow() {
    int x = 1;
    int y = 2;
    int z = x + y;
    return z;
}

// Test Case 2: Basic Conditional
// Description: A function with a simple if-else to test conditional branching.
int conditional(int x) {
    if (x > 0) {
        return 1;
    } else {
        return 0;
    }
}

// Test Case 3: Simple Loop
// Description: A function with a for loop to test backedges in the CFG.
int loop(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += i;
    }
    return sum;
}

// Test Case 4: Nested Conditionals
// Description: A function with nested if-else statements to test complex branching.
int nested_conditional(int x) {
    if (x > 0) {
        if (x > 10) {
            return 2;
        } else {
            return 1;
        }
    } else {
        return 0;
    }
}

// Test Case 5: Switch Statement
// Description: A function with a switch to test multiple branches from a single point.
int switch_case(int x) {
    switch (x) {
        case 1: return 1;
        case 2: return 2;
        case 3: return 3;
        default: return 0;
    }
}

// Test Case 6: Empty Function
// Description: A function with no instructions to test the minimal CFG case.
void empty_function() {
}

// Test Case 7: Multiple Return Points
// Description: A function with multiple returns to test multiple exit points.
int multiple_returns(int x) {
    if (x < 0) {
        return -1;
    }
    if (x == 0) {
        return 0;
    }
    return 1;
}

// Test Case 8: Loop with Conditional
// Description: A function combining a loop and conditional to test complex control flow.
int loop_with_conditional(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0) {
            sum += i;
        }
    }
    return sum;
}

// Test Case 9: While Loop with Break
// Description: A while loop with a break statement to test early loop exits.
int while_with_break(int n) {
    int i = 0;
    while (i < n) {
        if (i == 5) {
            break;
        }
        i++;
    }
    return i;
}

// Test Case 10: Unreachable Code
// Description: A function with code after a return to test unreachable blocks.
int unreachable_code() {
    return 42;
    int x = 1; // Unreachable
    return x;
}

// Test Case 11: Infinite Loop
// Description: A function with an infinite loop (no exit condition) to test CFG behavior.
void infinite_loop() {
    while (1) {
        int x = 1;
    }
}

// Test Case 12: Nested Loops
// Description: A function with nested loops to test multiple backedges.
int nested_loops(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum += i + j;
        }
    }
    return sum;
}

// Test Case 13: Function with Goto
// Description: A function using goto to test non-standard control flow.
int goto_test(int x) {
    if (x < 0) {
        goto negative;
    }
    return x;
negative:
    return -x;
}

// Test Case 14: Recursive Function
// Description: A recursive function to test call edges in the CFG.
int recursive(int n) {
    if (n <= 1) {
        return n;
    }
    return recursive(n - 1) + n;
}

// Test Case 15: Empty Loop
// Description: A loop with no body to test minimal loop structure.
int empty_loop(int n) {
    for (int i = 0; i < n; i++) {
        // Empty
    }
    return n;
}

int main() {
    // Call each function to ensure they are included in the IR
    linear_flow();
    conditional(5);
    loop(10);
    nested_conditional(15);
    switch_case(2);
    empty_function();
    multiple_returns(0);
    loop_with_conditional(8);
    while_with_break(10);
    unreachable_code();
    // infinite_loop(); // Commented out to avoid hanging
    nested_loops(3);
    goto_test(-5);
    recursive(4);
    empty_loop(5);
    return 0;
}